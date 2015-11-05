#include <stdio.h>
#include <stdlib.h>

struct arvore//Estrutura p/ a arvore.
{
int chave;
struct arvore* esq;
struct arvore* dir;
};

struct arvore* root = NULL; //raiz da arvore sera global, para que possa ser facilmente removida.

void adicionar (int a)//funcao que adiciona um inteiro a arvore.
{
    struct arvore * ramo = root;
    struct arvore * galho = NULL;
    struct arvore * novo = (struct arvore *)calloc(1,sizeof(struct arvore));
    novo->chave=a;
    novo->esq=NULL;
    novo->dir=NULL;
    if (root==NULL)//se nao houver elementos, o adicionado sera a raiz.
        {
            root=novo;
            return;
        }
    while (ramo!=NULL)//se houver, deve-se achar sua posicao na arvore.
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

int busca (struct arvore * tree, int a)//funcao de busca, retorna 1 se encontrar o inteiro pedido.
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

void remover (int a) //funcao para remover inteiros da arvore, incluindo a raiz.
{
    struct arvore * galho = NULL;
    struct arvore * ramo = root;
    while (ramo->chave!=a&&ramo!=NULL)//encontra a posiçao do inteiro a ser removido
    {
        galho=ramo;
        if (a>=ramo->chave)
            ramo=ramo->dir;
        else
            ramo=ramo->esq;
    }
    struct arvore *n = ramo->dir;
    while (n!=NULL&&n->esq!=NULL)//encontra o menor numero maior que o que vai ser removido
        n=n->esq;
    struct arvore *m = ramo->esq;//preenche m dependendo de da posicao do n.
    if(n!=NULL)
    {
        n->esq=ramo->esq;
        m=ramo->dir;
    }
    else
        m=ramo->esq;
    if(galho==NULL)//se o item a ser removido for a raiz.
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
    free(ramo);//libera a memoria alocada para o ramo removido.
}

void print_pre (struct arvore * tree)//imprime em pre-ordem
{
    if (tree==NULL)
        return;
    printf(" %d ",tree->chave);
    print_pre(tree->esq);
    print_pre(tree->dir);
}

void print_pos (struct arvore * tree)//imprime em pos-ordem
{
    if (tree==NULL)
        return;
    print_pos(tree->esq);
    print_pos(tree->dir);
    printf(" %d ",tree->chave);
}

void print_in (struct arvore * tree)//imprime em ordem
{
    if (tree==NULL)
        return;
    print_in(tree->esq);
    printf(" %d ",tree->chave);
    print_in(tree->dir);
}

void print_col (struct arvore * tree) // imprime em labelled bracketing
{
    if (tree==NULL)
    {
        printf("[]");//para quando o no estiver vazio
        return;
    }
    printf("[%d",tree->chave);
    print_col (tree->esq);
    print_col (tree->dir);
    printf("]");
}

int menu ()//funcao que imprime o menu e executa a opcao escolhida
{
    int i,j,n,a;
    printf("\nO que deseja fazer agora? Digite o numero com sua opcao:\n");
    printf("1. Adicionar novos numeros.\n2. Remover um item.\n3. Buscar um numero.\n4. Imprimir a arvore.\n5. Sair\nOpcao: ");
    scanf("%d",&i);
    switch (i)//pula para a opcao escolhida.
    {
        case 1:
            {
                printf("Quantos numeros pretende entrar? ");
                scanf("%d",&n);
                while (n<1)
                {
                    printf("Entre com pelo menos um numero. Quantos valores deseja entrar? ");
                    scanf("%d",&n);
                }
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
        case 4://conta com um switch interno, para que se escolha como sera impressa a arvore
            {
               printf("Como voce deseja imprimi-los?\n1. Em ordem.\n2. Pre-ordem.\n3. Pos-ordem.\n4. Labelled bracketing.\nOpcao: ");
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
                           print_col(root);
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

free_memory (struct arvore * raiz)//libera a memoria alocada na arvore.
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
    while (n<1)//Previne erros e garante que pelo menos 1 item estara na arvore.
    {
        printf("Entre com pelo menos um numero. Quantos valores deseja entrar? ");
        scanf("%d",&n);
    }
    printf("Entre com os numeros:\n");
    for (i=0;i<n;i++)//preenche a arvore.
    {
        scanf("%d",&a);
        adicionar (a);
    }
    i=0;
    while (i!=1)
        i=menu();//chama o menu e retorna 1 quando quiser sair.
    free_memory(root);//desaloca a memoria.
}
