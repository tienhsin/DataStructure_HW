#include<cstdlib>
#include<iostream>
#include<fstream>
#include<cstring>
#include<time.h>
using namespace std;

string buffer(char );
string reverse(string );
typedef struct table
{
    char asc;
    string str;
}table;

typedef struct node
{
    int count;
    char asc;
    bool flag;
	node *left;
    node *right;
}node;
void treebuilt(table t[],string );
void treewalk(string,node *);
int main(int argc,char* argv[])
{
    ifstream fin(argv[1],ios_base::binary);
    //ofstream fout(argv[2]);
     // 取得執行前時間
    clock_t start_time, end_time, time1,time2;
  	float total_time = 0;
  	start_time = clock(); /* mircosecond */
    if(!fin)
    {
        cout<<"fin fail"<<endl;
        return 1;
    }
    else cout<<"fin success"<<endl;
    /*if(!fout)
    {
        cout<<"fout fail"<<endl;
        fin.close();
        return 1;
    }*/

    int i=0;
    char c='0',temp[999999]={' '};
    while(!fin.eof())
    {
        fin.get(c);
        temp[i]=c;
        i++;
    }
    i=0;
    while(temp[i]!='\0')
    {
        //cout<<temp[i];
        i++;
    }

    char count[10]={'0'};
    i=0;
    while(temp[i]=='#')
        i++;
    while(temp[i]!='#')
    {
        count[i]=temp[i];
        i++;
    }
    int j=0;
    while(count[j]!='\0')
    {
        //cout<<count[j];
        j++;
    }
    table t[128];

    while(temp[i]=='#')
        i++;
    j=0;
    i++;
    while(temp[i]!='#')
    {
        t[j].asc=temp[i];
        i++;
        while(temp[i]!='\n')
        {
            t[j].str+=temp[i];
            i++;
        }
        t[j].str+='\0';
        i++;
        j++;
    }
    j=0;

    //cout<<t[0].asc<<" "<<t[0].str;
   /* while(j<128)
    {
        cout<<j<<"  "<<t[j].asc<<"  "<<t[j].str<<endl;
        j++;
    }*/

    while(temp[i]=='#')
        i++;
    i++;
    j=0;
    char code[9999];
    while(temp[i]!='\0')
    {
        code[j]=temp[i];
        i++;
        j++;
    }
    j=0;
    /*while(code[j]!='\0')
    {
        //cout<<code[j];
        j++;
    }*/

    string cc,tt;
    j=0;
    while(code[j]!='\0')
    {
        tt=buffer(code [j]);
        //cout<<tt;
        cc+=tt;
        //system("pause");
        j++;
    }
   // cout<<cc<<endl;
     treebuilt(t,cc);

    //string ccc;
    //int x,y;
   /* for(i=0;cc[i]!='\0';i++)
    {
        ccc+=cc[i];
        for(x=0;x<128;x++)
        {
            for(y=0;t[x].str[y]!='\0';y++)
            {
                if(ccc[y]!=t[x].str[y])
            }
        }
    }*/

	end_time=clock();
	total_time = (float)(end_time- start_time)/CLOCKS_PER_SEC;
    cout<<endl;
    printf("Time : %f sec \n", total_time);

    fin.close();
    //fout.close();
    return 0;
}
string buffer(char c)
{
    int i=0;
    string t;
    //char c;
    while(i<8)
    {
        if((c&1)==0)
        {
            c=c>>1;
            t+='0';
        }
        else if((c&1)==1)
        {
            c=c>>1;
            t+='1';
        }
        i++;
    }
    return reverse(t);
}
string reverse(string t)
{
    char t_r[8];
    int i,j=7;
    for(i=0;i<8;i++)
    {
        t_r[i]=t[j];
        j--;
        //fout<<t_r[i];
    }
   return t_r;
}
void treebuilt(table t[],string cc)
{
     int j=0;
    /* while(j<128)
    {
        cout<<j<<"  "<<t[j].asc<<""<<t[j].str<<endl;
        j++;
    }*/
    int i=0,count=0;
    node *p,*root;
    root=new node;
    root->left=root->right=NULL;
    for(i=0;i<128;i++)
    {
        count=0;
        p=root;
        if(t[i].str[0]!='\0'&&t[i].str[1]!='\0')
        {
            for(j=0;j<50;j++)
            {
                if(t[i].str[j]=='\0')
                {
                    p->asc=t[i].asc;
                    p->left=p->right=NULL;
                   // cout<<p->asc<<"  "<<count<<endl;
                   //system("pause");
                    break;
                }
                if(t[i].str[j]=='0')
                {
                    if(p->left!=NULL)
                        p=p->left;
                    else
                    {
                        //cout<<'n';
                        p->left=new node;
                        p=p->left;
                        p->left=p->right=NULL;
                    }
                   // cout<<'0';
                    count++;
                }
                else if(t[i].str[j]=='1')
                {
                     if(p->right!=NULL)
                        p=p->right;
                    else
                    {
                        //cout<<'y';
                        p->right= new node;
                        p=p->right;
                        p->right=p->left=NULL;
                    }
                    //cout<<'1';
                    count++;
                }
            }
        }
    }
    treewalk(cc,root);
}
void treewalk(string cc,node *root)
{
    int i;
    node *p;
    p=root;
    for(i=0;cc[i]!='\0';i++)
    {
        if(cc[i]=='0')
        {
            p=p->left;
            if(p->left==NULL&&p->right==NULL)
            {
                //cout<<'-';
                //fout<<p->asc;
                cout<<p->asc;
                p=root;
                continue;
            }
            //cout<<'n';
        }
        else if(cc[i]=='1')
        {
            p=p->right;
            if(p->left==NULL&&p->right==NULL)
            {
                //cout<<'*';
                //fout<<p->asc;
                cout<<p->asc;
                p=root;
                continue;
            }
            //cout<<'y';
        }
            //p=root;
    }
}

