// #include <fstream>
// #include <iostream>
// #include <string>
// #include <vector>

// int main() {
//     std::vector<std::string> cities = {"Delhi", "Noida", "Ghaziabad", "Faridabad", "Gurgaon", "Greater Noida", "Meerut", "Panipat", "Aligarh", "Agra", "Chandigarh", "Dehradun", "Jaipur", "Lucknow", "Patna"};

//     std::ofstream outfile("cities.bin", std::ios::out | std::ios::binary);

//     if (outfile) {
//         int size = cities.size();
//         outfile.write((char*)&size, sizeof(int));
//         for (const auto& city : cities) {
//             int len = city.length();
//             outfile.write((char*)&len, sizeof(int));
//             outfile.write(city.c_str(), len);
//         }
//         outfile.close();
//         std::cout << "File written successfully!" << std::endl;
//     }
//     else {
//         std::cout << "Error opening file!" << std::endl;
//     }

//     return 0;
// }

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::ifstream infile("cities.bin", std::ios::in | std::ios::binary);

    if (infile) {
        int size;
        infile.read((char*)&size, sizeof(int));

        std::vector<std::string> cities(size);
        for (int i = 0; i < size; i++) {
            int len;
            infile.read((char*)&len, sizeof(int));

            std::vector<char> buffer(len);
            infile.read(buffer.data(), len);

            cities[i] = std::string(buffer.begin(), buffer.end());
        }
        infile.close();

        // Print the contents of the vector
        for (const auto& city : cities) {
            std::cout << city << std::endl;
        }
    }
    else {
        std::cout << "Error opening file!" << std::endl;
    }

    return 0;
}

