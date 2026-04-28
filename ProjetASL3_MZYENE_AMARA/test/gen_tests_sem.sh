#!/bin/bash

# ============================================================
#  Tests sémantiques complémentaires — compilateur tpc
#  Dossiers : test_good2/  (doivent passer, exit 0)
#             test_bad/    (doivent échouer, exit != 0)
# ============================================================

mkdir -p test_good2 test_bad

# ────────────────────────────────────────────────────────────
# BONS PROGRAMMES  (doivent compiler sans erreur)
# ────────────────────────────────────────────────────────────

# ── good_char01 : variable char locale ──────────────────────
cat > test_good2/good_char01.tpc << 'EOF'
int main(void) {
    char c;
    c = 'a';
    return 0;
}
EOF

# ── good_char02 : char affecté à int (implicite, sans warning) ──
cat > test_good2/good_char02.tpc << 'EOF'
int main(void) {
    int n;
    char c;
    c = 'z';
    n = c;
    return 0;
}
EOF

# ── good_char03 : char dans expression arithmétique ─────────
cat > test_good2/good_char03.tpc << 'EOF'
int main(void) {
    char c;
    int n;
    c = 'a';
    n = c + 1;
    return 0;
}
EOF

# ── good_char04 : return 'a' dans fonction int ──────────────
cat > test_good2/good_char04.tpc << 'EOF'
int f(void) {
    return 'a';
}

int main(void) {
    int r;
    r = f();
    return 0;
}
EOF

# ── good_char05 : char global ────────────────────────────────
cat > test_good2/good_char05.tpc << 'EOF'
char g;

int main(void) {
    g = 'x';
    return 0;
}
EOF

# ── good_char06 : paramètre char ────────────────────────────
cat > test_good2/good_char06.tpc << 'EOF'
int f(char c) {
    return c;
}

int main(void) {
    int r;
    r = f('b');
    return 0;
}
EOF

# ── good_io01 : appel getchar ────────────────────────────────
cat > test_good2/good_io01.tpc << 'EOF'
int main(void) {
    int c;
    c = getchar();
    return 0;
}
EOF

# ── good_io02 : appel getint ────────────────────────────────
cat > test_good2/good_io02.tpc << 'EOF'
int main(void) {
    int n;
    n = getint();
    return 0;
}
EOF

# ── good_io03 : appel putchar ────────────────────────────────
cat > test_good2/good_io03.tpc << 'EOF'
int main(void) {
    putchar('A');
    return 0;
}
EOF

# ── good_io04 : appel putint ────────────────────────────────
cat > test_good2/good_io04.tpc << 'EOF'
int main(void) {
    putint(42);
    return 0;
}
EOF

# ── good_scope01 : param et var globale même nom (autorisé) ──
cat > test_good2/good_scope01.tpc << 'EOF'
int x;

int f(int x) {
    return x;
}

int main(void) {
    int r;
    r = f(1);
    return 0;
}
EOF

# ── good_scope02 : struct tag == nom de variable (autorisé) ──
cat > test_good2/good_scope02.tpc << 'EOF'
struct node {
    int val;
};

int node;

int main(void) {
    struct node x;
    node = 3;
    return 0;
}
EOF

# ── good_scope03 : struct tag == nom de fonction (autorisé) ──
cat > test_good2/good_scope03.tpc << 'EOF'
struct foo {
    int a;
};

int foo(void) {
    return 0;
}

int main(void) {
    struct foo x;
    foo();
    return 0;
}
EOF

# ── good_void01 : void f sans return ────────────────────────
cat > test_good2/good_void01.tpc << 'EOF'
void f(void) {
    int x;
    x = 1;
}

int main(void) {
    f();
    return 0;
}
EOF

# ── good_nested01 : if imbriqués ────────────────────────────
cat > test_good2/good_nested01.tpc << 'EOF'
int main(void) {
    int a, b;
    a = 1;
    b = 2;
    if (a) {
        if (b) {
            a = 0;
        }
    }
    return 0;
}
EOF

# ── good_nested02 : while dans if ───────────────────────────
cat > test_good2/good_nested02.tpc << 'EOF'
int main(void) {
    int i;
    i = 0;
    if (i) {
        while (i) {
            i = i + 1;
        }
    }
    return 0;
}
EOF

# ── good_multi_struct01 : deux structs différentes ───────────
cat > test_good2/good_multi_struct01.tpc << 'EOF'
struct Point {
    int x;
    int y;
};

struct Color {
    int r;
    int g;
};

int main(void) {
    struct Point p;
    struct Color c;
    p.x = 0;
    c.r = 255;
    return 0;
}
EOF

# ── good_multi_struct02 : struct avec champ char ─────────────
cat > test_good2/good_multi_struct02.tpc << 'EOF'
struct S {
    int a;
    char b;
};

int main(void) {
    struct S x;
    x.a = 1;
    x.b = 'z';
    return 0;
}
EOF

# ── good_expr01 : opérateurs relationnels ───────────────────
cat > test_good2/good_expr01.tpc << 'EOF'
int main(void) {
    int a, b, c;
    a = 1;
    b = 2;
    c = a < b;
    return 0;
}
EOF

# ── good_expr02 : opérateurs logiques ───────────────────────
cat > test_good2/good_expr02.tpc << 'EOF'
int main(void) {
    int a, b, c;
    a = 1;
    b = 0;
    c = a + b == 1;
    return 0;
}
EOF

# ── good_multi_return01 : plusieurs return dans branches ─────
cat > test_good2/good_multi_return01.tpc << 'EOF'
int sign(int n) {
    if (n) {
        return 1;
    }
    return 0;
}

int main(void) {
    int r;
    r = sign(5);
    return 0;
}
EOF

# ────────────────────────────────────────────────────────────
# MAUVAIS PROGRAMMES  (doivent provoquer une erreur sémantique)
# ────────────────────────────────────────────────────────────

# ── bad01 : variable non déclarée ───────────────────────────
cat > test_bad/bad01.tpc << 'EOF'
int main(void) {
    x = 5;
    return 0;
}
EOF

# ── bad02 : fonction non déclarée ───────────────────────────
cat > test_bad/bad02.tpc << 'EOF'
int main(void) {
    int r;
    r = f(1);
    return 0;
}
EOF

# ── bad03 : double déclaration variable globale ─────────────
cat > test_bad/bad03.tpc << 'EOF'
int x;
int x;

int main(void) {
    return 0;
}
EOF

# ── bad04 : double déclaration variable locale ──────────────
cat > test_bad/bad04.tpc << 'EOF'
int main(void) {
    int a;
    int a;
    return 0;
}
EOF

# ── bad05 : variable locale et paramètre même nom ───────────
cat > test_bad/bad05.tpc << 'EOF'
int f(int x) {
    int x;
    return x;
}

int main(void) {
    return f(1);
}
EOF

# ── bad06 : deux fonctions avec le même nom ─────────────────
cat > test_bad/bad06.tpc << 'EOF'
int f(void) {
    return 1;
}

int f(void) {
    return 2;
}

int main(void) {
    return 0;
}
EOF

# ── bad07 : variable globale et fonction même nom ───────────
cat > test_bad/bad07.tpc << 'EOF'
int f;

int f(void) {
    return 1;
}

int main(void) {
    return 0;
}
EOF

# ── bad08 : appel void dans une expression ──────────────────
cat > test_bad/bad08.tpc << 'EOF'
void f(void) {
    return;
}

int main(void) {
    int x;
    x = f();
    return 0;
}
EOF

# ── bad09 : trop d'arguments ────────────────────────────────
cat > test_bad/bad09.tpc << 'EOF'
int add(int a, int b) {
    return a;
}

int main(void) {
    int r;
    r = add(1, 2, 3);
    return 0;
}
EOF

# ── bad10 : pas assez d'arguments ───────────────────────────
cat > test_bad/bad10.tpc << 'EOF'
int add(int a, int b) {
    return a;
}

int main(void) {
    int r;
    r = add(1);
    return 0;
}
EOF

# ── bad11 : return avec valeur dans void ────────────────────
cat > test_bad/bad11.tpc << 'EOF'
void f(void) {
    return 42;
}

int main(void) {
    f();
    return 0;
}
EOF

# ── bad12 : return sans valeur dans int ─────────────────────
cat > test_bad/bad12.tpc << 'EOF'
int f(void) {
    return;
}

int main(void) {
    int r;
    r = f();
    return 0;
}
EOF

# ── bad13 : type struct inconnu ─────────────────────────────
cat > test_bad/bad13.tpc << 'EOF'
int main(void) {
    struct Unknown x;
    return 0;
}
EOF

# ── bad14 : accès à un champ inexistant ─────────────────────
cat > test_bad/bad14.tpc << 'EOF'
struct S {
    int a;
};

int main(void) {
    struct S x;
    x.b = 1;
    return 0;
}
EOF

# ── bad15 : accès champ sur non-struct ──────────────────────
cat > test_bad/bad15.tpc << 'EOF'
int main(void) {
    int x;
    x = 5;
    x.a = 1;
    return 0;
}
EOF

# ── bad16 : pas de main ──────────────────────────────────────
cat > test_bad/bad16.tpc << 'EOF'
int f(void) {
    return 1;
}
EOF

# ── bad17 : main retourne void ───────────────────────────────
cat > test_bad/bad17.tpc << 'EOF'
void main(void) {
    return;
}
EOF

# ── bad18 : utilisation d'une variable avant déclaration ────
cat > test_bad/bad18.tpc << 'EOF'
int main(void) {
    a = 1;
    int a;
    return 0;
}
EOF

# ── bad19 : struct re-définie ────────────────────────────────
cat > test_bad/bad19.tpc << 'EOF'
struct S {
    int a;
};

struct S {
    int b;
};

int main(void) {
    return 0;
}
EOF

# ── bad20 : appel d'une variable comme fonction ─────────────
cat > test_bad/bad20.tpc << 'EOF'
int main(void) {
    int f;
    int r;
    f = 3;
    r = f(1);
    return 0;
}
EOF

# ────────────────────────────────────────────────────────────
# Lancement des tests
# ────────────────────────────────────────────────────────────

echo ""
echo "=== Fichiers créés dans ./test_good2 ==="
ls test_good2/

echo ""
echo "=== Fichiers créés dans ./test_bad ==="
ls test_bad/

echo ""
echo "=== Tests BONS (doivent passer — exit 0) ==="
PASS=0; FAIL=0
for f in test_good2/*.tpc; do
    ./bin/tpcc < "$f" > /dev/null 2>&1
    code=$?
    if [ "$code" -eq 0 ]; then
        echo "PASS  $f"
        PASS=$((PASS+1))
    else
        echo "FAIL  $f  (exit $code)"
        ./bin/tpcc < "$f" 2>&1 | grep "\[ERROR\]"
        FAIL=$((FAIL+1))
    fi
done
echo "Résultat bons : $PASS passés, $FAIL échoués"

echo ""
echo "=== Tests MAUVAIS (doivent échouer — exit != 0) ==="
PASS2=0; FAIL2=0
for f in test_bad/*.tpc; do
    ./bin/tpcc < "$f" > /dev/null 2>&1
    code=$?
    if [ "$code" -ne 0 ]; then
        echo "PASS  $f  (exit $code)"
        PASS2=$((PASS2+1))
    else
        echo "FAIL  $f  (devait échouer mais exit 0)"
        FAIL2=$((FAIL2+1))
    fi
done
echo "Résultat mauvais : $PASS2 détectés, $FAIL2 non détectés"

echo ""
echo "=== Bilan global ==="
TOTAL_PASS=$((PASS + PASS2))
TOTAL_FAIL=$((FAIL + FAIL2))
echo "Total réussis : $TOTAL_PASS / $((TOTAL_PASS + TOTAL_FAIL))"
