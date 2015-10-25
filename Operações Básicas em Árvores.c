#include <stdio.h>
#include <stdlib.h>

struct arvore {
int chave;
struct arvore * esq;
struct arvore * dir;
};

void adicionar (struct arvore * tree,int a)
{
    struct arvore * ramo = tree;
    struct arvore * galho = NULL;
    struct arvore * novo = (struct arvore *)calloc(1,sizeof(struct arvore *));
    novo->chave=a;
    novo->esq=NULL;
    novo->dir=NULL;
    if (tree==NULL)
        tree=novo;
    else
    {
        while (ramo=!NULL)
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

void remover (struct arvore * tree, int a)
{
    struct arvore * galho = NULL;
    struct arvore * ramo = tree;
    while (ramo->chave!=a&&ramo!=NULL)
    {
        galho=ramo;
        if (a>=ramo->chave)
            ramo=ramo->dir;
        else
            ramo=ramo->esq;
    }
    if (ramo==NULL)//Quando a chave nao for encontrada
            return;
    struct arvore *n = ramo->dir;
    while (n!=NULL&&n->esq!=NULL)
        n=n->esq;
    struct arvore *m = ramo->esq;
    if(n!=NULL)
    {
        n->esq=p->esq;
        m=p->dir;
    }
    else
        m=p->esq;
    if(galho->chave<a)
        galho->dir=m;
    else
        galho->esq=m;
    free(ramo);
}

void print_pre ()
{

}

void print_pos ()
{

}

void print_in ()
{

}

int main ()
{
    struct arvore * root = NULL;

}
