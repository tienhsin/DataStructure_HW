#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <iomanip>
#include <time.h>
#include <string>
typedef int (*compfn)(const void*, const void*);


using namespace std;

struct WordInfo
{
   char word[20];
   int count;
};

int alg(char[],char[]);
int compare (struct WordInfo * a, struct WordInfo * b)
{
	if ( a->count > b->count)
		return -1;
	else if (a->count < b->count)
		return 1;
	else
		return 0;
 }

int main(int argc, char *argv[])
{
	 while(1)
{	 
	 // ���o����e�ɶ�
    clock_t start_time, end_time, time1,time2;
  	float total_time = 0;
  	start_time = clock(); /* mircosecond */

    WordInfo list[1000];
	char temp[20] ="";
    
    // initialization
    for(int i=0;i<1000;i++)
    {
        strcpy(list[i].word, temp);
        list[i].count = 0;
    }  
    
    ifstream inStream("test1_hw1_new-ANSI.txt");
    int c;
	bool flag = false;
    if(inStream.is_open())
    {
         while(!inStream.eof())
         {
            inStream >> temp;
            		
			char * pch;
			pch = strtok(temp,",.'\"!-;()");
		    
			while (pch != NULL)
			{
				strcpy(temp, pch);				
				pch = strtok (NULL, " ,.'\"!-;()");
			}    	
            
			c=temp[0];
            temp[0] = tolower(c); 
             
            int i;
			for(i=0; i<2000; i++)//�p�Glist�̭��w�g�����ӳ�r �����Ncount+1 ; �S�����ܴN���r�ƻs��list���U�Ӧ�m �ñNcount+1 
            {                                   
                if(alg(list[i].word, temp)==0)//algorithm �ۦP�^��1 ���P�^��0 
                {
                    if(list[i].word[0]=='\0')
					{
						strcpy(list[i].word, temp);
                        list[i].count++; 
                        break;
					}
					else
					{
						continue;
					}
                } 
                                               
                if(alg(list[i].word, temp)==1)
                {
                    list[i].count++;                     
                    break;
                }               
             }
			 
         } 
         
         inStream.close(); 
		
    } 
    else
    {
        cout << "The file does not exist." << endl;
        system("pause");
        exit(1); 
    }
  
	qsort ((void*)list, 1000, sizeof(struct WordInfo), (compfn)(compare));
	
	time1=clock();
     
	int k;
	cin>>k;

	time2=clock();
	for(int i=0;i<k;i++)
    {
		cout<<list[i].word<<"  "<<list[i].count<<endl;
		if(i==k-1&&list[i].count==list[i+1].count)
			k++;
	}
    
	end_time=clock();
	total_time = (float)(end_time-time2+time1 - start_time)/CLOCKS_PER_SEC;
    printf("Time : %f sec \n", total_time);

    char filename[20];             //�g��
    strcpy(filename, "result.txt");
    ofstream outStream(filename, ios::app);

    
    int index = 0;          
    if(outStream.is_open())
    {
        outStream << "Word statistic of the composition '" << "test1_hw1_new.txt" << "':" << endl << endl;
        for(index=0; strcmp(list[index].word, "")!=0; index++)
            outStream << list[index].word << " " << setw(20-strlen(list[index].word)) << list[index].count << endl; 
        
        outStream << endl << "Total: " << index << " words." << endl;
        outStream << "------------------------------" << endl << endl << endl;

        outStream.close();
    }    
    
    cout << "The word-statistic result is written to file '" << filename << "'." << endl << endl;
	
    system("pause");
    return EXIT_SUCCESS;
}
}

int alg(char a[], char b[])
{
	int i;
	for(i=0;i<20;i++)
	{	
		if(a[i]!=b[i])
		{
			return 0;
			break;
		}
		else if(a[i]==b[i]&&a[i]=='\0')
		{
			return 1;
		}
		else
		{
			continue;
		}
	}
}
		
