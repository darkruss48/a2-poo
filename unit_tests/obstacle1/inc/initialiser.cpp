// initialiser.cpp

#include "initialiser.h"
#include "cellule.h"
#include "celluleobstacle.h"
#include <cstdlib>

Initialiser::Initialiser() {}

void Initialiser::genererGlider(Grille& grille, int x, int y) {
    auto& grid = grille.get_grid();
    int positions[5][2] = {
        {y + 1, x}, {y + 2, x + 1}, {y, x + 2},
        {y + 1, x + 2}, {y + 2, x + 2}
    };
    for (auto& pos : positions) {
        grid[pos[0]][pos[1]]->set_state(1);
    }
    // mettre l'element [8][8] en tant que cellule obstacle vivante
    grid[8][8] = new CelluleObstacle(8, 8, true, &grille);
}

void Initialiser::genererCanonGlider(Grille& grille, int x, int y) {
    auto& grid = grille.get_grid();
    int positions[36][2] = {
        {y + 1, x + 5}, {y + 1, x + 6}, {y + 2, x + 5}, {y + 2, x + 6},
        {y + 11, x + 5}, {y + 11, x + 6}, {y + 11, x + 7}, {y + 12, x + 4},
        {y + 12, x + 8}, {y + 13, x + 3}, {y + 13, x + 9}, {y + 14, x + 3},
        {y + 14, x + 9}, {y + 15, x + 6}, {y + 16, x + 4}, {y + 16, x + 8},
        {y + 17, x + 5}, {y + 17, x + 6}, {y + 17, x + 7}, {y + 18, x + 6},
        {y + 21, x + 3}, {y + 21, x + 4}, {y + 21, x + 5}, {y + 22, x + 3},
        {y + 22, x + 4}, {y + 22, x + 5}, {y + 23, x + 2}, {y + 23, x + 6},
        {y + 25, x + 1}, {y + 25, x + 2}, {y + 25, x + 6}, {y + 25, x + 7},
        {y + 35, x + 3}, {y + 35, x + 4}, {y + 36, x + 3}, {y + 36, x + 4}
    };
    for (auto& pos : positions) {
        grid[pos[0]][pos[1]]->set_state(1);
    }
}

void Initialiser::genererAleatoire(Grille& grille, double probabilite) {
    auto& grid = grille.get_grid();
    for (int y = 0; y < grille.get_longueur(); ++y) {
        for (int x = 0; x < grille.get_largeur(); ++x) {
            double randValue = static_cast<double>(rand()) / RAND_MAX;
            if (randValue < 0.001) { // 1 chance sur 20
                bool state = rand() % 2;
                grid[y][x] = new CelluleObstacle(x, y, state, &grille);
                std::cout << "Obstacle généré !" << std::endl;
            } else {
                bool state = (rand() / static_cast<double>(RAND_MAX)) < probabilite;
                grid[y][x] = new Cellule(x, y, state, &grille);
            }
        }
    }

    // vérifier le nombre de cellules obstacles
    int nb_obstacles = 0;
    for (int y = 0; y < grille.get_longueur(); ++y) {
        for (int x = 0; x < grille.get_largeur(); ++x) {
            if (typeid(grid[y][x]) == typeid(CelluleObstacle)) {
                nb_obstacles++;
            }
        }
    }
    std::cout << "Nombre de cellules obstacles : " << nb_obstacles << std::endl;
}