#!/bin/bash

mkdir -p test_good

# ── good01 : programme minimal ──────────────────────────────────────────────
cat > test_good/good01.tpc << 'EOF'
int main(void) {
    return 0;
}
EOF

# ── good02 : variable globale + affectation ──────────────────────────────────
cat > test_good/good02.tpc << 'EOF'
int x;

int main(void) {
    x = 42;
    return 0;
}
EOF

# ── good03 : variable locale + affectation ──────────────────────────────────
cat > test_good/good03.tpc << 'EOF'
int main(void) {
    int a;
    a = 10;
    return 0;
}
EOF

# ── good04 : fonction sans paramètre appelée en instruction ─────────────────
cat > test_good/good04.tpc << 'EOF'
void f(void) {
    return;
}

int main(void) {
    f();
    return 0;
}
EOF

# ── good05 : fonction avec paramètres, appel correct ────────────────────────
cat > test_good/good05.tpc << 'EOF'
int add(int a, int b) {
    return a;
}

int main(void) {
    int r;
    r = add(1, 2);
    return 0;
}
EOF

# ── good06 : appel de fonction dans une expression ──────────────────────────
cat > test_good/good06.tpc << 'EOF'
int f(int x) {
    return x;
}

int main(void) {
    int a;
    a = f(3);
    return 0;
}
EOF

# ── good07 : if simple avec condition variable ───────────────────────────────
cat > test_good/good07.tpc << 'EOF'
int main(void) {
    int a;
    a = 1;
    if (a) {
        a = 2;
    }
    return 0;
}
EOF

# ── good08 : if-else ─────────────────────────────────────────────────────────
cat > test_good/good08.tpc << 'EOF'
int main(void) {
    int a;
    a = 0;
    if (a) {
        a = 1;
    } else {
        a = 2;
    }
    return 0;
}
EOF

# ── good09 : while ───────────────────────────────────────────────────────────
cat > test_good/good09.tpc << 'EOF'
int main(void) {
    int i;
    i = 0;
    while (i) {
        i = i + 1;
    }
    return 0;
}
EOF

# ── good10 : plusieurs variables locales ────────────────────────────────────
cat > test_good/good10.tpc << 'EOF'
int main(void) {
    int a, b, c;
    a = 1;
    b = 2;
    c = a + b;
    return 0;
}
EOF

# ── good11 : fonction récursive ──────────────────────────────────────────────
cat > test_good/good11.tpc << 'EOF'
int fact(int n) {
    if (n) {
        return fact(n);
    }
    return 1;
}

int main(void) {
    int r;
    r = fact(5);
    return 0;
}
EOF

# ── good12 : deux fonctions qui s'appellent ──────────────────────────────────
cat > test_good/good12.tpc << 'EOF'
int g(int x) {
    return x;
}

int f(int x) {
    return g(x);
}

int main(void) {
    int r;
    r = f(1);
    return 0;
}
EOF

# ── good13 : expression binaire complexe ────────────────────────────────────
cat > test_good/good13.tpc << 'EOF'
int main(void) {
    int a, b, c;
    a = 1;
    b = 2;
    c = a + b * 3;
    return 0;
}
EOF

# ── good14 : expression avec comparaison dans while ─────────────────────────
cat > test_good/good14.tpc << 'EOF'
int main(void) {
    int i;
    i = 0;
    while (i == 0) {
        i = 1;
    }
    return 0;
}
EOF

# ── good15 : void f(void) appelée, résultat ignoré ──────────────────────────
cat > test_good/good15.tpc << 'EOF'
void print(void) {
    return;
}

int main(void) {
    print();
    print();
    return 0;
}
EOF

# ── good16 : variable globale utilisée dans une fonction ────────────────────
cat > test_good/good16.tpc << 'EOF'
int g;

void set(int v) {
    g = v;
    return;
}

int main(void) {
    set(10);
    return 0;
}
EOF

# ── good17 : négation unaire ─────────────────────────────────────────────────
cat > test_good/good17.tpc << 'EOF'
int main(void) {
    int a;
    a = -1;
    return 0;
}
EOF

# ── good18 : opérateur ! ────────────────────────────────────────────────────
cat > test_good/good18.tpc << 'EOF'
int main(void) {
    int a, b;
    a = 1;
    b = !a;
    return 0;
}
EOF

# ── good19 : return de variable locale ──────────────────────────────────────
cat > test_good/good19.tpc << 'EOF'
int f(void) {
    int x;
    x = 5;
    return x;
}

int main(void) {
    int r;
    r = f();
    return 0;
}
EOF

# ── good20 : appel imbriqué dans expression ──────────────────────────────────
cat > test_good/good20.tpc << 'EOF'
int id(int x) {
    return x;
}

int main(void) {
    int a;
    a = id(id(3));
    return 0;
}
EOF

# ── good21 : déclaration simple de structure ────────────────────────────────
cat > test_good/good21.tpc << 'EOF'
struct S {
    int a;
};

int main(void) {
    return 0;
}
EOF

# ── good22 : variable de type struct ────────────────────────────────────────
cat > test_good/good22.tpc << 'EOF'
struct S {
    int a;
};

struct S x;

int main(void) {
    return 0;
}
EOF

# ── good23 : accès à un champ ───────────────────────────────────────────────
cat > test_good/good23.tpc << 'EOF'
struct S {
    int a;
};

int main(void) {
    struct S x;
    x.a = 5;
    return 0;
}
EOF

# ── good24 : lecture d’un champ ─────────────────────────────────────────────
cat > test_good/good24.tpc << 'EOF'
struct S {
    int a;
};

int main(void) {
    struct S x;
    int y;
    y = x.a;
    return 0;
}
EOF

# ── good25 : plusieurs champs ───────────────────────────────────────────────
cat > test_good/good25.tpc << 'EOF'
struct S {
    int a;
    int b;
};

int main(void) {
    struct S x;
    x.a = 1;
    x.b = 2;
    return 0;
}
EOF

# ── good26 : struct passée en paramètre ─────────────────────────────────────
cat > test_good/good26.tpc << 'EOF'
struct S {
    int a;
};

int f(struct S s) {
    return s.a;
}

int main(void) {
    struct S x;
    int r;
    r = f(x);
    return 0;
}
EOF

# ── good27 : struct retournée par fonction ──────────────────────────────────
cat > test_good/good27.tpc << 'EOF'
struct S {
    int a;
};

struct S f(void) {
    struct S x;
    return x;
}

int main(void) {
    struct S y;
    y = f();
    return 0;
}
EOF

# ── good28 : struct dans struct ─────────────────────────────────────────────
cat > test_good/good28.tpc << 'EOF'
struct A {
    int x;
};

struct B {
    struct A a;
};

int main(void) {
    struct B b;
    b.a.x = 3;
    return 0;
}
EOF

# ── good29 : même nom struct et variable (autorisé) ─────────────────────────
cat > test_good/good29.tpc << 'EOF'
struct S {
    int a;
};

int S;

int main(void) {
    struct S x;
    S = 5;
    return 0;
}
EOF

# ── good30 : struct globale utilisée dans fonction ──────────────────────────
cat > test_good/good30.tpc << 'EOF'
struct S {
    int a;
};

struct S g;

int main(void) {
    g.a = 10;
    return 0;
}
EOF

# ── good31 : affectation de struct ──────────────────────────────────────────
cat > test_good/good31.tpc << 'EOF'
struct S {
    int a;
};

int main(void) {
    struct S x, y;
    x = y;
    return 0;
}
EOF

# ── good32 : champ utilisé dans expression ──────────────────────────────────
cat > test_good/good32.tpc << 'EOF'
struct S {
    int a;
};

int main(void) {
    struct S x;
    int y;
    y = x.a + 1;
    return 0;
}
EOF

echo ""
echo "=== Fichiers créés dans ./test_good ==="
ls test_good/

echo ""
echo "=== Lancement des tests ==="
PASS=0; FAIL=0
for f in test/sem_err/test_good/*.tpc; do
    ./bin/tpcc < "$f" > /dev/null 2>&1
    code=$?
    if [ "$code" -eq 0 ]; then
        echo "PASS $f"
        PASS=$((PASS+1))
    else
        echo "FAIL $f (exit $code)"
        ./bin/tpcc < "$f" 2>&1 | grep "\[ERROR\]"
        FAIL=$((FAIL+1))
    fi
done
echo "Résultat : $PASS passés, $FAIL échoués"