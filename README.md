# KNN Implementation in C++

## Project Overview
This project is an implementation of the K-Nearest Neighbors (KNN) algorithm in C++, designed for educational purposes and to demonstrate the application of the algorithm in a GPU-accelerated environment. The implementation leverages CUDA to speed up the computation of KNN, making it suitable for larger datasets and exploring GPU computing.

## Features
- Basic KNN algorithm implementation in C++.
- Customizable parameters for KNN, such as the number of neighbors (`k`) and distance metrics.

## Requirements
- **C++ Compiler**: Tested with Visual Studio 2022, v143.
- **CMake**: Used for building the project, version 3.27.6.
- **Git**: To clone the repository.

## Setup and Installation
1. **Clone the Repository**
   ```sh
   git clone git@github.com:ASDIC4/knn_cpp.git
   cd knn_cpp
   ```

2. **Build the Project**
   Make sure you have CMake installed and properly configured.
   ```sh
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

3. **Run the Application**
   After building the project, run the executable:
   ```sh
   ./knn_cpp
   ```



## File Structure
- **main.cpp**: Contains the main function to run the KNN algorithm.
- **CMakeLists.txt**: Configuration file for building the project with CMake.

## Notes
- Only the CPU implementation using C++.

## Contact
For questions or suggestions, please contact me at [realzjca@gmail.com](mailto:realzjca@gmail.com).
