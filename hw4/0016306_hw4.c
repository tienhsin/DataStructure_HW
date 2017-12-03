#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define LH 1 /*左高*/
#define EH 0 /*等高*/
#define RH -1/*右高*/
int LL=0,LR=0,RL=0,RR=0;
typedef struct BITnode
{
    int data;
    int bf;/*節點平衡因子*/
    struct BITnode *lchild,*rchild;
}BITnode,*BITtree;
/*對以p為根的二元搜尋樹做右旋轉處理*/
/*處理之後 p指向新的樹根節點 及旋轉之前的左子樹的根節點*/
void r_rotate(BITtree *p)
{
    BITtree L;
    L=(*p)->lchild;
    (*p)->lchild=L->rchild; /*L的右子樹掛接為p的左子樹*/
    L->rchild=(*p);
    *p=L;
}
/*對以p為根的二元搜尋樹做左旋轉處理*/
/*處理之後 p指向新的樹根節點 及旋轉之前的右子樹的根節點*/
void l_rotate(BITtree *p)
{
    BITtree R;
    R=(*p)->rchild;
    (*p)->rchild=R->lchild;
    R->lchild=(*p);
    *p=R;
}
/*對以指標T所指節點為根的二元樹做左旋轉平衡處理*/
/*結束時T指向新結點*/
void leftbalance(BITtree *T)
{
    BITtree L,Lr;
    L=(*T)->lchild;
    switch(L->bf)/*檢察T的左子樹平衡度 並做相對應的處理*/
    {
        case LH:/*新節點插在T的左孩子的左子樹上 作右旋轉*/
            (*T)->bf=L->bf=EH;
            r_rotate(T);
            LL++;
            break;
        case RH:/*新節點插在T的左孩子的右子樹上 作雙旋轉*/
            Lr=L->rchild;
            LR++;
            switch(Lr->bf)/*修改平衡因子*/
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
            l_rotate(&(*T)->lchild);/*對T的左子樹作左旋轉平衡處理*/
            r_rotate(T);/*對T作右旋轉平衡處理*/
    }
}
/*對以指標T所指節點為根的二元樹做右旋轉平衡處理*/
/*結束時T指向新結點*/
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
        case LH:/*新節點插在T的右孩子的左子樹上 要做雙旋轉*/
            Rl=R->lchild;
            RL++;
            switch(Rl->bf)/*修改T及右孩子的平衡因子*/
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
/*若不存在和e有相同關鍵字的節點 則插入新節點e並返回true 否則返回false*/
/*失去平衡 則做平衡旋轉處理 布林變數talle反映長高與否*/
bool InsertAVL(BITtree *T ,int e ,bool *taller)
{
    if(!*T)/*插入新節點*/
    {
        *T=(BITtree)malloc(sizeof(BITnode));
        (*T)->data=e;
        (*T)->lchild=(*T)->rchild=NULL;
        (*T)->bf=EH;
        *taller=true;
    }
    else
    {
        if(e==(*T)->data)/*樹中已存在相同的節點 不再插入*/
        {
            *taller=false;
            return false;
        }
        if(e<(*T)->data)/*在樹的左子樹中找適當的位置插入*/
        {
            if(!InsertAVL(&(*T)->lchild,e,taller))
                return false;
            if(*taller)/*已插入*/
            {
                switch((*T)->bf)/*檢查T的平衡度*/
                {
                    case LH:/*原本左比右高 須做左平衡處理*/
                        leftbalance(T);
                        *taller=false;
                        break;
                    case EH:/*原本左右等高 現在因左子樹增高而樹增高*/
                        (*T)->bf=LH;
                        *taller=true;
                        break;
                    case RH:/*原本右比左高 現在等高*/
                        (*T)->bf=EH;
                        *taller=false;
                        break;
                }
            }
        }
        else/*繼續在右子樹尋找適當的位置插入*/
        {
            if(!InsertAVL(&(*T)->rchild,e,taller))
            return false;
            if(*taller)/*以插入到右子樹*/
            {
                switch((*T)->bf)/*檢查平衡因子*/
                {
                    case LH:/*原本左比右高 現在等高*/
                        (*T)->bf=EH;
                        *taller=false;
                        break;
                    case EH:/*原本左右子樹等高  現在因右子樹增高而樹增高*/
                        (*T)->bf=RH;
                        *taller=true;
                        break;
                    case RH:/*原本右子樹比左子樹高 須作右平衡處裡*/
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
