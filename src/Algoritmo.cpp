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
    int l, c, q_matrizes;
    string descartar;

    // lê o tamanho da matriz
    arquivo_entrada >> l >> c;
    arquivo_entrada >> descartar;
    q_matrizes = stoi(descartar);
    int k = 0;

    // aloca esoaço para a matriz
    string **matriz = new string *[l];
    for (int i = 0; i < l; i++)
    {
        matriz[i] = new string[c];
    }

    while (k != q_matrizes)
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

                if (matriz[i][j] == "#")
                {
                    arquivo_saida<< -1 << "\t";
                }
                else if (matriz[i][j] == "*")
                {
                    arquivo_saida << -2 << "\t";
                }else{
                    arquivo_saida << matriz[i][j] << "\t";
                }
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
                if (matriz[i][j] == "*")
                {
                    arquivo_saida_confere << "-2" << "\t";
                }
                else if (matriz[i][j] == "#")
                {
                    arquivo_saida_confere << "-1" << "\t";
                }
                else
                {
                    arquivo_saida_confere << "0" << "\t";
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
    string teste;
    ofstream arquivo_final("dataset/output.data");
    if (!arquivo_final)
    {
        throw "../main.cpp::lerTxt ---> Não foi possível abrir o arquivo";
    }
    ofstream arquivo_final_aux("dataset/caminhos_passados.data");
    if (!arquivo_final_aux)
    {
        throw "../main.cpp::lerTxt ---> Não foi possível abrir o arquivo";
    }

    ifstream arquivo_inicial;
    ifstream arquivo_inicial_aux;
    int x;
    x = 0;
    for (x = 0; x < k; x++)
    {

        arquivo_inicial.open(matrizes_name[x]);
        if (!arquivo_inicial)
        {
            throw "../main.cpp::lerTxt ---> Não foi possível abrir o arquivo";
        }
        arquivo_inicial >> teste;
        arquivo_inicial_aux.open(matrizes_name_aux[x]);
        if (!arquivo_inicial_aux)
        {
            throw "../main.cpp::lerTxt ---> Não foi possível abrir o arquivo";
        }
        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < c; j++)
            {
                arquivo_inicial >> teste;
                arquivo_final << teste << "\t";
                arquivo_inicial_aux >> teste;
                arquivo_final_aux << teste << "\t";
            }
            arquivo_final << endl;
            arquivo_final_aux << endl;
        }
        arquivo_final << "\n";
        arquivo_final_aux << "\n";
        arquivo_inicial.close();
        arquivo_inicial_aux.close();
    }

    arquivo_final.close();
    arquivo_final_aux.close();

    for(int i=0; i < k; i++){
        remove(matrizes_name_aux[i].c_str());
        remove(matrizes_name[i].c_str());
    }
}