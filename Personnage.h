#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <string>
#include "Equipement.h"

class Personnage {
protected:
    std::string nom;   // Nom du personnage
    int vie;           // Points de vie
    int attaque;       // Points d'attaque
    int defense;       // Points de défense
    int vitesse;       // Points de vitesse
    int energie;       // Points d'énergie accumulée pour les attaques spéciales

public:
    Personnage(std::string nom, int vie, int attaque, int defense, int vitesse);
    virtual ~Personnage() {}

    // Méthodes pour différents types d'attaques
    virtual void attaqueBase();
    virtual void attaqueAmelioree();
    virtual void attaqueSpeciale();

    // Méthode pour appliquer des dégâts
    void recevoirDegats(int degats);

    // Méthode pour équiper un équipement
    void equiper(const Equipement& equipement);

    // Vérifie si le personnage est encore en vie
    bool estVivant() const;

    // Affiche les statistiques du personnage
    void afficherStatistiques() const;

    // Accesseurs
    int getVitesse() const { return vitesse; }
    int getAttaque() const { return attaque; }
    int getVie() const { return vie; }
    std::string getNom() const { return nom; }  // Accesseur pour le nom
};

#endif

