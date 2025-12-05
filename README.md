# Jeu de la vie – Projet POO C++

## Présentation

Ce projet implémente le **Jeu de la vie de Conway** en C++ dans une architecture entièrement orientée objet : classes `GameEngine`, `Grid`, `Cell`, hiérarchie polymorphe, et séparation logique / affichage.

Deux modes sont disponibles :
- **Mode console** : lecture/écriture de fichiers, affichage ASCII
- **Mode graphique** : interface graphique basée sur SFML 3 avec édition interactive

## Prérequis

### Système et Outils
- **Système** : Linux (Ubuntu/Debian recommandé)
- **Compilation** : `g++`, `cmake`, `ninja`, `git`
- **Bibliothèques de développement** : X11, OpenGL, audio (OpenAL, Vorbis/FLAC), FreeType, etc.
- **SFML 3** : compilé et installé localement dans le dossier utilisateur

## Installation et Compilation

### 1. Cloner ou récupérer le projet

```bash
git clone https://github.com/Vladimir-Maj/Jeu-de-la-vie.git
cd Jeu-de-la-vie
```

### 2. Installer les dépendances système (Ubuntu/Debian)

```bash
sudo apt update && sudo apt upgrade -y

sudo apt install -y build-essential cmake ninja-build pkg-config git \
  libfreetype6-dev libx11-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev \
  libxrender-dev libudev-dev libgl1-mesa-dev libdrm-dev libgbm-dev \
  libopenal-dev libflac-dev libvorbis-dev libogg-dev libvorbisenc2 libvorbisfile3

sudo ldconfig
```

### 3. Compiler et installer SFML 3 localement

```bash
cmake -S SFML -B SFML/build -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=$HOME/.local/sfml3

cmake --build SFML/build
cmake --install SFML/build
```

### 4. Configurer et compiler le projet

```bash
cmake -S . -B build -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_PREFIX_PATH=$HOME/.local/sfml3

cmake --build build
```

L'exécutable est généré dans `build/JeuDeLaVie`.

## Utilisation

### Accéder à l'exécutable

```bash
cd build
```

### Syntaxe générale

```bash
./JeuDeLaVie [SOURCE] [OPTIONS] [AFFICHAGE] [MODE] [SIMULATION] [SPÉCIAL]
```

### Paramètres

| Catégorie | Flag | Argument | Description |
|-----------|------|----------|-------------|
| **SOURCE** | `-lc` | `<chemin>` | Charger une configuration existante |
| | `-mc` | `<chemin>` | Créer une nouvelle configuration |
| **OPTIONS** | `-w` | `<nombre>` | Largeur de la grille (requis avec `-mc`) |
| | `-h` | `<nombre>` | Hauteur de la grille (requis avec `-mc`) |
| | `--empty` | - | Grille vierge (au lieu d'aléatoire avec `-mc`) |
| **AFFICHAGE** | `-g` | - | Mode graphique SFML (sinon console) |
| **MODE** | `-e` | - | Mode édition interactif |
| **SIMULATION** | `-ic` | `<n>` | Nombre d'itérations (0 = infini) |
| | `-it` | `<ms>` | Délai entre générations en ms (défaut : 250) |
| **SPÉCIAL** | `--toric` | - | Bords rebouclés (mode torique) |
| | `--help` | - | Affiche l'aide |

## Exemples d'Utilisation

### Affichage console simple

```bash
./JeuDeLaVie -lc ../data/config/realConfig.txt -ic 10
```
Lance 10 générations de la config "realConfig" en mode console.

### Affichage graphique SFML

```bash
./JeuDeLaVie -lc ../data/config/realConfig.txt -g -ic 50 -it 200
```
Lance 50 générations en mode graphique SFML, avec 200ms entre chaque génération.

### Création et édition d'une nouvelle grille

```bash
./JeuDeLaVie -mc ../data/config/ma_config.txt -w 40 -h 40 --empty -g -e
```
Crée une grille vide 40×40, l'ouvre en édition interactive graphique (clic souris pour toggler les cellules).

### Mode torique avec graphique

```bash
./JeuDeLaVie -lc ../data/config/glider.txt -g -ic 50 -it 200 --toric
```
Lance le motif "glider" en mode torique (bords rebouclés), 50 générations, SFML.

## Fichiers de Configuration

Des exemples de configurations sont fournis dans `data/config/` :

- **realConfig.txt** : configuration réelle de démarrage
- **glider.txt** : motif classique "glider" du Jeu de la vie
- **config.txt** : configuration test simple (3×3)
- **Fichiers de test** : columnErrorConfig.txt, rowErrorConfig.txt, valueErrorConfig.txt (pour tester la robustesse)

Ces fichiers permettent de tester rapidement la simulation, le mode torique, et la robustesse de la lecture de fichiers.

## Tests Unitaires

Le projet inclut des tests unitaires permettant de vérifier automatiquement :

- La lecture correcte des fichiers de configuration
- L'évolution de motifs classiques (glider, grilles stables, etc.)
- Les cas limites (grille vide, grille stable, etc.)
- La cohérence du moteur de simulation

## Architecture

### Classes principales

- **`cmd`** : Parseur des arguments CLI
- **`GameEngine`** : Orchestrateur principal (gère la Grid, l'affichage, la simulation)
- **`Grid`** : Grille 2D contenant les cellules, calcul des voisins
- **`Cell`** (abstraite) : Classe de base polymorphe
  - **`CellSimple`** : Cellule éditable classique
  - **`CellObstacle`** : Cellule obstacle (non éditable)
- **`Display`** (abstraite) : Interface d'affichage (pattern Strategy)
  - **`Console`** : Rendu ASCII
  - **`Graphic`** : Rendu SFML 3
- **`FileManager`** : Gestion I/O (chargement/sauvegarde)

### Patterns et Principes POO

- **Strategy Pattern** : Hiérarchie Display (Console/Graphic interchangeables)
- **Polymorphisme** : Cell abstraite, Display abstraite
- **Composition** : GameEngine contient Grid, Display, FileManager
- **RAII** : Gestion mémoire via `std::unique_ptr`
- **Encapsulation** : Membres privés/protégés, accesseurs publics

## Documentation

Pour une documentation détaillée, consultez :
- `Diagrammes/diagramme_classes.md` : Diagramme UML complet
- `Diagrammes/diagramme_sequence.md` : Flux de séquence
- `Diagrammes/diagramme_activite.md` : Flux d'activité
- `Diagrammes/diagramme_cas_utilisation.md` : Cas d'utilisation
