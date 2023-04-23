#include "source.cpp"

// Function to check if a double is within a certain range
bool is_in_range(double value, double min, double max) 
{ 
    if (value < min || value > max){ return false; } else { return true; }
}

// Function to generate a unique object ID number
std::string generate_name()
{
    static int id_count = 0;
    std::stringstream ss;
    ss << std::setw(n) << std::setfill('0') << (++id_count % static_cast<int>(pow(10, n)));
    return ss.str();    
}

// Function to read data from file
template<typename T>
void read_file(std::vector<observable::astronomical_object<T>*> &data, const std::string &filename)
{ 
    std::ifstream infile(filename);
int counter;
    try{
    if (infile.is_open()){
        std::string id, obj_class, t, star1, star2, line;
        T ra, dec, z, mag, m, temp, d;

        while (std::getline(infile, line, '\n')) 
        {
            if(!line.empty()){
                counter++;
                std::istringstream row(line);

                    if (!row.good()) { 
                        throw std::invalid_argument("Invalid argument.");
                    }
                    row >> obj_class >> t >> ra >> dec;
                    id = generate_name();
                    
                    if (!is_in_range(ra, min_ra, max_ra)){
                        throw std::out_of_range("Invalid right ascension.");
                    }
                    if (!is_in_range(dec, min_dec, max_dec)){
                        throw std::out_of_range("Invalid declination.");
                    }

                    if (obj_class == "Star"){
                        row >> z >> mag >> temp;
                        if (!is_in_range(z, min_z, max_z)){
                            throw std::out_of_range("Invalid redshift.");
                        } else if (!is_in_range(mag, min_mag, max_mag)) {
                            throw std::out_of_range("Invalid magnitude.");
                        } else if (!is_in_range(temp, min_temp, max_temp)){
                            throw std::out_of_range("Invalid temperature.");
                        } else if (t != "O" && t != "B" && t != "A" && t != "F" && t != "G" && t != "K" && t != "M"){
                            throw std::out_of_range("Please enter a spectral type from [O, B, A, F, G, K, M].");
                        } else {
                            observable::star<T>* new_star = new observable::star<T>(id, t, ra, dec, z, mag, temp);
                            if (unique(data, new_star)){
                                data.push_back(new_star);
                            } else {
                                std::cout << "Star is already stored..." << std::endl;
                            }
                        }
                    } else if (obj_class == "Planet") {
                        row >> m;
                        if (!is_in_range(m, min_m, max_m)){
                            throw std::out_of_range("Invalid planetary mass.");
                        } else if (t != "T" && t != "G" && t != "I" && t != "D" && t != "E"){
                            throw std::out_of_range("Please enter a planet classifier from Terrestrial[T], Gas Giant[G], Ice Giant[I], Dwarf[D] or Exoplanet[E].");
                        } else {
                            observable::planet<T>* new_planet = new observable::planet<T>(id, t, ra, dec, m);
                            if (unique(data, new_planet)){
                                data.push_back(new_planet);
                            } else {
                                std::cout << "Planet is already stored..." << std::endl;
                            }
                        }
                    } else if (obj_class == "Galaxy") {
                        row >> z >> mag;
                        if (!is_in_range(z, min_z, max_z)){
                            throw std::out_of_range("Invalid redshift.");
                        } else if (!is_in_range(mag, min_mag, max_mag)){
                            throw std::out_of_range("Invalid magnitude.");
                        } else if( t != "E0" && t != "S0" && t != "S" && t != "SB" && t != "Irr" ){
                            throw std::out_of_range("Please enter a Hubble type from [E0, S0, S, SB, Irr].");
                        } else {
                            observable::galaxy<T>* new_galaxy = new observable::galaxy<T>(id, t, ra, dec, z, mag);
                            if (unique(data, new_galaxy)){
                                data.push_back(new_galaxy);
                            } else {
                                std::cout << "Galaxy is already stored..." << std::endl;
                            }
                        }
                    } else if (obj_class == "Binary") {
                        row >> z >> mag >> d >> star1 >> star2;
                        if (!is_in_range(z, min_z, max_z)){
                            throw std::out_of_range("Invalid redshift.");
                        } else if (!is_in_range(mag, min_mag, max_mag)){
                            throw std::out_of_range("Invalid magnitude.");
                        } else if (((t != "VB" && t != "SB" && t != "EB"))){
                            throw std::out_of_range("Please enter a Binary star classification from [VB, SB, EB].");
                        } else if ((!is_in_range(temp, min_temp, max_temp))){
                            throw std::out_of_range("Invalid temperature.");
                        } else if ((!is_in_range(d, min_d, max_d))){
                            throw std::out_of_range("Invalid separation.");
                        } else if ((star1 != "O" && star1 != "B" && star1 != "A" && star1 != "F" && star1 != "G" && star1 != "K" && star1 != "M")){
                                throw std::out_of_range("Please enter a spectral type for star 1 from [O, B, A, F, G, K, M].");
                        } else if ((star2 != "O" && star2 != "B" && star2 != "A" && star2 != "F" && star2 != "G" && star2 != "K" && star2 != "M")){
                                throw std::out_of_range("Please enter a spectral type for star 2 from [O, B, A, F, G, K, M].");
                        } else {
                            observable::star<T>* new_binary = new observable::binary_star<T>(id, t, ra, dec, z, mag, temp, d, star1, star2);
                            if (unique(data, new_binary)){
                                data.push_back(new_binary);
                            } else {
                                std::cout << "Binary star is already stored..." << std::endl;
                            }
                        }
                    }
            }
        }
        infile.close();
    } else { 
        std::cout << "Error opening '" << filename << std::endl;
        throw std::invalid_argument("Read Error: ");
    }
    }
                catch(const std::out_of_range& msg) {
                    std::cerr << "Invalid value: " << msg.what();
                } catch(const std::invalid_argument) {
                    std::cerr << "Error reading data from row " << counter;
                }
};

// Function to read data from user input
template<typename T>
void read_input(std::vector<observable::astronomical_object<T>*> &data) 
{
    bool quit{false};

    while (quit == false){
        std::string input;
        std::cout << "Enter source type (Star [s], Planet [p], Galaxy [g], Binary [b]) or 'q' to quit: ";
        std::cin >> input;
        if (input == "q") {
            std::cout<< "Quitting manual input..." << std::endl;
            quit = true;
            ;
        } else if (input == "s" || input == "p" || input == "g" || input == "b"){
            
            std::string id, obj_class, t, star1, star2;
            T ra, dec, z, mag, m, temp, d;
            
            id = generate_name();
            std::cout << "Enter right ascension [hours]: "; std::cin >> ra;
            while (!is_in_range(ra, min_ra, max_ra)) {
                std::cout << "Invalid value. Please enter a right ascension in the range ["<<min_ra<<", "<<max_ra<<"]h." << std::endl;
                std::cin.clear();
                std::cin.ignore();
                std::cin >> ra;
            };
            std::cout << "Enter declination [degrees]: "; std::cin >> dec;
            while (!is_in_range(dec, min_dec, max_dec)) {
                std::cout << "Invalid value. Please enter a declination in the range ["<<min_dec<<", "<<max_dec<<"] degrees." << std::endl;
                std::cin.clear();
                std::cin.ignore();
                std::cin >> dec;
            };
            if (input == "s" || input == "g" || input == "b") {
                std::cout << "Enter redshift: "; std::cin >> z;
                while (!is_in_range(z, min_z, max_z)) {
                    std::cout << "Invalid value. Please enter a redshift in the range ["<<min_z<<", "<<max_z<<"]." << std::endl;
                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> z;
                };
                std::cout << "Enter magnitude: "; std::cin >> mag;
                while (!is_in_range(mag, min_mag, max_mag)) {
                    std::cout << "Invalid value. Please enter a magnitude in the range ["<<min_mag<<", "<<max_mag<<"]." << std::endl;
                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> mag;
                };
                if (input == "s") {
                    std::cout << "Enter spectral type (O, B, A, F, G, K, M): "; std::cin >> t;
                    while (t != "O" && t != "B" && t != "A" && t != "F" && t != "G" && t != "K" && t != "M") {
                        std::cout << "Invalid spectral type. Please enter a valid spectral type." << std::endl;
                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> t;
                    };
                    std::cout << "Enter temperature [K]: "; std::cin >> temp;
                    while (!is_in_range(temp, min_temp, max_temp)) {
                        std::cout << "Invalid value. Please enter a temperature in the range ["<<min_temp<<", "<<max_temp<<"]K." << std::endl;
                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> temp;
                    };
                    observable::star<T>* new_star = new observable::star<T>(id, t, ra, dec, z, mag, temp);
                    if (unique(data, new_star)){
                        data.push_back(new_star);
                    } else {
                        std::cout << "Star is already stored..." << std::endl;
                    }
                } else if (input == "g") {
                    std::cout << "Enter Hubble type (E0, S0, S, SB, Irr): "; std::cin >> t;
                    while (t != "E0" && t != "S0" && t != "S" && t != "SB" && t != "Irr") {
                        std::cout << "Invalid Hubble classification. Please enter a valid planet classification." << std::endl;
                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> t;
                        };
                    observable::galaxy<T>* new_galaxy = new observable::galaxy<T>(id, t, ra, dec, z, mag);
                    if (unique(data, new_galaxy)){
                        data.push_back(new_galaxy);
                    } else {
                        std::cout << "Galaxy is already stored..." << std::endl;
                    }
                } else {
                    std::cout << "Enter Binary Star classifier (Visual Binary[VB], Spectroscopic Binary[SB], Eclipsing Binary[EB]): ";
                    std::cin >> t;
                    while ((t != "VB" && t != "SB" && t != "EB")) {
                        std::cout << "Invalid Binary classification. Please enter a valid planet classification." << std::endl;
                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> t;
                        };
                    std::cout << "Enter the temperature [K]: "; std::cin >> temp;
                    while (!is_in_range(temp, min_temp, max_temp)) {
                        std::cout << "Invalid value. Please enter a temperature in the range ["<<min_temp<<", "<<max_temp<<"]AU." << std::endl;
                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> temp;
                        };
                    std::cout << "Enter the separation between the stars [AU]: "; std::cin >> d;
                    while (!is_in_range(d, min_d, max_d)) {
                        std::cout << "Invalid value. Please enter a separation distance in the range ["<<min_d<<", "<<max_d<<"]AU." << std::endl;
                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> d;
                        };
                    std::cout << "Enter the spectral type of the first star: "; std::cin >> star1;
                    while (star1 != "O" && star1 != "B" && star1 != "A" && star1 != "F" && star1 != "G" && star1 != "K" && star1 != "M") {
                        std::cout << "Invalid spectral type. Please enter a valid spectral type." << std::endl;
                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> star1;
                        };
                    std::cout << "Enter the spectral type of the second star: "; std::cin >> star2;
                    while (star2 != "O" && star2 != "B" && star2 != "A" && star2 != "F" && star2 != "G" && star2 != "K" && star2 != "M") {
                        std::cout << "Invalid spectral type. Please enter a valid spectral type." << std::endl;
                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> star2;
                        };
                    observable::binary_star<T>* new_binary = new observable::binary_star<T>(id, t, ra, dec, z, mag, temp, d, star1, star2);
                        if (unique(data, new_binary)){
                            data.push_back(new_binary);
                        } else {
                        std::cout << "Binary star is already stored..." << std::endl;
                    }
                };
                } else if (input == "p") {
                    std::cout << "Enter Planet classifier (Terrestrial[T], Gas Giant[G], Ice Giant[I], Dwarf[D], Exoplanet[E]): ";
                    std::cin >> t;
                    while (t != "T" && t != "G" && t != "I" && t != "D" && t != "E") {
                        std::cout << "Invalid planet classification. Please enter a valid planet classification." << std::endl;
                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> t;
                        };
                    std::cout << "Enter the planet mass: ";
                    std::cin >> m;
                    while (!is_in_range(m, min_m, max_m)) {
                        std::cout << "Invalid value. Please enter a planetary mass in the range ["<<min_m<<", "<<max_m<<"] earth masses." << std::endl;
                        std::cin.clear();
                        std::cin.ignore();
                        std::cin >> m;
                        };
                    observable::planet<T>* new_planet = new observable::planet<T>(id, t, ra, dec, m);
                        if (unique(data, new_planet)){
                            data.push_back(new_planet);
                        } else {
                        std::cout << "Planet is already stored..." << std::endl;
                    }
                };
        } else {

            std::cout << "Error: Invalid source type." << std::endl;
            quit == true;
        };
    };
};
// Function to write data to file
template<typename T, class Y>
void write(const std::vector<Y*> &data, const std::string &filename) 
{
   std::ofstream file(filename);
    if (file.is_open()) {
        file << std::left << std::setw(10) << "Class" << std::setw(5) << "ID"  << std::setw(5) << "RA" 
             << std::setw(10) << "Dec" << std::setw(10) << "z" << std::setw(10) << "M" << std::setw(10) 
             << "SClass" << std::setw(10) << "Temp." << std::setw(10) << "HClass" << std::setw(10) 
             << "PlClass" << std::setw(10) << "BClass" << std::setw(5) << "d" << std::setw(5) << "BS1" 
             << std::setw(5) << "BS2" << std::endl;
        file << std::string(150, '-') << std::endl;

        for (auto &obj : data) 
    {
        if (auto binary_star_ptr = dynamic_cast<observable::binary_star<double>*>(obj)) 
    {
        file << *binary_star_ptr;
    } 
    else if (auto galaxy_ptr = dynamic_cast<observable::galaxy<double>*>(obj)) 
    {
        file << *galaxy_ptr;
    } 
    else if (auto planet_ptr = dynamic_cast<observable::planet<double>*>(obj)) 
    {
        file << *planet_ptr;
    } else if (auto star_ptr = dynamic_cast<observable::star<double>*>(obj)) 
    {
        file << *star_ptr;
    } else {
        file << "Error opening file " << filename << std::endl;
    };}
}
}
// Function to print data as a table in the terminal
template<typename T, class Y>
void print(const std::vector<Y*> &data) 
{
    std::cout << std::left << std::setw(10) << "Class" << std::setw(5) << "ID"  << std::setw(5) << "RA" 
              << std::setw(10) << "Dec" << std::setw(10) << "z" << std::setw(10) << "M" << std::setw(10) 
              << "SClass" << std::setw(10) << "Temp." << std::setw(10) << "HClass" << std::setw(10) 
              << "PlClass" << std::setw(10) << "BClass" << std::setw(5) << "d" << std::setw(5) << "BS1" 
              << std::setw(5) << "BS2" << std::endl;
    std::cout << std::string(150, '-') << std::endl;

    for (auto &obj : data) 
    {
        if (auto binary_star_ptr = dynamic_cast<observable::binary_star<double>*>(obj)) 
    {
        std::cout << *binary_star_ptr;
    } 
    else if (auto galaxy_ptr = dynamic_cast<observable::galaxy<double>*>(obj)) 
    {
        std::cout << *galaxy_ptr;
    } 
    else if (auto planet_ptr = dynamic_cast<observable::planet<double>*>(obj)) 
    {
        std::cout << *planet_ptr;
    } else if (auto star_ptr = dynamic_cast<observable::star<double>*>(obj)) 
    {
        std::cout << *star_ptr;
    };
};
}
