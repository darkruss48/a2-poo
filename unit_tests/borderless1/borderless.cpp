/*
Ce test unitaire permet de vérifier la nature "borderless" (en français - "sans bordures") du jeu de la vie.
Autrement dit, lorsqu'une cellule se trouve tout en bas à gauche, elle va rentrer en compte lors de la
vérification des cellules adjacentes tout en haut à droite.
Cela est permis par la fonction check_coin qui vérifie toutes les cellules en bordure (4 coins + bordures).
Ce qui est décrit comme étant une case "problèmatique" est en réalité une case se trouvant à l'autre bout 
de la grille. Les cases dites "non problèmatiques" sont celles qui sont adjacentes à la case en question.

Compiler ce fichier avec cette commande (Linux) :
g++ borderless.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system

('prog' peut être changé par le nom de l'executable souhaité)


######################
Ce test unitaire sur la grille torique initialise une grille complètement vide.

"
*/



#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

const int cellSize = 10;
const int gridWidth = 40;
const int gridHeight = 40;

std::vector<std::vector<int>> grid(gridWidth, std::vector<int>(gridHeight));

void initializeGrid() {
    std::srand(std::time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = 0; // 1 en vie, 0 mort
        }
    }
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
        update();

        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}
