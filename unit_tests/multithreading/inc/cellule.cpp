#include "cellule.h"
#include "grille.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

Cellule::Cellule(int x, int y, bool state, Grille* grid)
{
    this->x = x;
    this->y = y;
    this->state = state;
    this->grille = grid;
}

void Cellule::update_state(const std::vector<std::vector<Cellule*>>& grid_) {
    int longueur = grid_.size();          // Nombre de lignes
    int largeur = grid_[0].size();        // Nombre de colonnes
    int aliveNeighbors = 0;

    // Calcul des voisins vivants
    for (int j = -1; j <= 1; ++j) {
        int ny = (y + j + longueur) % longueur;
        for (int i = -1; i <= 1; ++i) {
            int nx = (x + i + largeur) % largeur;
            if (i == 0 && j == 0)
                continue;
            if (grid_[ny][nx]->get_state())
                ++aliveNeighbors;
        }
    }

    // Application des règles du jeu de la vie
    if (state) {
        if (aliveNeighbors < 2 || aliveNeighbors > 3)
            state = false;
    } else {
        if (aliveNeighbors == 3)
            state = true;
    }
}

Grille Cellule::get_grille()
{
    return *grille;
}

int Cellule::get_state() const
{
    return state;
}

void Cellule::set_state(bool state) {
    this->state = state;
}
