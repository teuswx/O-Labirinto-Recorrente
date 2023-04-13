#include "Labirinto.hpp"
Labirinto::Labirinto(int tam_matriz_vector, int tam_matriz, vector<string> matrizes_name, vector<string> matrizes_name_aux)
{
    this->tam_matriz_vector = tam_matriz_vector;
    this->tam_matriz = tam_matriz;
    this->matrizes_name = matrizes_name;
    this->matrizes_name_aux = matrizes_name_aux;

    // aloca espaço para a matriz
    matriz = new int *[tam_matriz];
    for (int i = 0; i < tam_matriz; i++)
    {
        matriz[i] = new int[tam_matriz];
    }
    // cria a matriz axiliar dos arquivos
    matriz_aux = new short int *[tam_matriz];
    for (int i = 0; i < tam_matriz; i++)
    {
        matriz_aux[i] = new short int[tam_matriz];
    }
}

// função para imprimir a matriz
void Labirinto::imprimir()
{
    fstream arquivo;
    string aux;

    for (int x = 0; x < tam_matriz_vector; x++)
    {
        arquivo.open(matrizes_name[x]);
        arquivo >> aux;
        for (int i = 0; i < tam_matriz; i++)
        {
            for (int j = 0; j < tam_matriz; j++)
            {
                arquivo >> matriz[i][j];
                cout << matriz[i][j] << "\t";
            }
            cout << "\n";
        }
        cout << "\n";
        arquivo.close();
    }
}

// função para carregar a matriz e preencher
void Labirinto::comecar_matriz(int x)
{
    ifstream arquivo, arquivo_aux;
    string valor;

    arquivo.open(matrizes_name[x]);
    arquivo >> valor;
    for (int i = 0; i < tam_matriz; i++)
    {
        for (int j = 0; j < tam_matriz; j++)
        {
            arquivo >> valor;
            if (valor == "#")
            {
                matriz[i][j] = -1;
            }
            else if (valor == "*")
            {
                matriz[i][j] = -2;
            }
            else
            {
                matriz[i][j] = stoi(valor);
            }
        }
    }
    arquivo.close();

    arquivo_aux.open(matrizes_name_aux[x]);

    for (int i = 0; i < tam_matriz; i++)
    {
        for (int j = 0; j < tam_matriz; j++)
        {
            arquivo_aux >> valor;
            matriz_aux[i][j] = stoi(valor);
            
        }
    }
    arquivo_aux.close();

}

// função apra sobreescrever a matriz para salvar os dados das casas
void Labirinto::sobreescrever_matriz(int x)
{
    ofstream arquivo, arquivo_aux;

    arquivo.open(matrizes_name[x]);
    arquivo_aux.open(matrizes_name_aux[x]);
    arquivo << 1 << "\n";
    for (int i = 0; i < tam_matriz; i++)
    {
        for (int j = 0; j < tam_matriz; j++)
        {
            arquivo << matriz[i][j] << "\t";
            arquivo_aux << matriz_aux[i][j] << "\t";
        }
        arquivo << "\n";
        arquivo_aux << "\n";
    }
    arquivo.close();
    arquivo_aux.close();

}
// função apra verificar se o algortimo já passou em todas matrizes
bool Labirinto::verifica_passagem_matriz()
{ 
    fstream arquivo;
    string aux1;
    int aux;
    for (int x = 0; x < tam_matriz_vector; x++)
    {
        arquivo.open(matrizes_name[x]);

        arquivo >> aux1;
        aux = stoi(aux1);

        if (aux == 1)
        {
            verifica = true;
        }
        else
        {
            verifica = false;
        }
        arquivo.close();
    }
    return verifica;
}

//função para verificar quantas casas da matriz o persongame passou e quantas não
void Labirinto::verifica_casas(){
    fstream arquivo;
    string aux;
    int cont_passou, cont_nao_passou;

    
    cont_passou = 0;
    for (int x = 0; x < tam_matriz_vector; x++)
    {
        cont_nao_passou = 0;
        arquivo.open(matrizes_name_aux[x]);

        for (int i = 0; i < tam_matriz; i++)
        {
            for (int j = 0; j < tam_matriz; j++)
            {
                arquivo >> matriz_aux[i][j];
                if(matriz_aux[i][j] == 1){
                    cont_passou++;
                }else if(matriz_aux[i][j] == 0 || matriz_aux[i][j] == -2){
                    cont_nao_passou++;
                }
               
            }
        }
        arquivo.close();
        cout << "--------------------------------------------------------------\n";
        cout << "Quantidade de casas não percorridas da matriz " << x << " : " << cont_nao_passou << endl;
    }
    cout << "--------------------------------------------------------------\n";
    cout << "Quantidade total de casas percorridas: " << cont_passou<< endl;
}
// retorna 1 ou 2 para gerar as posições aleatorias
int Labirinto::numero_aleatorio()
{
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(-1, 1);
    return dist(mt);
}
// retorna um numero de 0 até o tamanho desejado para teletransportar o personagem
int Labirinto::numero_aleatorio_teletransporte(int tam)
{
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, tam);
    return dist(mt);
}

// função para começar o algortimo (jogo)
void Labirinto::caminho()
{

    int i_aux, j_aux, i, j, x, item, perigo; // define as variaveis de controle do algoritmo
    bool caminho = true, caminho_zero = false; // define a variavel de controle do loop
    vida_tchola = 10;

    item = 0;
    perigo = 0;
    do
    {
        cout << "Digite em qual matriz voce quer começar a partir de 0: "; // matriz definida pelo usuário
        cin >> x;
    } while (x < 0 || x > tam_matriz_vector);
    
   
    x_inicial = x;                                              

    comecar_matriz(x); // inicializa a matriz

    do
    { 
        cout << "Digite a posição x inicial do seu personagem: "; // posição de linha definida pelo usuário
        cin >> i;
        cout << "Digite a posição y inicial do seu personagem: "; // posição de coluna definida pelo usuário
        cin >> j;
        if(matriz[i][j] == -1){
            cout << "\nAtenção! essa posição é uma parede o personagem não pode começar ai\n";
            cout << "\n\nDigite novamente\n\n";
        }
    } while (matriz[i][j] == -1 || i < 0 || i > tam_matriz || j < 0 || j > tam_matriz); // enquanto for igual uma # o do while realiza teletransporte

    // guarda a posição inicial do personagem
    i_inicial = i;
    j_inicial = j;
    

    while (caminho)
    {
        // começo real do jogo
        do{
            i_aux = numero_aleatorio();
            j_aux = numero_aleatorio();
        }while (i_aux == 0 && j_aux == 0);

        // inicio do personagem
        i += i_aux;
        j += j_aux;

        verifica_passagem_matriz(); // verifica se ja passou em todas matrizes
        
        if (x_inicial == x && j_inicial == j && i_inicial == i && caminho_zero == true && verifica_passagem_matriz() == true)
        { // verifica se todos os critérios de parada do jogo foi atendido
            caminho = false;
            cout << "\n\n!Você chegou ao fim do jogo!\n\n";
        }
        else if (i < 0 || i > tam_matriz - 1 || j < 0 || j > tam_matriz - 1) // caso o personagem caminhe para fora dos limites da matriz ele entra em um portal
        {
            sobreescrever_matriz(x);
            x = numero_aleatorio_teletransporte(tam_matriz_vector - 1);
            comecar_matriz(x);
            do
            {
                i = numero_aleatorio_teletransporte(tam_matriz - 1);
                j = numero_aleatorio_teletransporte(tam_matriz - 1);

            } while (matriz[i][j] == -1);

            if (matriz[i][j] == -2)
            {
                vida_tchola--;
                if (vida_tchola == 0)
                {
                    cout << "\n\n!Voce morreu!\n\n";
                    caminho = false;
                }
                matriz_aux[i][j] = 1;
                perigo++;
            }
            else if (matriz[i][j] != 0) // caso seja um numero inteiro positio não nulo
            {
                sacola++;
                if (vida_tchola < 10 && sacola == 4)
                {
                    vida_tchola++;
                    sacola -= 4;
                }
                else if (sacola >= 4)
                {
                    sacola = 0;
                }
                matriz[i][j]--;
                item++;
                matriz_aux[i][j] = 1;
                caminho_zero = false;
            }
            else if (matriz[i][j] == 0)
            {
                matriz_aux[i][j] = 1;
            }
        }
        else if (matriz[i][j] == -1) // caso o personagem caminhe para uma parede
        {
            i -= i_aux;
            j -= j_aux;
        }
        else if (matriz[i][j] == -2) // caso o personagem encontre um perigo
        {
            vida_tchola--;
            if (vida_tchola == 0)
            {
                cout << "\n\nVoce morreu!\n\n";
                caminho = false;
            }
            matriz_aux[i][j] = 1;
            perigo++;
        }
        else if (matriz[i][j] != 0) //caso seja um numero inteiro positio não nulo
        {
            sacola++;
            if (vida_tchola < 10 && sacola == 4)
            {
                vida_tchola++;
                sacola -= 4;
            }
            else if (sacola >= 4)
            {
                sacola = 0;
            }
            matriz[i][j]--;
            item++;
            matriz_aux[i][j] = 1;
            caminho_zero = false;
        }
        else if (matriz[i][j] == 0) 
        {
            matriz_aux[i][j] = 1;
        }

        if(i_inicial == i && j_inicial == j){ // começa a partida do caminho caso o personagem chegue na posição incial
            caminho_zero = true;
        }
    }

    verifica_casas();
    cout << "--------------------------------------------------------------\n";
    cout << "Quantidade de itens consumidos: " << item << "\n";
    cout << "--------------------------------------------------------------\n";
    cout << "Quantidade de perigos enfrentados: " << perigo << "\n";
    cout << "--------------------------------------------------------------\n";
    cout << "Matriz final: \n\n";
}