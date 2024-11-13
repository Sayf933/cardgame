#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <string>

class Equipement {
public:
    std::string type;
    int bonusVie;       // Applique un bonus de vie
    int bonusAttaque;   // Applique un bonus d'attque
    int bonusDefense;   // Applique un bonus de défense
    int bonusVitesse;   // Applique un bonus de vitesse

    Equipement(std::string type, int bonusVie, int bonusAttaque, int bonusDefense, int bonusVitesse)
        : type(type), bonusVie(bonusVie), bonusAttaque(bonusAttaque), bonusDefense(bonusDefense), bonusVitesse(bonusVitesse) {}
};

#endif

