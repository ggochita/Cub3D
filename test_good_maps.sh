#!/bin/bash

# Couleurs pour une meilleure lisibilité
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}=== Test de toutes les cartes dans maps/good ====${NC}\n"

# Compiler le programme
make > /dev/null

# Vérifier si la compilation a réussi
if [ $? -ne 0 ]; then
    echo -e "${RED}Erreur de compilation. Impossible de continuer les tests.${NC}"
    exit 1
fi

# Initialiser les compteurs
success_count=0
failure_count=0
failed_maps=""

# Tester chaque carte
for map in maps/good/*; do
    # Ignorer les dossiers
    if [ -d "$map" ]; then
        continue
    fi
    
    # Exécuter le programme avec la carte et le tuer après 1 seconde
    # (puisque les cartes valides lancent le jeu et ne se terminent pas)
    timeout 1s ./cub3D "$map" > /dev/null 2>&1
    exit_code=$?
    
    # Le code 124 signifie que timeout a tué le processus, ce qui est bon signe
    # car cela signifie que le programme a démarré correctement
    if [ $exit_code -eq 124 ]; then
        echo -e "${GREEN}✓${NC} $map - Carte valide acceptée"
        success_count=$((success_count + 1))
    else
        # Exécuter à nouveau pour obtenir le message d'erreur
        output=$(./cub3D "$map" 2>&1)
        echo -e "${RED}✗${NC} $map - Carte valide rejetée: ${output}"
        failure_count=$((failure_count + 1))
        failed_maps="$failed_maps\n   - $map"
    fi
done

# Afficher le résumé
total=$((success_count + failure_count))
echo -e "\n${YELLOW}=== Résumé des tests ===${NC}"
echo -e "Cartes testées: ${YELLOW}$total${NC}"
echo -e "Cartes valides acceptées: ${GREEN}$success_count${NC}"
echo -e "Cartes valides rejetées: ${RED}$failure_count${NC}"

if [ $failure_count -eq 0 ]; then
    echo -e "\n${GREEN}Tous les tests ont réussi!${NC}"
else
    echo -e "\n${RED}Cartes problématiques:${failed_maps}${NC}"
fi 