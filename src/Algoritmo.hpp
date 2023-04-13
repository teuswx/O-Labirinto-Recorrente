#include "Labirinto.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Algoritmo
{   private:
        vector<string> matrizes_name, matrizes_name_aux; ;
    public:
        Algoritmo();
        void algoritmo();
        void imprimir_matriz();
};