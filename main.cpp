#include "crow.h"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello gabby";
    });

    app.port(3000).multithreaded().run(); // Run the server on port 3000 (localhost:3000)
}