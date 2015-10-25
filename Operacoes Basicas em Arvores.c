#include <stdio.h>
#include <stdlib.h>

struct arvore {
int chave;
struct arvore * esq;
struct arvore * dir;
};

struct arvore * root = NULL;

void adicionar (int a)
{
    struct arvore * ramo = root;
    struct arvore * galho = NULL;
    struct arvore * novo = (struct arvore *)calloc(1,sizeof(struct arvore));
    novo->chave=a;
    novo->esq=NULL;
    novo->dir=NULL;
    if (root==NULL)
        {
            root=novo;
            return;
        }
    while (ramo!=NULL)
        {
            galho=ramo;
            if (a>=ramo->chave)
                ramo=ramo->dir;
            else
                ramo=ramo->esq;
        }
    if (a>=galho->chave)
        galho->dir=novo;
    else
        galho->esq=novo;
}

int busca (struct arvore * tree, int a)
{
    struct arvore * galho = tree;
    if (galho==NULL)
        return 0;
    if (galho->chave==a)
        return 1;
    else
    {
        if (a>galho->chave)
            return busca (galho->dir,a);
        else
            return busca (galho->esq,a);
    }
}

void remover (int a)
{
    struct arvore * galho = NULL;
    struct arvore * ramo = root;
    while (ramo->chave!=a&&ramo!=NULL)
    {
        galho=ramo;
        if (a>=ramo->chave)
            ramo=ramo->dir;
        else
            ramo=ramo->esq;
    }
    struct arvore *n = ramo->dir;
    while (n!=NULL&&n->esq!=NULL)
        n=n->esq;
    struct arvore *m = ramo->esq;
    if(n!=NULL)
    {
        n->esq=ramo->esq;
        m=ramo->dir;
    }
    else
        m=ramo->esq;
    if(galho==NULL)
    {
        root=m;
    }
    else
    {
        if(galho->chave<a)
            galho->dir=m;
        else
            galho->esq=m;
    }
    free(ramo);
}

void print_pre (struct arvore * tree)
{
    if (tree==NULL)
        return;
    printf(" %d ",tree->chave);
    print_pre(tree->esq);
    print_pre(tree->dir);
}

void print_pos (struct arvore * tree)
{
    if (tree==NULL)
        return;
    print_pos(tree->esq);
    print_pos(tree->dir);
    printf(" %d ",tree->chave);
}

void print_in (struct arvore * tree)
{
    if (tree==NULL)
        return;
    print_in(tree->esq);
    printf(" %d ",tree->chave);
    print_in(tree->dir);
}

void print_con (struct arvore * tree)
{
    if (tree==NULL)
    {
        printf("[]");
        return;
    }
    printf("[%d",tree->chave);
    print_con (tree->esq);
    print_con (tree->dir);
    printf("]");
}

int menu ()
{
    int i,j,n,a;
    printf("\nO que deseja fazer agora? Digite o numero com sua opcao:\n");
    printf("1. Adicionar novos numeros.\n2. Remover um item.\n3. Buscar um numero.\n4. Imprimir a arvore.\n5. Sair\nOpcao: ");
    scanf("%d",&i);
    switch (i)
    {
        case 1:
            {
                printf("Quantos numeros pretende entrar? ");
                scanf("%d",&n);
                printf("Entre com os numeros:\n");
                for (j=0;j<n;j++)
                {
                    scanf("%d",&a);
                    adicionar (a);
                }
                printf("Itens adicionados!\n");
                return 0;
            }
        case 2:
            {
                printf("Qual numero voce deseja remover? ");
                scanf("%d",&a);
                if (busca(root,a)==1)
                {
                    remover(a);
                    printf("Item removido!\n");
                    return 0;
                }
                else
                {
                    printf("O item nao pode ser removido pois nao se encontra na arvore.\n");
                    return 0;
                }
            }
        case 3:
            {
                printf("Qual numero deseja buscar? ");
                scanf("%d",&a);
                if (busca(root,a)==1)
                    printf("Numero encontrado! Ele ja esta na arvore.\n");
                else
                    printf("Numero nao encontrado.\n");
                return 0;
            }
        case 4:
            {
               printf("Como voce deseja imprimi-los?\n1. Em ordem.\n2. Pre-ordem.\n3. Pos-ordem.\n4. Com conchetes.\nOpcao: ");
               scanf("%d",&j);
               switch (j)
               {
                   case 1:
                       {
                           print_in(root);
                           printf("\n");
                           return 0;
                       }
                   case 2:
                       {
                           print_pre(root);
                           printf("\n");
                           return 0;
                       }
                   case 3:
                       {
                           print_pos(root);
                           printf("\n");
                           return 0;
                       }
                   case 4:
                       {
                           print_con(root);
                           printf("\n");
                           return 0;
                       }
                   default:
                       {
                           printf("Ocorreu um erro. Tente novamente.\n");
                           return 0;
                       }
               }
            }
        case 5:
            return 1;
        default:
            {
            printf("Ocorreu um erro. Tente novamente.\n");
            return 0;
            }
    }
}

free_memory (struct arvore * raiz)
{
    if (raiz==NULL)
        return;
    free_memory(raiz->esq);
    free_memory(raiz->dir);
    free(raiz);
}

int main ()
{
    int n,i,a;
    printf("Inicializando arvore. Quantos valores deseja entrar? ");
    scanf("%d",&n);
    while (n<1)
    {
        printf("Entre com pelo menos um numero. Quantos valores deseja entrar? ");
        scanf("%d",&n);
    }
    printf("Entre com os numeros:\n");
    for (i=0;i<n;i++)
    {
        scanf("%d",&a);
        adicionar (a);
    }
    i=0;
    while (i!=1)
    {
        i=menu();
    }
    free_memory(root);
}
