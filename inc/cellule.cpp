#include "cellule.h"
#include "grille.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>


void Grille::init() {
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < longueur; ++y) {
            grid[x][y] = Cellule(x, y, false, this);
        }
    }
}


Cellule::Cellule(int x, int y, bool state, Grille* grid)
{
    this->x = x;
    this->y = y;
    this->state = state;
    this->grille = grid;
}

std::vector<Cellule> Cellule::check_coin()
{
    {
    std::vector<Cellule> adjacentCells;
    // Faire coin par coin
    if (x == 0 && y == 0) {// en haut a droite
        // Cases "non problèmatiques"
        // std::cout << "COIN" << std::endl;
        // afficher nombre élément dans la première ligne
        // std::cout << grille->get_grid().size() << std::endl;
        adjacentCells.push_back(grille->get_grid()[0][1]);
        // std::cout << "COIN2" << std::endl;
        adjacentCells.push_back(grille->get_grid()[1][0]);
        adjacentCells.push_back(grille->get_grid()[1][1]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][0]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][1]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][grille->get_longueur() - 1]);
        adjacentCells.push_back(grille->get_grid()[0][grille->get_longueur() - 1]);
        adjacentCells.push_back(grille->get_grid()[1][grille->get_longueur() - 1]);
    }
    else if (x == 0 && y == grille->get_longueur() - 1) { // en haut a gauche
        // Cases "non problèmatiques"
        adjacentCells.push_back(grille->get_grid()[0][grille->get_longueur() - 2]);
        adjacentCells.push_back(grille->get_grid()[1][grille->get_longueur() - 2]);
        adjacentCells.push_back(grille->get_grid()[1][grille->get_longueur() - 1]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grille->get_grid()[0][0]);
        adjacentCells.push_back(grille->get_grid()[1][0]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][0]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][grille->get_longueur() - 1]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][grille->get_longueur() - 2]);
    }
    else if (x == grille->get_largeur() - 1 && y == 0) { // en bas a droite
        // Cases "non problèmatiques"
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 2][0]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 2][1]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][1]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grille->get_grid()[0][0]);
        adjacentCells.push_back(grille->get_grid()[0][1]);
        adjacentCells.push_back(grille->get_grid()[0][grille->get_longueur() - 1]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][grille->get_longueur() - 1]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 2][grille->get_longueur() - 1]);   
    }
    else if (x == grille->get_largeur() - 1 && y == grille->get_longueur() - 1) { // en bas a gauche
        // Cases "non problèmatiques"
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 2][grille->get_longueur() - 1]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 2][grille->get_longueur() - 2]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][grille->get_longueur() - 2]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grille->get_grid()[0][0]);
        adjacentCells.push_back(grille->get_grid()[0][grille->get_longueur() - 1]);
        adjacentCells.push_back(grille->get_grid()[0][grille->get_longueur() - 2]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][0]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 2][0]);
    }
    else if (x == 0) { // Bordure haute
        // Cases "non problèmatiques"
        adjacentCells.push_back(grille->get_grid()[0][y - 1]);
        adjacentCells.push_back(grille->get_grid()[0][y + 1]);
        adjacentCells.push_back(grille->get_grid()[1][y - 1]);
        adjacentCells.push_back(grille->get_grid()[1][y]);
        adjacentCells.push_back(grille->get_grid()[1][y + 1]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][y - 1]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][y]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][y + 1]);
    }
    else if (x == grille->get_largeur() - 1) { // Bordure basse
        // Cases "non problèmatiques"
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][y - 1]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 1][y + 1]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 2][y - 1]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 2][y]);
        adjacentCells.push_back(grille->get_grid()[grille->get_largeur() - 2][y + 1]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grille->get_grid()[0][y - 1]);
        adjacentCells.push_back(grille->get_grid()[0][y]);
        adjacentCells.push_back(grille->get_grid()[0][y + 1]);
    }
    else if (y == 0) { // Bordure gauche
        // Cases "non problèmatiques"
        adjacentCells.push_back(grille->get_grid()[x - 1][0]);
        adjacentCells.push_back(grille->get_grid()[x + 1][0]);
        adjacentCells.push_back(grille->get_grid()[x - 1][1]);
        adjacentCells.push_back(grille->get_grid()[x][1]);
        adjacentCells.push_back(grille->get_grid()[x + 1][1]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grille->get_grid()[x - 1][grille->get_longueur() - 1]);
        adjacentCells.push_back(grille->get_grid()[x][grille->get_longueur() - 1]);
        adjacentCells.push_back(grille->get_grid()[x + 1][grille->get_longueur() - 1]);
    }
    else if (y == grille->get_longueur() - 1) { // Bordure droite
        // Cases "non problèmatiques"
        adjacentCells.push_back(grille->get_grid()[x - 1][grille->get_longueur() - 1]);
        adjacentCells.push_back(grille->get_grid()[x + 1][grille->get_longueur() - 1]);
        adjacentCells.push_back(grille->get_grid()[x - 1][grille->get_longueur() - 2]);
        adjacentCells.push_back(grille->get_grid()[x][grille->get_longueur() - 2]);
        adjacentCells.push_back(grille->get_grid()[x + 1][grille->get_longueur() - 2]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grille->get_grid()[x - 1][0]);
        adjacentCells.push_back(grille->get_grid()[x][0]);
        adjacentCells.push_back(grille->get_grid()[x + 1][0]);
    }
    else {
        // std::cout << "NORMALE" << std::endl;
        // Afficher emplacement + nb calculée
        // std::cout << "x: " << x << " y: " << y << " nb: " << std::count(adjacentCells.begin(), adjacentCells.end(), 1) << std::endl;

    }
    return adjacentCells;
}
}

void Cellule::update_state(std::vector<std::vector<Cellule>>& grid_)
{
    // Vérifier si c'est vide --> pas danc un coin
    std::vector<Cellule> adjacentCells = check_coin();
    if (adjacentCells.size() == 0) {
        for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) { // case centrale ; on l'oublie
                continue;
            }
            adjacentCells.push_back(grille->get_grid()[x+i][y+j]);
            // std::cout << "VIDE" << std::endl;
        }
    }
    }
    // std::cout << "b"<< std::endl;
    // Checker si 3 des cases adjacentes sont en vie
    int aliveNeighbors = std::count_if(adjacentCells.begin(), adjacentCells.end(), [](Cellule& cell) {
    return cell.get_state() == 1;
    });
    // if (std::count(adjacentCells.begin(), adjacentCells.end(), 1) == 3) {
    if (aliveNeighbors == 3) {
        grid_[x][y] = Cellule(x, y, true, grille); // en vie
    }
    // else if (std::count(adjacentCells.begin(), adjacentCells.end(), 1) == 2) {} // change rien
    else if (aliveNeighbors == 2) {} // change rien
    else if (aliveNeighbors < 2 || aliveNeighbors > 3)  {
    // else if (std::count(adjacentCells.begin(), adjacentCells.end(), 1) < 2 || std::count(adjacentCells.begin(), adjacentCells.end(), 1) > 3)  {
        grid_[x][y] = Cellule(x, y, false, grille); // mort
    }
    else {
        std::cout << "Problème, on passe a la suite" << std::endl;
        // Afficher emplacement + nb calculée
        std::cout << "x: " << x << " y: " << y << " nb: " << aliveNeighbors << std::endl;
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
