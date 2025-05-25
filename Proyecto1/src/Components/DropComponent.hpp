#ifndef DROPCOMPONENT_HPP
#define DROPCOMPONENT_HPP

#include <sol/sol.hpp>

struct DropComponent {
    int increase;
    std::string path;

    DropComponent(int increase = 1, std::string& path = "") {
        this->increase = increase;
        this->path = path;
    }
};

#endif // DROPCOMPONENT_HPP