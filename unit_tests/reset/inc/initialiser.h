#pragma
#include "grille.h"

class Initialiser {
public:
    Initialiser();
    void genererGlider(Grille& grille, int x, int y);
    void genererCanonGlider(Grille& grille, int x, int y);
    void genererAleatoire(Grille& grille, double probabilite);
};