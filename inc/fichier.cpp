// fichier.cpp
#include "fichier.h"
#include <fstream>
#include <iostream>

void Fichier::sauvegarder_grille(Grille& grille, const std::string& nom_fichier) {
    std::ofstream fichier(nom_fichier);
    if (fichier.is_open()) {
        int longueur = grille.get_longueur();
        int largeur = grille.get_largeur();
        fichier << longueur << " " << largeur << std::endl;
        const auto& grid = grille.get_grid();
        for (int y = 0; y < longueur; ++y) {
            for (int x = 0; x < largeur; ++x) {
                fichier << grid[y][x].get_state() << " ";
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
        std::cout << "Longueur : " << longueur << " Largeur : " << largeur << std::endl;
        Grille* grille = new Grille(longueur, largeur);
        // grille->init();
        auto& grid = grille->get_grid();
        std::cout << "Taille de la grille : " << grid.size() << " x " << grid[0].size() << std::endl;
        for (int y = 0; y < longueur; ++y) {
            for (int x = 0; x < largeur; ++x) {
                int state;
                fichier >> state;
                grid[y][x].set_state(state == 1);
            }
        }
        fichier.close();
        std::cout << "Taille de la grid1 : " << grid[0][0].get_grille().get_grid().size() << " x " << grid[0][0].get_grille().get_grid().size() << std::endl;
        return grille;
    } else {
        std::cerr << "Impossible d'ouvrir le fichier en lecture : " << nom_fichier << std::endl;
        return nullptr;
    }
}