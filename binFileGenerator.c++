// #include <iostream>
// #include <fstream>
// #include <vector>

// int main()
// {
//     // Step 1: Declare a vector of vectors.
//     std::vector<std::vector<int>> matrix = {{0,20,24,28,30,50,72,91,140,233,245,248,268,528,999},
// 											{20,0,13,32,15,45,81,102,150,244,256,259,279,549,980},
// 											{24,13,0,29,12,41,77,98,146,240,252,255,275,545,976},
// 											{28,32,29,0,32,61,86,107,156,250,262,265,285,555,986},
// 											{30,15,12,32,0,30,66,87,135,229,241,244,264,534,965},
// 											{50,45,41,61,30,0,38,59,108,202,214,217,237,507,938},
// 											{72,81,77,86,66,38,0,21,70,164,176,179,199,469,900},
// 											{91,102,98,107,87,59,21,0,49,143,155,158,178,448,879},
// 											{140,150,146,156,135,108,70,49,0,94,106,109,129,399,830},
// 											{233,244,240,250,229,202,164,143,94,0,12,15,35,305,736},
// 											{245,256,252,262,241,214,176,155,106,12,0,3,23,293,724},
// 											{248,259,255,265,244,217,179,158,109,15,3,0,20,290,721},
// 											{268,279,275,285,264,237,199,178,129,35,23,20,0,270,701},
// 											{528,549,545,555,534,507,469,448,399,305,293,290,270,0,431},
// 											{999,980,976,986,965,938,900,879,830,736,724,721,701,431,0}};

//     // Step 2: Open the binary file in write mode using std::ofstream.
//     std::ofstream output_file("data.bin", std::ios::binary);

//     // Step 3: Use a nested loop to write each integer in the matrix to the file.
//     for (const auto& row : matrix) {
//         for (const auto& val : row) {
//             output_file.write(reinterpret_cast<const char*>(&val), sizeof(val));
//         }
//     }

//     // Step 4: Close the file.
//     output_file.close();

//     // Step 5: Open the binary file in read mode using std::ifstream.
//     std::ifstream input_file("data.bin", std::ios::binary);

//     // Step 6: Calculate the number of rows and columns in the matrix.
//     const int rows = matrix.size();
//     const int cols = matrix[0].size();

//     // Step 7: Create a new matrix with the same dimensions as the original matrix.
//     std::vector<std::vector<int>> new_matrix(rows, std::vector<int>(cols));

//     // Step 8: Use a nested loop to read each integer from the file into the new matrix.
//     for (int i = 0; i < rows; ++i) {
//         for (int j = 0; j < cols; ++j) {
//             input_file.read(reinterpret_cast<char*>(&new_matrix[i][j]), sizeof(new_matrix[i][j]));
//         }
//     }

//     // Step 9: Close the file.
//     input_file.close();

//     // Step 10: Print the contents of the new matrix to verify that it was read correctly.
//     for (const auto& row : new_matrix) {
//         for (const auto& val : row) {
//             std::cout << val << ' ';
//         }
//         std::cout << '\n';
//     }

//     return 0;
// }

#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream file("data.bin", ios::binary);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }

    // Get the size of the file
    file.seekg(0, ios::end);
    int file_size = file.tellg();
    file.seekg(0, ios::beg);

    // Create a vector to store the file contents
    vector<unsigned char> file_data(file_size);

    // Read the file contents into the vector
    file.read((char*)file_data.data(), file_size);

    // Close the file
    file.close();

    // Create a vector of vectors to store the data
    vector<vector<int>> data;

    // Determine the row size based on the size of the integers
    int int_size = sizeof(int);
    int row_size = file_size / int_size;
    row_size = sqrt(row_size);

    // Convert the file data into a vector of vectors
    for (int i = 0; i < file_size; i += row_size * int_size) {
        vector<int> row(row_size);
        for (int j = 0; j < row_size; j++) {
            int value = 0;
            for (int k = 0; k < int_size; k++) {
                value |= file_data[i + j * int_size + k] << (8 * k);
            }
            row[j] = value;
        }
        data.push_back(row);
    }

    // Print the data
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            cout << data[i][j] << " ";
        }
        cout<<" \n" <<endl;
    }

    return 0;
}

