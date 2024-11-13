#include "Berserker.h"
#include <iostream>

// Constructeur pour initialiser le Berserker
Berserker::Berserker(std::string nom, int vie, int attaque, int defense, int vitesse)
    : Personnage(nom, vie, attaque, defense, vitesse) {}

// Implémentation de la capacité Frappe Punitive
void Berserker::frappePunitive() {
    int degats = 0.3 * vie;      // Inflige 30% des points de vie actuels en dégâts
    vie -= 0.1 * vie;            // Réduit la vie de 10%
    std::cout << nom << " utilise Frappe Punitive, infligeant " << degats << " dégâts.\n";
    energie += 20;               // Augmente l'énergie de 20 points
}

// Implémentation de la capacité Coup Déchaîné
void Berserker::coupDechaine() {
    int degats = 0.5 * vie;      // Inflige 50% des points de vie en dégâts
    vie -= 0.15 * vie;           // Réduit la vie de 15%
    std::cout << nom << " utilise Coup Déchaîné, infligeant " << degats << " dégâts.\n";
    energie += 30;               // Augmente l'énergie de 30 points
}

// Implémentation de la capacité ultime Mouvement Alpha
void Berserker::mouvementAlpha() {
    if (energie >= 100) {        // Nécessite 100 points d'énergie
        int degats = 0.75 * vie; // Inflige 75% des points de vie en dégâts
        vie += 0.5 * vie;        // Régénère 50% des points de vie
        std::cout << nom << " utilise Mouvement Alpha, infligeant " << degats << " dégâts et se régenère de la vie.\n";
        energie -= 100;          // Consomme 100 points d'énergie
    } else {
        std::cout << "Énergie insuffisante pour Mouvement Alpha.\n";
    }
}
