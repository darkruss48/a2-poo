// initialiser.cpp

#include "initialiser.h"
#include "cellule.h"
#include <cstdlib>

Initialiser::Initialiser() {}

void Initialiser::genererGlider(Grille& grille, int x, int y) {
    // Code pour insérer un glider à la position (x, y)
    auto& grid = grille.get_grid();
    int positions[5][2] = {
        {x + 1, y}, {x + 2, y + 1}, {x, y + 2},
        {x + 1, y + 2}, {x + 2, y + 2}
    };
    for (auto& pos : positions) {
        grid[pos[0]][pos[1]].set_state(1);
    }
}

void Initialiser::genererCanonGlider(Grille& grille, int x, int y) {
    
    auto& grid = grille.get_grid();
    int positions[36][2] = {
        {x + 1, y + 5}, {x + 1, y + 6}, {x + 2, y + 5}, {x + 2, y + 6},
        {x + 11, y + 5}, {x + 11, y + 6}, {x + 11, y + 7}, {x + 12, y + 4},
        {x + 12, y + 8}, {x + 13, y + 3}, {x + 13, y + 9}, {x + 14, y + 3},
        {x + 14, y + 9}, {x + 15, y + 6}, {x + 16, y + 4}, {x + 16, y + 8},
        {x + 17, y + 5}, {x + 17, y + 6}, {x + 17, y + 7}, {x + 18, y + 6},
        {x + 21, y + 3}, {x + 21, y + 4}, {x + 21, y + 5}, {x + 22, y + 3},
        {x + 22, y + 4}, {x + 22, y + 5}, {x + 23, y + 2}, {x + 23, y + 6},
        {x + 25, y + 1}, {x + 25, y + 2}, {x + 25, y + 6}, {x + 25, y + 7},
        {x + 35, y + 3}, {x + 35, y + 4}, {x + 36, y + 3}, {x + 36, y + 4}
    };
    for (auto& pos : positions) {
        grid[pos[0]][pos[1]].set_state(1);
    }
}

void Initialiser::genererAleatoire(Grille& grille, double probabilite) {
    // Code pour remplir la grille aléatoirement selon la probabilité donnée
    auto& grid = grille.get_grid();
    for (auto& ligne : grid) {
        for (auto& cellule : ligne) {
            cellule.set_state((rand() / static_cast<double>(RAND_MAX)) < probabilite ? 1 : 0);
        }
    }
}