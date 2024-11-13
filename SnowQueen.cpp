#include "SnowQueen.h"
#include <iostream>

// Constructeur pour initialiser SnowQueen
SnowQueen::SnowQueen(std::string nom, int vie, int attaque, int defense, int vitesse)
    : Personnage(nom, vie, attaque, defense, vitesse) {}

// Implémentation de la capacité Javelot de Glace
void SnowQueen::javelotDeGlace() {
    int degats = 1.25 * attaque; // Inflige 125% de l'attaque en dégâts
    std::cout << nom << " utilise Javelot de Glace, infligeant " << degats << " dégâts.\n";
    energie += 20;               // Augmente l'énergie de 20 points
}

// Implémentation de la capacité Vent Glacial
void SnowQueen::ventGlacial() {
    int degats = 1.5 * attaque;  // Inflige 150% de l'attaque en dégâts
    std::cout << nom << " utilise Vent Glacial, infligeant " << degats << " dégâts.\n";
    energie += 30;               // Augmente l'énergie de 30 points
}

// Implémentation de la capacité ultime LetItGo
void SnowQueen::letItGo() {
    if (energie >= 100) {        // Nécessite 100 points d'énergie
        int degats = 1.75 * attaque; // Inflige 175% de l'attaque en dégâts
        std::cout << nom << " utilise LetItGo, infligeant " << degats << " dégâts.\n";
        energie -= 100;          // Consomme 100 points d'énergie
    } else {
        std::cout << "Énergie insuffisante pour LetItGo.\n";
    }
}

