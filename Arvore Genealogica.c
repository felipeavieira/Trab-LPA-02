#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct lista
{
struct arvore* tree;
struct lista * prox;
};

struct arvore
{
char * nome;
struct arvore * esq;
struct arvore * dir;
};

struct arvore * search = NULL;

void buscar (struct arvore * tree, char * a)
{
    if (tree==NULL)
        return;
    if (strcmp(tree->nome,a)==0)
        search = tree;
    else
    {
        buscar (tree->esq,a);
        buscar (tree->dir,a);
    }
}

struct arvore * add_first ()
{
    char *a1, *a2, *a3;
    a1=(char*)calloc(40,sizeof(char));
    a2=(char*)calloc(40,sizeof(char));
    a3=(char*)calloc(40,sizeof(char));
    scanf("%s %s %s",a1,a2,a3);
    struct arvore* novo = (struct arvore*)calloc(1,sizeof(struct arvore));
    novo->nome=a1;
    struct arvore* novo1 = (struct arvore*)calloc(1,sizeof(struct arvore));
    novo1->nome=a2;
    novo1->esq=NULL;
    novo1->dir=NULL;
    struct arvore* novo2 = (struct arvore*)calloc(1,sizeof(struct arvore));
    novo2->nome=a3;
    novo2->esq=NULL;
    novo2->dir=NULL;
    novo->esq=novo1;
    novo->dir=novo2;
    return novo;
}

void add (struct arvore * root)
{
    char *a1, *a2, *a3;
    a1=(char*)calloc(40,sizeof(char));
    a2=(char*)calloc(40,sizeof(char));
    a3=(char*)calloc(40,sizeof(char));
    scanf("%s %s %s",a1,a2,a3);
    struct arvore * novo1 = (struct arvore*)calloc(1,sizeof(struct arvore));
    novo1->nome=a2;
    novo1->esq=NULL;
    novo1->dir=NULL;
    struct arvore * novo2 = (struct arvore*)calloc(1,sizeof(struct arvore));
    novo2->nome=a3;
    novo2->esq=NULL;
    novo2->dir=NULL;
    struct arvore * tree = root;
    buscar (root,a1);
    if (search==NULL)
    {
        printf("Voce deve entrar primeiro com o filho para entrar com os pais.\nNao foi entrada a seguinte relacao: %s %s %s.\n",a1,a2,a3);
    }
    else
    {
        search->esq=novo1;
        search->dir=novo2;
        search=NULL;
    }
}

struct lista * list (struct arvore * tree)//com problemas...
{
    struct lista * listaarvore;
    struct lista * first;
    struct lista * next1;
    struct lista * next2;
    struct lista * last;
    listaarvore=(struct lista *)calloc(1,sizeof(struct lista));
    listaarvore->tree=tree;
    first=listaarvore;
    last=listaarvore;
    while (first->tree->dir!=NULL&&first->tree->esq!=NULL)
    {
        next1=(struct lista *)calloc(1,sizeof(struct lista));
        next2=(struct lista *)calloc(1,sizeof(struct lista));
        next1->tree=first->tree->dir;
        next2->tree=first->tree->esq;
        last->prox=next1;
        next1->prox=next2;
        next2->prox=NULL;
        first=first->prox;
        last=next2;
    }
    return listaarvore;
}

void print_ant(struct arvore * tree)
{
    if (tree->esq==NULL)
        return;
    printf("%s %s ",tree->esq->nome,tree->dir->nome);
    print_ant(tree->esq);
    print_ant(tree->dir);
}

void print_ger(struct lista * lista, double i)
{
    double j;
    for (j=0;j<pow(2,i);j++)
    {
        if (lista==NULL)
            return;
        printf(" %s ",lista->tree->nome);
        lista=lista->prox;
    }
    i++;
    printf("\n");
    if (lista!=NULL)
        print_ger(lista,j);
}

void print_col(struct arvore * tree)
{
    if (tree==NULL)
        return;
    printf("[%s",tree->nome);
    print_col (tree->esq);
    print_col (tree->dir);
    printf("]");
}

void parentesco (struct arvore * tree, char * ind)
{

}

int menu(struct arvore * root, struct lista * lista)
{
    int i,j;
    printf("\nO que deseja fazer agora? Digite o numero com sua opcao:\n");
    printf("1. Imprimir.\n2. Calcular grau de parentesco.\n3. Sair.\nSua opcao: ");
    scanf("%d",&i);
    switch (i)
    {
    case 1:
        {
            printf("O que deseja imprimir?\n1. Antepassados.\n2. Por geracao.\n3. Arvore com conchetes.\nSua opcao: ");
            scanf("%d",&j);
            switch (j)
            {
            case 1:
                {
                    char a[40];
                    printf("Voce deseja imprimir os antepassados de que individuo?\n");
                    scanf("%s",a);
                    buscar(root,a);
                    if (search==NULL)
                    {
                        printf("Essa pessoa nao se encontra na lista.");
                        return 0;
                    }
                    print_ant(search);
                    printf("\n");
                    search=NULL;
                    return 0;
                }
            case 2:
                {
                    double k=0;
                    print_ger(lista,k);
                    return 0;
                }
            case 3:
                {
                    print_col(root);
                    return 0;
                }
            default:
                {
                    printf("Ocorreu um erro. Tente novamente.\n");
                    return 0;
                }
            }

        }
    case 2:
        {

        }
    case 3:
        {
            return 1;
        }
    default:
        {
            printf("Ocorreu um erro. Tente novamente.\n");
            return 0;
        }
    }
}

void free_lista (struct lista * lista)
{
    if (lista->prox!=NULL)
        free_lista(lista->prox);
    free(lista);
}

free_tree(struct arvore * root)
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
    while (n<1)
    {
        printf("Entre com pelo menos uma relacao. Quantas relacoes voce pretende entrar? ");
        scanf("%d",&n);
    }
    printf("Entre com as relacoes:\n");
    root=add_first();
    for (i=0;i<n-1;i++)
    {
        add (root);
    }
    lista=list(root);
    while (j!=1)
        j=menu(root,lista);
    free_lista(lista);
    free_tree(root);
}
