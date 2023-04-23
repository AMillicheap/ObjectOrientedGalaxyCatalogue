#include "source.h"
  
template<typename T> std::string observable::astronomical_object<T>::get_name() const { return name; };
template<typename T> std::string observable::astronomical_object<T>::get_obj_type() const { return obj_type; };
template<typename T> T observable::astronomical_object<T>::get_right_ascension() const { return right_ascension; };
template<typename T> T observable::astronomical_object<T>::get_declination() const { return declination; };
template<typename T> T observable::luminous_object<T>::get_magnitude() const { return magnitude; };
template<typename T> T observable::luminous_object<T>::get_redshift() const { return redshift; };
template<typename T> T observable::non_luminous_object<T>::get_mass() const { return mass; };
template<typename T> T observable::star<T>::get_temperature() const { return temperature; };
template<typename T> T observable::binary_star<T>::get_separation() const { return separation; };
template<typename T> std::string observable::binary_star<T>::get_star1_type() const { return star1_type; };
template<typename T> std::string observable::binary_star<T>::get_star2_type() const { return star2_type; };

template<typename T>
bool observable::star<T>::operator== (const observable::star<T> &other) const
{
    if (this->get_class() != other.get_class() || this->get_obj_type() != other.get_obj_type() 
        || this->get_right_ascension() != other.get_right_ascension() || this->get_declination() != other.get_declination() 
        || this->get_magnitude() != other.get_magnitude() || this->get_redshift() != other.get_redshift()
        || this->get_temperature() != other.get_temperature()){
                return false;
            } else {
                return true;
            }
}

template<typename T>
bool observable::galaxy<T>::operator== (const observable::galaxy<T> &other) const
{
    if (this->get_class() != other.get_class() || this->get_obj_type() != other.get_obj_type() 
        || this->get_right_ascension() != other.get_right_ascension() || this->get_declination() != other.get_declination() 
        || this->get_magnitude() != other.get_magnitude() || this->get_redshift() != other.get_redshift()){
                return false;
            } else {
                return true;
            }
}

template<typename T>
bool observable::planet<T>::operator== (const observable::planet<T> &other) const
{
    if (this->get_class() != other.get_class() || this->get_obj_type() != other.get_obj_type() 
        || this->get_right_ascension() != other.get_right_ascension() || this->get_declination() != other.get_declination() 
        || this->get_mass() != other.get_mass()){
                return false;
            } else {
                return true;
            }
}

template<typename T>
bool observable::binary_star<T>::operator== (const observable::binary_star<T> &other) const
{
    if (this->get_class() != other.get_class() || this->get_obj_type() != other.get_obj_type() 
        || this->get_right_ascension() != other.get_right_ascension() || this->get_declination() != other.get_declination() 
        || this->get_separation() != other.get_separation() || this->get_star1_type() != other.get_star1_type() 
        || this->get_star2_type() != other.get_star2_type()){
                return false;
            } else {
                return true;
            }
}
//Function to check if an added object is unique
template <typename T, class Y>
bool unique(std::vector<observable::astronomical_object<T>*> objects, Y *new_object) 
{
    for (auto obj : objects){
        if(obj->get_class() == new_object->get_class()){
            auto object = dynamic_cast<Y*>(obj);
            if (*object == *new_object){
                return false;
        }
        }
    }
        return true;        
}

template <typename T> std::ostream& operator<<(std::ostream &os, const observable::binary_star<T> data) 
{
    os << std::left << std::setw(10) << data.get_class() << std::setw(5) << data.get_name() << std::setw(5) 
                << data.get_right_ascension() << std::setw(10) << data.get_declination() << std::setw(10)
                << data.get_redshift() << std::setw(10) << data.get_magnitude() << std::setw(10)
                << "N/A" << std::setw(10) << "N/A" << std::setw(10) << "N/A" << std::setw(10) << "N/A" 
                << std::setw(10) << data.get_obj_type() << std::setw(5) 
                << data.get_separation() << std::setw(5) 
                << data.get_star1_type() << std::setw(5) 
                << data.get_star2_type() << std::endl;
                return os;
}
template<typename T> std::ostream& operator<<(std::ostream &os, const observable::star<T> data)
{
    os << std::left << std::setw(10) << data.get_class() << std::setw(5) << data.get_name() << std::setw(5) 
              << data.get_right_ascension() << std::setw(10) << data.get_declination() << std::setw(10)
              << data.get_redshift() << std::setw(10) << data.get_magnitude() 
              << std::setw(10) << data.get_obj_type() << std::setw(10) << data.get_temperature() 
              << std::setw(10) << "N/A" << std::setw(10) << "N/A"<< std::setw(10) << "N/A" << std::setw(5) 
              << "N/A" << std::setw(5) << "N/A" << std::setw(5) << "N/A" << std::endl;
              return os;
};
template<typename T> std::ostream& operator<<(std::ostream &os, const observable::planet<T> data)
{
    os << std::left << std::setw(10) << data.get_class() << std::setw(5) << data.get_name() << std::setw(5) 
              << data.get_right_ascension() << std::setw(10) << data.get_declination() << std::setw(10) 
              << "N/A" << std::setw(10) << "N/A" << std::setw(10) << "N/A" << std::setw(10) << "N/A" << std::setw(10) << "N/A" 
              << std::setw(10) << data.get_obj_type() << std::setw(10) << "N/A" << std::setw(5) 
              << "N/A" << std::setw(5) << "N/A" << std::setw(5) << "N/A" << std::endl;
              return os;
};
template <typename T> std::ostream& operator<<(std::ostream &os, const observable::galaxy<T> data)
{
    os << std::left << std::setw(10) << data.get_class() << std::setw(5) << data.get_name() << std::setw(5) 
              << data.get_right_ascension() << std::setw(10) << data.get_declination() << std::setw(10)
              << data.get_redshift() << std::setw(10) << data.get_magnitude() 
              << std::setw(10) << "N/A" << std::setw(10) << "N/A" << std::setw(10) << data.get_obj_type() << std::setw(10) 
              << "N/A" << std::setw(10) << "N/A"<< std::setw(5) << "N/A" << std::setw(5) << "N/A" 
              << std::setw(5) << "N/A" << std::endl;
              return os;
}

