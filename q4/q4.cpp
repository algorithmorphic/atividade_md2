// Cabeçalho
// Artur Ricardo dos Santos Lopes
// 190102977
// Lucca Medeiros Silva
// 222031528

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Função para calcular o MDC usando o Algoritmo de Euclides
long long mdc(long long a, long long b, bool comPassos = false) {
    if (comPassos) {
        std::cout << "  Algoritmo de Euclides: Calculando MDC(" << a << ", " << b << ")\n";
    }
    while (b) {
        if (comPassos) {
            std::cout << "    " << a << " mod " << b << " = " << a % b << "\n";
        }
        a %= b;
        std::swap(a, b);
    }
    return a;
}

// Função para calcular o MDC estendido e o inverso modular
long long mdcEstendido(long long a, long long b, long long &x, long long &y, bool comPassos = false) {
    if (comPassos) {
        std::cout << "  Algoritmo de Euclides Estendido: Calculando inverso modular de " << a << " em relação a " << b << "\n";
    }
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long d = mdcEstendido(b % a, a, x1, y1, comPassos);
    x = y1 - (b / a) * x1;
    y = x1;

    if (comPassos) {
        std::cout << "    Passo: a=" << a << ", b=" << b << ", x=" << x << ", y=" << y << ", d=" << d << "\n";
    }
    return d;
}

long long inversoModular(long long a, long long m, bool comPassos = false) {
    long long x, y;
    long long g = mdcEstendido(a, m, x, y, comPassos);
    if (g != 1) {
        return -1; // inverso não existe
    }
    if (comPassos) {
        std::cout << "  Inverso modular de " << a << " em relação a " << m << " é " << (x % m + m) % m << "\n";
    }
    return (x % m + m) % m;
}

// Função para exponenciação modular (a^b mod m)
long long powMod(long long base, long long exp, long long mod, bool comPassos = false) {
    long long res = 1;
    base %= mod;
    if (comPassos) {
        std::cout << "  Calculando potência modular: " << base << "^" << exp << " mod " << mod << "\n";
    }
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
            if (comPassos) {
                std::cout << "    Expoente ímpar: res = (" << res << " * " << base << ") % " << mod << " = " << (res * base) % mod << "\n";
            }
        }
        base = (base * base) % mod;
        exp /= 2;
        if (comPassos && exp > 0) {
            std::cout << "    Base ao quadrado: base = (" << base << " * " << base << ") % " << mod << " = " << (base * base) % mod << ", exp = " << exp << "\n";
        }
    }
    return res;
}

// Função para verificar se um número é primo
bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Função para calcular o totiente de Euler (phi)
long long phi(long long n) {
    long long result = n;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

void solveQ4() {
    std::cout << "\n--- QUESTÃO 4: DIVISÃO MODULAR E TEOREMAS ---\n";

    // Valores de exemplo
    long long H = 7, G = 3, Zn = 11, a = 10, n1 = 13; // 'a' é o 'x' do enunciado na expressão a^x mod n1

    std::cout << "Saída para os valores\n";
    std::cout << "H: " << H << ", G: " << G << ", Zn: " << Zn << ", a: " << a << ", n1: " << n1 << "\n\n";

    // Cálculo da divisão modular H ÷ G (mod Zn)
    std::cout << "  Cálculo da divisão modular H / G (mod Zn):\n";
    long long invG = inversoModular(G, Zn, true);

    if (invG == -1) {
        std::cout << "  Erro: O inverso modular de " << G << " em relação a " << Zn << " não existe.\n";
    } else {
        std::cout << "  Substituindo, temos que o inverso de " << G << " em " << Zn << " é " << invG << ".\n\n";
        long long divisaoModular = (H * invG) % Zn;
        std::cout << "  Fazendo a multiplicação modular: " << H << " * " << invG << " mod " << Zn << " \xE2\x89\xA1 " << divisaoModular << "\n";
        std::cout << "  Sendo " << invG << " o inverso de " << G << ".\n";
        std::cout << "  Valor final da congruência: " << divisaoModular << "\n";
    }

    std::cout << "\n  Cálculo de a^x mod n1: " << a << "^" << a << " mod " << n1 << "\n";
    long long resultadoPowMod;

    if (isPrime(n1)) {
        std::cout << "    n1 (" << n1 << ") é primo. Aplicando Pequeno Teorema de Fermat.\n";
        long long expFermat = a % (n1 - 1);
        std::cout << "    Novo expoente = " << a << " % (" << n1 << " - 1) = " << expFermat << "\n";
        resultadoPowMod = powMod(a, expFermat, n1, true);
    } else if (mdc(a, n1) == 1) {
        std::cout << "    mdc(" << a << ", " << n1 << ") = 1. Aplicando Teorema de Euler.\n";
        long long phiN1 = phi(n1);
        std::cout << "    phi(n1) = " << phiN1 << ". Novo expoente = " << a << " % " << phiN1 << " = " << (a % phiN1) << "\n";
        resultadoPowMod = powMod(a, a % phiN1, n1, true);
    } else {
        std::cout << "    Aplicando Divisão Euclidiana (exponenciação modular padrão).\n";
        resultadoPowMod = powMod(a, a, n1, true);
    }
    std::cout << "  Resultado de " << a << "^" << a << " mod " << n1 << " = " << resultadoPowMod << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    solveQ4();
    return 0;
}

