# Projet Game Of Life

## Introduction
Ce dépôt est une adaptation du Jeu de la Vie par John Conway en utilisant la bibliothèque graphique SFML.

## Table des matières
1. [Installation](#installation)
2. [Usage](#usage)
3. [Fonctionnalités](#fonctionnalités)
4. [Technologies utilisées](#technologies-utilisées)
5. [Licence](#licence)

## Installation

### Prérequis
- **Environnement Linux**
- **clang++** (ou tout autre compilateur C++)
- **SFML**

### Étapes
1. Clonez le dépôt :
   ```bash
   git clone https://github.com/darkruss48/a2-poo.git
   cd a2-poo
   ```
2. Compilez le programme avec le makefile :
   ```bash
   #! Utiliser make sur Linux
   make
   ```
3. Exécutez le programme :
   ```bash
   #! Voir la section pour lancer l'exécutable compilé
   ./main
   ```

## Usage
Cette adaptation du Jeu de la Vie possède 3 modes.
- Le mode console, affichant l'évolution des populations dans une console
- Le mode window, affichant l'évolution des populations dans une fenêtre graphique
- Le mode reset, permettant la génération de grille.

### Mode console

Pour lancer le mode console, exécuter cette commande :
```bash
./main console <nombre_itérations> <nom_fichier> <délai>
```

Le délai correspond au temps d'attente entre deux calculs de populations.


### Mode window

Pour lancer le mode fenetré, exécuter cette commande :
```bash
./main console <nom_fichier>
```

Sur la fenêtre d'exécution vous trouverez un bouton pause ainsi qu'une barre permettant de changer la vitesse d'exécution du programme.


### Mode reset

Pour lancer le mode reset, exécuter cette commande :
```bash
./main reset <nom_fichier> <modèle> <longueur> <largeur>
```
Il existe 3 modèles :
- **Planeur** (glider) : génère un planeur se dirigeant en bas a droite.
- **Générateur de planeur** (canon) :génère une forme générant un planeur toutes les 30 itérations.
- **Aléatoire** (aleatoire) : génère une grille aléatoire dans les dimensions spécifié.

Attention ! Générer unr grille avec un nom crééra un fichier avec ce nom, si un fichier avec ce nom existe il sera remplacé !


## Tests unitaires

Les tests unitaires sont décrits dans le fichier PDF.

## Fonctionnalités
POO en C++ : Utilise la Programmation Orientée Objet.
Cellules obstacles : supporte les cellules obstacles, ne changeant jamais d'état.
Fenêtre graphique : utilise SFML pour simuler un environnement utilisateur afin de mieux visualiser les populations.

## Licence
Ce projet est sous licence MIT.
