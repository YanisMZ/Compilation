#!/bin/bash

mkdir -p test

# Test 1

cat > test/test1.tpc << 'EOF'
struct aircraft {
int height, width;
};

int main(void) {
int a;
a = 10;
b = 5;
return 0;
}
EOF

# Test 2

cat > test/test2.tpc << 'EOF'
int main(void) {
return;
}
EOF

# Test 3

cat > test/test3.tpc << 'EOF'
void f(void) {
return 5;
}

int main(void) {
return 0;
}
EOF

# Test 4

cat > test/test4.tpc << 'EOF'
int main(void) {
int a;
a = 10;
}
EOF

# Test 5

cat > test/test5.tpc << 'EOF'
int main(void) {
foo();
return 0;
}
EOF

# Test 6

cat > test/test6.tpc << 'EOF'
int f(int x) {
return x;
}

int main(void) {
f(1, 2);
return 0;
}
EOF

# Test 7

cat > test/test7.tpc << 'EOF'
int main(void) {
if (1) {
int a;
}
return 0;
}
EOF

# Test 8

cat > test/test8.tpc << 'EOF'
void f(void) {}

int main(void) {
int a;
a = f();
return 0;
}
EOF

# Test 9

cat > test/test9.tpc << 'EOF'
int a;

return 5;

int main(void) {
return 0;
}
EOF

# Test 10

cat > test/test10.tpc << 'EOF'
int f(int x, int x) {
return x;
}

int main(void) {
return 0;
}
EOF

echo "Tous les fichiers de test ont été créés dans le dossier ./test"
