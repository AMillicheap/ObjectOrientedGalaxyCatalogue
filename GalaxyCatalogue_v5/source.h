#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <cmath>

// Constant definitions  
    const int n{3};  //Digit order of object ID
    const double min_ra{0.0};
    const double max_ra{24.0};
    const double min_dec{-90.0};
    const double max_dec{90.0};
    const double min_m{0.05};
    const double max_m{3200};
    const double min_z{0.0};
    const double max_z{1.0};
    const double min_mag{-10.0}; 
    const double max_mag{15.0};
    const double min_temp{3000};
    const double max_temp{25000};
    const double min_d{5};
    const double max_d{500};

namespace observable {

// Abstract base class for astronomical objects
template<typename T>
class astronomical_object {

protected:
    std::string name;
    std::string obj_type;
    T right_ascension;
    T declination;
public:
    astronomical_object() {};
    astronomical_object(std::string id, std::string t, T ra, T dec) : 
        name{id}, obj_type{t}, right_ascension{ra}, declination{dec} {};
    virtual ~astronomical_object() {};
    virtual std::string get_class() const = 0;
    std::string get_name() const;
    std::string get_obj_type() const;
    T get_right_ascension() const;
    T get_declination() const;
};


//----------------------- Derived classes for luminous / non-luminous objects -------------------------------------------------
// Derived class for luminous sources
template<typename T>
class luminous_object : public astronomical_object<T> {

protected:
    T magnitude;
    T redshift;
public:
    luminous_object(){}
    luminous_object(std::string id, std::string t, T ra, T dec, T z, T mag) :
        astronomical_object<T>(id, t, ra, dec), redshift{z}, magnitude{mag}{}
    virtual ~luminous_object(){}
    T get_magnitude() const;
    T get_redshift() const;
};

// Derived class for non-luminous sources
template<typename T>
class non_luminous_object : public astronomical_object<T> {

protected:
    T mass;   
public:
    non_luminous_object(){};
    non_luminous_object(std::string id, std::string t, T ra, T dec, T m) : 
        astronomical_object<T>(id, t, ra, dec), mass(m) {};
    virtual ~non_luminous_object() {};
    T get_mass() const;
};

//----------------------- Derived classes for stars / planets / galaxies / binary stars -------------------------------------------------
// Derived class for stars
// obj_type : Spectral Class (O, B, A, F, G, K, M)

// Derived class for stars
// obj_type : Spectral Type [O, B, A, F, G, K, M]
template<typename T>
class star : public luminous_object<T> {

protected:
    T temperature;
public:
    star(){};
    star(std::string id, std::string t, T ra, T dec, T z, T mag, T temp) : 
        luminous_object<T>(id, t, ra, dec, z, mag), temperature{temp}{};
    ~star(){};
    std::string get_class() const { return "Star"; };
    T get_temperature() const;
    bool operator==(const observable::star<T> &other) const;
};


// Derived class for planets
// obj_type : Planet Classifier (Terrestrial[T], Gas Giant[G], Ice Giant[I], Dwarf[D], Exoplanet[E])
template<typename T>
class planet : public non_luminous_object<T> {

public:
    planet(){};
    planet(std::string id, std::string t, T ra, T dec, T m) : 
        non_luminous_object<T>(id, t, ra, dec, m){};
    ~planet(){};
    std::string get_class() const { return "Planet"; };
    bool operator==(const observable::planet<T> &other) const;
};

// Derived class for galaxies 
// obj_type : Hubble Type (E0, S0, S, SB, Irr)
template<typename T>
class galaxy : public luminous_object<T> {

public:
    galaxy(){}
    galaxy(std::string id, std::string t, T ra, T dec, T z, T mag) : 
        luminous_object<T>(id, t, ra, dec, z, mag){}
    ~galaxy(){}

    std::string get_class() const { return "Galaxy"; };
    bool operator==(const observable::galaxy<T> &other) const;
};

// Derived class for binary stars
// obj_type : Binary Star Classifier (Visual Binary[VB], Spectroscopic Binary[SB], Eclipsing Binary[EB])
template<typename T>
class binary_star : public star<T> {

private:
    T separation;
    std::string star1_type;
    std::string star2_type;
public:
    binary_star(){}
    binary_star(std::string id, std::string t, T ra, T dec, T z, T mag, T temp, T d, std::string star1, std::string star2) : 
        star<T>(id, t, ra, dec, z, mag, temp), separation{d}, star1_type{star1}, star2_type{star2}{}
    ~binary_star(){}
    std::string get_class() const { return "Binary"; };
    T get_separation() const;
    std::string get_star1_type() const;
    std::string get_star2_type() const;
    bool operator==(const observable::binary_star<T> &other) const;

};
};