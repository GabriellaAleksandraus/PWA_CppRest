# Server

We need a server so clients have a way to access all the information that we would like to share with them. This is both the PWA data, HTML, JavaScript files and the data from the sensors. It has also an endpoint to update the moisture value. An endpoint is a route that the server listens ex: localhost:5000/get_moisture. The server will listen to the port 5000. We can send a get request to the server to get the moisture value. 

We need a server because we want a single point of access for all client needs. And the client is the person that has the PWA on the phone. The server will be the one that will handle the requests from the client and send the responses back. The server will also handle the data from the sensors and send it to the client.


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

Where target is your built executable (cpp_server)

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
curl http://localhost:5000/set_moisture/50
```

We can get the value by sending a get request to /get_moisture.

```bash
curl http://localhost:5000/get_moisture
```

send to cloud

```bash 
scp index.html manifest.json serviceworker.js build/cpp_server USER@IP_ADDRES:/PATH
```

Forward port from Windows to WSL
```ps
netsh interface portproxy add v4tov4 listenport=5000 listenaddress=0.0.0.0 connectport=5000 connectaddress=(output of: wsl hostname -I)
```

In cloud digital ocean
- Droplets
- PWA
- Console
- Run the program in build as usual

## Frontend

We can create a frontend to interact with the server. It's a simple html page that shows the current moisture value. We use JavaScript to make a get request to the server to get the moisture value and update the page. We put on click event on a button and when we receive the response from the server we use document.getElementById to find which HTML element to update the value. However there is a inconvenience because we need to know the IP address of the server and this is dynamic because it's based on what network the local server is running on. Since we want people to get access to HTML file we need to create a route that is /index.html and serve the file.

## IP address

To get the right IP configuration address. The computer/phone has to run on the same network. Get the Wi-Fi address for the phone and get the vEthernet for the computer.

```bash
ipconfig
```

