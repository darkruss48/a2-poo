#include "grille.h"
#include "cellule.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "celluleobstacle.h"
#include <thread>
#include <ctime>
#include <cstdlib>
#include <iostream>

const int cellSize = 7;

Grille::Grille(int longueur, int largeur) : longueur(longueur), largeur(largeur){
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
    // Réserver de l'espace pour 'longueur' lignes
    this->largeur = largeur;
    this->longueur = longueur;
    grid.resize(longueur);
    for (int y = 0; y < longueur; ++y) {
        grid[y].resize(largeur);
        for (int x = 0; x < largeur; ++x) {
            grid[y][x] = new Cellule(x, y, false, this);
        }
    }
    // grid.reserve(longueur);
    // for (int y = 0; y < longueur; ++y) {
    //     std::vector<Cellule> row;
    //     row.reserve(largeur);
    //     for (int x = 0; x < largeur; ++x) {
    //         row.emplace_back(x, y, false, this);
    //     }
    //     grid.push_back(std::move(row));
    // }
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
    /*
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
    */    
}


Grille::~Grille() {
    //  for (int y = 0; y < longueur; ++y) {
         // for (int x = 0; x < largeur; ++x) {
             // delete grid[y][x];
         // }
    //  }
}


void Grille::update() {
    int num_threads = 16; // Nombre de threads
    int section_size = longueur / num_threads;
    std::vector<std::thread> threads;
    std::vector<std::vector<Cellule*>> new_grid(longueur, std::vector<Cellule*>(largeur));
    // deep copy de new_grid, afin d'éviter de travailler sur grid
    for (int y = 0; y < longueur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (CelluleObstacle* obstacle = dynamic_cast<CelluleObstacle*>(grid[y][x])) {
                new_grid[y][x] = new CelluleObstacle(*obstacle);
            } else {
                new_grid[y][x] = new Cellule(*grid[y][x]);
            }
        }
    }
    // fin deep copy
    for (int i = 0; i < num_threads; ++i) {
        int y_start = i * section_size;
        int y_end = (i == num_threads - 1) ? longueur : y_start + section_size;
        threads.emplace_back(&Grille::update_section, this, y_start, y_end, std::ref(new_grid));
    }

    for (auto& th : threads) {
        th.join();
    }

    grid = new_grid;
}

void Grille::update_section(int y_start, int y_end, std::vector<std::vector<Cellule*>>& new_grid) {
    for (int y = y_start; y < y_end; ++y) {
        for (int x = 0; x < largeur; ++x) {
            new_grid[y][x]->update_state(grid);
        }
    }
}

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
    for (int y = 0; y < longueur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            // verifier que la cellule est un obstacle
            if (CelluleObstacle* obstacle = dynamic_cast<CelluleObstacle*>(grid[y][x])) {
                cell.setPosition(x * cellSize, y * cellSize);
                if (grid[y][x]->get_state() == 1) {
                    cell.setFillColor(sf::Color::Green);
                } else {
                    cell.setFillColor(sf::Color::Red);
                }
                window.draw(cell);
            } else {
                if (grid[y][x]->get_state() == 1) {
                    cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(grid[y][x]->get_state() ? sf::Color::White : sf::Color::Black);
                window.draw(cell);
            }
            }
            // window.draw(cell);
            // if (grid[y][x]->get_state() == 1) {
            //     cell.setPosition(x * cellSize, y * cellSize);
            //     window.draw(cell);
            // }
        }
    }
}

std::vector<std::vector<Cellule*>>& Grille::get_grid()
{
    // std::cout << "Taille de la GRILLE : " << grid.size() << " x " << grid[0].size() << std::endl;
    return grid;
}