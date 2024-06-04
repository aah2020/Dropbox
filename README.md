# Dropbox C++ Project

This project demonstrates a simple `Dropbox` application written in C++ using CMake for building, Google Test for unit testing and cppcheck for static code analysis.The project is set up with a CI/CD pipeline using GitHub Actions to automate building and testing.

## Features
The implementation supports the following features:
- Dropbox clinet takes one directory (the source) as argument, keeps monitoring changes in that directory, and uploads any change to its server.
- Dropbox server takes one directory (the destination) as argument and receives any change from its client.
- Bonus 1: The application is optimized to identify the changes in the source directory on runtime and transfer only the newly added or removed files.
- Bonus 2: Supports depth of source directory more than 1 i.e. any changes in the subdirectory is also identified.

## Non-functional Requrements
- `CI/CD` using Github framework.
- Automated `unit` and `integration testing` using `GTest`.
- Console and file based logging support.
- Option to perform static code analysis using
    - `CPPCheck` and
    - `Clang-Tidy`.
- Option to perform `Ccache` for fast compilation.

## Scope
- Implemented for Unix platform only.
- Any changes on the server side does not trigger synchronization on the client side.
- Performance and security issues are put out of the scope of this project.

## Prerequisites
Before you begin, ensure you have met the following requirements:
- CMake.
- A modern C++ compiler (GCC).
- GTest
- CPPCheck (optional)
- Clang-Tidy (optional)
- CCache (optional)

## Setting Up the Project
To set up the HelloWorld project, follow these steps:

1. Clone the repository to your local machine:
`git clone git@github.com:aah2020/Dropbox.git`

2. Navigate into the project directory:
`cd Dropbox`

## Building the Project
To build the project using CMake, run the following commands:

1. Create a build directory and navigate into it:
`mkdir build && cd build`

2. Configure the project with CMake:
`cmake ..`

3. Build the project:
`cmake --build .`

The executable will be created in the `build` directory.

## Running the Project
* start server: `./src/server/DropboxServer` <destination_directory>
    - note that the default server runtime is 60 seconds. Provide necessary params for non-default values.
* start client: `./src/client/DropboxClient` <source_directory>
    - - note that the default client runtime is 60 seconds. Provide necessary params for non-default values.

* Next add or remove any files or directory in the source directory, corresponding files will be updated in the destination_directory.


## Running the Tests
* Run the following command in build directory: `ctest` or `ctest -V`.