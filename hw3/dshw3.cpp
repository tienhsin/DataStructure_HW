#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include <stdlib.h>
#define Max 20000 //�̦h���X�Ӹ`�I
using namespace std;
typedef struct edgenode
{
    int adjvex;
    struct edgenode* next;
} edgenode;

edgenode* create_node(int data)
{
    edgenode* n = (edgenode*)malloc(sizeof(edgenode));
    n->adjvex = data;
    n->next = NULL;
    //printf("x");
    return n;
}
void insert_node(edgenode* n1, edgenode* n2)
{
    n2->next = n1->next;
    n1->next = n2;
}
typedef struct vertexnode
{
    double weight;
    double w2;
    int no;
    edgenode *firstedge;
}vertexnode;

void print_lists(vertexnode lists[]);//,char *argv[]);
void free_lists(edgenode *p);
void pagerank(vertexnode *p,int ,double,int);
int cmp( const void *a ,const void *b)
{
    return (*(vertexnode *)a).weight < (*(vertexnode *)b).weight ? 1 : -1;
}

int main(int argc,char *argv[])
{
    int l,i=0,n1,n2;

    ifstream fin(argv[1]);
    fin>>l;//�ɮת��Ĥ@�ӼƦr�Ol
    int iter=atoi(argv[2]);//��J����
    double damping=atof(argv[3]);//��Jdamping factor
    int top=atoi(argv[4]);//��J�n�L�X�Ӫ��etop�W
    //scanf("%d",&l);
    vertexnode adjlist[Max];
    while(i<Max)//��`�I����l��
    {
        adjlist[i].weight=1;
        adjlist[i].w2=(1-damping);//0.15;
        adjlist[i].firstedge=NULL;//�`�I�٨S���M��L�I���s��
        adjlist[i].no=i;//�`�I�s��
        i++;
    }
    i=1;
    int j=0;
    edgenode *p;
    while(i<l+1)//Ū�i�s��
    {
        fin>>n1>>n2;
        //scanf("%d %d",&n1,&n2);
        while(1)
        {
            if(n1==j)
            {
                if(adjlist[j].firstedge==NULL)
                {
                    adjlist[j].firstedge=create_node(n2);
                    //printf("*");
                    break;
                }
                else
                {
                    p=adjlist[j].firstedge;
                    while(p->next!=NULL)p=p->next;
                    insert_node(p,create_node(n2));
                    //printf("+");
                    break;
                }
            }
            j++;
        }
        j=0;
        i++;
    }
   // print_lists(adjlist);//, &argv[5]);
    pagerank(adjlist,iter,damping,top);
    qsort(adjlist,Max,sizeof(adjlist[0]),cmp);
    for(j=0;j<top;j++)
    {
        printf("%d   %f\n",adjlist[j].no,adjlist[j].weight);
    }
    for(i=0;i<Max;i++)
        free_lists(adjlist[i].firstedge);

    return 0;
}
void pagerank(vertexnode *p,int iter,double damping,int top)
{
    int i=0,c=0,k,j=0;
    //scanf("%d",&iter);//����
    //scanf("%d",&damp);//0.85
    //scanf("%d",&k);
    edgenode *n;
    while(i<iter)
    {
        j=0;
        while(j<Max)
        {
            c=0;
            n=(p+j)->firstedge;
            while(n)//�s��X��node
            {
                c++;
                n=n->next;
            }
            if(c!=0)
            {
                n=(p+j)->firstedge;
                while(n)//��pagerank�[��w2
                {
                   // printf("%f  ",(p+(n->adjvex))->w2);
                    (p+(n->adjvex))->w2+=damping*((p+j)->weight)/c;
                    n=n->next;
                }
            }
            j++;
        }
        for(j=0;j<Max;j++)
        {
            //printf("%d   %f\n",j,(p+j)->w2);
            (p+j)->weight=(p+j)->w2;
            (p+j)->w2=(1-damping);
           //printf("%d   %f\n",j,(p+j)->weight);
        }
        i++;
    }
}
void print_lists(vertexnode lists[])//,char *argv[])
{
    //ofstream fout(argv[5]);
    int i;
    edgenode *p;
    for(i=0;i<Max;i++)
    {
        p=lists[i].firstedge;
        printf("%d  ",lists[i].no);
        //fout<<lists[i].no<<"  ";
        while(p)
        {
            printf("%d   ",p->adjvex);
            //fout<<p->adjvex<<"  ";
            p=p->next;
        }
        printf("\n");
        //fout<<endl;
    }
}
void free_lists(edgenode *x)
{
    if(x==NULL)
        return;
    if (x->next!= NULL)
    {
        free_lists(x->next);
    }
    free(x);
}



