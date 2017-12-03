#include<cstdlib>
#include<iostream>
#include<fstream>
#include<cstring>
#include<time.h>
using namespace std;
typedef struct data
{
    int count;
    char asc;
    bool flag;
    data *left;
    data *right;
}data;
typedef struct code
{
    char asc;
    string c;
}code;
int cmp( const void *a ,const void *b)
{
    return ((data *)a)->count > ((data *)b)->count ? 1 : -1;
}
void traverse(data node, char c, char code[]);
char table[128][100];
void print(ofstream& fout);
void printcode(char a[],char t[128][100],ofstream& fout);
int main(int argc,char* argv[])
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    clock_t start_time, end_time, time1,time2;
    float total_time = 0;
    start_time = clock();

    if(!fin)
    {
        cout<<"¥¢±Ñ"<<endl;
        return 1;
    }
    //else if(fin.is_open())cout<<"open"<<endl;
    if(!fout)
    {
        cout<<"¼gÀÉ¥¢±Ñ"<<endl;
        fin.close();
        return 1;
    }


    data list[128];
    char temp,artical[9999];
    int i,now=0;
    for(i=0;i<128;i++)
    {
        list[i].asc=i;
        list[i].count=0;
        list[i].flag=false;
    }
    fin.get(temp);
    while(!fin.eof())
    {
        artical[now]=temp;
        now++;
        for(i=0;i<128;i++)
            if(i==temp)
            {
                list[i].count++;
                break;
            }
            fin.get(temp);
    }
    for(i=0;i<128;i++)
        if(list[i].count!=0)
        {
            list[i].flag=true;
            list[i].right=NULL;
            list[i].left=NULL;
        }
    qsort(list,128,sizeof(data),cmp);
    /*for(i=0;i<128;i++)
        if(list[i].flag==true)
            cout<<list[i].asc<<"   "<<list[i].count<<endl;
    */data node[9999];
    i=0;
    while(i!=9999)
    {
        node[i].flag=true;
        i++;
    }
    int k=0,i1;
    while(1)
    {
         for(i=0;i<128;i++)
        {
            if(list[i].flag==true)
            {
                node[k].asc=list[i].asc;
                node[k].right=list[i].right;
                node[k].left=list[i].left;
                node[k].count=list[i].count;
                list[i].flag=node[k].flag=false;

                k++;
                i1=1;
                while(1)
                {
                    if(list[i+i1].flag==true)
                    {
                        node[k].asc=list[i+i1].asc;
                        node[k].right=list[i+i1].right;
                        node[k].left=list[i+i1].left;
                        node[k].count=list[i+i1].count;//cout<<node[k].count<<endl;
                        node[k].flag=false;
                        k++;
                        break;
                    }
                    else i1++;
                }
                list[i+i1].asc='A';
                list[i+i1].left=&node[k-2];
                list[i+i1].right=&node[k-1];
                list[i+i1].count= node[k-2].count+ node[k-1].count;//cout<<node[k-2].count<<endl;
                qsort(list,128,sizeof(data),cmp);
                  break;
            }
        }
        if(i==126)
        {
			node[k].asc= list[i+1].asc;
            node[k].right=list[i+1].right;
            node[k].left=list[i+1].left;
            node[k].count=list[i+1].count;
            list[i+1].flag=node[k].flag=false;
            break;
        }
        else if(i==127)
        {
			node[k].asc= list[i].asc;
            node[k].right=list[i].right;
            node[k].left=list[i].left;
            node[k].count=list[i].count;
            list[i+1].flag=node[k].flag=false;
            break;
        }
    }
    char code[100] ="";
    traverse(node[k],' ', code);
    printcode(artical,table,fout);

    end_time=clock();
    total_time = (float)(end_time- start_time)/CLOCKS_PER_SEC;
    cout<<endl;
    printf("Time : %f sec \n", total_time);

    fin.close();
    return 0;
}
int j=-1;
int count=0;
void traverse(data node, char c, char code[])
{
	code[j] = c;
	/*cout << node.count << "[" << node.asc << "]" << endl;*/
	if(node.left==NULL || node.right==NULL)
	{
		code[j+1]='\0';
		//cout << code << endl;
		strcpy(table[node.asc], code);
		//count+=node.count*j;
		code[j] =' ';
		return;
	}
	else
	{
        j++;
		traverse(*node.left, '0', code);
		traverse(*node.right, '1', code);
		j--;
		code[j]=' ';
	}
}
void print(ofstream& fout)
{
	//fout<<count<<endl;
	fout<<"###"<<endl;
	cout<<"###"<<endl;
	for(int i=0; i<=127; i++)
	{
		char c = i;
		if(table[i][0]!='\0')
		{
            fout << c << ":" << table[i] << endl;
            cout << c << ":" << table[i] << endl;
		}
	}
}
void printcode(char a[],char t[128][100],ofstream& fout)
{
    int i,j,k;
    string temp;
    char c=0;
    for(i=0;a[i]!='\0';i++)
    {
        for(k=0;k<128;k++)
        {
            if(a[i]==k)
            {
                temp+=t[k];
               // cout<<t[k]<<endl;
            }
        }
    }
    //cout<<temp<<endl;
    fout<<temp.size()<<endl;
    cout<<temp.size()<<endl;
    print(fout);
    i=0;
     fout<<"############"<<endl;
     cout<<"###"<<endl;
    while(i<temp.size())
    {
        if(temp[i]=='0')
        {
            c=c<<1;
            //c=c&0;
        }
        else if(temp[i]=='1')
        {
            c=c<<1;
            c=c | 1;
        }
        if((i+1)%8==0)
        {
            fout<<c;
           cout<<c;
            //c=0;
            //system("pause");
            //c=0;
        }
        i++;
    }
    if(i%8!=0)
    {
        c=c<<(8-i);
        fout<<c;

        cout<<c;
        //system("pause");
    }
}
