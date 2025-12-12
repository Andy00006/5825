#!/usr/bin/env bash
set -euo pipefail

USAGE="Usage: $0 <fichier.csv> histo <max|src|real>  OR  $0 <fichier.csv> leaks \"FactoryID\""

if [ $# -lt 2 ]; then
  echo "ERREUR: arguments insuffisants."
  echo "$USAGE"
  exit 1
fi

CSV="$1"
ACTION="$2"

START_MS=$(date +%s%3N)

if [ ! -f "$CSV" ]; then
  echo "ERREUR: fichier $CSV introuvable."
  exit 2
fi

# compile si nécessaire
if [ ! -x build/eau_analyse ]; then
  echo "Compilation via make..."
  if ! make; then
    echo "ERREUR: compilation échouée."
    exit 3
  fi
fi

case "$ACTION" in
  histo)
    if [ $# -ne 3 ]; then
      echo "ERREUR: histo requiert un paramètre : max|src|real"
      echo "$USAGE"
      exit 4
    fi
    MODE="$3"
    if [[ "$MODE" != "max" && "$MODE" != "src" && "$MODE" != "real" ]]; then
      echo "ERREUR: mode inconnu $MODE"
      exit 5
    fi
    ./build/eau_analyse histo "$CSV" "$MODE"
    DAT="vol_${MODE}.dat"
    if [ -f "$DAT" ] && command -v gnuplot >/dev/null 2>&1; then
      cat > plot_${MODE}.plt <<EOF
set terminal pngcairo size 1200,600 enhanced
set datafile separator ","
set title "Histogramme usines - ${MODE}"
set ylabel "volume (k.m3.year-1)"
set xlabel "usine (id)"
set style data histogram
set style fill solid 1.00 border -1
set boxwidth 0.9
set output "vol_${MODE}.png"
plot "${DAT}" using 2:xtic(1) title "${MODE}"
EOF
      gnuplot plot_${MODE}.plt 2>/dev/null || true
      echo "PNG (simple) : vol_${MODE}.png"
    else
      echo "Fichier de données : $DAT (gnupot absent ou fichier manquant)"
    fi
    ;;
  leaks)
    if [ $# -ne 3 ]; then
      echo "ERREUR: leaks requiert l'identifiant d'usine (respect de la casse)."
      echo "$USAGE"
      exit 6
    fi
    FAC="$3"
    ./build/eau_analyse leaks "$CSV" "$FAC"
    ;;
  *)
    echo "ERREUR: action inconnue $ACTION"
    echo "$USAGE"
    exit 7
    ;;
esac

END_MS=$(date +%s%3N)
DURATION_MS=$((END_MS - START_MS))
echo "Durée totale : ${DURATION_MS} ms"
