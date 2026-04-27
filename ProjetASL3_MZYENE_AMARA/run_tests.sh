#!/bin/bash

# Script pour exécuter tous les tests .tpc avec ./bin/tpcc
# Usage : ./run_tests.sh

set -u

EXEC="./bin/tpcc"
if [ ! -x "$EXEC" ]; then
    echo "Erreur : exécutable introuvable ou non exécutable : $EXEC" >&2
    echo "Compilez d'abord avec 'make'." >&2
    exit 1
fi

mapfile -t TEST_FILES < <(find test -type f -name '*.tpc' | sort)
if [ ${#TEST_FILES[@]} -eq 0 ]; then
    echo "Aucun fichier .tpc trouvé dans le dossier test/." >&2
    exit 1
fi

passed=0
failed=0

for test_file in "${TEST_FILES[@]}"; do
    printf "%-70s" "$test_file"
    if "$EXEC" < "$test_file" > /dev/null 2>&1; then
        echo "✅  OK"
        passed=$((passed + 1))
    else
        echo "❌  ERREUR"
        failed=$((failed + 1))
    fi
done

printf "\nRésultat : %d réussis, %d échoués, %d total\n" "$passed" "$failed" "$((passed + failed))"

if [ "$failed" -ne 0 ]; then
    exit 1
fi
