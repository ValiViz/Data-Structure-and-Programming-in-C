#include<stdio.h>

struct inf
{
	char c;
	
	int line;
};

int main()
{
	FILE* fp;
	
	struct inf s[205],str[205];
	
	char c;
	
	int tem=0,num=0,line=1,point=-1,read=0;
	
	fp=fopen("example.c","r");
	
	while ((c = fgetc(fp)) != EOF)
	{

		if (tem == 0 && c == '/')
		{
			char d = fgetc(fp);

			if (d == '/')
			{
				while (fgetc(fp) != '\n')
				{
					tem = 1;
				}
				
				line++;

				tem = 0;
			}
			
			else if(d == '*')
			{
				tem = 1;
			}
			
			else
			c=d;
		}
		
		if(tem == 1 && c == '*')
		{
			char e=fgetc(fp);
			
			if(e=='/')
			{
				tem=0;
			}
			
			else
			c=e;
		}

		if (tem == 0 && c == '\'' )
		{
			while (fgetc(fp) != '\'')
			{
				tem = 1;
			}
			
			tem=0;
		}
		
		if (tem == 0 && c == '\"' )
		{
			while (fgetc(fp) != '\"')
			{
				tem = 1;
			}
			
			tem=0;
		}

		if (tem == 0 && (c == '{' || c == '}' || c == '(' || c == ')'))
		{
			s[num].c = c;

			s[num].line = line;

			num++;
		}

		if (c == '\n')
		{
			line++;
		}
	}
	
	while(read<num)
	{
		if(s[read].c=='}')
		{
			if(point==-1||str[point].c!='{')
			{
				printf("without maching '}' at line %d",s[read].line);
				
				return 0;
			}
			
			else
			{
				point--;
			}
		}
		
		else if(s[read].c==')')
		{
			if(point==-1||str[point].c!='(')
			{
				printf("without maching ')' at line %d",s[read].line);
				
				return 0;
			}
			
			else
			{
				point--;
			}
		}
		
		else if(s[read].c=='(')
		{
			point++;
			
			str[point].c=s[read].c;
			
			str[point].line=s[read].line;
		}
		
		else if(s[read].c=='{')
		{
			if(point==-1||str[point].c!='(')
			{
				point++;
				
				str[point].c=s[read].c;
			
				str[point].line=s[read].line;
			}
			
			else if(str[point].c=='(')
			{
				printf("without maching '(' at line %d",str[point].line);
				
				return 0;
			}
		}
		
		read++;
		
		if(read==num&&point!=-1)
		{
			printf("without maching '%c' at line %d",str[point].c,str[point].line);
			
			return 0;
		}
	}
	
	while(point<num-1)
	{
		point++;
		
		printf("%c",s[point].c);
	}
	
	return 0;
}
