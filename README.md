# PWA_CppRest

We want to create a C++ restApi but we don't want to do everything by ourselves. We want to use third part libraries like crow to make http requests and responses easier. Since crow uses Cmake it will be easy to integrate it to our project if we also use Cmake. Since it is an established tool in C++ eco system we will use it to build our project.


## Cmake

To build Cmake project we need to create a CMakeLists.txt file. This file will contain the instructions to build the project.

Create a build directory in the root of the project. This is where we will build the project.

```bash
mkdir build
cd build
```

First we need to configure Cmake for this project which means to find a compiler and set up the project. We can do this by running the following command:

```bash
cmake ..
```

This will create the necessary files to build the project. Now we can build the project by running the following command:

```bash
cmake --build .
```

To run the program we can run the following command:

```bash
./<target>
```

Where target is your built executable.

## Crow
To include crow in our project we make use of fetchContent in Cmake. This will download the crow library and include it in our project.

```cmake
include(FetchContent)


FetchContent_Declare(
    crow
    GIT_REPOSITORY <url>
    GIT_TAG <version>
)

FetchContent_MakeAvailable(crow)
```

This will download the crow library and include it in our project. We can now use the crow library in our project.

Crow is dependent on Asio so we had to make the same steps to include Asio in our project.

## Server

To create a server we need to create a crow::SimpleApp object and define the routes we want to handle.

The server keeps track of a moisture value. We can update the value by sending a get request to /set_moisture/\<value\>.

```bash
curl http://localhost:3000/set_moisture/50
```

We can get the value by sending a get request to /get_moisture.

```bash
curl http://localhost:3000/get_moisture
```

