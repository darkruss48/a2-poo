#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

const int cellSize = 7;
const int gridWidth = 200;
const int gridHeight = 200;

std::vector<std::vector<int>> grid(gridWidth, std::vector<int>(gridHeight));

void initializeGrid() {
    std::srand(std::time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            // grid[x][y] = std::rand() % 2;  // Randomly initialize cells as alive or dead
            grid[x][y] = 0; // 1 en vie, 0 mort
        }
    }
    // Vaisseau de base
    // Vaisseau de base (Glider)
    grid[11][10] = 1;
    grid[12][11] = 1;
    grid[10][12] = 1;
    grid[11][12] = 1;
    grid[12][12] = 1;
    // Canon à planeurs (Gosper Glider Gun)
    /*
    grid[1][5] = 1;
    grid[1][6] = 1;
    grid[2][5] = 1;
    grid[2][6] = 1;

    grid[11][5] = 1;
    grid[11][6] = 1;
    grid[11][7] = 1;
    grid[12][4] = 1;
    grid[12][8] = 1;
    grid[13][3] = 1;
    grid[13][9] = 1;
    grid[14][3] = 1;
    grid[14][9] = 1;
    grid[15][6] = 1;
    grid[16][4] = 1;
    grid[16][8] = 1;
    grid[17][5] = 1;
    grid[17][6] = 1;
    grid[17][7] = 1;
    grid[18][6] = 1;

    grid[21][3] = 1;
    grid[21][4] = 1;
    grid[21][5] = 1;
    grid[22][3] = 1;
    grid[22][4] = 1;
    grid[22][5] = 1;
    grid[23][2] = 1;
    grid[23][6] = 1;
    grid[25][1] = 1;
    grid[25][2] = 1;
    grid[25][6] = 1;
    grid[25][7] = 1;

    grid[35][3] = 1;
    grid[35][4] = 1;
    grid[36][3] = 1;
    grid[36][4] = 1;
    */
}

std::vector<int> check_coin(int x, int y)
{
    std::vector<int> adjacentCells;
    // Faire coin par coin
    if (x == 0 && y == 0) {// en haut a droite
        // Cases "non problèmatiques"
        adjacentCells.push_back(grid[0][1]);
        adjacentCells.push_back(grid[1][0]);
        adjacentCells.push_back(grid[1][1]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grid[gridWidth - 1][0]);
        adjacentCells.push_back(grid[gridWidth - 1][1]);
        adjacentCells.push_back(grid[gridWidth - 1][gridHeight - 1]);
        adjacentCells.push_back(grid[0][gridHeight - 1]);
        adjacentCells.push_back(grid[1][gridHeight - 1]);
    }
    else if (x == 0 && y == gridHeight - 1) { // en haut a gauche
        // Cases "non problèmatiques"
        adjacentCells.push_back(grid[0][gridHeight - 2]);
        adjacentCells.push_back(grid[1][gridHeight - 2]);
        adjacentCells.push_back(grid[1][gridHeight - 1]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grid[0][0]);
        adjacentCells.push_back(grid[1][0]);
        adjacentCells.push_back(grid[gridWidth - 1][0]);
        adjacentCells.push_back(grid[gridWidth - 1][gridHeight - 1]);
        adjacentCells.push_back(grid[gridWidth - 1][gridHeight - 2]);
    }
    else if (x == gridWidth - 1 && y == 0) { // en bas a droite
        // Cases "non problèmatiques"
        adjacentCells.push_back(grid[gridWidth - 2][0]);
        adjacentCells.push_back(grid[gridWidth - 2][1]);
        adjacentCells.push_back(grid[gridWidth - 1][1]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grid[0][0]);
        adjacentCells.push_back(grid[0][1]);
        adjacentCells.push_back(grid[0][gridHeight - 1]);
        adjacentCells.push_back(grid[gridWidth - 1][gridHeight - 1]);
        adjacentCells.push_back(grid[gridWidth - 2][gridHeight - 1]);   
    }
    else if (x == gridWidth - 1 && y == gridHeight - 1) { // en bas a gauche
        // Cases "non problèmatiques"
        adjacentCells.push_back(grid[gridWidth - 2][gridHeight - 1]);
        adjacentCells.push_back(grid[gridWidth - 2][gridHeight - 2]);
        adjacentCells.push_back(grid[gridWidth - 1][gridHeight - 2]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grid[0][0]);
        adjacentCells.push_back(grid[0][gridHeight - 1]);
        adjacentCells.push_back(grid[0][gridHeight - 2]);
        adjacentCells.push_back(grid[gridWidth - 1][0]);
        adjacentCells.push_back(grid[gridWidth - 2][0]);
    }
    else if (x == 0) { // Bordure haute
        // Cases "non problèmatiques"
        adjacentCells.push_back(grid[0][y - 1]);
        adjacentCells.push_back(grid[0][y + 1]);
        adjacentCells.push_back(grid[1][y - 1]);
        adjacentCells.push_back(grid[1][y]);
        adjacentCells.push_back(grid[1][y + 1]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grid[gridWidth - 1][y - 1]);
        adjacentCells.push_back(grid[gridWidth - 1][y]);
        adjacentCells.push_back(grid[gridWidth - 1][y + 1]);
    }
    else if (x == gridWidth - 1) { // Bordure basse
        // Cases "non problèmatiques"
        adjacentCells.push_back(grid[gridWidth - 1][y - 1]);
        adjacentCells.push_back(grid[gridWidth - 1][y + 1]);
        adjacentCells.push_back(grid[gridWidth - 2][y - 1]);
        adjacentCells.push_back(grid[gridWidth - 2][y]);
        adjacentCells.push_back(grid[gridWidth - 2][y + 1]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grid[0][y - 1]);
        adjacentCells.push_back(grid[0][y]);
        adjacentCells.push_back(grid[0][y + 1]);
    }
    else if (y == 0) { // Bordure gauche
        // Cases "non problèmatiques"
        adjacentCells.push_back(grid[x - 1][0]);
        adjacentCells.push_back(grid[x + 1][0]);
        adjacentCells.push_back(grid[x - 1][1]);
        adjacentCells.push_back(grid[x][1]);
        adjacentCells.push_back(grid[x + 1][1]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grid[x - 1][gridHeight - 1]);
        adjacentCells.push_back(grid[x][gridHeight - 1]);
        adjacentCells.push_back(grid[x + 1][gridHeight - 1]);
    }
    else if (y == gridHeight - 1) { // Bordure droite
        // Cases "non problèmatiques"
        adjacentCells.push_back(grid[x - 1][gridHeight - 1]);
        adjacentCells.push_back(grid[x + 1][gridHeight - 1]);
        adjacentCells.push_back(grid[x - 1][gridHeight - 2]);
        adjacentCells.push_back(grid[x][gridHeight - 2]);
        adjacentCells.push_back(grid[x + 1][gridHeight - 2]);
        // Cases "problèmatiques"
        adjacentCells.push_back(grid[x - 1][0]);
        adjacentCells.push_back(grid[x][0]);
        adjacentCells.push_back(grid[x + 1][0]);
    }
    else {
        // std::cout << "NORMALE" << std::endl;
        // Afficher emplacement + nb calculée
        // std::cout << "x: " << x << " y: " << y << " nb: " << std::count(adjacentCells.begin(), adjacentCells.end(), 1) << std::endl;

    }
    return adjacentCells;
}

void update()
{
    // Parcourir toute la grille
    std::srand(std::time(0));
    // travailler sur une copie de la grille
    std::vector<std::vector<int>> grid_ = grid;
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            // check si 3 des cases adjacentes sont en vie, dans ce cas elle est en vie
            // Stocker de grid[x-1][y-1] jusqu'a grid[x+1][y+1]
            
            // Check si c'est une bordure
            // std::cout << "a"<< std::endl;
            std::vector<int> adjacentCells = check_coin(x, y);
            // std::cout << adjacentCells.size() << std::endl;

            // Vérifier si c'est vide --> pas danc un coin
            if (adjacentCells.size() == 0) {
                for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (i == 0 && j == 0) { // case centrale ; on l'oublie
                        continue;
                    }
                    adjacentCells.push_back(grid[x+i][y+j]);
                    // std::cout << "VIDE" << std::endl;
                }
            }
            }            
            // std::cout << "b"<< std::endl;
            // Checker si 3 des cases adjacentes sont en vie
            if (std::count(adjacentCells.begin(), adjacentCells.end(), 1) == 3) {
                grid_[x][y] = 1; // en vie
            }
            else if (std::count(adjacentCells.begin(), adjacentCells.end(), 1) == 2) {} // change rien
            else if (std::count(adjacentCells.begin(), adjacentCells.end(), 1) < 2 || std::count(adjacentCells.begin(), adjacentCells.end(), 1) > 3)  {
                grid_[x][y] = 0; // mort
            }
            else {
                std::cout << "Problème, on passe a la suite" << std::endl;
                // Afficher emplacement + nb calculée
                std::cout << "x: " << x << " y: " << y << " nb: " << std::count(adjacentCells.begin(), adjacentCells.end(), 1) << std::endl;
            }
            // std::cout << "b"<< std::endl;


        }
    }
    // Update la carte
    grid = grid_;
}

void renderGrid(sf::RenderWindow &window) {
    int x, y;
    
    window.clear();
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    for (x = 0; x < gridWidth; ++x) {
        for (y = 0; y < gridHeight; ++y) {
            if (grid[x][y] == 1) {
                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);
            }
        }
    }
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");
    
    initializeGrid();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        renderGrid(window);

        

        // Mort / Vivant
        update();

        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}
