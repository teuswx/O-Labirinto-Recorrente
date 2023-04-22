> Status Development: finished :heavy_check_mark:

# O Labirinto Recorrente

## Objetivo 🎯

O jogo simula vários labirintos onde o jogador deve chegar à posição inicial após percorrer um caminho com todos itens consumidos. No entanto, existem barreiras e portais que o jogador pode encontrar, as quais o desviarão aleatoriamente. Além disso, o jogador possui apenas 10 vidas, o que significa que se ele ficar sem pontos de vida, o jogo termina.

Para ajudar a entender melhor o jogo, imagine que você é um explorador dentro de um labirinto e seu objetivo é encontrar o caminho de volta para a posição inicial. No entanto, para fazer isso, você deve coletar todos os itens no caminho até que sua rota não possua mais itens. Mas cuidado! Existem barreiras e portais que o levarão a caminhos aleatórios, o que pode tornar a sua missão ainda mais desafiadora. E lembre-se, você só tem 10 vidas para completar o seu objetivo.

## Lógica :bulb:

Para começar o programa o arquivo "input.data" deverá ser inserido na pasta "dataset", possuir matrizes com o tamanho de linhas, colunas e quantidade de matrizes já definidas na primeira linha, posteriormente conter números positivos(itens), #(barreiras) e *(perigos). Arquivo exemplo:
##### input.data
![image_2023-04-10_220838468](https://user-images.githubusercontent.com/102326098/231029225-c008ab0e-ad25-4e98-b8f6-83db873285b7.png)

Para evitar o erro "stack overflow", o código da classe *Algoritmo.cpp* separa cada matriz em arquivos diferentes junto de seus auxiliares na pasta dataset. Posteriormente é instânciado um contrutor da classe *Labirinto* na qual é passado como parâmetro o tamanho do vector de nomes dos arquivos(*k*), o tamanho da matriz quadrada(*l*), um vector dos nomes dos arquivos gerados(*matrizes_name*) e um vector dos nomes dos arquivos auxiliares gerados(*matrizes_name_aux*).

Os Arquivos auxiliares são criados para facilitar a verificação de passagem, no caso do programa, se o personagem passou em todas matrizes antes de chegar no seu objetivo.

Para gerar os números aleatórios fui utilizado a biblioteca random, o código foi implementado nos métodos Labirinto::numero_aleatorio e Labirinto::numero_aleatorio_telestransporte na classe *Labirinto*. A definição random_device gera um número imprevisível, porém em um tempo mais lento, o que é perfeito para uitlizar como semente para um gerador rápido como o [Mersenne Twister](https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/) na definição mt19937, e por fim, colocando esses números em um intervalo utilizando a definição uniform_int_distribution dist(). Método exemplo: 
<pre>
    <code>
        
       int Labirinto::numero_aleatorio()
        {
            random_device rd;
            mt19937 mt(rd());
            uniform_int_distribution<int> dist(-1, 1);
            return dist(mt);
        }
        
    </code> 
</pre>
O algoritmo do jogo foi desenvolvido na classe *Labirinto.cpp* no método Labirinto::caminho. Para definir o caminhamento, foi necessário carregar a matriz inicial no método Labirinto::comecar_matriz no atributo matriz, após esse processo, será gerado uma posição aleatória inicial para o personagem na matriz. Contudo, essa posição foi trata utilizando um do while para verificar se existe uma barreira, caso exista, outra posição será gerada. A posição incial é guardada nas variáveis x_inicial(matriz inicial), i_incial(linha inicial) e j_inicial(coluna incial).


A estrutura condicional do jogo é definida da seguinte maneira:

**Obs**
Antes da primeira condição existem variáveis i e j auxiliares recebendo os numeros -1, 1 e 0 aleatoriamente da função  numero_aleatorio() citada anteriormente, que são somadas as variáveis i e j atuais que geram a próxima posição em volta do personagem.

![Screenshot from 2023-04-11 13-27-07](https://user-images.githubusercontent.com/102326098/231227983-659c8a41-c866-4858-a25f-a73122fc22db.png)

<pre>
    <code>
        enquanto(caminho for verdadeiro){
            
            se(condição 1){
                //código
            }se não se(condição 2){
                //código
            }se não se(condição 3){
                //código
            }se não se(condição 4){
                //código
            }se não se(condição 5){
                //código
            }se não se(condição 6){
                //código
            }
        }

        if(condição 7){
            //código
        }
    </code>
</pre>

* **condição 1**: Verifica se o personagem cumpriu com os objetivos do jogo, ou seja, se ele chegou na posição incial, se o caminho percorrido não possuia itens e se houve passagem em todas as matrizes.

* **condição 2**: Verifica se o personagem está prestes a se mover para fora da matriz. Caso isso aconteça, a matriz atual será sobreescrita e vai ser gerado uma nova posição aleátoria para o personagem sempre verificando os casos em que há parede, perigo, ou itens.

* **condição 3**: Se o personagem encontrar uma parede ele volta para posição anterior.

* **condição 4**: Se o personagem encontrar um perigo será subtraido 1 de sua vida, caso sua vida seja igual a 0, o jogo acaba.

* **condição 5**: Se o personagem encontrar um numero diferente de 0 é subtraido1 item da posição, adicionado 1 ao contador item, o contador boleano caminho de itens zerados recebe falso e a variável sacola recebe 1, se sacola for igual a 4, é acrescentado 1 a vida do personagem.

* **condição 6**: Se o numero for igual a 0, o caminho continua sendo verdadeiro, o que mantém o laço enquanto.

* **condição 7**: Se a posição inicial for igual a posição atual, o contador booleano de caminho de intens zerados é verdadeiro.

## Exemplo de execução :hammer: 

**Arquivo**

![Screenshot from 2023-04-12 09-09-58](https://user-images.githubusercontent.com/102326098/231454162-93e368bd-c8c5-45a7-a935-a5fa518118a9.png)

**Execução**

![image](https://user-images.githubusercontent.com/102326098/233474766-c9c3e927-f1cc-4fc6-8804-4b129b682e3a.png)

**Arquivo das posições passadas**

![Screenshot from 2023-04-12 09-14-55](https://user-images.githubusercontent.com/102326098/231454890-02a7ea1b-c57b-4b01-b493-7c2c68272ba3.png)

## Perguntas ❓

**1. Há mais de uma maneira de resolver esse problema ?**

Resposta: Como o programa é bastante parecido com um jogo, as possibilidades para criar regras e percursos são altamente amplas. Logo, existem maneiras variadas de resolver o problema em questão. Como, por exemplo,  estruturas de controle para verificar os casos específicos em que o personagem pode ou não entrar em um portal para outra matriz.

**2. Qual o custo computacional gerado pelo programa?**

Devido a quantidade de laços de repetição e estruturas de controle para manipular os dados fornecidos, o custo principal é kn²m, Onde k é um número aleátorio, pois depende de como o programa vai se comportar, n é o tamanho da matriz e m é a quantidade de matrizes. Este é o pior custo gerado pelo programa pois ocorre quando o algoritmo percorre todas as casas(n) e matrizes(m) em uma quantidade aleátoria de veze(k).
## Conclusão :ballot_box_with_check:

Durante o desenvolvimento do projeto que envolveu a manipulação de matrizes, enfrentou-se o desafio de encontrar maneiras eficientes de percorrer e acessar seus elementos. Foi elaborado um código que envolveu múltiplos laços de repetição, o que nos levou a pensar em técnicas de otimização para minimizar o custo computacional.

Ao concluir o projeto, foi possível analisar cuidadosamente o custo computacional de todo o processo, que se mostrou bastante complexo. A análise nos permitiu identificar gargalos de desempenho e implementar técnicas como a redução de operações redundantes e a utilização de estruturas de dados mais eficientes.

Essa experiência proporcionou um aprendizado valioso sobre técnicas de otimização de código, que podem ser aplicadas em projetos futuros. Esse conhecimento é fundamental para o desenvolvimento de soluções eficientes e escaláveis em diferentes áreas.
## Compilação e Execução :electric_plug:

O programa foi feito de acordo com a proposta e possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:
| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

</body>
