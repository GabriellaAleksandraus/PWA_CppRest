#include <cstdlib>
#include <iostream>

// how to test
// g++ test.cpp

// test 1
// ./a.out

//test 2 
// PWA_DIR="GABBY/" ./a.out
int main(){
    std::string path = "";
    if (const char* env_p = std::getenv("PWA_DIR")){
        path = env_p;
    }
    
    std::cout << "PATH is: " << path + "index.html" << std::endl;
}