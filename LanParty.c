#include<stdio.h>
#include<stdlib.h>
struct jucator
{
    char *nume;
    char *prenume;
    int exp;
};
typedef struct jucator ELEM1;
struct echipa
{
    int nr;
    float punctaj;
    char *nechipa;
    ELEM1 *membru;
    struct echipa* next;
};
typedef struct echipa ELEM2;
struct stiva
{
    ELEM2 *e;
    struct stiva *next;
};
typedef struct stiva STACK;
struct meci
{
    ELEM2 *e1;
    ELEM2 *e2;
    struct meci *next;
};
typedef struct meci MECI;
struct Champions
{
    ELEM2 *echipa;
};
typedef struct Champions CHAMPS;
struct Arbore
{
    ELEM2 *echipa;
    struct Arbore *right , *left;
};
typedef struct Arbore BST;
ELEM2* CitireDate(int *n,FILE *f)
{
    int i=0,j;
    ELEM2* cap;
    ELEM2 *p,*q;
    fscanf(f,"%d",n);
    p=malloc(sizeof(ELEM2));
    if(p==NULL)
    {
        printf("\n Alocarea esuata. ");
        exit(1);
    }
    fscanf(f,"%d",&p->nr);
    p->nechipa=malloc(sizeof(char)*50);
    fscanf(f,"%[^\n]s",p->nechipa);
    p->membru=malloc(sizeof(ELEM1)*p->nr);
    p->punctaj=0;
    for(j=0;j<p->nr;j++)
    {
            p->membru[j].nume=malloc(sizeof(char)*50);
            fscanf(f,"%s",p->membru[j].nume);
            p->membru[j].prenume=malloc(sizeof(char)*50);
            fscanf(f,"%s",p->membru[j].prenume);
            fscanf(f,"%d",&p->membru[j].exp);
            p->punctaj=p->punctaj+p->membru[j].exp;
    }
    p->punctaj=p->punctaj/p->nr;
    p->next=NULL;
    for(i=1;i<*n;i++)
    {
        q=malloc(sizeof(ELEM2));
        if(p==NULL)
        {
            printf("\n Alocarea a esuat. ");
            exit(1);
        }
        fscanf(f,"%d",&q->nr);
        q->nechipa=malloc(sizeof(char)*50);
        fscanf(f,"%[^\n]s",q->nechipa);
        q->membru=malloc(sizeof(ELEM1)*q->nr);
        q->punctaj=0;
        for(j=0;j<q->nr;j++)
        {
            q->membru[j].nume=malloc(sizeof(char)*50);
            fscanf(f,"%s",q->membru[j].nume);
            q->membru[j].prenume=malloc(sizeof(char)*50);
            fscanf(f,"%s",q->membru[j].prenume);
            fscanf(f,"%d",&q->membru[j].exp);
            q->punctaj=q->punctaj+q->membru[j].exp;
        }
        q->punctaj=q->punctaj/q->nr;
        q->next=p;
        p=q;
    }
    cap=p;
    return cap;
}
void AfisareDate(ELEM2* cap,FILE *f)
{
    ELEM2* p;
    for(p=cap;p!=NULL;p=p->next)
    {
        fprintf(f,"%s\n",p->nechipa);
    }
}
void StergereLista(ELEM2 **cap)
{
    ELEM2 *p;
    for(p=(*cap);p!=NULL;p=p->next)
    {
        free(p);
    }
}
float GasireMinim(ELEM2* cap)
{
    float min;
    ELEM2* p;
    min=cap->punctaj;
    for(p=cap;p!=NULL;p=p->next)
    {
        if(p->punctaj<min) min=p->punctaj;
    }
    return min;
}
int VerificPutereaLuiDoi(int x)
{
   if (x == 0)
      return 0;
   while( x != 1)
   {
      if(x % 2 != 0)
         return 0;
      x /= 2;
   }
   return 1;
}
ELEM2* Preliminarii(ELEM2* cap,int *n)
{
    ELEM2 *p,*q,*z;
    float x;

    if(VerificPutereaLuiDoi(*n)==1) return cap;
    while(VerificPutereaLuiDoi(*n)==0)
    {
    p=cap;
    x=GasireMinim(cap);
    while((VerificPutereaLuiDoi(*n)==0)&&(p->punctaj==x)&&(p!=NULL))
    {
        q=p->next;
        free(p->membru);
        free(p);
        p=q;
        x=GasireMinim(p);
        *n=*n-1;
    }
    cap=p;
    if((cap!=NULL)&&(VerificPutereaLuiDoi(*n)==0))
    {
        for(;p!=NULL;p=p->next)
        {
            q=p->next;
            while((q!=NULL)&&(q->punctaj==x)&&(VerificPutereaLuiDoi(*n)==0)&&(cap->punctaj!=x))
            {
                z=q->next;
                free(q->membru);
                free(q);
                q=z;
                p->next=q;
                x=GasireMinim(cap);
                *n=*n-1;
            }
        }
    }
    }
    return cap;
}
MECI* MeciNou(ELEM2 *p,ELEM2 *q)
{
    MECI *x;
    x=malloc(sizeof(MECI));
    x->e1=p;
    x->e2=q;
    x->next=NULL;
    return x;
}
int MeciNu(MECI *front)
{
    if(front==NULL)
    {
        return 0;
    }
    return 1;
}
void PushIt(MECI **front,MECI **rear,ELEM2 *p,ELEM2 *q)
{
    MECI *x;
    x=MeciNou(p,q);
    if((*rear)!=NULL)
    {
        (*rear)->next=x;
    }
    (*rear)=x;
    if((*front)==NULL)
    {
        (*front)=x;
    }
}
void PopIt(MECI **front)
{
    MECI *x;
    if(MeciNu(*front)) return;
    x=(*front);
    (*front)=(*front)->next;
    free(x);
}
void Meciuri(MECI *front,FILE *f)
{
    MECI *x;
    for(x=front;x!=NULL;x=x->next)
    {
        fprintf(f,"%-25s -- %25s\n", x->e1->nechipa,x->e2->nechipa);
    }
}
STACK* NodNou(ELEM2* p)
{
    STACK* x;
    x=malloc(sizeof(STACK));
    x->e=p;
    x->next=NULL;
    return x;
}
int StackEmpty(STACK* top)
{
    if(top==NULL)
    {
        return 1;
    }
    return 0;
}
void PushStack(STACK **top,ELEM2 *p)
{
    STACK *x;
    x=malloc(sizeof(STACK));
    x=NodNou(p);
    if(StackEmpty(*top))
    {
        (*top)=x;
    }
    else
    {
         x->next=(*top);
        (*top)=x;
    }
}
void PopStack(STACK **top)
{
    STACK *x;
    if(StackEmpty(*top)) return;
    x=(*top);
    (*top)=(*top)->next;
    free(x);
}
void ShowStack(STACK *top,FILE *f)
{
    STACK *s;
    for(s=top;s!=NULL;s=s->next)
    {
        fprintf(f,"%-25s --- %0.2f\n", s->e->nechipa,s->e->punctaj);
    }
}
void Pregatiri(MECI **front,MECI **rear,ELEM2 *cap,int n)
{
    int i=0;
    ELEM2 *p;
    p=cap;
    while((i<n/2)&&(cap!=NULL))
    {
        PushIt(front,rear,p,p->next);
        p=p->next->next;
        i++;
    }
}
void DeleteStack(STACK **top)
{
    STACK *s;
    if(StackEmpty((*top))) return;
    for(s=(*top);s!=NULL;s=s->next)
    {
        free(s);
    }
    (*top)=NULL;
}
void RewardStack(STACK *top)
{
    STACK *s;
    if(StackEmpty(top)) return;
    for(s=top;s!=NULL;s=s->next)
    {
        s->e->punctaj=s->e->punctaj+1;
    }
}
void EliberareMeci(MECI **front,MECI **rear)
{
    MECI *m;
    for(m=(*front);m!=NULL;m=m->next)
    {
        free(m);
    }
    (*front)=NULL;
    (*rear)=NULL;
}
void PregatiriStack(MECI **front,MECI **rear,STACK *top)
{
    STACK *s;
    s=top;
    for(s=top;s!=NULL;s=s->next)
    {
        PushIt(front,rear,s->e,s->next->e);
        s=s->next;
    }
}
ELEM2* Campionii(STACK *top,ELEM2 *cap)
{
    ELEM2 *p,*q;
    STACK *s;
    p=cap;
    if(cap==NULL)
    {
        cap=top->e;
        cap->next=NULL;
        return cap;
    }
    else
    {
        for(s=top;s!=NULL;s=s->next)
        {
            q=s->e;
            q->next=NULL;
            p->next=q;
            p=q;
        }
        return cap;
    }
}
BST* ElementNouCopac(ELEM2* p)
{
    BST *node=malloc(sizeof(BST));
    node->echipa=p;
    node->left=NULL;
    node->right=NULL;
    return node;
}
BST* InserareCopac(BST *node,ELEM2 *p)
{
    if(node==NULL) return ElementNouCopac(p);
    if(p->punctaj<node->echipa->punctaj) node->left=InserareCopac(node->left,p);
    else if(p->punctaj>node->echipa->punctaj) node->right=InserareCopac(node->right,p);
   // else node->echipa=p;
    return node;
}
void AfisareCopac(BST *root,FILE *f)
{
    if(root!=NULL)
    {
        AfisareCopac(root->right,f);
        fprintf(f,"%-20s -- %0.2f\n", root->echipa->nechipa,root->echipa->punctaj);
        AfisareCopac(root->left,f);
    }
}
void StergereCopac(BST **root)
{
    if(*root!=NULL)
    {
        StergereCopac(*root->right);
        free(*root);
        StergereCopac(*root->left);
    }
}
void Clasament(ELEM2* cap,FILE *f)
{
    ELEM2 *p;
    BST *root=NULL;
    for(p=cap;p!=NULL;p=p->next)
    {
       root=InserareCopac(root,p);
    }
    AfisareCopac(root,f);
    StergereCopac(&root); //Pentru eliberare de memorie.
}
void lanParty(MECI **front,MECI **rear,STACK **top,STACK **top1,ELEM2 *cap,int n,FILE *f)
{
    int i;
    MECI *m;
    Pregatiri(front,rear,cap,n);
    while(n>1)
    {
        PregatiriStack(front,rear,(*top));
        DeleteStack(top);
        Meciuri(*front,f);
        for(m=(*front),i=0;i<n/2;m=m->next,i++)
        {
            if((m->e1->punctaj)>=(m->e2->punctaj))
            {
                PushStack(top,m->e1);
                PushStack(top1,m->e2);
            }
            if((m->e2->punctaj)>(m->e1->punctaj))
            {
                PushStack(top,m->e2);
                PushStack(top1,m->e1);
            }
        }
        RewardStack((*top));
        ShowStack(*top,f);
        DeleteStack(top1);
        EliberareMeci(front,rear);
       n=n/2;
    }
}
void lanParty2(MECI **front,MECI **rear,STACK **top,STACK **top1,ELEM2 *cap,int n,FILE *f)
{
    int i;
    MECI *m;
    ELEM2 *cap1=NULL;
    Pregatiri(front,rear,cap,n);
    while(n>1)
    {
        PregatiriStack(front,rear,(*top));
        DeleteStack(top);
        Meciuri(*front,f);
        for(m=(*front),i=0;i<n/2;m=m->next,i++)
        {
            if((m->e1->punctaj)>=(m->e2->punctaj))
            {
                PushStack(top,m->e1);
                PushStack(top1,m->e2);
            }
            if((m->e2->punctaj)>(m->e1->punctaj))
            {
                PushStack(top,m->e2);
                PushStack(top1,m->e1);
            }
        }
        RewardStack((*top));
        ShowStack(*top,f);
        if(n>8)
        {
            DeleteStack(top1);
        }
        EliberareMeci(front,rear);
       n=n/2;
    }
    cap1=Campionii(*top,cap1);
    cap1=Campionii(*top1,cap1);
    Clasament(cap1,f);
    DeleteStack(top1);  // Pentru eliberare de memorie.
    DeleteStack(top);   // Pentru eliberare de memorie.
    EliberareMeci(front,rear); //Pentru eliberare de memorie.
    StergereLista(&cap1); //Pentru eliberare de memorie.
}
int main (int argc,char* argv[])
{
    int var1,var2,var3,var4,var5,n;
    ELEM2 *cap;
    STACK *top=NULL,*top1=NULL;
    FILE *f,*g,*h;
    MECI *front=NULL,*rear=NULL;
    f=fopen(argv[2],"rt");
    h = fopen(argv[1],"rt");
    g=fopen(argv[3],"wt");
    cap=CitireDate(&n,f);
    fscanf(h,"%d",&var1);
    fscanf(h,"%d",&var2);
    fscanf(h,"%d",&var3);
    fscanf(h,"%d",&var4);
    fscanf(h,"%d",&var5);
    if((var1== 1)&&(var2==0))
    {
        AfisareDate(cap,g);
    }
    if((var2==1)&&(var3==0))
    {
       cap=Preliminarii(cap,&n);
       AfisareDate(cap,g);
    }
    if((var3==1)&&(var4==0))
    {
       cap=Preliminarii(cap,&n);
       AfisareDate(cap,g);
       lanParty(&front,&rear,&top,&top1,cap,n,g);
    }
    if((var4==1)&&(var5==0))
    {
       cap=Preliminarii(cap,&n);
       AfisareDate(cap,g);
       lanParty2(&front,&rear,&top,&top1,cap,n,g);
    }
    if((var5==1))
    {
       cap=Preliminarii(cap,&n);
       AfisareDate(cap,g);
       lanParty2(&front,&rear,&top,&top1,cap,n,g);
    }
    StergereLista(cap); //Pentru eliberare de memorie.
    fclose(f);
    fclose(g);
    fclose(h);
}

