/*
Name:  Wesley Tiozzo
N#: 8077925
Institution: ICMC - USP São Carlos
Course: Introduction to Computer Science I (2012)


Tic Tac Toe
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define P1 'X'
#define P2 'O'

char** iniciar(){
    char **M; 
    int i, j;
    M = (char**)malloc(3*sizeof(char*)); 
    for(i = 0;i<3;i++) M[i] = (char*)malloc(3*sizeof(char)); 
    /*
    _|_|_
    _|_|_
     | |
    */
    for(i=0;i<2;i++)
        for(j=0;j<3;j++)
            M[i][j] = '_';
    for(j=0;j<3;j++)
        M[2][j] = ' ';
    return M;
}

void desenha(char **M){
    int i, j;
    for(i=0;i<3;i++){
        for(j=0;j<2;j++){
            printf("%c|", M[i][j]);
        }
        printf("%c\n", M[i][2]);
    }
}

/*Verifica se a jogada foi valida ou nao
Entrada: matriz e posicoes de jogada
Saida: 0 caso posicao invalida, 1 caso posicao valida*/
int posicao_vazia(char **M, int linha, int coluna){
    if((linha < 0) || (linha > 2))  return 0;
    if((coluna < 0) || (coluna > 2))  return 0;
    if((M[linha][coluna] == ' ') || (M[linha][coluna] == '_'))
        return 1;
    return 0;
}

/*Executa a jogada do usuario*/
void jogada(char **M, char player){
    int cont = 1;
    int i, j;
    while(cont == 1){
        printf("\nDigite a jogada: ");
        scanf("%d %d", &i, &j);
        if(posicao_vazia(M, i, j) == 1) cont = 0;
        else printf("posicao invalida\n");
    }
    M[i][j] = player;
}

/*Jogada de nivel de dificuldade facil(sequencial)*/
void jogada_easy(char **M, char player){
    int i, j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if((M[i][j] == ' ') || (M[i][j] == '_')){ 
                M[i][j] = player; 
                i = 3; 
                j = 3; 
            }
        }
    }
}

void jogada_medium(char **M, char player){
    int i, j;
    int ok = 0;
    //Enquanto nao encontrar uma posicao vazia, faz uma jogada aleatoria entre 0 e 2
    while(ok == 0){ 
        i = rand()%3; 
        j = rand()%3;
        if(posicao_vazia(M, i, j) == 1){
            M[i][j] = player;
            ok = 1;
        }
    }
}

/*Verifica se da para ganhar, verifica se vai perder e trava o adversario, caso contrario rand*/
void jogada_hard(char **M, char player){
    int i, j;
    int cont;
    char jog;
    //Linha
    for(i=0;i<3;i++){/*Verifica para bola e incrementa tabuleiro*/
        cont = 0;
        for(j=0;j<3;j++){
            if(M[i][j] == player){
                cont++;
            }
        }

        if(cont > 1)
            for(j=0;j<3;j++){/*Verifica colunas novamente*/
                if(posicao_vazia(M, i, j) == 1){
                    M[i][j] = player;
                    return;
                }
        }
    }
    //Coluna
    for(j=0;j<3;j++){
        cont = 0;
        for(i=0;i<3;i++){
            if(M[i][j] == player)
                cont++;
        }

        if(cont > 1)
            for(i=0;i<3;i++){
                if(posicao_vazia(M, i, j) == 1){
                    M[i][j] = player;
                    return;
                }
            }
    }
    //Diagonal '\'
    for(i=0;i<3;i++){
        if(M[i][i] == player){
            cont++;
        }
    }
    if(cont>1){
        for(i=0;i<3;i++){
            if(posicao_vazia(M, i, i) == 1){
                M[i][i] = player;
                return;
            }
        }
    }
    //Diagonal '/''
    cont = 0;
    for(i=0;i<3;i++){
        if(M[i][2-i] == player){
            cont++;

        }
    }
    if(cont>1){
        for(i=0;i<3;i++){
            if(posicao_vazia(M, i, 2-i) == 1){
                M[i][2-i] = player;
                return;
            }
        }
    }


    if(player == P1)
        jog = P2;
    else jog = P1;
    //Se o jogador vai ganhar: verificar
    //Linhas
    for(i=0;i<3;i++){
        cont = 0;
        for(j=0;j<3;j++){
            if(M[i][j] == jog)
                cont++;
        }

    if(cont > 1)
        for(j=0;j<3;j++){
            if(posicao_vazia(M, i, j) == 1){
                M[i][j] = player;
                return;
            }
        }
    }
    //Coluna
    for(j=0;j<3;j++){
        cont = 0;
        for(i=0;i<3;i++){
            if(M[i][j] == jog)
                cont++;
        }

    if(cont > 1)
        for(i=0;i<3;i++){
            if(posicao_vazia(M, i, j) == 1){
                M[i][j] = player;
                return;
            }
        }
    }
    //Diagonal '\'
    cont = 0;
    for(i=0;i<3;i++){
        if(M[i][i] == jog){
            cont++;
        }
    }
    if(cont>1){
        for(i=0;i<3;i++){
            if(posicao_vazia(M, i, i) == 1){
                M[i][i] = player;
                return;
            }
        }
    }
    //Diagonal '/'
    cont = 0;
    for(i=0;i<3;i++){
        if(M[i][2-i] == jog){
            cont++;
        }
    }
    if(cont>1){
        for(i=0;i<3;i++){
            if(posicao_vazia(M, i, 2-i) == 1){
                M[i][2-i] = player;
                return;
            }
        }
    }
    jogada_medium(M, player);
}

/*Verifica se o jogador(parametro) ganhou(verifica se tem 3 linhas, colunas ou diagonais
preenchidas com player)
Entrada: matriz, jogador
Saidas: 1 = ganhou,0 = perdeu*/
int ganhou(char **M, char player){
    int i, j;
    int flag;
    /*Verifica toda linha se ganhou de acordo com a linha*/
    for(i=0;i<3;i++){
        flag = 1;

        for(j=0;j<3;j++){
            if(M[i][j] != player)   flag = 0;
        }
        if(flag == 1)    return 1;
    }
    /*Verifica toda coluna se ganhou de acordo com a coluna*/
    for(j=0;j<3;j++){
        flag = 1;

        for(i=0;i<3;i++){
            if(M[i][j] != player)   flag = 0;
        }
        if(flag == 1)    return 1;
    }
    /*Verificando diagonais*/
    flag = 1;
    for(i=0;i<3;i++){
        if(M[i][i] != player)
            flag = 0;
    }
    if(flag == 1)   return 1;

    flag = 1;
    for(i=0;i<3;i++){
        if(M[i][2-i] != player)
            flag = 0;
    } if(flag == 1) return 1;

    /*Caso contrario player nao ganhou*/
    return 0;
}

/*Salva o jogo no arquivo: Esta função foi criado com o intuito de praticar o tópico de arquivos, pois
raramente o usuário iria querer salvar sua jogada em um simples tic tac toe
Entradas: matriz, nivel de dificuldade, contador de jogada, slot(arquivo que deseja salvar)*/
void savegame(char **M, int nivel, int cont, int slot){
    FILE *fp;
    int i, j;
    if(slot == 1)   fp = fopen("save1.dat", "w");
    if(slot == 2)   fp = fopen("save2.dat", "w");
    if(slot == 3)   fp = fopen("save3.dat", "w");
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if (M[i][j] == ' ') M[i][j] = 'S';/*se houver espaco vazio, nao pode salvar por isso
             substitui por caracter e tbm pq a scanf le ate espaco vazio*/
            fprintf(fp, "%c ", M[i][j]);
        }
    }
    fprintf(fp, "%d ", nivel);
    fprintf(fp, "%d", cont);
    fclose(fp);
}

/*Carrega o jogo
Entradas: matriz, nivel de dificuldade, contador de jogada, slot(arquivo que deseja carregar)*/
void loadgame(char **M, int *nivel, int *cont, int slot){
    FILE *fp;
    int i, j;
    if(slot == 1)   fp = fopen("save1.dat", "r");
    if(slot == 2)   fp = fopen("save2.dat", "r");
    if(slot == 3)   fp = fopen("save3.dat", "r");
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            fscanf(fp, "%c ", &M[i][j]);
            if (M[i][j] == 'S') M[i][j] = ' '; /*se for caracter, substituir por espaco*/
        }
    }
    fscanf(fp, "%d ", nivel);
    fscanf(fp, "%d", cont);
    fclose(fp);
}

/*Loop de jogador vs jogador
Entradas: matriz, jogador, contador de jogadas p/ verificar em q ponto do jogo esta*/
void loopjogada0(char **M, char jogador, int cont){
    int playsave, slot;
    for(; cont<9;cont++){
      printf("\nDeseja\n1 - Jogar\n2 - Salvar\n");
      scanf("%d", &playsave);
      if(playsave == 2){
        printf("\nDigite o slot para salvar\n1, 2 ou 3 \n");
        scanf("%d", &slot);
        savegame(M, 0, cont, slot);
        cont = 9;
    }
    else{
      jogada(M, jogador);
      system("clear||cls");
      desenha(M);
      if(ganhou(M, jogador) == 1){
       printf("\n\nParabens Jogador %c \n", jogador);
       system("clear||cls");
       /*Sair do for*/
       cont = 9; 
   }
   else{
       if(jogador == P1)
          jogador = P2;
      else{
       jogador = P1;
      }
    }
if((ganhou(M, P1) == 0) && (ganhou(M, P2) == 0) && cont == 9)
    printf("\n\nDeu veia meu irmao ('_`) ");
    }
}
}

/*Jogador vs pc nivel facil*/
void looppve1(char **M, char jogador, int cont){
    int playsave, slot;
    for(; cont<9;cont++){
        printf("\nDeseja\n1 - Jogar\n2 - Salvar\n");
        scanf("%d", &playsave);
        if(playsave == 2){
            printf("\nDigite o slot para salvar\n1, 2 ou 3 \n");
            scanf("%d", &slot);
            savegame(M, 1, cont, slot);
            cont = 9;
        }
        else{
         if(jogador == P1) jogada(M, jogador);
        else jogada_easy(M, jogador);
        system("clear||cls");
        desenha(M);
        if(ganhou(M, jogador) == 1){
            printf("\n\nParabens Jogador %c \n", jogador);
            system("clear||cls");
            cont = 9; 
        }
        else{
         if(jogador == P1)
            jogador = P2;
        else{
         jogador = P1;
            }
            }
            }
        }
        if((ganhou(M, P1) == 0) && (ganhou(M, P2) == 0) && cont == 9)
            printf("\n\nDeu veia meu irmao ('_`) ");
}
/*Jogador vs pc nivel medio*/
void looppve2(char **M, char jogador, int cont){
    int playsave, slot;
    for(; cont<9;cont++){
        printf("\nDeseja\n1 - Jogar\n2 - Salvar\n");
        scanf("%d", &playsave);
        if(playsave == 2){
            printf("\nDigite o slot para salvar\n1, 2 ou 3 \n");
            scanf("%d", &slot);
            savegame(M, 2, cont, slot);
            cont = 9;
        }
    else{
     if(jogador == P1) jogada(M, jogador);
    else jogada_medium(M, jogador);
        system("clear||cls");
        desenha(M);
    if(ganhou(M, jogador) == 1){
        printf("\n\nParabens Jogador %c \n", jogador);
        system("clear||cls");
        cont = 9; 
    }
    else{
     if(jogador == P1)
        jogador = P2;
    else{
        jogador = P1;
        }
        }
        }
        }
    if((ganhou(M, P1) == 0) && (ganhou(M, P2) == 0) && (cont == 9))
        printf("\n\nDeu veia meu irmao ('_`) ");
}
/*Jogador vs pc nivel hard*/
void looppve3(char **M, char jogador, int cont){
    int playsave, slot;
    for(; cont<9;cont++){
        printf("\nDeseja\n1 - Jogar\n2 - Salvar\n");
        scanf("%d", &playsave);
        if(playsave == 2){
            printf("\nDigite o slot para salvar\n1, 2 ou 3 \n");
            scanf("%d", &slot);
            savegame(M, 3, cont, slot);
            cont = 9;
        }
    else{
     if(jogador == P1) jogada(M, jogador);
    else jogada_hard(M, jogador);
        system("clear||cls");
        desenha(M);
    if(ganhou(M, jogador) == 1){
        printf("\n\nParabens Jogador %c \n", jogador);
        cont = 9; 
    }
    else{
     if(jogador == P1)
        jogador = P2;
    else{
        jogador = P1;
        }
        }
        }
        }
    if((ganhou(M, P1) == 0) && (ganhou(M, P2) == 0) && (cont == 9))
        printf("\n\nDeu veia meu irmao ('_`) ");
}

int main()
{
    char **M;
    int cont = 9;
    char jogador;
    int opcao, n, slot, nivel;

    do{
        printf("\t\t\t\tTic Tac Toe (beta version)\n");
        printf("\n1 - JOGADOR VS JOGADOR");
        printf("\n2 - JOGADOR VS COMPUTADOR");
        printf("\n3 - CARREGAR JOGADA");
        printf("\n4 - SAIR");
        printf("\n\nDigite sua opcao: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                    system("clear||cls");
                    printf("PLAYER 1 VS PLAYER 2\n\n");
                    M = iniciar();
                    desenha(M);
                    jogador = P1;
                    loopjogada0(M, jogador, 0);
            break;

            case 2: system("clear||cls");
                    printf("1 - Dificuldade Facil");
                    printf("\n2 - Dificuldade Media");
                    printf("\n3 - Dificuldade Dificil");
                    printf("\n\nDigite a opcao de dificuldade: ");
                    scanf("%d", &n);
                    if(n == 1){
                         system("clear||cls");
                         printf("PLAYER 1 VS PC\t\t\t\t\t\t     Dificuldade: Facil\n\n");
                         M = iniciar();
                         desenha(M);
                         srand(time(NULL));
                         jogador = P1;
                         looppve1(M, jogador, 0);
                    }
                    else if(n == 2){
                         system("clear||cls");
                         printf("PLAYER 1 VS PC\t\t\t\t\t\t     Dificuldade: Medio\n\n");
                         M = iniciar();
                         desenha(M);
                         srand(time(NULL));
                         jogador = P1;
                         looppve2(M, jogador, 0);
                    }
                    else if(n == 3){
                         system("clear||cls");
                         printf("PLAYER 1 VS PC\t\t\t\t\t\t    Dificuldade: Dificil\n\n");
                         M = iniciar();
                         desenha(M);
                         srand(time(NULL));
                         jogador = P1;
                         looppve3(M, jogador, 0);

                    }
                    else printf("\n opcao invalida, digite novamente\n");
            break;

            case 3: printf("\nQual o slot: \n");
                    scanf("%d", &slot);
                    M = iniciar();
                    loadgame(M, &nivel, &cont, slot);
                    if(cont%2 == 0) jogador = P1;
                    else jogador = P2;
                    //Load gamë:
                    if(nivel == 0){
                        system("clear||cls");
                    printf("PLAYER 1 VS PLAYER 2\n\n");
                    desenha(M);
                     loopjogada0(M, jogador, cont);
                    }
                     if(nivel == 1) {
                             system("clear||cls");
                    printf("PLAYER 1 VS PC\t\t\t\t\t\t     Dificuldade: Facil\n\n");
                    desenha(M);
                     looppve1(M, jogador, cont);
                     }
                     if(nivel == 2) {
                             system("clear||cls");
                    printf("PLAYER 1 VS PC\t\t\t\t\t\t     Dificuldade: Medio\n\n");
                    desenha(M);
                     looppve2(M, jogador, cont);
                     }
                     if(nivel == 3) {
                             system("clear||cls");
                    printf("PLAYER 1 VS PC\t\t\t\t\t\t    Dificuldade: Dificil\n\n");
                    desenha(M);
                     looppve3(M, jogador, cont);
                     }

                break;
        }
        } while(opcao!=4);
    return 0;
}
