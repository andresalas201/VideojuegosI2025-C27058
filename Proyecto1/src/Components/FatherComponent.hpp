#ifndef FATHERCOMPONENT_HPP
#define FATHERCOMPONENT_HPP

#include "AttackComponent.hpp"

struct FatherComponent {

    AttackComponent* father;
    FatherComponent (AttackComponent* father = nullptr) : father(father) {}

};

#endif // FATHERCOMPONENT_HPP