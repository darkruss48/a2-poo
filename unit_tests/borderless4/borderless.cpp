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
Ce test unitaire sur la grille torique initialise une grille avec des "toupies" sur les bordures.

"
*/



#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 35;

std::vector<std::vector<int>> grid(gridWidth, std::vector<int>(gridHeight));

void initializeGrid() {
    std::srand(std::time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = 0; // 1 en vie, 0 mort
        }
    }
    // Toupie en haut au milieu
    grid[gridWidth / 2][0] = 1;
    grid[gridWidth / 2 + 1][0] = 1;
    grid[gridWidth / 2 + 2][0] = 1;

    grid[0][22] = 1;
    grid[0][23] = 1;
    grid[0][24] = 1;

    grid[gridWidth / 2][gridHeight / 2] = 1;
    grid[gridWidth / 2][gridHeight / 2 + 1] = 1;
    grid[gridWidth / 2][gridHeight / 2 + 2] = 1;
}

std::vector<int> check_coin(int x, int y)
{
    std::vector<int> voisins;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0)
                continue;
            int nx = (x + i + gridWidth) % gridWidth;
            int ny = (y + j + gridHeight) % gridHeight;
            voisins.push_back(grid[nx][ny]);
        }
    }
    return voisins;
}

void update()
{    
    std::vector<std::vector<int>> grid_ = grid;
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            std::vector<int> voisins = check_coin(x, y);
            int aliveNeighbors = std::count(voisins.begin(), voisins.end(), 1);

            if (grid[x][y] == 1) {
                if (aliveNeighbors < 2 || aliveNeighbors > 3)
                    grid_[x][y] = 0; // Meurt
            } else {
                if (aliveNeighbors == 3)
                    grid_[x][y] = 1; // Naît
            }
        }
    }
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

        sf::sleep(sf::milliseconds(1000));
    }

    return 0;
}
