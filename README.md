# Atividade de Matemática Discreta II

| Aluno                          | Matrícula |
| ------------------------------ | :-------: |
| Artur Ricardo dos Santos Lopes | 190102977 |
| Lucca Medeiros Silva           | 222031528 |

## Introdução

Este repositório contém a resolução da Atividade de Matemática Discreta II, que aborda diversos conceitos fundamentais da teoria dos números e seus algoritmos. A atividade consiste em quatro questões de programação em C/C++ e uma seção de Verdadeiro ou Falso. O objetivo é implementar sistemas e funções que demonstrem o entendimento de tópicos como criptografia RSA, fatoração de Pollard, algoritmos de Euclides, exponenciação modular e funções aritméticas.

Todos os códigos foram desenvolvidos em C++17, com foco em clareza, modularidade e a exibição passo a passo dos cálculos, conforme solicitado no enunciado da atividade.

## Estrutura do Projeto

O projeto está organizado em diretórios, um para cada questão, contendo o código-fonte (`.cpp`) e o executável compilado.

```
.
├── docs
│   └── atividade_MD2_2025_2_k.pdf
├── q1/
│   └── q1.cpp
├── q2/
│   └── q2.cpp
├── q3/
│   └── q3.cpp
├── q4/
│   └── q4.cpp
└── README.md
```

## Como Compilar e Executar

Para compilar e executar os programas, você precisará de um compilador C++ (como `g++`) instalado em seu sistema.

### Compilação

Abra um terminal e navegue até o diretório `atividade_md2`. Para compilar cada questão, utilize os seguintes comandos:

```bash
g++ -std=c++17 -Wall q1/q1.cpp -o q1/q1
g++ -std=c++17 -Wall q2/q2.cpp -o q2/q2
g++ -std=c++17 -Wall q3/q3.cpp -o q3/q3
g++ -std=c++17 -Wall q4/q4.cpp -o q4/q4
```

Estes comandos criarão os executáveis `q1`, `q2`, `q3` e `q4` dentro de seus respectivos diretórios.

### Execução

Após a compilação, você pode executar cada programa a partir do diretório `atividade_md2`:

```bash
./q1/q1
./q2/q2
./q3/q3
./q4/q4
```

Cada programa solicitará as entradas necessárias e exibirá os passos e resultados conforme especificado na atividade.

## Questão 1: Sistema RSA com Fatoração ρ de Pollard e Teoremas Modulares

### Descrição

Esta questão implementa um sistema RSA completo, incluindo:
1.  **Fatoração ρ de Pollard:** Para encontrar os fatores primos `p` e `q` de dois números compostos `N1` e `N2` fornecidos pelo usuário. O programa exibe todas as iterações do método.
2.  **Geração de Chaves RSA:** Cálculo do módulo `n = p * q`, totiente de Euler `φ(n)`, expoente público `e` e expoente privado `d` (usando o Algoritmo de Euclides Estendido para o inverso modular).
3.  **Codificação e Decodificação:** Criptografia e descriptografia de uma mensagem textual, convertendo caracteres para números (A=11, B=12, ..., Z=36, Espaço=00). A exponenciação modular utiliza o Pequeno Teorema de Fermat, o Teorema de Euler ou a Divisão Euclidiana, com indicação clara do teorema aplicado e seus cálculos passo a passo.

O programa valida as entradas `N1` e `N2` (3 ou 4 dígitos) e confirma que a mensagem decifrada é idêntica à original.

### Exemplo de Uso

Ao executar `./q1/q1`, o programa solicitará `N1` e `N2`, e então uma mensagem para criptografar. A saída detalhará cada etapa do processo.

## Questão 2: Chaves Periódicas

### Descrição

Esta questão resolve o problema de encontrar o primeiro ano futuro (maior que 0) em que várias chaves periódicas podem ser utilizadas simultaneamente. Cada chave `Ki` tem um ciclo `Ci`, e só pode ser usada em anos múltiplos de `Ci`.

O problema é resolvido calculando o Mínimo Múltiplo Comum (MMC) dos ciclos de todas as chaves. O programa aceita `N` (número de chaves, 1 a 10) e `N` ciclos `Ci` (2 a 20). Ele verifica se o ano resultante está dentro do limite de 1 a 50 anos, informando caso contrário.

### Exemplo de Uso

Ao executar `./q2/q2`, o programa pedirá o número de chaves e, em seguida, os valores dos ciclos. A saída mostrará o cálculo do MMC e o ano sincronizado ou a mensagem de impossibilidade.

## Questão 3: A Razão de Eficiência de um Número

### Descrição

Esta questão calcula a "Razão de Eficiência" de um número `N`, definida como `σ(N) / τ(N)`, onde:
*   `τ(N)`: Conta o número total de divisores de `N`.
*   `σ(N)`: Calcula a soma de todos os divisores de `N`.

O programa realiza a fatoração prima de `N` (usando Trial Division para `N <= 10^5`), exibe os fatores e seus expoentes, calcula `τ(N)` e `σ(N)` com seus passos intermediários, e finalmente imprime a Razão de Eficiência com duas casas decimais.

### Exemplo de Uso

Ao executar `./q3/q3`, o programa solicitará um inteiro `N` (1 a 10^5). A saída incluirá a fatoração, os cálculos de `τ(N)` e `σ(N)`, e a razão final.

## Questão 4: Complementar Código e Verdadeiro/Falso

### Descrição

Esta questão envolve duas partes:
1.  **Complementar Código:** Preencher linhas faltantes em um código C++ que realiza divisão modular (`H ÷ G (mod Zn)`) e exponenciação modular (`a^x mod n1`), aplicando o Pequeno Teorema de Fermat ou o Teorema de Euler conforme o caso. As linhas foram completadas no arquivo `q4.cpp`.
2.  **Verdadeiro ou Falso:** Classificar afirmações sobre os conceitos implementados. As respostas são apresentadas abaixo.

### Saída para os valores fornecidos

**Valores:** H: 7, G: 3, Zn: 11, a: 10, n1: 13

```text
--- QUESTÃO 4: DIVISÃO MODULAR E TEOREMAS ---
Saída para os valores
H: 7, G: 3, Zn: 11, a: 10, n1: 13

  Cálculo da divisão modular H / G (mod Zn):
  Algoritmo de Euclides Estendido: Calculando inverso modular de 3 em relação a 11
    Passo: a=3, b=11, x=4, y=-1, d=1
  Inverso modular de 3 em relação a 11 é 4
  Substituindo, temos que o inverso de 3 em 11 é 4.

  Fazendo a multiplicação modular: 7 * 4 mod 11 ≡ 6
  Sendo 4 o inverso de 3.
  Valor final da congruência: 6

  Cálculo de a^x mod n1: 10^10 mod 13
    n1 (13) é primo. Aplicando Pequeno Teorema de Fermat.
    Novo expoente = 10 % (13 - 1) = 10
  Calculando potência modular: 10^10 mod 13
    Expoente ímpar: res = (1 * 10) % 13 = 10
    Base ao quadrado: base = (10 * 10) % 13 = 9, exp = 5
    Expoente ímpar: res = (10 * 9) % 13 = 12
    Base ao quadrado: base = (9 * 9) % 13 = 3, exp = 2
    Base ao quadrado: base = (3 * 3) % 13 = 9, exp = 1
    Expoente ímpar: res = (12 * 9) % 13 = 4
  Resultado de 10^10 mod 13 = 4
```

### Respostas Verdadeiro ou Falso

As afirmações a seguir são classificadas como Verdadeiro (V) ou Falso (F) com base na teoria dos números e na implementação esperada:

1.  **(V)** O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.
2.  **(F)** Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.
3.  **(V)** A operação (H * inverso) % Zn representa a divisão modular de H por G.
4.  **(V)** Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod n1.
5.  **(F)** A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas sem otimização.
6.  **(V)** Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.
7.  **(V)** O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo.