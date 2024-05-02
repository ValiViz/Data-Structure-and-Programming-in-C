#include<stdio.h>
#include<string.h>

typedef struct{
	char name[25];
	char number[12];
	int time;
}Person;

void SortbyName (Person book[], int );

int main()
{
	int n;
	int flag=0, count=0;
	Person Phonebook[105] = {0}, PrePhonebook = {0};
	scanf("%d", &n);
	getchar();
	for(int i=0; i<n; i++)
	{
		flag=0;
		scanf("%s %s ", PrePhonebook.name, PrePhonebook.number);
		for(int j = 0; (!flag) && j < count; j++)
		{
			
			if(strcmp(PrePhonebook.number, Phonebook[j].number)==0)
			{
				flag=1;
				break;
			}
			if(strcmp(PrePhonebook.name, Phonebook[j].name)==0)
			{
			   
				Phonebook[j].time++;
				sprintf(PrePhonebook.name , "%s_%d", Phonebook[j].name, Phonebook[j].time );
				Phonebook[count] = PrePhonebook;
				 count++;
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
		
		    Phonebook[count] = PrePhonebook;
		    count++;
		} 
    }

    SortbyName (Phonebook, count);
    for(int i=0; i<count; i++)
    {
    	printf("%s %s\n", Phonebook[i].name, Phonebook[i].number);
	}
	return 0;
 } 
 
 void SortbyName (Person book[], int n)
 {
 	int i,j;
 	Person tem;
 	for(i=0; i<n; i++)
 	    for(j=0; j<n; j++)
 	    {
 	    	if(strcmp(book[j].name, book[j+1].name)>0)
 	    	{
 	    		tem=book[j];
 	    		book[j]=book[j+1];
 	    		book[j+1]=tem;
			 }
	   }
 }
