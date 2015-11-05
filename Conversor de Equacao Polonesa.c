#include <stdio.h>
#include <stdlib.h>
struct unidade
{
    char ch;
    struct undidade * prox;
};

struct arvore
{
    struct unidade * c;
    struct arvore * esq;
    struct arvore * dir;
};

char a;

struct unidade * add_un ()
{
    struct unidade * novo = (struct unidade*)calloc(1,sizeof(struct unidade));

    if (a=='+'||a=='-'||a=='*'||a=='/'||a=='^')
    {
        novo->ch=a;
        novo->prox=NULL;
    }
    else
    {
        struct unidade * marcador = novo;
        struct unidade * novo1;
        marcador->ch=a;
        marcador->prox=NULL;
        scanf("%c",&a);
        while (a!=' '&&a!='\n')
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

int add(struct arvore * root)
{
    int i=0;
    if (root->esq==NULL)
    {
        root->esq=(struct arvore*)calloc(1,sizeof(struct arvore));
        root->esq->c=add_un();
        root->esq->esq=NULL;
        root->esq->dir=NULL;
        return 1;
    }
    if (i==0&&(root->esq->c->ch=='+'||root->esq->c->ch=='-'||root->esq->c->ch=='/'||root->esq->c->ch=='*'||root->esq->c->ch=='^'))
    {
        i=add(root->esq);
    }
    if (i==0&&root->dir==NULL)
    {
        root->dir=(struct arvore*)calloc(1,sizeof(struct arvore));
        root->dir->c=add_un();
        root->dir->esq=NULL;
        root->dir->dir=NULL;
        return 1;
    }
    if(i==0&&(root->dir->c->ch=='+'||root->dir->c->ch=='-'||root->dir->c->ch=='/'||root->dir->c->ch=='*'||root->dir->c->ch=='^'))
    {
        i=add(root->dir);
    }
    return i;
}

void print_lista (struct unidade * lista)
{
    while(lista!=NULL)
    {
        printf("%c",lista->ch);
        lista=lista->prox;
    }
}

void print_in(struct arvore * root)
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

void print_rpn (struct arvore * root)
{
    if (root==NULL)
        return;
    print_rpn(root->esq);
    print_rpn(root->dir);
    print_lista(root->c);
    printf(" ");
}

int main ()
{
    printf("Entre com uma equacao na notacao polonesa:\n");
    scanf("%c",&a);
    struct arvore * root = (struct arvore * )calloc(1,sizeof(struct arvore));
    root->c=add_un();
    root->esq=NULL;
    root->dir=NULL;
    while (a!='\n')
    {
        scanf("%c",&a);
        if (a!=' '&&a!='\n')
            add(root);
    }
    printf("\nA equacao na notacao infixa eh:\n");
    print_in(root);
    printf("\nA equacao na notacao posfixa (RPN) eh:\n");
    print_rpn(root);

}
