#include "Personnage.h"
#include <iostream>

Personnage::Personnage(std::string nom, int vie, int attaque, int defense, int vitesse)
    : nom(nom), vie(vie), attaque(attaque), defense(defense), vitesse(vitesse), energie(0) {}

void Personnage::attaqueBase() {
    std::cout << nom << " utilise une attaque de base !\n";
    energie += 10;  // Augmente l'énergie de 10 points
}

void Personnage::attaqueAmelioree() {
    std::cout << nom << " utilise une attaque améliorée !\n";
    energie += 15;  // Augmente l'énergie de 15 points
}

void Personnage::attaqueSpeciale() {
    if (energie >= 100) {
        std::cout << nom << " utilise une attaque spéciale !\n";
        energie -= 100;  // Consomme 100 points d'énergie
    } else {
        std::cout << "Énergie insuffisante pour l'attaque spéciale.\n";
    }
}

void Personnage::recevoirDegats(int degats) {
    vie -= degats;
    if (vie < 0) vie = 0;  // Empêche les points de vie d'être négatifs
}

bool Personnage::estVivant() const {
    return vie > 0;
}

void Personnage::afficherStatistiques() const {
    std::cout << "Nom: " << nom << ", Vie: " << vie << ", Attaque: " << attaque 
              << ", Défense: " << defense << ", Vitesse: " << vitesse << ", Énergie: " << energie << std::endl;
}

void Personnage::equiper(const Equipement& equipement) {
    vie += equipement.bonusVie;
    attaque += equipement.bonusAttaque;
    defense += equipement.bonusDefense;
    vitesse += equipement.bonusVitesse;

    std::cout << nom << " a équipé : " << equipement.type << " (Bonus - Vie: " << equipement.bonusVie
              << ", Attaque: " << equipement.bonusAttaque << ", Défense: " << equipement.bonusDefense
              << ", Vitesse: " << equipement.bonusVitesse << ")" << std::endl;
}


