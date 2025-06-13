#ifndef TAGCOMPONENT_HPP
#define TAGCOMPONENT_HPP

struct TagComponent {
    std::string tag;
    
    TagComponent(const std::string& tag = "none") {
        this->tag = tag;
    }
};

#endif // TAGCOMPONENT_HPP