// main.cpp
#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "inc/grille.h"
#include "inc/cellule.h"
#include "inc/fichier.h"

// Paramètres de la grille
const int cellSize = 5;
const int gridWidth = 200;
const int gridHeight = 200;


void mode_console(int argc, char* argv[])
{
    std::cout << "Mode console activé" << std::endl;
    if (argc > 3) {
        int nb_iterations = std::stoi(argv[2]);
        std::string nom_fichier = argv[3];
        // Charger la grille
        Grille* grille_ = Fichier::charger_grille(nom_fichier);
        if (grille_) {
            std::cout << "Initialisation de la grille ..." << std::endl;
            auto& grid = grille_->get_grid();
            std::cout << grid.size() << std::endl;
            std::cout << "Grille initialisée !" << std::endl;
            std::cout << "Taille de la grid : " << grid[0][0].get_grille().get_grid().size() << " x " << grid[0][0].get_grille().get_grid().size() << std::endl;
            // Calculer la population x fois
            for (int i = 0; i < nb_iterations; ++i) {
                grille_->update();
            }
            // Sauvegarder
            Fichier::sauvegarder_grille(*grille_, nom_fichier);

            sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                grille_->render_grid(window);
            }
            
            // Libérer la mémoire allouée dynamiquement
            delete grille_;

        } else {
            std::cerr << "Erreur lors du chargement de la grille" << std::endl;
        }
    } else {
        std::cerr << "Not enough arguments provided after --console" << std::endl;
    }
}

void mode_window(int argc, char* argv[])
{
    std::cout << "Mode graphique activé" << std::endl;
    if (argc > 2) {
        std::string nom_fichier = argv[2];
        Grille* grille_ = Fichier::charger_grille(nom_fichier);
        if (grille_) {
            std::cout << "Initialisation de la grille ..." << std::endl;
            auto& grid = grille_->get_grid();
            std::cout << grid.size() << std::endl;
            std::cout << "Grille initialisée !" << std::endl;
            std::cout << "Taille de la grille : " << grid[0][0].get_grille().get_grid().size() << " x " << grid[0][0].get_grille().get_grid().size() << std::endl;
            // Afficher

            sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                grille_->render_grid(window);
            }
            
            // Libérer la mémoire allouée dynamiquement
            delete grille_;

        }
    }
}

void mode_reset(int argc, char* argv[])
{
    std::cout << "Mode reset activé" << std::endl;
    if (argc > 2) {
        std::string nom_fichier = argv[2];
        // Grille* grille_ = Fichier::charger_grille(nom_fichier);
        Grille grille(gridWidth, gridHeight);
        std::cout << "Initialisation de la grille ..." << std::endl;
        auto& grid = grille.get_grid();
        std::cout << grid.size() << std::endl;
        std::cout << "Grille initialisée !" << std::endl;
        std::cout << "Taille de la grille : " << grid[0][0].get_grille().get_grid().size() << " x " << grid[0][0].get_grille().get_grid().size() << std::endl;
        // Reset                
        Fichier::sauvegarder_grille(grille, nom_fichier);
        std::cout << "Grille réinitialisée !" << std::endl;

    }
}

int main(int argc, char* argv[]) {
    // Grille grille(gridWidth, gridHeight);
    // Sauvegarder la grille
    // Fichier::sauvegarder_grille(grille, "apagnan");
    // Vérifier si le mode console ("--console") est activé
    if (argc > 1 && std::string(argv[1]) == "console") {
        mode_console(argc, argv);
    } else if (argc > 1 && std::string(argv[1]) == "window") {
        mode_window(argc, argv);
    } else if (argc > 1 && std::string(argv[1]) == "reset") {
        mode_reset(argc, argv);
    }

    return 0;
}