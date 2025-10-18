// Cabeçalho
// Artur Ricardo dos Santos Lopes
// 190102977
// Lucca Medeiros Silva
// 222031528

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <limits>

// ---------- Utilidades ----------

long long mdc(long long a, long long b, bool comPassos = false) {
    if (comPassos) std::cout << "  Algoritmo de Euclides: Calculando MDC(" << a << ", " << b << ")\n";
    while (b) {
        if (comPassos) std::cout << "    " << a << " mod " << b << " = " << a % b << "\n";
        a %= b;
        std::swap(a, b);
    }
    return a;
}

long long mdcEstendido(long long a, long long b, long long &x, long long &y, bool comPassos = false) {
    if (comPassos)
        std::cout << "  Algoritmo de Euclides Estendido: Calculando inverso modular de "
                  << a << " em relação a " << b << "\n";
    if (a == 0) { x = 0; y = 1; return b; }
    long long x1, y1;
    long long d = mdcEstendido(b % a, a, x1, y1, comPassos);
    x = y1 - (b / a) * x1;
    y = x1;
    if (comPassos)
        std::cout << "    Passo: a=" << a << ", b=" << b << ", x=" << x << ", y=" << y << ", d=" << d << "\n";
    return d;
}

long long inversoModular(long long a, long long m, bool comPassos = false) {
    long long x, y;
    long long g = mdcEstendido(a, m, x, y, comPassos);
    if (g != 1) return -1; // inverso não existe
    long long inv = (x % m + m) % m;
    if (comPassos)
        std::cout << "  Inverso modular de " << a << " em relação a " << m << " é " << inv << "\n";
    return inv;
}

long long powMod(long long base, long long exp, long long mod, bool comPassos = false) {
    if (mod == 1) return 0;
    long long res = 1 % mod;
    base %= mod;
    if (comPassos)
        std::cout << "  Calculando potência modular: " << base << "^" << exp << " mod " << mod << "\n";
    while (exp > 0) {
        if (exp & 1) {
            long long old = res;
            res = (res * base) % mod;
            if (comPassos)
                std::cout << "    Expoente ímpar: res = (" << old << " * " << base
                          << ") % " << mod << " = " << res << "\n";
        }
        long long oldBase = base;
        base = (base * base) % mod;
        exp >>= 1;
        if (comPassos && exp > 0)
            std::cout << "    Base ao quadrado: base = (" << oldBase << "^2) % "
                      << mod << " = " << base << ", exp = " << exp << "\n";
    }
    return res;
}

bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

long long phi(long long n) {
    long long result = n;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// ---------- Q4 ----------

void solveQ4() {
    std::cout << "\n--- QUESTÃO 4: DIVISÃO MODULAR E TEOREMAS ---\n";

    long long H, G, Zn, x, n1;

    // Lê apenas o que a questão pede: H, G, Zn, x, n1 (a base será a = x)
    std::cout << "Informe H, G, Zn (para H / G (mod Zn)):\n";
    std::cout << "H = ";  std::cin >> H;
    std::cout << "G = ";  std::cin >> G;
    std::cout << "Zn = "; std::cin >> Zn;

    std::cout << "\nInforme x e n1 (para a^x (mod n1), com a = x):\n";
    std::cout << "x = ";   std::cin >> x;
    std::cout << "n1 = ";  std::cin >> n1;

    long long a = x; // conforme a leitura da Q4: usa-se a = x

    std::cout << "\nSaída para os valores\n";
    std::cout << "H: " << H << ", G: " << G << ", Zn: " << Zn
              << ", x: " << x << ", n1: " << n1 << " (a = x = " << a << ")\n\n";

    // --- Divisão modular H / G (mod Zn) ---
    std::cout << "  Cálculo da divisão modular H / G (mod Zn):\n";
    long long g = mdc(G, Zn, true);
    if (g != 1) {
        std::cout << "  Erro: mdc(" << G << ", " << Zn << ") = " << g
                  << " ≠ 1. Inverso não existe; divisão modular indefinida.\n";
    } else {
        long long invG = inversoModular(G, Zn, true);
        std::cout << "  Substituindo, temos que o inverso de " << G
                  << " em " << Zn << " é " << invG << ".\n\n";
        long long divisaoModular = ((H % Zn + Zn) % Zn) * 1LL * invG % Zn;
        std::cout << "  Fazendo a multiplicação modular: " << H << " * " << invG
                  << " mod " << Zn << " ≡ " << divisaoModular << "\n";
        std::cout << "  Sendo " << invG << " o inverso de " << G << ".\n";
        std::cout << "  Valor final da congruência: " << divisaoModular << "\n";
    }

    // --- a^x (mod n1) com seleção de teorema (e a = x) ---
    std::cout << "\n  Cálculo de a^x mod n1: " << a << "^" << x << " mod " << n1 << " (com a = x)\n";
    long long resultadoPowMod;
    if (isPrime(n1)) {
        std::cout << "    n1 (" << n1 << ") é primo. Aplicando Pequeno Teorema de Fermat.\n";
        long long expFermat = x % (n1 - 1);
        std::cout << "    Novo expoente = " << x << " % (" << n1 << " - 1) = " << expFermat << "\n";
        resultadoPowMod = powMod(a, expFermat, n1, true);
    } else if (mdc(a, n1) == 1) {
        std::cout << "    mdc(" << a << ", " << n1 << ") = 1. Aplicando Teorema de Euler.\n";
        long long phiN1 = phi(n1);
        std::cout << "    phi(n1) = " << phiN1 << ". Novo expoente = " << x
                  << " % " << phiN1 << " = " << (x % phiN1) << "\n";
        resultadoPowMod = powMod(a, x % phiN1, n1, true);
    } else {
        std::cout << "    Aplicando exponenciação modular padrão.\n";
        resultadoPowMod = powMod(a, x, n1, true);
    }
    std::cout << "  Resultado de " << a << "^" << x << " mod " << n1
              << " = " << resultadoPowMod << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    solveQ4();
    return 0;
}