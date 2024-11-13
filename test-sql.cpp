#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>              /*Ces bibliothèques permettent de faire le lien entre notre code et notre BDD */
#include <cppconn/prepared_statement.h>      
#include <cppconn/resultset.h>
#include <iostream>
#include "Personnage.h"
#include "Equipement.h"



sql::mysql::MySQL_Driver* driver;
std::unique_ptr<sql::Connection> con;

// Fonction pour se connecter à MySQL
void connecterMySQL() {
    driver = sql::mysql::get_mysql_driver_instance();
    // On entre ici les informations de connexion à la base de données
    con.reset(driver->connect("tcp://127.0.0.1:3306", "sayf", "sayfamine")); // On entre ici les informations de connexion à MySQL
    con->setSchema("cardgame");  // On entre ici le nom de la base de données
}

// Fonction pour créer la table Equipements dans MySQL
void creerTableEquipements() {
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    stmt->execute("CREATE TABLE IF NOT EXISTS Equipements ("
                  "id INT AUTO_INCREMENT PRIMARY KEY,"
                  "type VARCHAR(50),"
                  "bonusVie INT,"
                  "bonusAttaque INT,"
                  "bonusDefense INT,"
                  "bonusVitesse INT)");
}

// Fonction pour ajouter un équipement dans la base de données
void ajouterEquipement(const Equipement& equipement) {
    std::unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("INSERT INTO Equipements (type, bonusVie, bonusAttaque, bonusDefense, bonusVitesse) VALUES (?, ?, ?, ?, ?)")
    );
    pstmt->setString(1, equipement.type);
    pstmt->setInt(2, equipement.bonusVie);
    pstmt->setInt(3, equipement.bonusAttaque);
    pstmt->setInt(4, equipement.bonusDefense);
    pstmt->setInt(5, equipement.bonusVitesse);
    pstmt->execute();
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

// Fonction pour fermer la connexion à la base de données
void fermerConnexion() {
    con->close();
}


int main() {
    // Connexion à la base de données MySQL
    connecterMySQL();

    // Création de la table d'équipements
    creerTableEquipements();

    // Ajouts de plusieurs équipements 
    Equipement heaume("Heaume", 10, 5, 3, 2);
    ajouterEquipement(heaume);
    std::cout << "Équipement ajouté : " << heaume.type << std::endl;

    Equipement plastron("Plastron", 20, 0, 8, 1);
    ajouterEquipement(plastron);
    std::cout << "Équipement ajouté : " << plastron.type << std::endl;

    Equipement epee("Épée", 0, 15, 0, 3);
    ajouterEquipement(epee);
    std::cout << "Équipement ajouté : " << epee.type << std::endl;

    Equipement bouclier("Bouclier", 5, 0, 10, 0);
    ajouterEquipement(bouclier);
    std::cout << "Équipement ajouté : " << bouclier.type << std::endl;
    
    // Fermeture de la connexion
    fermerConnexion();
    return 0;
}

