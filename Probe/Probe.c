#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>  

int wfg[5][5] = {{0, 0, 1, 0, 0}, {1, 0, 0, 1, 0}, {0, 1, 0, 0, 1}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
int probe(int start,int sender,int receiver)
{
	//printf("%d %d %d \n",start,sender,receiver);
	if(start==receiver)
	{
		return 1;
	}
	int dead=0;
	for(int i=0;i<5;i++)
	{
		if(wfg[receiver][i]==1)
		{
			dead |= probe(start,receiver,i);
		}
	}
	return dead;
}
int main()
{
	int sender,receiver,start;
	
	printf("Enter Start:");
	scanf("%d",&start);
	
	int dead=0;
	
	for(int i=0;i<5;i++)
	{
		if(wfg[start][i]==1)
		{
			dead |= probe(start,start,i);
		}
	}
	
	if(dead==1)
	{
		printf("Deadlock Detected!");
	}
	else{
		printf("There is no deadlock");
	}
	
}


