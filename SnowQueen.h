#ifndef SNOWQUEEN_H
#define SNOWQUEEN_H

#include "Personnage.h"

// Classe SnowQueen, qui hérite de Personnage
class SnowQueen : public Personnage {
public:
    // Constructeur pour initialiser SnowQueen avec des valeurs spécifiques
    SnowQueen(std::string nom, int vie, int attaque, int defense, int vitesse);

    // Capacités spécifiques à SnowQueen
    void javelotDeGlace();       // Attaque infligeant des dégâts accrus
    void ventGlacial();          // Attaque plus puissante avec un multiplicateur d'attaque
    void letItGo();              // Attaque ultime nécessitant 100 points d'énergie
};

#endif
