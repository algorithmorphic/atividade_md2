// Cabeçalho
// Artur Ricardo dos Santos Lopes
// 190102977
// Lucca Medeiros Silva
// 222031528

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>

// Função para garantir que N1 e N2 sejam primos e distintos
bool isSquareFreeAndComposite(long long n) {
    if (n < 4) return false; // 0,1,2,3 não servem
    long long m = n;
    for (long long p = 2; p * p <= m; ++p) {
        int cnt = 0;
        while (m % p == 0) { m /= p; ++cnt; if (cnt > 1) return false; }
    }
    // sobrou fator >1 conta como 1 primo com expoente 1
    // precisa ser composto (>= 2 fatores primos no total)
    int factors = 0;
    m = n;
    for (long long p = 2; p * p <= m; ++p) {
        if (n % p == 0) { ++factors; while (n % p == 0) n /= p; }
    }
    if (n > 1) ++factors;
    return factors >= 2; // composto e sem expoente repetido
}

// Função para calcular o MDC usando o Algoritmo de Euclides
long long gcd(long long a, long long b, bool print_steps = false) {
    if (print_steps) {
        std::cout << "  Algoritmo de Euclides: Calculando MDC(" << a << ", " << b << ")\n";
    }
    while (b) {
        if (print_steps) {
            std::cout << "    " << a << " mod " << b << " = " << a % b << "\n";
        }
        a %= b;
        std::swap(a, b);
    }
    return a;
}

// Função para calcular o MDC estendido e o inverso modular
long long extendedGcd(long long a, long long b, long long &x, long long &y, bool print_steps = false) {
    if (print_steps) {
        std::cout << "  Algoritmo de Euclides Estendido: Calculando inverso modular de " << a << " em relação a " << b << "\n";
    }
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long d = extendedGcd(b % a, a, x1, y1, print_steps);
    x = y1 - (b / a) * x1;
    y = x1;

    if (print_steps) {
        std::cout << "    Passo: a=" << a << ", b=" << b << ", x=" << x << ", y=" << y << ", d=" << d << "\n";
    }
    return d;
}

long long modInverse(long long a, long long m, bool print_steps = false) {
    long long x, y;
    long long g = extendedGcd(a, m, x, y, print_steps);
    if (g != 1) {
        return -1; // inverso não existe
    }
    if (print_steps) {
        std::cout << "  Inverso modular de " << a << " em relação a " << m << " é " << (x % m + m) % m << "\n";
    }
    return (x % m + m) % m;
}

// Função para exponenciação modular (a^b mod m)
long long power(long long base, long long exp, long long mod, bool print_steps = false) {
    long long res = 1;
    base %= mod;
    if (print_steps) {
        std::cout << "  Calculando potência modular: " << base << "^" << exp << " mod " << mod << "\n";
    }
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
            if (print_steps) {
                std::cout << "    Expoente ímpar: res = (" << res << " * " << base << ") % " << mod << " = " << (res * base) % mod << "\n";
            }
        }
        base = (base * base) % mod;
        exp /= 2;
        if (print_steps && exp > 0) {
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

// Função para exponenciação modular com seleção de teorema
long long modularExponentiation(long long M, long long E, long long N, bool print_steps = false) {
    if (print_steps) {
        std::cout << "  Aplicando Teorema Modular para M=" << M << ", E=" << E << ", N=" << N << "\n";
    }

    // Pequeno Teorema de Fermat
    if (isPrime(N)) {
        if (print_steps) {
            std::cout << "    N (" << N << ") é primo. Aplicando Pequeno Teorema de Fermat.\n";
            std::cout << "    Novo expoente E' = E % (N-1) = " << E << " % " << (N - 1) << " = " << (E % (N - 1)) << "\n";
        }
        return power(M, E % (N - 1), N, print_steps);
    }

    // Teorema de Euler
    if (gcd(M, N) == 1) {
        long long phiN = phi(N);
        if (print_steps) {
            std::cout << "    M (" << M << ") e N (" << N << ") são coprimos. Aplicando Teorema de Euler.\n";
            std::cout << "    phi(N) = " << phiN << ". Novo expoente E' = E % phi(N) = " << E << " % " << phiN << " = " << (E % phiN) << "\n";
        }
        return power(M, E % phiN, N, print_steps);
    }

    // Divisão Euclidiana (exponenciação modular padrão)
    if (print_steps) {
        std::cout << "    Aplicando Divisão Euclidiana (exponenciação modular padrão).\n";
    }
    return power(M, E, N, print_steps);
}

// Método ρ de Pollard para fatorar N
long long pollardRho(long long n, bool print_steps = false) {
    if (n % 2 == 0) return 2;
    long long x = 2, y = 2, d = 1;
    long long c = 1; // Pode ser qualquer valor, 1 é comum
    if (print_steps) {
        std::cout << "  Iniciando Fatoração ρ de Pollard para N=" << n << ", semente x0=2\n";
    }

    while (d == 1) {
        x = (x * x + c) % n;
        y = (y * y + c) % n;
        y = (y * y + c) % n;
        d = gcd(std::abs(x - y), n, print_steps);

        if (print_steps) {
            std::cout << "    Iteração: x=" << x << ", y=" << y << ", |x-y|=\n" << std::abs(x - y) << ", mdc(|x-y|, N)=" << d << "\n";
        }

        if (d == n) { // Ciclo encontrado, mas não fator. Tentar com outra semente ou c.
            if (print_steps) {
                std::cout << "    Ciclo encontrado, mas mdc é N. Tentando novamente com c diferente.\n";
            }
            x = 2; y = 2; c++; // Incrementa c e tenta novamente
            d = 1;
        }
    }
    return d;
}

// Função para converter char para int (A=11, B=12, ..., Z=36, Espaço=00)
int charToInt(char c) {
    if (c >= 'A' && c <= 'Z') {
        return 11 + (c - 'A');
    } else if (c >= 'a' && c <= 'z') {
        return 11 + (c - 'a');
    } else if (c == ' ') {
        return 0;
    }
    return -1; // Caractere inválido
}

// Função para converter int para char
char intToChar(int i) {
    if (i >= 11 && i <= 36) {
        return 'A' + (i - 11);
    } else if (i == 0) {
        return ' ';
    }
    return '?'; // Número inválido
}

void solveQ1() {
    long long N1, N2;
    std::cout << "\n--- QUESTÃO 1: SISTEMA RSA ---\n";

    // Etapa 1: Fatoração Interativa (Método ρ de Pollard)
    std::cout << "\nEtapa 1: Fatoração Interativa (Método ρ de Pollard)\n";
    do {
        std::cout << "  Digite o primeiro número composto N1 (3 ou 4 dígitos): ";
        std::cin >> N1;
        if (N1 < 100 || N1 > 9999) {
            std::cout << "  Erro: N1 deve ter entre 3 e 4 dígitos.\n";
        }

        if (!isSquareFreeAndComposite(N1)) {
            std::cout << "  Erro: cada N1 deve ser composto e produto de primos distintos (sem repetição).\n";
        }
    } while (N1 < 100 || N1 > 9999 || !isSquareFreeAndComposite(N1));

    do {
        std::cout << "  Digite o segundo número composto N2 (3 ou 4 dígitos, diferente de N1): ";
        std::cin >> N2;
        if (N2 < 100 || N2 > 9999) {
            std::cout << "  Erro: N2 deve ter entre 3 e 4 dígitos.\n";
        } else if (N2 == N1) {
            std::cout << "  Erro: N2 deve ser diferente de N1.\n";
        }

        if (!isSquareFreeAndComposite(N2)) {
            std::cout << "  Erro: cada N2 deve ser composto e produto de primos distintos (sem repetição).\n";
        }
    } while (N2 < 100 || N2 > 9999 || N2 == N1 || !isSquareFreeAndComposite(N2));

    std::cout << "  Fatorando N1 = " << N1 << " usando Pollard's Rho...\n";
    long long p = pollardRho(N1, true);
    std::cout << "  Fator encontrado para N1: p = " << p << "\n";

    std::cout << "  Fatorando N2 = " << N2 << " usando Pollard's Rho...\n";
    long long q = pollardRho(N2, true);
    std::cout << "  Fator encontrado para N2: q = " << q << "\n";

    std::cout << "  Primos RSA definidos: p = " << p << ", q = " << q << "\n";

    // Etapa 2: Geração das Chaves RSA
    std::cout << "\nEtapa 2: Geração das Chaves RSA\n";
    long long n = p * q;
    long long phi_n = (p - 1) * (q - 1);
    std::cout << "  Módulo n = p * q = " << p << " * " << q << " = " << n << "\n";
    std::cout << "  Totiente de Euler phi(n) = (p-1) * (q-1) = " << (p - 1) << " * " << (q - 1) << " = " << phi_n << "\n";

    long long e = 0;
    for (e = 2; e < phi_n; ++e) {
        if (gcd(e, phi_n) == 1) {
            break;
        }
    }
    std::cout << "  Expoente público e = " << e << " (menor E > 1 e E < phi(n) tal que mdc(E, phi(n))=1)\n";

    long long d = modInverse(e, phi_n, true);
    std::cout << "  Expoente privado d = " << d << " (inverso modular de E em relação a phi(n))\n";

    std::cout << "  Chave Pública: (n=" << n << ", e=" << e << ")\n";
    std::cout << "  Chave Privada: (n=" << n << ", d=" << d << ")\n";

    // Etapa 3: Codificação (Criptografia) e Decodificação (Descriptografia)
    std::cout << "\nEtapa 3: Codificação e Decodificação\n";
    std::string message_str;
    std::cout << "  Digite a mensagem a ser criptografada (apenas letras e espaços): ";
    std::cin.ignore(); // Limpar o buffer do teclado
    std::getline(std::cin, message_str);

    // Converter mensagem para números
    std::vector<long long> numeric_message;
    std::cout << "\n  Pré-codificação da mensagem: \n";
    for (char c : message_str) {
        int num = charToInt(c);
        if (num != -1) {
            numeric_message.push_back(num);
            std::cout << "    Caractere '" << c << "' -> " << (num < 10 ? "0" : "") << num << "\n";
        } else {
            std::cout << "    Ignorando caractere inválido: '" << c << "'\n";
        }
    }

    // Criptografia
    std::vector<long long> encrypted_blocks;
    std::cout << "\n  Criptografando mensagem...\n";
    for (long long M : numeric_message) {
        long long C = modularExponentiation(M, e, n, true);
        encrypted_blocks.push_back(C);
        std::cout << "    Bloco M = " << M << ": C = M^e mod n = " << M << "^" << e << " mod " << n << " = " << C << "\n";
    }
    std::cout << "  Mensagem criptografada (blocos numéricos): ";
    for (long long C : encrypted_blocks) {
        std::cout << C << " ";
    }
    std::cout << "\n";

    // Decodificação
    std::vector<long long> decrypted_blocks;
    std::cout << "\n  Decodificando mensagem...\n";
    for (long long C : encrypted_blocks) {
        long long M_decrypted = modularExponentiation(C, d, n, true);
        decrypted_blocks.push_back(M_decrypted);
        std::cout << "    Bloco C = " << C << ": M = C^d mod n = " << C << "^" << d << " mod " << n << " = " << M_decrypted << "\n";
    }

    // Reconversão para texto
    std::string decrypted_message_str = "";
    std::cout << "\n  Reconvertendo para texto: \n";
    for (long long M : decrypted_blocks) {
        char c = intToChar(M);
        decrypted_message_str += c;
        std::cout << "    Número " << (M < 10 ? "0" : "") << M << " -> Caractere '" << c << "'\n";
    }
    std::cout << "  Mensagem decifrada: " << decrypted_message_str << "\n";

    // Confirmação
    std::string original_processed_message = "";
    for (long long M : numeric_message) {
        original_processed_message += intToChar(M);
    }

    if (original_processed_message == decrypted_message_str) {
        std::cout << "\n  Confirmação: A mensagem decifrada é idêntica à mensagem original processada.\n";
    } else {
        std::cout << "\n  Confirmação: ATENÇÃO! A mensagem decifrada NÃO é idêntica à mensagem original processada.\n";
        std::cout << "    Original Processada: " << original_processed_message << "\n";
        std::cout << "    Decifrada: " << decrypted_message_str << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    solveQ1();
    return 0;
}

