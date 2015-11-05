#include <stdio.h>
#include <stdlib.h>

struct unidade//Estrutura que sera usada p/ representar um numero como uma lista de char.
{
    char ch;
    struct undidade * prox;
};

struct arvore//Estrutura p/ a arvore.
{
    struct unidade * c;
    struct arvore * esq;
    struct arvore * dir;
};

char a;//variavel global para manter o mesmo char entre as funcoes.

struct unidade * add_un ()//funcao que cria uma lista de char para representar um numero ou um operador.
{
    struct unidade * novo = (struct unidade*)calloc(1,sizeof(struct unidade));

    if (a=='+'||a=='-'||a=='*'||a=='/'||a=='^')// para o operador, a lista so precisa de uma particao.
    {
        novo->ch=a;
        novo->prox=NULL;
    }
    else //se for um numero, sera criada uma lista com o numero de algarismos do numero.
    {
        struct unidade * marcador = novo;
        struct unidade * novo1;
        marcador->ch=a;
        marcador->prox=NULL;
        scanf("%c",&a);
        while (a!=' '&&a!='\n')//continua a lista ate o proximo espaco.
        {
            novo1=(struct unidade*)calloc(1,sizeof(struct unidade));
            novo1->ch=a;
            novo1->prox=NULL;
            marcador->prox=novo1;
            marcador=novo1;
            scanf("%c",&a);
        }
    }
    return novo;
}

int add(struct arvore * root)//funcao que adiciona novos numeros ou operadores na arvore.
{
    int i=0;//Esse marcador sera muito importante, pois os if's so sao realizados se ele for 0.
    //Ele nao sera mais 0 quando o char ja tiver sido adicionado.
    if (root->esq==NULL)//a funcao tenta primeiro adicionar o char a esquerda.
    {
        root->esq=(struct arvore*)calloc(1,sizeof(struct arvore));
        root->esq->c=add_un();
        root->esq->esq=NULL;
        root->esq->dir=NULL;
        return 1;//avisa o programa que o char foi adicionado
    }
    //se a esquerda estiver preenchida por um operador, o programa pula para este ramo.
    //Se nao, ele tentara a esquerda.
    if (i==0&&(root->esq->c->ch=='+'||root->esq->c->ch=='-'||root->esq->c->ch=='/'||root->esq->c->ch=='*'||root->esq->c->ch=='^'))
    {
        i=add(root->esq);
    }
    //se a esquerda ja estiver preenchida por um numero, o programa testa a direita.
    //Se estiver vazia, ele adiciona o char a posicao.
    if (i==0&&root->dir==NULL)
    {
        root->dir=(struct arvore*)calloc(1,sizeof(struct arvore));
        root->dir->c=add_un();
        root->dir->esq=NULL;
        root->dir->dir=NULL;
        return 1;//avisa o programa que o char foi adicionado
    }
    //se for um operador, ele pode pular para ele.
    if(i==0&&(root->dir->c->ch=='+'||root->dir->c->ch=='-'||root->dir->c->ch=='/'||root->dir->c->ch=='*'||root->dir->c->ch=='^'))
    {
        i=add(root->dir);
    }
    return i;
}

void print_lista (struct unidade * lista)//Imprime a lista, seja numero ou operador.
{
    while(lista!=NULL)
    {
        printf("%c",lista->ch);
        lista=lista->prox;
    }
}

void print_in(struct arvore * root)//impressao infixa, analoga a em ordem.
{
    if (root==NULL)
        return;
    if (root->c->ch=='+'||root->c->ch=='-'||root->c->ch=='/'||root->c->ch=='*'||root->c->ch=='^')
        printf("(");
    print_in(root->esq);
    print_lista(root->c);
    print_in(root->dir);
    if (root->c->ch=='+'||root->c->ch=='-'||root->c->ch=='/'||root->c->ch=='*'||root->c->ch=='^')
        printf(")");
}

void print_rpn (struct arvore * root)//impressao RPN, analoga a pos-ordem.
{
    if (root==NULL)
        return;
    print_rpn(root->esq);
    print_rpn(root->dir);
    print_lista(root->c);
    printf(" ");
}

void free_lista (struct unidade * lista)//funcao que serve para liberar a memoria da lista
{
    if (lista==NULL)
        return;
    free_lista(lista->prox);
    free(lista);
}

void free_all(struct arvore * root)//funcao que libera a memoria da arvore, e chama a funcao de liberar a lista.
{
    if (root==NULL)
        return;
    free_all(root->esq);
    free_all(root->dir);
    free_lista(root->c);
    free(root);
}

int menu (struct arvore * root)// funcao menu, dara as opcoes do usuario.
{
    int i;
    printf("\nO que deseja fazer agora?\n1. Imprimir equacao infixa.\n2. Imprimir equacao posfixa (RPN).\n3. Sair.\nSua opcao: ");
    scanf("%d",&i);
    switch(i)
    {
    case 1:
        {
            printf("\nA equacao na notacao infixa eh:\n");
            print_in(root);
            printf("\n");
            return 1;
        }
    case 2:
        {
            printf("\nA equacao na notacao posfixa (RPN) eh:\n");
            print_rpn(root);
            printf("\n");
            return 1;
        }
    case 3:
        {
            return 0;
        }
    default:
        {
            printf("Opcao invalida. Tente novamente.\n");
            return 1;
        }
    }
}

int main ()
{
    printf("Entre com uma equacao na notacao polonesa. Coloque espaços entre os numeros e os operadores.\n");
    scanf("%c",&a);
    //preenche a raiz da arvore.
    struct arvore * root = (struct arvore * )calloc(1,sizeof(struct arvore));
    root->c=add_un();
    root->esq=NULL;
    root->dir=NULL;
    while (a!='\n')//preenche a arvore
    {
        scanf("%c",&a);
        if (a!=' '&&a!='\n')
            add(root);
    }
    int i = 1;
    while (i==1)// mantem o menu ate que o usuario queira sair.
    {
        i=menu(root);//retorna zero para a saida.
    }
    free_all(root);//liberacao da memoria alocada.
}
