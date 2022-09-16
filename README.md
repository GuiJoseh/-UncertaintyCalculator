# -UncertaintyCalculator
Trata-se de um uma calculadora desenvolvida por mim durante as aulas de física experimental na universidade com o objetivo de acelerar o processo do calculo de propagação de incerteza.
Para utilizar esse software, basta baixar o código fonte e compila-lo em sua máquina. Ao executar o programa você irá se deperar com um  terminal aguardando que você digite uma expressão matemática.
Atualmente encontram-se implementados os operadores:
- \+ : adição
- \- : subtração
- \* : multiplicação
- \/ : divisão
- \^ : potenciação
- log : logaritmo base 10
- ln : logaritimo base e
- sin : seno
- sen : seno
- cos : cosseno
- tan : tangente
- pi : valor da constante pi
- e  : valor da constante e
- () : parenteses para alterar a ordem de execução das operações como em qualquer calculadora cientifica
- [] : colchetes para indicar a incerteza  associado a um valor, deve ser posicionado á direita do valor ao qual essa incerteza se aplica

Exemplo: Suponha que precisamos calcular a energia cinética (mv^2/2) de um corpo que medimos a massa como sendo 3Kg ± 0.1 e velocidade de 10m/s  ± 0.2. A equação que deve ser colocada como entrada no programa é : (3[0.1]*10[0.2]^2)/2
