#include "crow.h"
#include <fstream>
#include <string>


int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){ 
        // This is a lambda function that will be called when the user visits the root URL

        return "Server is running";
    });

    //Ports

    CROW_ROUTE(app,"/index.html") ([](){
        std::ifstream in("../index.html"); //This is to read the file index.html
        std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()); //This is to convert the file to a string so we can understand it
        return crow::response(content); //we need to respond to the client with HTTP protocol and crow::response sets up all the necessary headers
    });

    CROW_ROUTE(app, "/manifest.json") ([](){
        std::ifstream in("../manifest.json"); //This is to read the file manifest.json
        std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()); //This is to convert the file to a string
        return crow::response(content);
    });

    CROW_ROUTE(app, "/serviceworker.js") ([](){
        std::ifstream in("../serviceworker.js"); //This is to read the file service-worker.js
        std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()); //This is to convert the file to a string
        crow::response response(content);
        response.add_header("Content-Type", "application/javascript");
        return response;
    });

    int moisture{};

    CROW_ROUTE(app, "/get_moisture")([&moisture](){ 
        // This is a lambda function that will be called when the user visits the root URL
        crow::json::wvalue data; //json is format that works well with web applications
        data["moisture"] = moisture;
        crow::response response(data);
        response.add_header("Access-Control-Allow-Origin", "*"); //This is to allow the web page to access the data
        return response;
    });

    CROW_ROUTE(app,"/set_moisture/<int>") ([&moisture](int value){
        
        moisture = value;
        return crow::response(200);
    });

    app.bindaddr("0.0.0.0").port(5000).run(); //This is to run the server on port 5000 (we need to give a port number that is not already in use)
}