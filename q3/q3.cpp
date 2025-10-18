// Cabeçalho
// Artur Ricardo dos Santos Lopes
// 190102977
// Lucca Medeiros Silva
// 222031528

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>

// Função para fatorar N em seus fatores primos e seus expoentes
std::map<long long, int> primeFactorization(long long n, bool print_steps = false) {
    std::map<long long, int> factors;
    long long temp_n = n;
    if (print_steps) {
        std::cout << "  Fatorando N = " << n << ":\n";
    }

    // Divide por 2
    if (temp_n % 2 == 0) {
        int count = 0;
        while (temp_n % 2 == 0) {
            temp_n /= 2;
            count++;
        }
        factors[2] = count;
        if (print_steps) {
            std::cout << "    Fator 2 com expoente " << count << "\n";
        }
    }

    // Divide por ímpares
    for (long long i = 3; i * i <= temp_n; i += 2) {
        if (temp_n % i == 0) {
            int count = 0;
            while (temp_n % i == 0) {
                temp_n /= i;
                count++;
            }
            factors[i] = count;
            if (print_steps) {
                std::cout << "    Fator " << i << " com expoente " << count << "\n";
            }
        }
    }

    // Se sobrou um número maior que 1, ele é primo
    if (temp_n > 1) {
        factors[temp_n] = 1;
        if (print_steps) {
            std::cout << "    Fator " << temp_n << " com expoente 1\n";
        }
    }
    return factors;
}

// Função para calcular tau(N) - número de divisores
long long calculateTau(const std::map<long long, int>& factors, bool print_steps = false) {
    long long tau_n = 1;
    if (print_steps) {
        std::cout << "\n  Calculando tau(N) (número de divisores):\n";
    }
    for (const auto& pair : factors) {
        long long prime = pair.first;
        int exponent = pair.second;
        tau_n *= (exponent + 1);
        if (print_steps) {
            std::cout << "    Para primo " << prime << ", expoente " << exponent << ": tau(N) *= (" << exponent << " + 1) = " << tau_n << "\n";
        }
    }
    return tau_n;
}

// Função para calcular sigma(N) - soma dos divisores
long long calculateSigma(const std::map<long long, int>& factors, bool print_steps = false) {
    long long sigma_n = 1;
    if (print_steps) {
        std::cout << "\n  Calculando sigma(N) (soma dos divisores):\n";
    }
    for (const auto& pair : factors) {
        long long prime = pair.first;
        int exponent = pair.second;
        long long term = (std::pow(prime, exponent + 1) - 1) / (prime - 1);
        sigma_n *= term;
        if (print_steps) {
            std::cout << "    Para primo " << prime << ", expoente " << exponent << ": sigma(N) *= ((" << prime << "^(" << exponent << "+1)) - 1) / (" << prime << " - 1)) = " << term << ". sigma(N) atual = " << sigma_n << "\n";
        }
    }
    return sigma_n;
}

void solveQ3() {
    std::cout << "\n--- QUESTÃO 3: A RAZÃO DE EFICIÊNCIA DE UM NÚMERO ---\n";
    long long N;
    std::cout << "  Digite um inteiro N (1 <= N <= 10^5): ";
    std::cin >> N;

    if (N < 1 || N > 100000) {
        std::cout << "  Erro: N deve estar entre 1 e 10^5.\n";
        return;
    }

    std::map<long long, int> factors = primeFactorization(N, true);

    std::cout << "\n  Fatoração dos primos (número, potência): ";
    for (const auto& pair : factors) {
        std::cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    std::cout << "\n";

    long long tau_n = calculateTau(factors, true);
    long long sigma_n = calculateSigma(factors, true);

    std::cout << "\n  Resultado Final:\n";
    std::cout << "  tau(N) (Número total de divisores) = " << tau_n << "\n";
    std::cout << "  sigma(N) (Soma de todos os divisores) = " << sigma_n << "\n";

    double efficiency_ratio = static_cast<double>(sigma_n) / tau_n;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Razão de Eficiência = sigma(N) / tau(N) = " << sigma_n << " / " << tau_n << " = " << efficiency_ratio << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    solveQ3();
    return 0;
}

