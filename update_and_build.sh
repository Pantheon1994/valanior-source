#!/bin/bash

# Chemins vers les répertoires
VALANIOR_SOURCE_DIR="/valanior-source"
DBC_DIR="/azeroth-server/bin/dbc"
BUILD_DIR="$VALANIOR_SOURCE_DIR/build"
INSTALL_PREFIX_DIR="/azeroth-server"

# Fonction pour afficher le répertoire courant et lister les fichiers
function list_files {
    echo "Current directory: $(pwd)"
    echo "Listing files:"
    ls -la
}

# Mettre à jour valanior-source
echo "Updating valanior-source..."
cd $VALANIOR_SOURCE_DIR || exit
list_files
git pull origin main

# Mettre à jour dbc
echo "Updating dbc..."
cd $DBC_DIR || exit
list_files
git pull origin master

# Installer les dépendances
echo "Installing dependencies..."
sudo apt update
sudo apt install -y cmake make gcc g++ clang clang++ libmariadbclient-dev libssl-dev libbz2-dev libreadline-dev libncurses-dev libboost-all-dev

# Créer le répertoire de build
echo "Creating build directory..."
mkdir -p $BUILD_DIR
cd $BUILD_DIR || exit
list_files

# Configurer le projet avec CMake
echo "Running CMake..."
cmake ../ -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX_DIR -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DWITH_WARNINGS=1 -DTOOLS_BUILD=all -DSCRIPTS=static -DMODULES=static
list_files

# Compiler le projet
echo "Building Valanior Source..."
cmake --build . -- -j $(nproc)
make install
list_files

echo "Done!"