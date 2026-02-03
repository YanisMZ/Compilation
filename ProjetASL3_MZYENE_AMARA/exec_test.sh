#!/bin/bash

# Dossiers contenant les tests
GOOD_TESTS_DIR="test/good"
SYN_ERR_TESTS_DIR="test/syn-err"

# Fichier de rapport
REPORT_FILE="rapport_final.txt"

# Commande du programme à tester
TPCAS_EXEC="./bin/tpcas"

# Initialiser le rapport
echo "Rapport des tests - $(date)" > $REPORT_FILE
echo "-----------------------------------------" >> $REPORT_FILE

# Tests réussis
echo "Tests GOOD:" >> $REPORT_FILE
good_success=0
good_total=0

for test_file in $GOOD_TESTS_DIR/*; do
    good_total=$((good_total + 1))
    $TPCAS_EXEC < "$test_file" > /dev/null 2>&1
    result=$?
    if [ $result -eq 0 ]; then
        echo "✅ $test_file : Réussi" >> $REPORT_FILE
        good_success=$((good_success + 1))
    else
        echo "❌ $test_file : Échoué (Code de retour: $result)" >> $REPORT_FILE
    fi
done

echo "-----------------------------------------" >> $REPORT_FILE

# Tests échoués
echo "Tests SYN-ERR:" >> $REPORT_FILE
syn_err_success=0
syn_err_total=0

for test_file in $SYN_ERR_TESTS_DIR/*; do
    syn_err_total=$((syn_err_total + 1))
    $TPCAS_EXEC < "$test_file" > /dev/null 2>&1
    result=$?
    if [ $result -ne 0 ]; then
        echo "✅ $test_file : Réussi (Erreur détectée)" >> $REPORT_FILE
        syn_err_success=$((syn_err_success + 1))
    else
        echo "❌ $test_file : Échoué (Code de retour: $result)" >> $REPORT_FILE
    fi
done

echo "-----------------------------------------" >> $REPORT_FILE

# Résumé des résultats
echo "Résumé:" >> $REPORT_FILE
echo "Tests GOOD: $good_success / $good_total réussis" >> $REPORT_FILE
echo "Tests SYN-ERR: $syn_err_success / $syn_err_total réussis" >> $REPORT_FILE

# Afficher le rapport
cat $REPORT_FILE

