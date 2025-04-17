#include <iostream>
#include <sol/sol.hpp>
#include <string>

int Pow (int a, int b) {
    int result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

void LuaTest() {
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua["pow"] = Pow;
    lua.script_file("scripts/script001.lua");
   
    std::string nombre = lua["var_nombre"];
    std::cout << "[C++] nombre: " << nombre << std::endl; 
    int edad = lua["var_edad"];
    std::cout << "[C++] edad: " << edad << std::endl;
    sol::table config = lua["table_config"];
    std::string title = config["title"];
    std::cout << "[C++] title: " << title << std::endl;
    bool fullscreen = config["fullscreen"];
    std::cout << "[C++] fullscreen: " << fullscreen << std::endl;
    int width = config["resolution"]["width"];
    std::cout << "[C++] width: " << width << std::endl;
    int height = config["resolution"]["height"];
    std::cout << "[C++] height: " << height << std::endl;
    sol::function factorial = lua["factorial"];
    int resultadoFact = factorial(5);
    std::cout << "[C++] resultado: " << resultadoFact << std::endl;

}

int main (int argc, char* argv[]) {
    std::cout << "Lua y sol" << std::endl;
    LuaTest();
    return 0;
}