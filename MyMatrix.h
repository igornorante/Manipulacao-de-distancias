#ifndef MyMatrix_H__
#define MyMatrix_H__

#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include <iomanip>
#include "MyVec.h"
#include <queue>
#include "MyPriorityQueue.h"
#include <cmath>
using namespace std;

struct elem
{
    double valor;
    bool status = false;
};



struct fila
{
    long long int x = 0;
    long long int y = 0;
    double dist = -1;
    bool operator>(const fila& other){
        return this->dist > other.dist; //Operador para comparação 
    }
};

struct Par
{
    int x; //Recebe a posição x de um elemento
    int y; //Recebe a posição y de um elemento
};


typedef struct {
    double h;       // ∈ [0, 360]
    double s;       // ∈ [0, 1]
    double v;       // ∈ [0, 1]
} hsv;

typedef struct {
    double r;       // ∈ [0, 1]
    double g;       // ∈ [0, 1]
    double b;       // ∈ [0, 1]
} rgb;

rgb hsv2rgb(hsv HSV)
{
    rgb RGB;
    double H = HSV.h, S = HSV.s, V = HSV.v,
            P, Q, T,
            fract;

    (H == 360.)?(H = 0.):(H /= 60.);
    fract = H - floor(H);

    P = V*(1. - S);
    Q = V*(1. - S*fract);
    T = V*(1. - S*(1. - fract));

    if      (0. <= H && H < 1.)
        RGB = (rgb) { V, T, P};
    else if (1. <= H && H < 2.)
        RGB = (rgb){Q, V, P};
    else if (2. <= H && H < 3.)
        RGB = (rgb){P,  V,  T};
    else if (3. <= H && H < 4.)
        RGB = (rgb){P,  Q,  V};
    else if (4. <= H && H < 5.)
        RGB = (rgb){T,  P,  V};
    else if (5. <= H && H < 6.)
        RGB = (rgb){V,  P,  Q};
    else
        RGB = (rgb){0.,  0.,  0};

    return RGB;
}




template<class T>
class MyMatrix {
private:
	T** matriz; //Elemento 
	long long int linhas; //Quantidade de linhas
	long long int colunas; //Quantidade de colunas
    rgb RGB; //Tipagem de cor

public:

    MyMatrix(); //Construtor padrão
    MyMatrix(int linhas, int colunas); //Construtor de matriz
    MyMatrix(const MyMatrix<T>& other); // Construtor de cópia
    MyMatrix& operator=(const MyMatrix<T>& other); // Operador de atribuição
    ~MyMatrix(); //Destrutor
    T &operator[](int pos) {return matriz[pos];} //Operador [] para operações com a matriz
	const T &operator[](int pos) const {return matriz[pos];} //Operador [] para operações com a matriz
    void set_elem(int linha, int coluna, const T&elem);
    const T &get_elem(int linha, int coluna);
    void distancia(string tipo); //Trivial
    void distancia_melhorado(string tipo); //Melhorado
    void distancia_eficiente(string tipo); //Eficiente
    double dist_percent(double elem, double maior_dist); //Dist percent para transformar em RGB
    int geraCorDist(double elem); //Gera RGB
    double calcula_euclid(int x1, int x2, int y1, int y2); //Calcula a distancia euclidiana
	
};

//Construtor padrão
template <class T>
MyMatrix<T>::MyMatrix(){
    matriz = NULL;
    linhas = colunas = 0;
}


//Construtor de matriz
template <class T>
MyMatrix<T>::MyMatrix(int linhas, int colunas) {
    this -> linhas = linhas;
    this -> colunas = colunas;
    matriz = new T*[this->linhas];
    for (int i = 0; i < linhas; ++i) {
        matriz[i] = new T[this->colunas];
    }
}

//Construtor de cópia
template <class T>
MyMatrix<T>::MyMatrix(const MyMatrix<T>& other) : linhas(other.linhas), colunas(other.colunas) {
    matriz = new T*[this->linhas];
    for (int i = 0; i < linhas; ++i) {
        matriz[i] = new T[this->colunas];
        for (int j = 0; j < colunas; ++j) {
            matriz[i][j] = other.matriz[i][j];
        }
    }
}

//Operador de atribuição
template <class T>
MyMatrix<T>& MyMatrix<T>::operator=(const MyMatrix<T>& other) {
    if (this == &other) {
        return *this; // Auto-atribuição
    }

    // Libera a memória existente
    for (int i = 0; i < linhas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;

    // Aloca nova memória
    linhas = other.linhas; 
    colunas = other.colunas;
    matriz = new T*[this->linhas];
    for (int i = 0; i < linhas; ++i) {
        matriz[i] = new T[this->colunas];
        for (int j = 0; j < colunas; ++j) {
            matriz[i][j] = other.matriz[i][j];
        }
    }

    return *this;
}

//Destrutor de matriz
template <class T>
MyMatrix<T>::~MyMatrix() {
    for (int i = 0; i < this->linhas; ++i) {
        delete[]matriz[i];
    }
    delete[]matriz;
}


//Metodo para setar um elemento na posição
template <class T>
void MyMatrix<T>::set_elem(int linha, int coluna,  const T&elem){
    matriz[linha][coluna] = elem;
}
//Metodo para retornar um elemento na posição
template <class T>
const T &MyMatrix<T>::get_elem(int linha, int coluna){
    return matriz[linha][coluna];
}


//Metodo para calcular a distancia euclidiana 
template <class T>
double MyMatrix<T>::calcula_euclid(int x1, int x2, int y1, int y2) {
    return sqrt(pow((x1-x2),2) + pow((y1-y2),2));
}



//Metodo para calcular distancia
template <class T>
void MyMatrix<T>::distancia(string tipo){

    int linha_reduzida = this->linhas; //Recebe o tamanho de linhas da matriz reduzida 
    int coluna_reduzida = this->colunas/3; //Recebe as colunas em tamanho reduzido, para pegar apenas um número ao invés de 3 do RGB
    double distancia;
    unsigned long long resumo = 0;
    double maior_distancia = 0;

    MyMatrix<double> matriz_resul(linha_reduzida, coluna_reduzida); //Matriz simplificada, não RGB

    //Transformar a matriz RGB para uma matriz comum, ou seja, com apenas um elemento por coluna
    //Matriz rgb = matriz
    //Matriz resumida = matriz_resul
    for(int i = 0; i < linha_reduzida; i++){

        for(int j = 0; j < this-> colunas; j+=3){ //Percorre a matriz pulando a coluna de 3 em 3

            if(matriz[i][j] == 0){
                matriz_resul.set_elem(i,j/3,0); //Se for um pixel preto, atualiza sua distancia para 0
            }
            else{
                 matriz_resul.set_elem(i,j/3,-1); //Se não for um pixel preto, atualiza sua distancia para -1
            }
        }
    }
    

    //Percorre a matriz fazendo o calculo das distancias de cada pixel até o preto mais proximo de forma trivial 
    for(int i = 0; i < linha_reduzida; i++){ //Matriz principal

        for(int j = 0; j < coluna_reduzida; j++){ //Matriz principal

            for(int l = 0; l < linha_reduzida; l++){ //Matriz secundária 

                for(int m = 0; m < coluna_reduzida; m++){ //Matriz secundária 

                    if(matriz_resul.get_elem(l,m) == 0){ //Se o pixel for preto 
                        distancia = calcula_euclid(i,l,j,m); //Calcula a distancia 

                    if(distancia < matriz_resul.get_elem(i,j) || matriz_resul.get_elem(i,j) == -1){ //Se a distancia for menor que a distancia armazenada na matriz ou se a distancia for -1
                        matriz_resul.set_elem(i,j,distancia); //Mantem no lugar apenas a menor distancia 
                    }
                    }
                }
            }
            if(matriz_resul.get_elem(i,j) > maior_distancia){ 
                maior_distancia = matriz_resul.get_elem(i,j); //Descobre qual o maior elemento da matriz resultante, ou seja, a maior distancia
            }
            
        }
    }


    //Se a chamada for apenas para calcular a distancia a função vai imprimir a matriz com os resultados
    for(int i = 0; i < linha_reduzida; i++){

            for(int j = 0; j < coluna_reduzida; j++){

                resumo += round(matriz_resul.get_elem(i,j)); //Faz o calculo do resumo
                if(tipo == "distancia")cout << round(matriz_resul.get_elem(i,j)) << " ";
            }
            if(tipo == "distancia")cout << endl;
    }

    //Se a chamada for apenas para imprimir a matriz com cores a função vai imprimir a matriz com os resultados
    if(tipo == "cor"){
        //Calcula o dist_percent de cada elemento da matriz e converte para RGB 
        for(int i = 0; i < linha_reduzida; i++){

            for(int j = 0; j < coluna_reduzida; j++){

                matriz_resul.set_elem(i,j,dist_percent(matriz_resul.get_elem(i,j), maior_distancia));
                geraCorDist(matriz_resul.get_elem(i,j));
            }
            cout << endl;
        }
    }

    if(tipo == "resumo") cout << resumo << endl;

}

//Função para calcular distancia melhorada
template <class T>
void MyMatrix<T>::distancia_melhorado(string tipo){

    int linha_reduzida = this->linhas; //Recebe o tamanho da matriz reduzida 
    int coluna_reduzida = this->colunas/3; //Recebe as colunas em tamanho reduzido, para pegar apenas um número ao invés de 3 do RGB
    MyVec<Par> vetor_pretos; //Vetor que armazena a posição dos pixels pretos
    double distancia;
    double maior_distancia; 
    unsigned long long resumo = 0;


    MyMatrix<double> matriz_resul(linha_reduzida, coluna_reduzida); //Matriz simplificada, não RGB



    //Transformar a matriz RGB para uma matriz comum, ou seja, com apenas um elemento por coluna
    //Matriz rgb = matriz
    //Matriz resumida = matriz_resul
    for(int i = 0; i < linha_reduzida; i++){

        for(int j = 0; j < this-> colunas; j+=3){ //Percorre a matriz pulando a coluna de 3 em 3

            if(matriz[i][j] == 0){
                matriz_resul.set_elem(i,j/3,0); //Se for um pixel preto, atualiza sua distancia para 0
            }
            else{
                 matriz_resul.set_elem(i,j/3,-1); //Se não for um pixel preto, atualiza sua distancia para -1
            }
        } 
    }


    //Percorrer a matriz e descobrir a posição dos pontos pretos
    for(int i = 0; i < linha_reduzida; i++){

        for(int j = 0; j < coluna_reduzida; j++){

            if(matriz_resul.get_elem(i,j) == 0){
                vetor_pretos.push_back({i,j});
            }
        }
    }
    
    //Vai percorrer os pares de posicoes do vetor que armazena os pixels pretos
    for(int i = 0; i < linha_reduzida; i++){

        for(int j = 0; j < coluna_reduzida; j++){

            for (int k = 0; k < vetor_pretos.size(); k++) { // Percorre o vector dos pixels pretos

                distancia = calcula_euclid(i,vetor_pretos[k].x,j,vetor_pretos[k].y); //Calcula a distancia euclidiana entre os pixels 
                if(distancia < matriz_resul.get_elem(i,j) || matriz_resul.get_elem(i,j) == -1){ //Se a distancia for menor que a distancia armazenada na matriz ou se a distancia for -1
                    matriz_resul.set_elem(i,j,distancia); //Mantem na posição da matriz a menor distancia encontrada
                    }
            }
            if(matriz_resul.get_elem(i,j) > maior_distancia){ 
                maior_distancia = matriz_resul.get_elem(i,j); //Descobre qual o maior elemento da matriz resultante, ou seja, a maior distancia
            }
        }    
    }
    
    //Se pedir para calcular as distancias, a matriz resultante será impressa 
    
    for(int i = 0; i < linha_reduzida; i++){

        for(int j = 0; j < coluna_reduzida; j++){

            resumo += round(matriz_resul.get_elem(i,j)); //Faz o calculo do resumo
            if(tipo == "distancia")cout <<round(matriz_resul.get_elem(i,j)) << " ";
        }
            if(tipo == "distancia")cout << endl;
        
    }
    if(tipo == "cor"){
        //Calcula o dist_percent de cada elemento da matriz e converte para RGB 
        for(int i = 0; i < linha_reduzida; i++){

            for(int j = 0; j < coluna_reduzida; j++){

                matriz_resul.set_elem(i,j,dist_percent(matriz_resul.get_elem(i,j), maior_distancia));
                geraCorDist(matriz_resul.get_elem(i,j));
            }

            cout << endl;
        }
    }
    
    if(tipo == "resumo")cout << resumo << endl;

}



//Função para calcular distancia eficiente
template <class T>
void MyMatrix<T>::distancia_eficiente(string tipo){

    int linha_reduzida = this->linhas; //Recebe o tamanho da matriz reduzida 
    int coluna_reduzida = this->colunas/3; //Recebe as colunas em tamanho reduzido, para pegar apenas um número ao invés de 3 do RGB
    MyPriorityQueue<fila> Fila; //Fila de prioridades que recebe a posição x e y do elemento e a sua distancia
    double distancia;
    unsigned long long resumo = 0;
    double maior_distancia;

    MyMatrix<double> matriz_resul(linha_reduzida, coluna_reduzida); //Matriz reduzida da matriz original

    //Transformar a matriz RGB para uma matriz comum, ou seja, com apenas um elemento por coluna 
    //Matriz rgb = matriz
    //Matriz resumida = matriz_resul
    for(int i = 0; i < linha_reduzida; i++){

        for(int j = 0; j < this->colunas; j+=3){ //Percorre a matriz pulando a coluna de 3 em 3

            if(matriz[i][j] == 0){ 
                matriz_resul.set_elem(i,j/3,0); //Se for um pixel preto, atualiza sua distancia para 0
                Fila.push({i,j/3,matriz_resul.get_elem(i,j/3)}); //Adiciona na fila de prioridade
            }
            else{
                 matriz_resul.set_elem(i,j/3,-1); //Se não for um pixel preto, atualiza sua distancia para -1
            }

        } 
    }

    double distancia_total;

    while(Fila.size() != 0){ //Enquanto não forem checados todos os elementos

        for(int i = -1; i < 2; i++){  //For que vai percorrer apenas os vizinhos dos pixels que estão na fila de prioridades

            for(int j = -1; j < 2; j++){

               long long int linha = Fila.top().x+i; //Posição real da lihna dos pixels vizinhos
               long long int coluna = Fila.top().y+j; //Posição real da coluna dos pixels vizinhos

                //Condição principal para definir a distancia máxima para o calculo, nesse caso, pegamos apenas os vizinhos que estão em uma posição válida
                if((linha >= 0 && coluna >= 0 && linha < linha_reduzida && coluna < coluna_reduzida) && !(linha == Fila.top().x && coluna == Fila.top().y)){
                    
                    // Fila.top().x é a posição x do elemento da frente da fila e Fila.top().y é a posição y
                    distancia = calcula_euclid(linha, Fila.top().x, coluna, Fila.top().y); //Calcula a distancia do elemento até a distancia armazenada na lista
                    distancia_total = distancia + (Fila.top().dist*-1) ;
                    distancia_total = floor((distancia_total) * 10) / 10; //Faz o arredondamento para manter sempre entre 1 e 1.4

                    
                        //Se o elemento da fila for um pixel preto && o elemento que será calculado não for um pixel preto  
                        if(Fila.top().dist == 0 && matriz_resul.get_elem(linha,coluna) != 0 )  { 

                            matriz_resul.set_elem(linha,coluna,distancia_total); //recebe a Distancia total 
                            Fila.push({linha,coluna,distancia_total*-1}); //Coloca o elemento que teve a distancia modificada na fila

                        }

                        //Se o elemento da fila não for um pixel preto  
                        else if(Fila.top().dist != 0 ){  

                            //Se a distancia total for maior que a distancia do elemento em questão && se a distancia atual for -1
                            if(distancia_total > matriz_resul.get_elem(linha,coluna) && matriz_resul.get_elem(linha,coluna) == -1){

                                matriz_resul.set_elem(linha,coluna,distancia_total); //recebe a Distancia total 
                                Fila.push({linha,coluna,distancia_total*-1}); //Coloca o elemento que teve a distancia modificada na fila

                            }
                            //Se a distancia total for menor que a distancia do elemento em questão 
                            else if(distancia_total < matriz_resul.get_elem(linha,coluna)){

                                matriz_resul.set_elem(linha,coluna,distancia_total); // recebe a Distancia total 
                                Fila.push({linha,coluna,distancia_total*-1}); //Coloca o elemento que teve a distancia modificada na fila
                                
                            }

                        }
                    
                }
              }
            }
        
        
        Fila.pop(); //Avança na fila
    }


    //Percorre a matriz resultante
    for(int i = 0; i < linha_reduzida; i++){

            for(int j = 0; j < coluna_reduzida; j++){

                if(matriz_resul.get_elem(i,j) > maior_distancia){ 

                    maior_distancia = matriz_resul.get_elem(i,j); //Descobre qual a maior distancia 

                }

                resumo += round(matriz_resul.get_elem(i,j)); //Calcula resumo
                if(tipo == "distancia")cout << round(matriz_resul.get_elem(i,j))<< " "; //Se pedir para calcular distancias imprime a matriz

            }
        if(tipo == "distancia")cout << endl;//Se pedir para calcular distancias imprime a matriz
        }


    //Se pedir para fazer o metodo de cor
    if(tipo == "cor"){
        //Calcula o dist_percent de cada elemento da matriz e converte para RGB 
        for(int i = 0; i < linha_reduzida; i++){

            for(int j = 0; j < coluna_reduzida; j++){

                matriz_resul.set_elem(i,j, dist_percent(matriz_resul.get_elem(i,j), maior_distancia)); //Coloca no lugar do elemento original sua distpercent
                geraCorDist(matriz_resul.get_elem(i,j)); //Converte para RGB

            }
            cout << endl;
        }
    }

    if(tipo == "resumo") cout << resumo << endl;
        
}




//Metodo para converter o numero para um numero real entre 0 e 1
template <class T>
double MyMatrix<T>::dist_percent(double elem, double maior_dist){
    return elem/maior_dist;
}

//Funçao para converter para RGB
template <class T>
int MyMatrix<T>::geraCorDist(double elem) {

	if(elem <= 0.00000001) {
		cout << 0 << " " << 0 << " " << 0 << " ";
        return 1;
	}
	hsv corHSV;
	corHSV.h = 360*elem; //A entrada da funcao hsv2rgb usa valores de h entre 0 e 360 
	corHSV.s = 1;
	corHSV.v = 1;
	rgb c = hsv2rgb(corHSV);

    int rgbR = c.r*255; //Os componentes rgb gerados pela funcao hsv2rgb estao entre 0 e 1 --> precisamos converter para algo entre 0 e 255
    int rgbG = c.g*255;
    int rgbB = c.b*255;

    //rgbR,rgbG e rgbB sao os componentes RGB gerados. Adapte o resto do codigo para que ele retorne a cor utilizando o tipo que voce criou no seu trabalho...
	cout << rgbR << " " << rgbG << " " << rgbB << " ";
    return 1;
}




#endif