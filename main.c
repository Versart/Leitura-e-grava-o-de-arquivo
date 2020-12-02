/*
    Codigo desenvolvido para a cadeira de Algoritmo e Estrutura de Dados
    Professor responsavel é o prof. Gentil
    Alunos que trabalharam no programa: Lucas Felipe, Wesley Versart, Franscico Remo
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<conio.h>
#define MAX 10
//Registro para armazenar as informações dos alunos
struct dados{
long cod;
char nome[50];
int dt_nascimento[3];
float notas[3];
float media;
char conceito[3];
};
void limpar(){//Função para limpar a tela
    system("cls");
}
void separar(){
    printf("**********************\n");
}
void tela(){//Função para mostrar as opções disponiveis do programa
    printf("1-Cadastrar\n2-Alterar\n3-Deletar\n4-Pesquisar\n5-Listar todos\n6-Ordenar\n7-Sair\n");
}
void ordenar(struct dados *alu,int quant){//Função para ordenar os alunos em ordem alfabetica
    struct dados aux;
    limpar();
    //Ordenando a lista dos alunos em ordem alfabética
    for(int i=0;i<quant;i++){
        for(int j=0;j<quant-1;j++){
            if(alu[j].nome[0]>alu[j+1].nome[0]){
                aux=alu[j];
                alu[j]=alu[j+1];
                alu[j+1]=aux;
            }
        }
    }
    FILE *arq;
    arq=fopen("alunos.txt","rb+");//abrindo o arquivo para gravar a lista ordenada
    //Laço para gravar os dados alterados
    for(int i=0;i<quant;i++){
       fseek(arq,i*sizeof(struct dados),SEEK_SET);
       fwrite(&alu[i],sizeof(struct dados),1,arq);
    }
    fclose(arq);
    printf("Dados ordenados\n");
    printf("Digite alguma tecla para sair!\n");
    getch();
}
void listar(struct dados *estudantes,int numero){//Função para listar todos os alunos da lista
    limpar();
    separar();
    for(int i=0;i<numero;i++){
            printf("Nome:%s\n",estudantes[i].nome);
            printf("Nascimento:%d/%d/%d\n",estudantes[i].dt_nascimento[0],estudantes[i].dt_nascimento[1],estudantes[i].dt_nascimento[2]);
            printf("Conceito:%s\n",estudantes[i].conceito);
            separar();
    }
    printf("Digite alguma tecla para sair!\n");
    getch();
}
void deletar(char *nomeAluno,struct dados *novo){//Função para deletar um aluno do arquivo
    FILE *arq,*arqAux;
    int nums=0;
    arq=fopen("alunos.txt","rb");
    arqAux=fopen("nova.txt","wb+");//Arquivo que será a nova lista dos alunos
    struct dados leitura;
    if(arq==NULL && arqAux==NULL)
        printf("Erro na abertura do arquivo!");
    else{
        /*
            Percorre o arquivo dos alunos e passa para o novo arquivo,
            exceto o aluno que sera excluido
        */
        while(fread(&leitura,sizeof(struct dados),1,arq)==1){
            if(strcmpi(nomeAluno,leitura.nome)==0){
            }
            else{
                fwrite(&leitura,sizeof(struct dados),1,arqAux);//
            }
        }
    }
    fclose(arq);
    fclose(arqAux);
    remove("alunos.txt");//Excluindo o antigo arquivo dos alunos
    rename("nova.txt","alunos.txt");//Renomeando o novo arquivo
    fclose(arq);
    fclose(arqAux);
    int alunos=0;
    arq=fopen("alunos.txt","rb");
    if(arq==NULL){

    }
    else{
        //Carregando a struct de alunos com o novo arquivo
        while(!feof(arq)){
            if(fread(&novo[alunos],sizeof(struct dados),1,arq)==1)
                alunos++;
        }
        fclose(arq);
    }

}
void pesquisar(struct dados *pesq,int numero){//Função para pesquisar um aluno do sistema
    char nome[30];
    int encontrado=0,opcao,codigo;
    do{
        limpar();
        printf("Numero de alunos na lista:%d\n",numero);
        printf("1-Pesquisa por nome\n2-Pesquisa por codigo\n");
        scanf("%d%*c",&opcao);
        if(opcao>=3 || opcao<=0){
            limpar();
            printf("Opcao invalida!\n");
            printf("Digite alguma tecla para sair\n");
            getch();
        }
    }while(opcao>=3 || opcao<=0);
    if(opcao==1){
        limpar();
        printf("Digite o nome do aluno:");
        scanf("%30[^\n]%*c",nome);
        for(int i=0;i<numero;i++){
            if(strcmpi(nome,pesq[i].nome)==0){
                encontrado=1;
                limpar();
                separar();
                printf("Codigo:%d\n",pesq[i].cod);
                printf("Nome:%s\n",pesq[i].nome);
                printf("Nascimento:%d/%d/%d\n",pesq[i].dt_nascimento[0],pesq[i].dt_nascimento[1],pesq[i].dt_nascimento[2]);
                printf("Conceito:%s\n",pesq[i].conceito);
                separar();
                printf("Digite alguma tecla para sair!\n");
                getch();
            }
        }
        if(encontrado==0){
            limpar();
            printf("Aluno não encontrado!\n");
            printf("Digite alguma tecla para sair!\n");
            getch();
        }
    }
    else if(opcao==2){
        limpar();
        printf("Digite o codigo do aluno:");
        scanf("%d%*c",&codigo);
        for(int i=0;i<numero;i++){
            if(codigo==pesq[i].cod){
                encontrado=1;
                limpar();
                separar();
                printf("Codigo:%d\n",pesq[i].cod);
                printf("Nome:%s\n",pesq[i].nome);
                printf("Nascimento:%d/%d/%d\n",pesq[i].dt_nascimento[0],pesq[i].dt_nascimento[1],pesq[i].dt_nascimento[2]);
                printf("Conceito:%s\n",pesq[i].conceito);
                separar();
                printf("Digite alguma tecla para sair!\n");
                getch();
            }
        }
        limpar();
        if(encontrado==0)
            printf("Aluno nao encontrado!\n");
            printf("Digite alguma tecla para sair!\n");
            getch();
    }
}
void alterar(struct dados *alter,int pos){//Função para alterar alguma informação de um aluno
     int escolha;
    do{
        limpar();
        printf("Deseja alterar a data de nascimento do aluno:%s ?\n",alter[pos].nome);
        printf("1-Sim\n2-Nao\n");
        scanf("%d%*c",&escolha);
        if(escolha<=0 || escolha>=3){
            printf("Opção inválida!\n");
            printf("Digite alguma tecla para sair!\n");
            getch();
        }
    }while(escolha<=0 || escolha>=3);
    limpar();
    if(escolha==1){
        printf("Digite o dia do nascimento:");
        scanf("%d%*c",&alter[pos].dt_nascimento[0]);
        printf("Digite o mes do nascimento:");
        scanf("%d%*c",&alter[pos].dt_nascimento[1]);
        printf("Digite o ano do nascimento:");
        scanf("%d%*c",&alter[pos].dt_nascimento[2]);
    }
    limpar();
    printf("Deseja alterar as notas do aluno:%s?\n",alter[pos].nome);
    printf("1-Sim\n2-Nao\n");
    scanf("%d%*c",&escolha);
    if(escolha==1){
        limpar();
        alter[pos].media=0;
        for(int i=0;i<3;i++){
            printf("Digite a nota da prova %d:",i+1);
            scanf("%f%*c",&alter[pos].notas[i]);
            alter[pos].media+=alter[pos].notas[i]/3;
        }
        if(alter[pos].media>=9)
            strcpy(alter[pos].conceito,"MB");
        else if(alter[pos].media>=7)
            strcpy(alter[pos].conceito,"B");
        else if(alter[pos].media>=6)
            strcpy(alter[pos].conceito,"RE");
        else
            strcpy(alter[pos].conceito,"RU");
    }
    //Alterando os dados no arquivo
    FILE *arq;
    arq=fopen("alunos.txt","rb+");
    fseek(arq,pos*sizeof(struct dados),SEEK_SET);
    fwrite(&alter[pos],sizeof(struct dados),1,arq);
    if(ferror(arq)==0){
        printf("Dado alterado!\n");
        printf("Digite alguma tecla para sair!\n");
        getch();
    }
    fclose(arq);
}

void cadastro(struct dados *estud,int *quant){//Função para cadastrar um aluno
    FILE *arq;
    int repetido,codigo;
    do{
         limpar();
         repetido=1;
         printf("Digite um codigo para o aluno:(apenas numeros):\n");
         scanf("%d%*c",&codigo);
         for(int i=0;i<*quant;i++){//Laço para evitar que alunos tenham o mesmo codigo
            if(codigo==estud[i].cod){
                repetido=0;
            }
         }
         if(repetido==0){
            printf("Ja existe um aluno cadastrado com esse codigo!\n");
            printf("Digite alguma tecla para sair!\n");
            getch();
         }
    }while(repetido==0);
    estud[*quant].cod=codigo;
    limpar();
    printf("Digite um nome para o aluno:");
    scanf("%30[^\n]%*c",estud[*quant].nome);
    estud[*quant].nome[0]=toupper(estud[*quant].nome[0]);
    printf("Digite o dia do seu nascimento:");
    scanf("%d%*c",&estud[*quant].dt_nascimento[0]);
    printf("Digite o numero do mes do seu nascimento:");
    scanf("%d%*c",&estud[*quant].dt_nascimento[1]);
    printf("Digite o ano do  seu nascimento:");
    scanf("%d%*c",&estud[*quant].dt_nascimento[2]);
    estud[*quant].media=0;
    for(int i=0;i<3;i++){
        printf("Digite a nota da prova %d:",i+1);
        scanf("%f%*c",&estud[*quant].notas[i]);
        estud[*quant].media+=estud[*quant].notas[i]/3;
    }
    if(estud[*quant].media>=9)
        strcpy(estud[*quant].conceito,"MB");
    else if(estud[*quant].media>=7)
        strcpy(estud[*quant].conceito,"B");
    else if(estud[*quant].media>=6)
        strcpy(estud[*quant].conceito,"RE");
    else
        strcpy(estud[*quant].conceito,"RU");
    limpar();
    arq=fopen("alunos.txt","ab");//Abrindo o arquivo para adicionar o aluno novo
    if(arq==NULL)
        printf("Erro na abertura do arquivo!\n");
    else{
        fwrite(&estud[*quant],sizeof(struct dados),1,arq);
        if(ferror(arq)==0){
            printf("Dados gravados!\n");
            printf("Digite alguma tecla para sair!\n");
            getch();
        }

    }
    fclose(arq);

    *quant+=1;
    printf("Alunos:%d\n",*quant);
}

int main()
{
    //vetor de alunos
    struct dados aluno[MAX];
    struct dados leitura;
    int opcao,alunos=0,encontrado=0;
    char nome[30];
    FILE *arq;


    arq=fopen("alunos.txt","rb");
    if(arq==NULL){

    }
    else{
        /*
        Lendo a quantidade de alunos ja cadastrados e
        carregando o vetor de struct
        */
        while(!feof(arq)){
            if(fread(&aluno[alunos],sizeof(struct dados),1,arq)==1)
                alunos++;
        }
        fclose(arq);
    }

    do{
         encontrado=0;
         limpar();
         if(alunos==0)
             printf("Nenhum aluno no sistema!\n");
         tela();
         scanf("%d%*c",&opcao);
         switch(opcao){
            case 1:
                if(alunos<MAX){
                    cadastro(aluno,&alunos);
                }
                else{
                    limpar();
                    printf("Cadastro cheio!\n");
                    printf("Digite alguma tecla para sair!\n");
                    getch();
                }

                break;
            case 2:
                if(alunos>0){
                    printf("Quantidade alunos:%d\n",alunos);
                    printf("Nome do aluno que deseja alterar:");
                    scanf("%30[^\n]%*c",nome);
                    for(int i=0;i<alunos;i++){
                        if(stricmp(nome,aluno[i].nome)==0){
                            alterar(aluno,i);
                            encontrado=1;
                        }
                    }
                    if(encontrado==0){
                        limpar();
                        printf("Aluno não encontrado!\n");
                        printf("Digite alguma tecla para sair\n");
                        getch();
                    }
                }
                else{
                   limpar();
                   printf("Nenhum aluno no sistema!\n");
                   printf("Digite alguma tecla para sair\n");
                   getch();
                }
                break;
            case 3:
                if(alunos>0){
                    limpar();
                    printf("Digite o nome do aluno que deseja deletar:");
                    scanf("%30[^\n]",nome);
                    for(int i=0;i<alunos;i++){
                        if(stricmp(nome,aluno[i].nome)==0){
                            deletar(nome,aluno);
                            alunos--;
                            encontrado=1;
                        }
                    }
                    if(encontrado==0){
                        limpar();
                        printf("Aluno não encontrado!\n");
                        printf("Digite alguma tecla para sair\n");
                        getch();
                    }
                    else{
                        limpar();
                        printf("Aluno deletado!\n");
                        printf("Digite alguma tecla para sair!\n");
                        getch();
                    }
                }
                else{
                    limpar();
                    printf("Nenhum aluno no sistema!\n");
                    printf("Digite alguma tecla para sair\n");
                    getch();
                }

                break;
            case 4:
                if(alunos>0){
                    pesquisar(aluno,alunos);
                }
                else{
                    limpar();
                    printf("Nenhum aluno no sistema!\n");
                    printf("Digite alguma tecla para sair!\n");
                    getch();
                }
                break;
            case 5:
                if(alunos>0){
                    listar(aluno,alunos);
                }
                else{
                    limpar();
                    printf("Nenhum aluno no sistema!\n");
                    printf("Digite uma tecla para sair\n");
                    getch();
                }

                break;
            case 6:
                if(alunos>0){
                    ordenar(aluno,alunos);
                }
                else{
                    limpar();
                    printf("Nenhum aluno no sistema!\n");
                    printf("Digite alguma tecla para sair\n");
                    getch();
                }
                break;
            case 7:
                limpar();
                printf("Programa encerrado!\n");
                break;
            default:
                printf("Programa encerrado!\n");
         }
    }while(opcao!=7);











    return 0;
}
