#pragma once
#include "grille.h"
#include <string>
#include <memory>

class Fichier {
public:
    static void sauvegarder_grille(Grille& grille, const std::string& nom_fichier);
    static Grille* charger_grille(const std::string& nom_fichier);
};