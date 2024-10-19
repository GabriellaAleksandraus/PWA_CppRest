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

    CROW_ROUTE(app,"/index.html") ([](){
        std::ifstream in("../index.html"); //This is to read the file index.html
        std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()); //This is to convert the file to a string
        return crow::response(content);
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

    app.bindaddr("0.0.0.0").port(3000).run();
}