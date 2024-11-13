#include "Personnage.h"
#include "Berserker.h"
#include "SnowQueen.h"
#include "Equipement.h"
#include <iostream>
#include <sstream>
#include <limits>
#include "mysql_driver.h"
#include "mysql_connection.h"
#include <cppconn/statement.h>                   /*Ces bibliothèques permettent de faire le lien entre notre code et notre BDD */
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

// Fonction de connexion à la base de données
sql::mysql::MySQL_Driver* driver;
std::unique_ptr<sql::Connection> con;

void connecterMySQL() {
    driver = sql::mysql::get_mysql_driver_instance();
    con.reset(driver->connect("tcp://127.0.0.1:3306", "sayf", "sayfamine"));  // Informations de connexion à la base de données
    con->setSchema("cardgame");  // Nom de la base de données
}

// Fonction pour récupérer un équipement en fonction de son type
Equipement recupererEquipement(const std::string& type) {
    std::unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("SELECT bonusVie, bonusAttaque, bonusDefense, bonusVitesse FROM Equipements WHERE type = ?")
    );
    pstmt->setString(1, type);

    std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

    if (res->next()) {
        return Equipement(
            type,
            res->getInt("bonusVie"),
            res->getInt("bonusAttaque"),
            res->getInt("bonusDefense"),
            res->getInt("bonusVitesse")
        );
    } else {
        throw std::runtime_error("Equipement non trouvé dans la base de données.");
    }
}

// Fonction pour fermer la connexion MySQL
void fermerConnexion() {
    con->close();
}

// Fonction pour obtenir une action valide du joueur
int obtenirAction(const std::string& nomJoueur) {
    while (true) {
        std::string input;
        std::cout << "\n" << nomJoueur << ", choisissez votre action (1: Attaque de base, 2: Attaque améliorée, 3: Attaque spéciale) : ";
        std::getline(std::cin, input);

        // Convertir la saisie en entier en utilisant std::stringstream
        std::stringstream ss(input);
        int action;
        if (ss >> action && (action >= 1 && action <= 3)) {
            return action;  // Si la conversion a réussi et l'action est correcte
        } else {
            std::cout << "Entrée invalide. Veuillez entrer un nombre entre 1 et 3." << std::endl;
        }
    }
}

int main() {
    // Connexion à la base de données MySQL
    connecterMySQL();

    // Saisie des pseudonymes des joueurs
    std::string pseudoJoueur1, pseudoJoueur2;
    std::cout << "Entrez le pseudo du Joueur 1 : ";
    std::getline(std::cin, pseudoJoueur1);
    std::cout << "Entrez le pseudo du Joueur 2 : ";
    std::getline(std::cin, pseudoJoueur2);

    // Création des personnages
    Berserker joueur1(pseudoJoueur1, 250, 35, 15, 20);
    SnowQueen joueur2(pseudoJoueur2, 220, 30, 18, 22);

    // Récupération et équipement des personnages avec des équipements depuis la base de données
    try {
        Equipement heaume = recupererEquipement("Heaume");
        Equipement plastron = recupererEquipement("Plastron");

        joueur1.equiper(heaume);
        joueur2.equiper(plastron);

        // Affiche les statistiques après l'équipement
        std::cout << "\nStatistiques après équipement :" << std::endl;
        joueur1.afficherStatistiques();
        joueur2.afficherStatistiques();
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de la récupération de l'équipement : " << e.what() << std::endl;
    }

    // Combat en tour par tour interactif
    std::cout << "\nDébut du combat en tour par tour :" << std::endl;

    while (joueur1.estVivant() && joueur2.estVivant()) {
        // Tour du Joueur 1
        int action = obtenirAction(joueur1.getNom());

        switch (action) {
            case 1:
                joueur1.frappePunitive();  // Attaque de base du Berserker
                joueur2.recevoirDegats(joueur1.getAttaque());
                break;
            case 2:
                joueur1.coupDechaine();  // Attaque améliorée du Berserker
                joueur2.recevoirDegats(joueur1.getAttaque() * 1.5);
                break;
            case 3:
                joueur1.mouvementAlpha();  // Attaque spéciale du Berserker
                joueur2.recevoirDegats(joueur1.getAttaque() * 2);
                break;
        }

        joueur1.afficherStatistiques();
        joueur2.afficherStatistiques();

        if (!joueur2.estVivant()) break;

        // Tour du Joueur 2
        action = obtenirAction(joueur2.getNom());

        switch (action) {
            case 1:
                joueur2.javelotDeGlace();  // Attaque de base de la SnowQueen
                joueur1.recevoirDegats(joueur2.getAttaque());
                break;
            case 2:
                joueur2.ventGlacial();  // Attaque améliorée de la SnowQueen
                joueur1.recevoirDegats(joueur2.getAttaque() * 1.5);
                break;
            case 3:
                joueur2.letItGo();  // Attaque spéciale de la SnowQueen
                joueur1.recevoirDegats(joueur2.getAttaque() * 1.7);
                break;
        }

        joueur1.afficherStatistiques();
        joueur2.afficherStatistiques();
    }

    // Affichage du résultat final du combat
    std::cout << "\nFin du combat :" << std::endl;
    if (joueur1.estVivant() && !joueur2.estVivant()) {
        std::cout << joueur1.getNom() << " remporte la victoire !" << std::endl;
    } else if (!joueur1.estVivant() && joueur2.estVivant()) {
        std::cout << joueur2.getNom() << " remporte la victoire !" << std::endl;
    } else {
        std::cout << "Le combat se termine par une égalité !" << std::endl;
    }

    // Fermeture de la connexion à la base de données
    fermerConnexion();

    return 0;
}
