#ifndef BERSERKER_H
#define BERSERKER_H

#include "Personnage.h"

// Classe Berserker, qui hérite de Personnage
class Berserker : public Personnage {
public:
    // Constructeur pour initialiser le Berserker avec des valeurs spécifiques
    Berserker(std::string nom, int vie, int attaque, int defense, int vitesse);

    // Capacités spécifiques au Berserker
    void frappePunitive();     // Attaque spéciale infligeant des dégâts basés sur les points de vie
    void coupDechaine();       // Attaque plus puissante, consommant de la vie
    void mouvementAlpha();     // Attaque ultime, nécessitant 100 points d'énergie
};

#endif

