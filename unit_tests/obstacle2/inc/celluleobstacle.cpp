#include "celluleobstacle.h"

CelluleObstacle::CelluleObstacle(int x, int y, bool state, Grille* grid)
    : Cellule(x, y, state, grid) {}

void CelluleObstacle::update_state(const std::vector<std::vector<Cellule*>>& grid) {
    // Ne rien faire, l'état ne change pas
}