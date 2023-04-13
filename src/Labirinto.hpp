#ifndef _LABIRINTO_HPP
#define _LABIRINTO_HPP
#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <set>
using namespace std;

class Labirinto{
    private:
    int tam_matriz_vector, vida_tchola, sacola,tam_matriz, **matriz, x_inicial, i_inicial, j_inicial;
    bool verifica;
    short int **matriz_aux;
    vector<string> matrizes_name, matrizes_name_aux;

    public:
    Labirinto(int tam_matriz_vector, int tam_matriz, vector<string> matrizes_name, vector<string> matrizes_name_aux);
    void setVida(int vida);
    int getVida();
    void imprimir();  
    int numero_aleatorio();
    int numero_aleatorio_teletransporte(int tam);
    void caminho();
    void comecar_matriz(int x);
    void sobreescrever_matriz(int x);
    void imprimir_carregada();
    bool verifica_passagem_matriz();
    void verifica_casas();
};
#endif