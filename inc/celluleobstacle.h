#include <vector>
#pragma once
#include "cellule.h"

class Grille;

class CelluleObstacle : public Cellule
{
    public:
        // Constructeur
        CelluleObstacle(int x, int y, bool state, Grille* grid);
        void update_state(const std::vector<std::vector<Cellule*>>& grid) override;
};