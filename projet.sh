#!/bin/bash

# Aide
if [ $# -lt 2 ]; then
    echo "Usage: $0 <data.csv> <histo|leaks> [option]"
    exit 1
fi

FICHIER="$1"
CMD="$2"

# 1. Compilation
echo "Compilation..."
(cd codeC && make)
if [ $? -ne 0 ]; then
    echo "Erreur compilation"
    exit 1
fi

EXECUTABLE="./codeC/prog"
DEBUT=$(date +%s%3N)

# 2. Exécution Histo
if [ "$CMD" = "histo" ]; then
    MODE="$3"
    if [ -z "$MODE" ]; then echo "Mode manquant (max/src)"; exit 1; fi
    
    # Nettoyage précédent
    rm -f histo.dat
    
    # Appel C
    $EXECUTABLE "$FICHIER" "histo" "$MODE"
    if [ ! -f "histo.dat" ]; then echo "Erreur C"; exit 1; fi

    # Gnuplot : Min et Max
    echo "Génération Graphique..."
    gnuplot -e "
        set terminal png size 1200,800;
        set output 'images/graph_${MODE}.png';
        set datafile separator ';';
        set title 'Histogramme Eau - ${MODE}';
        set style data histograms;
        set style fill solid;
        set xtics rotate by -45 scale 0;
        plot 'histo.dat' using 2:xtic(1) title 'Volume'
    "
    echo "Image générée dans images/graph_${MODE}.png"

# 3. Exécution Leaks
elif [ "$CMD" = "leaks" ]; then
    ID="$3"
    if [ -z "$ID" ]; then echo "ID manquant"; exit 1; fi
    
    $EXECUTABLE "$FICHIER" "leaks" "$ID"
    echo "Calcul terminé. Voir leaks.dat"
fi

FIN=$(date +%s%3N)
DUREE=$((FIN-DEBUT))
echo "Temps total : ${DUREE} ms"
