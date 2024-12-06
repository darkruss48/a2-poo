#include <vector>
#pragma once

class Grille;

class Cellule
{
    private:
        int x;
        int y;
        bool state;
        std::vector<Cellule*> check_coin();
        Grille* grille;
    
    public:
        // Constructeur
        Cellule(int x, int y, bool state, Grille* grid);public:

        virtual ~Cellule() = default;
        virtual void update_state(const std::vector<std::vector<Cellule*>>& grid);
        int get_state() const;
        void set_state(bool state);
        Grille get_grille();
};