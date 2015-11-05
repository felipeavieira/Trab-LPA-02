#include <stdio.h>
#include <stdlib.h>
#include <string.h>//biblioteca necessaria para o uso da funcao strcmp
#include <math.h>//biblioteca necessaria para o uso da funcao pow

struct lista //estrutura da lista que sera utilizada para obter os individuos por geracao.
{
struct arvore* tree;
struct lista * prox;
};

struct arvore//estrutura da arvore.
{
char * nome;
int geracao;// sera util para calcular parentesco.
struct arvore * esq;
struct arvore * dir;
};

struct arvore * search = NULL;//variavel global que carrega o endereco do no procurado.

void buscar (struct arvore * root, char * a)// funcao que realiza busca de um individuo e coloca seu endereco em search
{
    if (root==NULL)
        return;//se search nao for alterado, individuo nao esta na arvore.
    if (strcmp(root->nome,a)==0)
    {
        search = root;
        return;
    }
    buscar (root->esq,a);
    buscar (root->dir,a);
}

struct arvore * add_first ()//adiciona a raiz da arvore e seus pais.
{
    struct arvore* novo = (struct arvore*)calloc(1,sizeof(struct arvore));
    struct arvore* novo1 = (struct arvore*)calloc(1,sizeof(struct arvore));
    struct arvore* novo2 = (struct arvore*)calloc(1,sizeof(struct arvore));
    novo->nome=(char*)calloc(40,sizeof(char));
    novo1->nome=(char*)calloc(40,sizeof(char));
    novo2->nome=(char*)calloc(40,sizeof(char));
    scanf("%s %s %s",novo->nome,novo1->nome,novo2->nome);
    novo->geracao=0;
    novo->esq=novo1;
    novo->dir=novo2;
    novo1->esq=NULL;
    novo1->dir=NULL;
    novo1->geracao=1;
    novo2->geracao=1;
    novo2->esq=NULL;
    novo2->dir=NULL;
    return novo;
}

void add(struct arvore * root)//adiciona nova relacao somente se o filho ja se encontra na arvore
{
    struct arvore* novo1 = (struct arvore*)calloc(1,sizeof(struct arvore));
    struct arvore* novo2 = (struct arvore*)calloc(1,sizeof(struct arvore));
    char * novo = (char*)calloc(40,sizeof(char));
    novo1->nome=(char*)calloc(40,sizeof(char));
    novo2->nome=(char*)calloc(40,sizeof(char));
    scanf("%s %s %s", novo, novo1->nome, novo2->nome);
    buscar(root,novo);
    if (search==NULL)//verifica se filho esta na arvore
        printf("Voce deve entrar primeiro com o filho para entrar com os pais.\nNao foi entrada a seguinte relacao: %s %s %s.\n",novo,novo1->nome,novo2->nome);
    else//se estiver, adiciona a relacao.
    {
        novo1->esq=NULL;
        novo1->dir=NULL;
        novo1->geracao=(search->geracao+1);
        novo2->esq=NULL;
        novo2->dir=NULL;
        novo2->geracao=(search->geracao+1);
        search->esq=novo1;
        search->dir=novo2;
        search=NULL;
    }
}

struct lista * list (struct arvore * root)// preenche uma lista que retorna a arvore por gerecoes
{
    struct lista * raizlista;
    struct lista * first;
    struct lista * next1;
    struct lista * next2;
    struct lista * last;
    raizlista=(struct lista *)calloc(1,sizeof(struct lista));
    raizlista->tree=root;
    first=raizlista;
    last=raizlista;
    do
    {
        if (first->tree->dir!=NULL)
        {
            next2=(struct lista *)calloc(1,sizeof(struct lista));
            next2->tree=first->tree->esq;
            next2->prox=NULL;
            next1=(struct lista *)calloc(1,sizeof(struct lista));
            next1->tree=first->tree->dir;
            next1->prox=next2;
            last->prox=next1;
            first = first->prox;
            last = next2;
        }
        else
            first=first->prox;
    }
    while (first->prox!=NULL);
    return raizlista;//retorna o primeiro da lista.
}

void print_ant(struct arvore * root)//impressao analoga ao pre ordem
{
    if (root->esq==NULL)
        return;
    printf("%s %s ",root->esq->nome,root->dir->nome);
    print_ant(root->esq);
    print_ant(root->dir);
}

void print_ger(struct lista * lista, double i)// imprime a arvore por geracoes utilizando a lista que ja foi preenchida.
{
    double j;
    for (j=0;j<pow(2,i);j++)//sabemos quantas vezes repetir pois cada geracao tem 2^n individuos, com n = geracao e raiz tem n=0
    {
        if (lista==NULL)
            return;
        printf("%s ",lista->tree->nome);
        lista=lista->prox;
    }
    i++;
    printf("\n");
    if (lista!=NULL)
        print_ger(lista,j);
}

void print_col(struct arvore * root)//impressao em labelled bracketing
{
    if (root==NULL)
        return;
    printf("[%s",root->nome);
    print_col (root->esq);
    print_col (root->dir);
    printf("]");
}

void parentesco (struct arvore * root) //calcula o grau de parentesco
{
    char a[40], b[40];
    struct arvore * ind1, * ind2;
    printf("\nVoce deseja saber o parentesco entre que individuos? Entre com os nomes separados por espacos.\n");
    scanf("%s %s",a,b);
    buscar(root,a);
    ind1=search;
    if (search==NULL)//verifica se o ind1 esta na arvore
    {
        printf("%s nao esta na arvore.\n",ind1->nome);
        return;
    }
    search=NULL;
    buscar(root,b);
    ind2=search;
    if (search==NULL)//verifica se o ind2 esta na arvore
    {
        printf("%s nao esta na arvore.\n",ind2->nome);
        return;
    }
    search=NULL;
    /*agora sera verificado se a pessoa mais antiga eh antepassado do mais novo, usando as geracoes que foram preenchidas.
    caso seja, sera feita uma subtracao das geracoes e teremos o parentesco.
    se nao for retorna-se 0.*/
    if (ind1->geracao<ind2->geracao)
    {
        buscar(ind1,b);
        if (search!=NULL)
        {
            printf("O grau de parentesco entre %s e %s eh de %d\n",ind1->nome,ind2->nome,(ind2->geracao-ind1->geracao));
            search=NULL;
            return;
        }
    }
    if (ind2->geracao<ind1->geracao)
    {
        buscar(ind2,a);
        if (search!=NULL)
        {
            printf("O grau de parentesco entre %s e %s eh de %d\n",ind1->nome,ind2->nome,(ind1->geracao-ind2->geracao));
            search=NULL;
            return;
        }
    }
    printf("O grau de parentesco entre %s e %s eh de 0\n",ind1->nome,ind2->nome);
}

int menu(struct arvore * root, struct lista * lista)//imprime o menu e executa a opcao escolhida
{
    int i,j;
    printf("\nO que deseja fazer agora? Digite o numero com sua opcao:\n");
    printf("1. Imprimir.\n2. Calcular grau de parentesco.\n3. Sair.\nSua opcao: ");
    scanf("%d",&i);
    switch (i)//switch que permite a escolha da opcao.
    {
    case 1:
        {
            printf("\nO que deseja imprimir?\n1. Antepassados.\n2. Por geracao.\n3. Labelled bracketing.\nSua opcao: ");
            scanf("%d",&j);
            switch (j)
            {
            case 1:
                {
                    char a[40];
                    printf("\nVoce deseja imprimir os antepassados de que individuo?\n");
                    scanf("%s",a);
                    buscar(root,a);
                    if (search==NULL)
                    {
                        printf("Essa pessoa nao se encontra na lista.\n");
                        return 0;
                    }
                    printf("\n");
                    print_ant(search);
                    printf("\n");
                    search=NULL;
                    return 0;
                }
            case 2:
                {
                    double k=0;
                    printf("\n");
                    print_ger(lista,k);
                    printf("\n");
                    return 0;
                }
            case 3:
                {
                    printf("\n");
                    print_col(root);
                    printf("\n");
                    return 0;
                }
            default:
                {
                    printf("\nOcorreu um erro. Tente novamente.\n");
                    return 0;
                }
            }

        }
    case 2:
        {
            parentesco(root);
            return 0;
        }
    case 3:
        {
            return 1;
        }
    default:
        {
            printf("\nOcorreu um erro. Tente novamente.\n");
            return 0;
        }
    }
}

void free_lista (struct lista * lista)//desaloca a memoria da lista
{
    if (lista->prox!=NULL)
        free_lista(lista->prox);
    free(lista);
}

void free_tree(struct arvore * root)//desaloca a memoria da arvore
{
    if (root==NULL)
        return;
    free_tree(root->esq);
    free_tree(root->dir);
    free(root->nome);
    free(root);
}

int main()
{
    int n, i, j;
    struct arvore * root = NULL;
    struct lista * lista = NULL;
    printf("Inicializando arvore genealogica.\nQuantas relacoes voce pretende entrar? ");
    scanf("%d",&n);
    while (n<1)//Previne erros e garante que pelo menos 1 item estara na arvore.
    {
        printf("Entre com pelo menos uma relacao. Quantas relacoes voce pretende entrar? ");
        scanf("%d",&n);
    }
    printf("Entre com as relacoes:\n");
    root=add_first();//adiciona a raiz da arvore e seus pais.
    for (i=0;i<n-1;i++)
    {
        add (root);//adiciona as demais relacoes.
    }
    lista=list(root);//preenche a lista.
    while (j!=1)
        j=menu(root,lista);
    free_lista(lista);//desalocacao de memoria.
    free_tree(root);
}
