#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define LH 1 /*����*/
#define EH 0 /*����*/
#define RH -1/*�k��*/
int LL=0,LR=0,RL=0,RR=0;
typedef struct BITnode
{
    int data;
    int bf;/*�`�I���Ŧ]�l*/
    struct BITnode *lchild,*rchild;
}BITnode,*BITtree;
/*��Hp���ڪ��G���j�M�𰵥k����B�z*/
/*�B�z���� p���V�s����ڸ`�I �α��ध�e�����l�𪺮ڸ`�I*/
void r_rotate(BITtree *p)
{
    BITtree L;
    L=(*p)->lchild;
    (*p)->lchild=L->rchild; /*L���k�l�𱾱���p�����l��*/
    L->rchild=(*p);
    *p=L;
}
/*��Hp���ڪ��G���j�M�𰵥�����B�z*/
/*�B�z���� p���V�s����ڸ`�I �α��ध�e���k�l�𪺮ڸ`�I*/
void l_rotate(BITtree *p)
{
    BITtree R;
    R=(*p)->rchild;
    (*p)->rchild=R->lchild;
    R->lchild=(*p);
    *p=R;
}
/*��H����T�ҫ��`�I���ڪ��G���𰵥����७�ųB�z*/
/*������T���V�s���I*/
void leftbalance(BITtree *T)
{
    BITtree L,Lr;
    L=(*T)->lchild;
    switch(L->bf)/*�˹�T�����l�𥭿ū� �ð��۹������B�z*/
    {
        case LH:/*�s�`�I���bT�����Ĥl�����l��W �@�k����*/
            (*T)->bf=L->bf=EH;
            r_rotate(T);
            LL++;
            break;
        case RH:/*�s�`�I���bT�����Ĥl���k�l��W �@������*/
            Lr=L->rchild;
            LR++;
            switch(Lr->bf)/*�ק省�Ŧ]�l*/
            {
                case LH:
                    (*T)->bf=RH;
                    L->bf=EH;
                    break;
                case EH:
                    (*T)->bf=L->bf=EH;
                    break;
                case RH:
                    (*T)->bf=EH;
                    L->bf=LH;
                    break;
            }
            Lr->bf=EH;
            l_rotate(&(*T)->lchild);/*��T�����l��@�����७�ųB�z*/
            r_rotate(T);/*��T�@�k���७�ųB�z*/
    }
}
/*��H����T�ҫ��`�I���ڪ��G���𰵥k���७�ųB�z*/
/*������T���V�s���I*/
void rightbalance(BITtree *T)
{
    BITtree R,Rl;
    R=(*T)->rchild;
    switch(R->bf)
    {
        case RH:
            (*T)->bf=R->bf=EH;
            l_rotate(T);
            RR++;
            break;
        case LH:/*�s�`�I���bT���k�Ĥl�����l��W �n��������*/
            Rl=R->lchild;
            RL++;
            switch(Rl->bf)/*�ק�T�Υk�Ĥl�����Ŧ]�l*/
            {
                case RH:
                    (*T)->bf=LH;
                    R->bf=EH;
                    break;
                case EH:
                    (*T)->bf=R->bf=EH;
                    break;
                case LH:
                    (*T)->bf=EH;
                    R->bf=RH;
                    break;
            }
            Rl->bf=EH;
            r_rotate(&(*T)->rchild);
            l_rotate(T);
    }
}
/*�Y���s�b�Me���ۦP����r���`�I �h���J�s�`�Ie�ê�^true �_�h��^false*/
/*���h���� �h�����ű���B�z ���L�ܼ�talle�ϬM�����P�_*/
bool InsertAVL(BITtree *T ,int e ,bool *taller)
{
    if(!*T)/*���J�s�`�I*/
    {
        *T=(BITtree)malloc(sizeof(BITnode));
        (*T)->data=e;
        (*T)->lchild=(*T)->rchild=NULL;
        (*T)->bf=EH;
        *taller=true;
    }
    else
    {
        if(e==(*T)->data)/*�𤤤w�s�b�ۦP���`�I ���A���J*/
        {
            *taller=false;
            return false;
        }
        if(e<(*T)->data)/*�b�𪺥��l�𤤧�A����m���J*/
        {
            if(!InsertAVL(&(*T)->lchild,e,taller))
                return false;
            if(*taller)/*�w���J*/
            {
                switch((*T)->bf)/*�ˬdT�����ū�*/
                {
                    case LH:/*�쥻����k�� ���������ųB�z*/
                        leftbalance(T);
                        *taller=false;
                        break;
                    case EH:/*�쥻���k���� �{�b�]���l��W���Ӿ�W��*/
                        (*T)->bf=LH;
                        *taller=true;
                        break;
                    case RH:/*�쥻�k�񥪰� �{�b����*/
                        (*T)->bf=EH;
                        *taller=false;
                        break;
                }
            }
        }
        else/*�~��b�k�l��M��A����m���J*/
        {
            if(!InsertAVL(&(*T)->rchild,e,taller))
            return false;
            if(*taller)/*�H���J��k�l��*/
            {
                switch((*T)->bf)/*�ˬd���Ŧ]�l*/
                {
                    case LH:/*�쥻����k�� �{�b����*/
                        (*T)->bf=EH;
                        *taller=false;
                        break;
                    case EH:/*�쥻���k�l�𵥰�  �{�b�]�k�l��W���Ӿ�W��*/
                        (*T)->bf=RH;
                        *taller=true;
                        break;
                    case RH:/*�쥻�k�l��񥪤l�� ���@�k���ųB��*/
                        rightbalance(T);
                        *taller=false;
                        break;
                }
            }
        }
    }
    return true;
}
void preorder(BITtree T)
{
    if(T==NULL)
        return ;
    printf("%d,",T->data);
    preorder(T->lchild);
    preorder(T->rchild);
}
int main(int argc,char *argv[])
{
    FILE *fptr;
    fptr=fopen(argv[1],"r");
    if(fptr==NULL)
        printf("fail\n");
    int i,temp;
    BITtree T=NULL;
    bool taller;
    while(!feof(fptr))
    {
        fscanf(fptr,"%d",&temp);
        InsertAVL(&T,temp,&taller);
    }
    preorder(T);
    printf("\nLL : %d\nLR : %d\nRL : %d\nRR : %d\n",LL,LR,RL,RR);
    fclose(fptr);
    return 0;
}
