# Jeu de la vie – Projet POO C++

## Présentation
Implémentation du Jeu de la vie de Conway en C++ avec une architecture orientée objet : `GameEngine`, `Grid`, `Cell` (et dérivées), séparation logique/affichage, et deux modes d’IHM : console (I/O fichiers) et graphique SFML 3.

## Prérequis
- Système : Linux (Ubuntu/Debian recommandé)
- Outils : `g++`, `cmake`, `ninja`, `git`
- Dépendances pour SFML 3 : X11, OpenGL, audio (OpenAL, Vorbis/FLAC), FreeType, etc.
- SFML 3 compilé et installé localement (ex. `$HOME/.local/sfml3`)

### Installation rapide des paquets (Ubuntu/Ark)
```bash
sudo apt update && sudo apt install -y \
  build-essential cmake ninja-build pkg-config git \
  libfreetype6-dev libx11-dev libxrandr-dev libxcursor-dev libxi-dev libxinerama-dev libxrender-dev libudev-dev \
  libgl1-mesa-dev libdrm-dev libgbm-dev \
  libopenal-dev libflac-dev libvorbis-dev libogg-dev libvorbisenc2 libvorbisfile3
```

## Compilation
1) Se placer à la racine du projet
```bash
cd /media/sf_UbuntuShare/VSCode/ProjetPOO/Jeu-de-la-vie
```
2) Construire et installer SFML 3 (si nécessaire)
```bash
cmake -S SFML -B SFML/build -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=$HOME/.local/sfml3

cmake --build SFML/build
cmake --install SFML/build
```
3) Configurer et compiler le projet
```bash
cmake -S . -B build -GNinja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_PREFIX_PATH=$HOME/.local/sfml3

cmake --build build
```
L’exécutable est généré dans `build/JeuDeLaVie`.

## Utilisation
Se placer dans `build/` :
```bash
cd build
```
Syntaxe générale :
```bash
./JeuDeLaVie [SOURCE] [OPTIONS] [AFFICHAGE] [MODE] [SIMULATION] [SPÉCIAL]
```
- SOURCE : `-lc <chemin>` (load) ou `-mc <chemin>` (make)
- OPTIONS : `-w <largeur>`, `-h <hauteur>`, `--empty` (grille vide)
- AFFICHAGE : `-g` pour SFML (sinon console)
- MODE : `-e` édition interactive
- SIMULATION : `-ic <n>` itérations (0 = infini), `-it <ms>` délai (défaut 250ms)
- SPÉCIAL : `--toric` (bords rebouclés), `--help` (aide)

## Exemples
- Console, 10 générations :
```bash
./JeuDeLaVie -lc ../data/config/realConfig.txt -ic 10
```
- Graphique SFML, 50 générations, 200ms :
```bash
./JeuDeLaVie -lc ../data/config/realConfig.txt -g -ic 50 -it 200
```
- Création + édition d’une grille vide 40×40 :
```bash
./JeuDeLaVie -mc ../data/config/ma_config.txt -w 40 -h 40 --empty -g -e
```

## Fichiers de configuration
Exemples dans `data/config/` : `realConfig.txt`, `glider.txt`, `config.txt`, et des fichiers de test d’erreurs (lignes/colonnes/valeurs). Utile pour tester lecture, mode torique et robustesse.

## Tests unitaires
Le projet inclut des tests pour vérifier la lecture des fichiers, l’évolution de motifs (glider, grilles stables), les cas limites (grille vide), et la cohérence du moteur de simulation.
