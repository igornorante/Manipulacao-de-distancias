#include <iostream> 
#include <iomanip>
#include <cmath>
#include <cstring>
#include <string>
#include "MyMatrix.h"
#include "MyPriorityQueue.h"
#include "MyVec.h"
using namespace std;


int main(int argc, char *argv[]){

if (argc < 2) {
    cerr << "Uso: " << argv[0] << " <argumento>" << endl;
    return 1;
}

string algoritmo = argv[1];
string modo_saida = argv[2];



if(algoritmo == "trivial"){

    string tam;
    int L, A, Tipo;
    double elem;
    cin >> tam;
    cin >> L >> A; 
    cin >> Tipo;

    MyMatrix<double> matriz(A,L*3);

    for(int i = 0; i < A; i++){
        for(int j = 0; j < L*3; j++){
            cin >> elem;
            matriz.set_elem(i,j,elem);
        }
    }

    if(modo_saida == "distancia"){
     matriz.distancia(modo_saida);
    }

    if(modo_saida == "resumo"){
    matriz.distancia(modo_saida);
    }

    if(modo_saida == "cor"){
        cout << tam << "\n";
        cout << L << " " << A <<"\n";
        cout << Tipo << endl; 
        matriz.distancia(modo_saida);
    }

}

if(algoritmo == "melhorado"){

    string tam;
    int L, A, Tipo;
    double elem;
    cin >> tam;
    cin >> L >> A; 
    cin >> Tipo;

    MyMatrix<double> matriz(A,L*3);

    for(int i = 0; i < A; i++){
        for(int j = 0; j < L*3; j++){
            cin >> elem;
            matriz.set_elem(i,j,elem);
        }
    }

    if(modo_saida == "distancia"){
     matriz.distancia_melhorado(modo_saida);
    }
    if(modo_saida == "resumo"){
    matriz.distancia_melhorado(modo_saida);
    
    }
    if(modo_saida == "cor"){
        cout << tam << "\n";
        cout << L << " " << A <<"\n";
        cout << Tipo << endl; 
        matriz.distancia_melhorado(modo_saida);
    }

}


if(algoritmo == "eficiente"){

    string tam;
    int L, A, Tipo;
    double elem;
    cin >> tam;
    cin >> L >> A; 
    cin >> Tipo;


    MyMatrix<double> matriz(A,L*3);

    for(int i = 0; i < A; i++){
        for(int j = 0; j < L*3; j++){
            cin >> elem;
            matriz.set_elem(i,j,elem);
        }
    }
    

    if(modo_saida == "distancia"){
     matriz.distancia_eficiente(modo_saida);
    }
    if(modo_saida == "resumo"){
    matriz.distancia_eficiente(modo_saida);
    }
    if(modo_saida == "cor"){
        cout << tam << "\n";
        cout << L << " " << A <<"\n";
        cout << Tipo << endl; 
        matriz.distancia_eficiente(modo_saida);
    }

}



return 0;
}







