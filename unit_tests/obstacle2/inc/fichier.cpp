// fichier.cpp
#include "fichier.h"
#include <fstream>
#include <iostream>
#include "celluleobstacle.h"
#include <typeinfo>

void Fichier::sauvegarder_grille(Grille& grille, const std::string& nom_fichier) {
    std::ofstream fichier(nom_fichier);
    if (fichier.is_open()) {
        int longueur = grille.get_longueur();
        int largeur = grille.get_largeur();
        fichier << longueur << " " << largeur << std::endl;
        auto& grid = grille.get_grid();
        for (int y = 0; y < longueur; ++y) {
            for (int x = 0; x < largeur; ++x) {
                Cellule* cellule = grid[y][x];
                if (typeid(*cellule) == typeid(CelluleObstacle)) {
                    std::cout << "Obstacle détecté !" << std::endl;
                    CelluleObstacle* obstacle = dynamic_cast<CelluleObstacle*>(cellule);
                    fichier << (obstacle->get_state() ? "@ " : "# ");
                } else {
                    // std::cout << typeid(*cellule).name() << std::endl;
                    // std::cout << typeid(CelluleObstacle).name() << std::endl;
                    fichier << (cellule->get_state() ? "1 " : "0 ");
                }
            }
            fichier << std::endl;
        }
        fichier.close();
    } else {
        std::cerr << "Impossible d'ouvrir le fichier en écriture : " << nom_fichier << std::endl;
    }
}

Grille* Fichier::charger_grille(const std::string& nom_fichier) {
    std::ifstream fichier(nom_fichier);
    if (fichier.is_open()) {
        int longueur, largeur;
        fichier >> longueur >> largeur;
        Grille* grille = new Grille(longueur, largeur);
        auto& grid = grille->get_grid();
        for (int y = 0; y < longueur; ++y) {
            for (int x = 0; x < largeur; ++x) {
                std::string value;
                fichier >> value;
                if (value == "@") {
                    grid[y][x] = new CelluleObstacle(x, y, true, grille);
                } else if (value == "#") {
                    grid[y][x] = new CelluleObstacle(x, y, false, grille);
                } else {
                    bool state = (value == "1");
                    grid[y][x] = new Cellule(x, y, state, grille);
                }
            }
        }
        fichier.close();
        return grille;
    } else {
        std::cerr << "Impossible d'ouvrir le fichier en lecture : " << nom_fichier << std::endl;
        return nullptr;
    }
}