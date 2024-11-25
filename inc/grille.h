#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "cellule.h"
#pragma once

class Grille{
    private:
        int longueur;
        int largeur;
        std::vector<std::vector<Cellule>> grid; // Pointeur afin d'économiser la mémoire
    
    public:
        // Constructeur
        Grille() : longueur(0), largeur(0) {}
        Grille(int longueur, int largeur);
        // Constructeur par copie
        // Grille(const Grille& grille) : longueur(grille.longueur), largeur(grille.largeur), grid(grille.grid.size()) {
        //     for (size_t i = 0; i < grille.grid.size(); ++i) {
        //         grid[i] = grille.grid[i];
        //     }
        // }
        void update();
        void init();
        void render_grid(sf::RenderWindow &window);
        // Getters
        int get_longueur() const;
        int get_largeur() const;
        std::vector<std::vector<Cellule>>& get_grid();
};