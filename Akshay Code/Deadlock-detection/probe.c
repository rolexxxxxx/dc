#include <stdio.h>
#include <stdlib.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>

struct node{
	int b;
	int s;
	int r;

};
int waiting;
int waitnum;
int *waitp;
int mynode;
int soc ;

void* fun(){
	struct node *tem = (struct node *)malloc(sizeof(struct node ));
	int mlen = sizeof(struct node );
	int alen = sizeof(struct sockaddr_in);
	struct sockaddr_in abc;
	abc.sin_addr.s_addr = INADDR_ANY;
	abc.sin_family = AF_INET;
	
	
	while(1){
	
	int res=recvfrom(soc,tem,mlen,0,(struct sockaddr*)&abc,&alen);
	if(res==-1){
	continue;
	}
	
	printf("recieved from b = %d s = %d r = %d \n", tem->b,tem->s,tem->r);
	
	if(tem->b == mynode){
	
	printf("deadlock detected \n");
	continue;
	}
	
	for(int i=0;i<waitnum;i++){
	abc.sin_port = htons(4500+waitp[i]);
	tem->s = mynode;
	tem->r = waitp[i];
	sendto(soc,tem,mlen,0,(struct sockaddr*)&abc,alen);
	}
	
	}
	

}


int main(int num,char * argv[]){

	int t;
	waiting=0;
	waitnum = 0;
	if(num>2){
	waiting =1;
	waitnum = num-2;
	waitp = (int*)malloc(sizeof(int)*waitnum);
	for(int i=0;i<waitnum;i++){
	waitp[i] = atoi(argv[i+2]);
	}
	}
	
	//mynode = 0;
	mynode = atoi(argv[1]);
	 soc = socket(AF_INET,SOCK_DGRAM,0);
	
	struct sockaddr_in a;
	a.sin_family = AF_INET;
	a.sin_addr.s_addr = INADDR_ANY;
	a.sin_port = htons(4500+mynode);
	
	bind(soc,(struct sockaddr*)&a,sizeof(struct sockaddr));
	pthread_t t1;
	pthread_create(&t1,NULL,fun,NULL);
	struct node *tem = (struct node *)malloc(sizeof(struct node ));
	int mlen = sizeof(struct node );
	int alen = sizeof(struct sockaddr_in);
	struct sockaddr_in abc;
	abc.sin_addr.s_addr = INADDR_ANY;
	abc.sin_family = AF_INET;
	
	
	
	while(1){
	printf("Enter process to send probe to ");
	scanf("%d",&t);
	abc.sin_port = htons(4500+t);
	tem->b= mynode;
	tem->s = mynode;
	tem->r = t;
	sendto(soc,tem,mlen,0,(struct sockaddr*)&abc,alen);
	}
	
	return 1;
}
