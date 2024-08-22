


**MyMatrix: Estrutura de Dados para Manipulação de Matrizes Genéricas**

O arquivo MyMatrix.cpp define uma estrutura de dados chamada MyMatrix, projetada para representar matrizes genéricas. Junto com essa estrutura, o código inclui diversas funções para manipulação de matrizes e processamento de imagens. Abaixo, uma descrição detalhada das principais funcionalidades e implementações.
Estrutura da Classe MyMatrix

A classe MyMatrix é implementada utilizando templates (template <typename T>), permitindo a criação de matrizes que podem armazenar diferentes tipos de dados, como int, double, float, entre outros.
Construtor MyMatrix(int linhas, int colunas)

    Inicializa uma nova matriz com as dimensões especificadas (linhas e colunas).
    A memória é alocada dinamicamente para a matriz usando new T*[this->linhas] e matriz[i] = new T[this->colunas].

Construtor de Cópia MyMatrix(const MyMatrix& other)

    Cria uma cópia independente de uma matriz existente (other).
    Aloca nova memória e copia os elementos da matriz original para a nova instância.

Operador de Atribuição MyMatrix& operator=(const MyMatrix& other)

    Permite a atribuição de uma matriz a outra.
    Trata corretamente a auto-atribuição e libera a memória da matriz existente antes de copiar os dados da matriz atribuída.

Destrutor ~MyMatrix()

    Libera a memória alocada para a matriz quando o objeto MyMatrix sai de escopo, prevenindo vazamentos de memória.

Métodos para Manipulação de Matrizes
set_elem e get_elem

    set_elem: Define o valor de um elemento em uma posição específica da matriz, dada pelas coordenadas de linha e coluna.
    get_elem: Retorna o valor de um elemento em uma posição específica da matriz.

calcula_euclid

    Calcula a distância euclidiana entre dois pontos em um espaço bidimensional, utilizando suas coordenadas (x, y).

Algoritmos de Cálculo de Distância
distancia, distancia_melhorado e distancia_eficiente

Esses métodos calculam a distância de cada pixel ao pixel preto mais próximo em uma imagem representada pela matriz:

    distancia: Implementa um algoritmo simples que percorre todos os pixels da imagem e calcula a distância até cada pixel preto.
    distancia_melhorado: Otimiza o algoritmo básico, armazenando as posições dos pixels pretos em um vetor (MyVec) para reduzir o número de comparações.
    distancia_eficiente: Utiliza uma fila de prioridades (MyPriorityQueue) para implementar um algoritmo eficiente que simula uma "propagação de onda" a partir dos pixels pretos.

Métodos para Geração de Saída Visual
dist_percent e geraCorDist

    dist_percent: Converte uma distância em um valor percentual em relação à maior distância encontrada na matriz, normalizando o intervalo de distâncias.
    geraCorDist: Converte uma distância percentual em uma cor RGB utilizando o sistema de cores HSV como intermediário.

Observações Adicionais

    O código utiliza a biblioteca MyVec.h para implementar o vetor de pixels pretos no algoritmo distancia_melhorado.
    A biblioteca MyPriorityQueue.h é utilizada para implementar a fila de prioridades no algoritmo distancia_eficiente.
    O código assume que a entrada é uma imagem monocromática representada por uma matriz, onde 0 representa pixels brancos e valores diferentes de 0 representam pixels pretos.

Informações Ausentes

    Leitura/Exibição de Imagens PPM: O código em MyMatrix.txt não inclui implementações para leitura ou exibição de imagens no formato PPM. Para utilizar o código com imagens PPM, seria necessário implementar essas funcionalidades ou utilizar bibliotecas externas.

