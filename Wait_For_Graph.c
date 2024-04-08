#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isDeadlock = false;
int noOfProcesses;

void findDeadlock(int wfg[][noOfProcesses], int *vis, int node, int n)
{
	if(vis[node] == 1)
	{
		isDeadlock = true;
		return;
	}
	vis[node] = 1;
	for(int i = 0;i < n;i++)
	{
		if(wfg[node][i] == 1)
		{
			findDeadlock(wfg, vis, i, n);
		}
	}
	vis[node] = 0;
	return;
}


int main()
{
	int noOfResources;
	printf("\nEnter the number of Processes: ");
	scanf("%d", &noOfProcesses);
	printf("\nEnter the number of Resources: ");
	scanf("%d", &noOfResources);
	int processes[noOfProcesses][noOfResources];
	int resources[noOfResources][noOfProcesses];
	for(int i = 0;i < noOfProcesses;i++)
	{
		for(int j = 0;j < noOfResources;j++)
		{
			processes[i][j] = 0;
		}
	}
	for(int i = 0;i < noOfResources;i++)
	{
		for(int j = 0;j < noOfProcesses;j++)
		{
			resources[i][j] = 0;
		}
	}
	for(int i = 0;i < noOfProcesses;i++)
	{
		printf("\nProcess %d waiting for\n", i+1);
		for(int j = 0;j < noOfResources;j++)
		{
			int temp;
			scanf("%d", &temp);
			if(temp == -1)
				break;
			processes[i][temp-1] = 1;
		}
	}
	for(int i = 0;i < noOfResources;i++)
	{
		printf("\nResource %d allocated for\n", i+1);
		for(int j = 0;j < noOfProcesses;j++)
		{
			int temp;
			scanf("%d", &temp);
			if(temp == -1)
				break;
			resources[i][temp-1] = 1;
		}
	}
	for(int i = 0;i < noOfProcesses;i++)
	{
		for(int j = 0;j < noOfResources;j++)
		{
			printf("%d ",processes[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	for(int i = 0;i < noOfResources;i++)
	{
		for(int j = 0;j < noOfProcesses;j++)
		{
			printf("%d ",resources[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	int waitForGraph[][4] = {{0,1,0,0},{0,0,1,0},{0,0,0,1},{1,0,0,0}};
	/*int waitForGraph[noOfProcesses][noOfProcesses];
	for(int i = 0;i < noOfProcesses;i++)
	{
		for(int j = 0;j < noOfProcesses;j++)
		{
			waitForGraph[i][j] = 0;
		}
	}
	for(int i = 0;i < noOfProcesses;i++)
	{
		for(int j = 0;j < noOfResources;j++)
		{	
			if(processes[i][j] == 1)
			{
				for(int k = 0;k < noOfProcesses;k++)
				{
					if(resources[j][k] == 1)
					{
						waitForGraph[i][k] = 1;
					}
				}
			}
		}
	}
	for(int i = 0;i < noOfProcesses;i++)
	{
		for(int j = 0;j < noOfProcesses;j++)
		{
			printf("%d ",waitForGraph[i][j]);
		}
		printf("\n");
	}*/
	int visited[] = {0,0,0,0};
	findDeadlock(waitForGraph, visited, 0, noOfProcesses);
	for(int i = 0;i < noOfProcesses;i++)
	{
		visited[i] = 1;
		for(int j = 0;j < noOfProcesses;j++)
		{	
			if(processes[i][j] == 1 && visited[j] == 1)
			{
				isDeadlock = true;
				break;
			}
		}
		if(isDeadlock)
			break;
	}
	if(isDeadlock)
		printf("\n\nThere is a deadlock!!!");
	else
		printf("\n\nThere is no deadlock!!!");
	return 0;
}
