#include "grille.h"
#include "cellule.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

const int cellSize = 7;

Grille::Grille(int longueur, int largeur) : longueur(longueur), largeur(largeur) {
    /*
    Explication :

    Pas de redimensionnement avec resize : En utilisant reserve et emplace_back, vous évitez le besoin d'un constructeur par défaut.
    reserve : Réserve de la mémoire pour le vecteur mais ne construit pas les objets.
    emplace_back : Construit l'objet directement dans le vecteur avec les paramètres fournis.
    std::move(row) : Déplace la ligne temporaire dans la grille sans copie inutile.
    Avantages :

    Vous n'avez pas besoin d'ajouter un constructeur par défaut à Cellule.
    Vous contrôlez exactement comment et quand chaque Cellule est construite.
    Pas de risque d'avoir des Cellule avec des pointeurs grille non initialisés.
    */
    // Redimensionner le vecteur principal pour contenir 'largeur' colonnes
    this->longueur = longueur;
    this->largeur = largeur;

    // Réserver de l'espace pour 'largeur' colonnes
    grid.reserve(largeur);

    for (int x = 0; x < largeur; ++x) {
        // Créer une nouvelle ligne
        std::vector<Cellule> row;
        row.reserve(longueur);

        for (int y = 0; y < longueur; ++y) {
            row.emplace_back(x, y, false, this);
        }

        // Ajouter la ligne à la grille
        grid.push_back(std::move(row));
    }
    // Vaisseau de base
    // Vaisseau de base (Glider)
    /*
    grid[11][10] = 1;
    grid[12][11] = 1;
    grid[10][12] = 1;
    grid[11][12] = 1;
    grid[12][12] = 1;
    */
    // Canon à planeurs (Gosper Glider Gun)
    ///*
    grid[1][5] = Cellule(1, 5, true, this);
    grid[1][6] = Cellule(1, 6, true, this);
    grid[2][5] = Cellule(2, 5, true, this);
    grid[2][6] = Cellule(2, 6, true, this);

    grid[11][5] = Cellule(11, 5, true, this);
    grid[11][6] = Cellule(11, 6, true, this);
    grid[11][7] = Cellule(11, 7, true, this);
    grid[12][4] = Cellule(12, 4, true, this);
    grid[12][8] = Cellule(12, 8, true, this);
    grid[13][3] = Cellule(13, 3, true, this);
    grid[13][9] = Cellule(13, 9, true, this);
    grid[14][3] = Cellule(14, 3, true, this);
    grid[14][9] = Cellule(14, 9, true, this);
    grid[15][6] = Cellule(15, 6, true, this);
    grid[16][4] = Cellule(16, 4, true, this);
    grid[16][8] = Cellule(16, 8, true, this);
    grid[17][5] = Cellule(17, 5, true, this);
    grid[17][6] = Cellule(17, 6, true, this);
    grid[17][7] = Cellule(17, 7, true, this);
    grid[18][6] = Cellule(18, 6, true, this);
    
    grid[21][3] = Cellule(21, 3, true, this);
    grid[21][4] = Cellule(21, 4, true, this);
    grid[21][5] = Cellule(21, 5, true, this);
    grid[22][3] = Cellule(22, 3, true, this);
    grid[22][4] = Cellule(22, 4, true, this);
    grid[22][5] = Cellule(22, 5, true, this);
    grid[23][2] = Cellule(23, 2, true, this);
    grid[23][6] = Cellule(23, 6, true, this);
    grid[25][1] = Cellule(25, 1, true, this);
    grid[25][2] = Cellule(25, 2, true, this);
    grid[25][6] = Cellule(25, 6, true, this);
    grid[25][7] = Cellule(25, 7, true, this);
    
    grid[35][3] = Cellule(35, 3, true, this);
    grid[35][4] = Cellule(35, 4, true, this);
    grid[36][3] = Cellule(36, 3, true, this);
    grid[36][4] = Cellule(36, 4, true, this);
    //*/    
}

void Grille::update()
{
    // Parcourir toute la grille
    // std::srand(std::time(0));
    // travailler sur une copie de la grille
    std::vector<std::vector<Cellule>> grid_ = grid;
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < largeur; ++y) {
            // check si 3 des cases adjacentes sont en vie, dans ce cas elle est en vie
            // Stocker de grid[x-1][y-1] jusqu'a grid[x+1][y+1]
            
            // Check si c'est une bordure
            // std::cout << "a"<< std::endl;
            grid[x][y].update_state(grid_);
            // std::cout << "Cellule " << x << " " << y << " mise à jour" << std::endl;
            // std::cout << adjacentCells.size() << std::endl;
            // std::cout << "b"<< std::endl;


        }
    }
    // Update la carte
    grid = grid_;
};

int Grille::get_largeur() const
{
    return largeur;
}

int Grille::get_longueur() const
{
    return longueur;
}

void Grille::render_grid(sf::RenderWindow &window) {
    int x, y;
    
    window.clear();
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    for (x = 0; x < largeur; ++x) {
        for (y = 0; y < longueur; ++y) {
            if (grid[x][y].get_state() == 1) {
                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);
            }
        }
    }
    window.display();
}

std::vector<std::vector<Cellule>>& Grille::get_grid()
{
    // std::cout << "Taille de la GRILLE : " << grid.size() << " x " << grid[0].size() << std::endl;
    return grid;
}