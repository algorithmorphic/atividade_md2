// Cabeçalho
// Artur Ricardo dos Santos Lopes
// 190102977
// Lucca Medeiros Silva
// 222031528

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Função para calcular o MDC (Máximo Divisor Comum)
long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

// Função para calcular o MMC (Mínimo Múltiplo Comum)
long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return std::abs(a * b) / gcd(a, b);
}

void solveQ2(){
    std::cout << "\n--- QUESTÃO 2: CHAVES PERIÓDICAS ---\n";
    int n;
    std::cout << "  Digite o número de chaves (1 <= N <= 10): ";
    std::cin >> n;

    if (n < 1 || n > 10) {
        std::cout << "  Erro: O número de chaves deve estar entre 1 e 10.\n";
        return;
    }

    std::vector<long long> cycles(n);
    std::cout << "  Digite os " << n << " ciclos das chaves (2 <= Ci <= 20):\n";
    for(int i = 0; i < n; ++i){
        std::cout << "    Ciclo " << i + 1 << ": ";
        std::cin >> cycles[i];
        if (cycles[i] < 2 || cycles[i] > 20) {
            std::cout << "    Erro: O ciclo da chave deve estar entre 2 e 20.\n";
            return;
        }
    }

    long long res_lcm = 1;
    std::cout << "  Calculando o MMC dos ciclos:\n";
    for(long long cycle : cycles){
        long long old_lcm = res_lcm;
        res_lcm = lcm(res_lcm, cycle);
        std::cout << "    MMC(" << old_lcm << ", " << cycle << ") = " << res_lcm << "\n";
    }

    if(res_lcm >= 1 && res_lcm <= 50)
        std::cout << "  O primeiro ano futuro em que todas as chaves podem ser utilizadas simultaneamente é: " << res_lcm << std::endl;
    else
        std::cout << "  Não existe ano válido para esta combinação dentro do limite de 1 a 50 anos." << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    solveQ2();
    return 0;
}

