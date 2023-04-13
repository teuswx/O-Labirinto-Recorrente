#include "Algoritmo.hpp"

Algoritmo::Algoritmo()
{
}

// O método algoritmo irá ler os dados do arquivo
void Algoritmo::algoritmo()
{
    // cria o arquivo de leitura
    ifstream arquivo_entrada("dataset/input.data");
    if (!arquivo_entrada)
    {
        throw "../main.cpp::lerTxt ---> Não foi possível abrir o arquivo de entrada";
    }
    cout << "\n\n";
    int l, c;

    // lê o tamanho da matriz
    arquivo_entrada >> l >> c;

    int k = 0;

    // aloca esoaço para a matriz
    string **matriz = new string *[l];
    for (int i = 0; i < l; i++)
    {
        matriz[i] = new string[c];
    }
    
    while (!arquivo_entrada.eof())
    {
        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < c; j++)
            {
                arquivo_entrada >> matriz[i][j];
            }
        }

        // possibilita guardar os nomes dos arquivos e posteirormente ler eles aleatoriamente
        matrizes_name.push_back("dataset/matriz_" + to_string(k) + ".data");

        ofstream arquivo_saida(matrizes_name[k]);
        if (!arquivo_saida)
        {
            throw "../main.cpp::lerTxt ---> Não foi possível abrir o arquivo de saida";
        }

        arquivo_saida << 0 << "\n"; // adiciona um 0 na matriz para verificar se o algoritmo já passou por ela
        
        // Escrever elementos da matriz no arquivo de saída
        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < c; j++)
            {
                arquivo_saida << matriz[i][j] << "\t";
            }
            arquivo_saida << endl;
        }
        arquivo_saida.close();

        matrizes_name_aux.push_back("dataset/matriz_" + to_string(k) + "_aux.data");
        ofstream arquivo_saida_confere(matrizes_name_aux[k]);
        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < c; j++)
            {   
                if(matriz[i][j] == "*"){
                    arquivo_saida_confere << -2 << "\t";
                }else if(matriz[i][j] == "#"){
                    arquivo_saida_confere << -1 << "\t";
                }else{
                    arquivo_saida_confere<< 0 << "\t";
                }
            }
            arquivo_saida_confere << "\n";
        }
        arquivo_saida_confere.close();

        k++;

    }
    // Desalocar memória da matriz
    for (int i = 0; i < l; i++)
    {
        delete[] matriz[i];
    }
    delete[] matriz;

    arquivo_entrada.close();

    Labirinto la(k, l, matrizes_name, matrizes_name_aux);
    la.caminho();
    la.imprimir();

}