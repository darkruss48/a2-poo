/*
Ce test unitaire permet de vérifier le bon fonctionnement des cellules obstacles.
Une cellule obstacle est une cellule qui ne peut pas changer d'état (vivant ou mort).

Compilez ce programme avec cette commande (Linux) :
make

Executer ce programme compilé de cette manière :
./main reset test aleatoire 80 80 && ./main window test


######################
Ce test unitaire initialise une grille aléatoire contenant 1% de cellules obstacles.
*/


#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "inc/grille.h"
#include "inc/cellule.h"
#include "inc/fichier.h"
#include "inc/bouton.h"
#include "inc/slidebar.h"
#include "inc/initialiser.h"
#include "inc/celluleobstacle.h"

// Paramètres de la grille
float Grille::cellSize = 7;
const int gridWidth = 230;
const int gridHeight = 120;
const int buttonAreaHeight = 50; // Hauteur de la zone des boutons

sf::Font font;

const std::string a = "crampte";

// Button bouton_pause(10, 10, 100, 50, a);


#include <thread>
#include <chrono>

// Fonction pour afficher la grille dans la console
void afficher_grille_console(Grille& grille) {
    auto& grid = grille.get_grid();
    int longueur = grille.get_longueur();
    int largeur = grille.get_largeur();

    for (int y = 0; y < longueur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            Cellule* cellule = grid[y][x];
            if (CelluleObstacle* obstacle = dynamic_cast<CelluleObstacle*>(cellule)) {
                std::cout << (obstacle->get_state() ? "@ " : "# ");
            } else {
                std::cout << (cellule->get_state() ? "1 " : "0 ");
            }
        }
        std::cout << std::endl;
    }
}


void handleButtonClick(sf::RenderWindow& window, Button& bouton_pause) {
    static bool need_release = false; // Initialisation unique
    // bouton pressé seulement lorsqu'on clique
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !need_release) {
        need_release = true;

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (bouton_pause.isClicked(mousePos)) {
            bouton_pause.setPause(!bouton_pause.getPause());
        }
    } else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        need_release = false;
    }
}

void mode_console(int argc, char* argv[]) {
    std::cout << "Mode console activé" << std::endl;
    if (argc > 4) {
        int nb_iterations = std::stoi(argv[2]);
        std::string nom_fichier = argv[3];
        int delai_ms = std::stoi(argv[4]); // Délai en millisecondes

        // Charger la grille
        Grille* grille_ = Fichier::charger_grille(nom_fichier);
        if (grille_) {
            std::cout << "Grille chargée avec succès." << std::endl;

            for (int iteration = 1; iteration <= nb_iterations; ++iteration) {
                std::cout << "======== Itération " << iteration << "/" << nb_iterations << " ========" << std::endl;

                // Afficher la grille
                afficher_grille_console(*grille_);

                // Mettre à jour la grille pour la prochaine itération
                grille_->update();

                // Attendre le délai spécifié
                std::this_thread::sleep_for(std::chrono::milliseconds(delai_ms));
            }

            delete grille_;
        } else {
            std::cerr << "Erreur : impossible de charger la grille depuis le fichier " << nom_fichier << std::endl;
        }
    } else {
        std::cerr << "Usage : ./prog console <nombre_itérations> <nom_fichier> <délai_en_ms>" << std::endl;
    }
}


void _mode_console(int argc, char* argv[])

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
            std::cout << "Taille de la grid : " << grid[0][0]->get_grille().get_grid().size() << " x " << grid[0][0]->get_grille().get_grid().size() << std::endl;
            // Calculer la population x fois
            for (int i = 0; i < nb_iterations; ++i) {
                grille_->update();
            }
            // Sauvegarder
            Fichier::sauvegarder_grille(*grille_, nom_fichier);

            /*
            sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                grille_->render_grid(window);
            }
            */
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
            // nombre de cellules allumées
            int nb_alive = 0;
            int nb_eteinte = 0;
            for (int y = 0; y < grille_->get_longueur(); ++y) {
                for (int x = 0; x < grille_->get_largeur(); ++x) {
                    if (grid[y][x]->get_state() == 1) {
                        nb_alive++;
                    } else {
                        nb_eteinte++;
                    }
                }
            }
            std::cout << "Nombre de cellules allumées : " << nb_alive << std::endl;
            std::cout << "Nombre de cellules éteintes : " << nb_eteinte << std::endl;
            std::cout << "Taille de la grille : " << grid[0][0]->get_grille().get_grid().size() << " x " << grid[0][0]->get_grille().get_grid().size() << std::endl;
            std::cout << "Taille de la grille : " << grille_->get_largeur() << " x " << grille_->get_longueur() << std::endl;
            // Afficher

            const int minGridSize = 80;
            int windowWidth;
            int windowHeight;

            // Ajuster cGrille::ellSize si la grille est plus petite que 50x50
            if (grille_->get_largeur() < minGridSize || grille_->get_longueur() < minGridSize) {
                windowWidth = minGridSize * Grille::cellSize;
                windowHeight = minGridSize * Grille::cellSize + buttonAreaHeight;
                std::cout << "Ajustement de la taille des cellules ..." << std::endl;
                std::cout << "Largeur : " << grille_->get_largeur() << " Longueur : " << grille_->get_longueur() << std::endl;
                float scaleFactor = (float)minGridSize / std::max(grille_->get_largeur(), grille_->get_longueur());
                Grille::cellSize *= scaleFactor;
                std::cout << Grille::cellSize << std::endl;
            }
            else{
                windowWidth = grille_->get_largeur() * Grille::cellSize;
                windowHeight = grille_->get_longueur() * Grille::cellSize + buttonAreaHeight;

            }

            sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game of Life");
            
            // Mise à jour de la position du bouton
            int buttonYPosition = grille_->get_longueur() * Grille::cellSize + (buttonAreaHeight - 50) / 2; // 50 est la hauteur du bouton
            Button bouton_pause(10, buttonYPosition, 200, 50, a);

            // ... après la création du bouton pause
            int slideBarX = bouton_pause.getButtonShape().getPosition().x + bouton_pause.getButtonShape().getSize().x + 20; // 20 pixels d'écart
            int slideBarY = bouton_pause.getButtonShape().getPosition().y;
            int slideBarWidth = 300; // Un peu plus longue que le bouton
            int slideBarHeight = 30 ;// bouton_pause.getButtonShape().getSize().y;

            int minDelay = 0;    // Valeur minimale du délai
            int maxDelay = 1000;  // Valeur maximale du délai
            int initialDelay = 100; // Valeur initiale du délai

            SlideBar slideBar(slideBarX, slideBarY, slideBarWidth, slideBarHeight, minDelay, maxDelay, initialDelay);

            int delay = slideBar.getValue(); 
            static sf::Clock clock;

            while (window.isOpen()) {
                // attendre 30 secondes
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                handleButtonClick(window, bouton_pause);

                // Gérer les interactions avec la SlideBar
                slideBar.handleEvent(window, event);

                // Récupérer la valeur du délai depuis la SlideBar
                delay = slideBar.getValue();

                window.clear();

                // Mettre à jour la grille seulement si le jeu n'est pas en pause
                if (!bouton_pause.getPause()) {
                    if (clock.getElapsedTime().asMilliseconds() >= delay) {
                        grille_->update();
                        clock.restart();
                    }
                }

                // Rendre la grille
                grille_->render_grid(window);

                // Afficher le bouton en bas de la fenêtre
                bouton_pause.render(window);
                slideBar.render(window);

                window.display(); // Appel unique à window.display()
            }

            // Sauvegarder
            // Fichier::sauvegarder_grille(*grille_, nom_fichier);

            /*
            
            */
            // Libérer la mémoire allouée dynamiquement
            delete grille_;

        }
    }
}

void mode_reset(int argc, char* argv[])
{
    std::cout << "Mode reset activé" << std::endl;
    if (argc > 6) {
        std::string nom_fichier = argv[2];
        std::string quoi_generer = argv[3];
        int longueur = std::stoi(argv[4]);
        int largeur = std::stoi(argv[5]);
        std::string obstacle = argv[6];

        Grille grille(largeur, longueur);
        std::cout << "Initialisation de la grille..." << std::endl;

        Initialiser initialiser;

        if (quoi_generer == "glider") {
            if (longueur < 5 || largeur < 5) {
                std::cerr << "Les dimensions doivent être au minimum de 5x5" << std::endl;
                return;
            }
            initialiser.genererGlider(grille, 0, 0);
        } else if (quoi_generer == "canon") {
            if (longueur < 40 || largeur < 40) {
                std::cerr << "Les dimensions doivent être au minimum de 40x40" << std::endl;
                return;
            }
            initialiser.genererCanonGlider(grille, 10, 10);
        } else if (quoi_generer == "aleatoire") {
            initialiser.genererAleatoire(grille, 0.5); // Probabilité de 50%
        } else {
            std::cerr << "Type de génération non reconnu" << std::endl;
            return;
        }

        Fichier::sauvegarder_grille(grille, nom_fichier);
        std::cout << "Grille générée et sauvegardée avec succès !" << std::endl;

    } else {
        std::cerr << "Usage : ./prog reset <nom_fichier> <quoi_generer> <longueur> <largeur>" << std::endl;
    }
}
// {
//     std::cout << "Mode reset activé" << std::endl;
//     if (argc > 2) {
//         std::string nom_fichier = argv[2];
//         // Grille* grille_ = Fichier::charger_grille(nom_fichier);
//         Grille grille(gridWidth, gridHeight);
//         std::cout << "Initialisation de la grille ..." << std::endl;
//         auto& grid = grille.get_grid();
//         std::cout << grid.size() << std::endl;
//         std::cout << "Grille initialisée !" << std::endl;
//         std::cout << "Taille de la grille : " << grid[0][0].get_grille().get_grid().size() << " x " << grid[0][0].get_grille().get_grid().size() << std::endl;
//         // Reset                
//         Fichier::sauvegarder_grille(grille, nom_fichier);
//         std::cout << "Grille réinitialisée !" << std::endl;

//     }
// }

void mode_view(int argc, char* argv[])
{
    std::cout << "Mode view activé" << std::endl;
    if (argc > 2) {
        std::string nom_fichier = argv[2];
        // Charger la grille
        // Grille* grille_ = Fichier::charger_grille(nom_fichier);
        Grille* grille_ = new Grille(gridWidth, gridHeight);
        if (grille_) {
            std::cout << "Initialisation de la grille ..." << std::endl;
            auto& grid = grille_->get_grid();
            std::cout << grid.size() << std::endl;
            // Rendre la grille aléatoire, 1 cellule sur 2 allumée de manière random
            std::srand(std::time(nullptr));
            for (int y = 0; y < gridHeight; ++y) {
                for (int x = 0; x < gridWidth; ++x) {
                    if (std::rand() % 2 == 0) {
                        grid[y][x]->set_state(true);
                    } else {
                        grid[y][x]->set_state(false);
                    }
                }
            }
            std::cout << "Grille initialisée !" << std::endl;
            std::cout << "Taille de la grid : " << grid[0][0]->get_grille().get_grid().size() << " x " << grid[0][0]->get_grille().get_grid().size() << std::endl;
            // Calculer la population x fois
            // for (int i = 0; i < nb_iterations; ++i) {
            //     grille_->update();
            // }

            const int minGridSize = 50;
            int windowWidth = minGridSize * Grille::cellSize;
            int windowHeight = minGridSize * Grille::cellSize + buttonAreaHeight;

            // Ajuster Grille::cellSize si la grille est plus petite que 50x50
            if (grille_->get_largeur() < minGridSize || grille_->get_longueur() < minGridSize) {
                float scaleFactor = (float)minGridSize / std::max(grille_->get_largeur(), grille_->get_longueur());
                Grille::cellSize *= scaleFactor;
            }

            sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game of Life");
            // sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

            // sf::RenderWindow window;
            // window.create(sf::VideoMode(gridWidth * Grille::cellSize, gridHeight * Grille::cellSize + buttonAreaHeight), "Game of Life", sf::Style::Titlebar | sf::Style::Close);
            // Mise à jour de la position du bouton
            int buttonYPosition = gridHeight * Grille::cellSize + (buttonAreaHeight - 50) / 2; // 50 est la hauteur du bouton
            Button bouton_pause(10, buttonYPosition, 200, 50, a);

            // ... après la création du bouton pause
            int slideBarX = bouton_pause.getButtonShape().getPosition().x + bouton_pause.getButtonShape().getSize().x + 20; // 20 pixels d'écart
            int slideBarY = bouton_pause.getButtonShape().getPosition().y;
            int slideBarWidth = 300; // Un peu plus longue que le bouton
            int slideBarHeight = 30 ;// bouton_pause.getButtonShape().getSize().y;

            int minDelay = 0;    // Valeur minimale du délai
            int maxDelay = 1000;  // Valeur maximale du délai
            int initialDelay = 100; // Valeur initiale du délai

            SlideBar slideBar(slideBarX, slideBarY, slideBarWidth, slideBarHeight, minDelay, maxDelay, initialDelay);

            int delay = slideBar.getValue(); 
            static sf::Clock clock;

            while (window.isOpen()) {
                // attendre 30 ms
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                handleButtonClick(window, bouton_pause);

                // Gérer les interactions avec la SlideBar
                slideBar.handleEvent(window, event);

                // Récupérer la valeur du délai depuis la SlideBar
                delay = slideBar.getValue();

                window.clear();

                // Mettre à jour la grille seulement si le jeu n'est pas en pause
                if (!bouton_pause.getPause()) {
                    if (clock.getElapsedTime().asMilliseconds() >= delay) {
                        grille_->update();
                        clock.restart();
                    }
                }

                // Mettre à jour la grille seulement si le jeu n'est pas en pause
                if (!bouton_pause.getPause()) {
                    grille_->update();
                }

                // Rendre la grille
                grille_->render_grid(window);
                slideBar.render(window);

                // Afficher le bouton en bas de la fenêtre
                bouton_pause.render(window);

                window.display(); // Appel unique à window.display()
            }

            // Sauvegarder
            // Fichier::sauvegarder_grille(*grille_, nom_fichier);

            /*
            
            */
            // Libérer la mémoire allouée dynamiquement
            delete grille_;

        } else {
            std::cerr << "Erreur lors du chargement de la grille" << std::endl;
        }
    } else {
        std::cerr << "Not enough arguments provided after --console" << std::endl;
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
    // } else if (argc > 1 && std::string(argv[1]) == "view") {
    //     mode_view(argc, argv);
    } else {
        std::cerr << "Mode non reconnu" << std::endl;
    }

    return 0;
}