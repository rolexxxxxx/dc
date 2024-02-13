#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

struct sockaddr_in abc,sender,tosend;
int cordinator,max,mynode;
int soc;
struct msg_node{
	
	char msg[100];
	int node_no;
};


void *meelc(){
char elect_inti[100]="elect_inti";
char me_elected[100]="me_elected";
struct msg_node *tem = malloc(sizeof(struct msg_node));
	socklen_t len = sizeof(sender);
printf("calling me elc \n");
		tem->node_no = mynode;
	strcpy(tem->msg,me_elected);
	
		for(int i=0+1;i<=max;i++){
		tosend.sin_port = htons(i+4500);
		sendto(soc,tem,sizeof(struct msg_node),0,(struct sockaddr *)&tosend,len);
	}
}


void *fun(){
	//printf("sdcv");

	struct msg_node *tem = malloc(sizeof(struct msg_node));
	socklen_t len = sizeof(sender);

	char elect_inti[100]="elect_inti";
	char me_elected[100]="me_elected";
	int inpt;
	while(1){
		printf("enter 1 to check cordinator: ");
		scanf("%d",&inpt);
		if(inpt==1){
			tosend.sin_port = htons(cordinator+4500);
			strcpy(tem->msg,"alive");
			tem->node_no=mynode;
			sendto(soc,tem,sizeof(struct msg_node),0,(struct sockaddr *)&tosend,len);
			recvfrom(soc,tem,sizeof(struct msg_node),0,(struct sockaddr *)&sender,&len);
	
	sleep(8);
	if(strcmp(tem->msg,"salive")!=0){
	printf("\ndead cordinator\n");
	tem->node_no = mynode;
	strcpy(tem->msg,elect_inti);
	
	for(int i=mynode+1;i<=max;i++){
		tosend.sin_port = htons(i+4500);
		sendto(soc,tem,sizeof(struct msg_node),0,(struct sockaddr *)&tosend,len);
	}
	
	
	sleep(8);
	if(strcmp(tem->msg,"OK")!=0){
	
		tem->node_no = mynode;
	strcpy(tem->msg,me_elected);
	cordinator = mynode;
		for(int i=0+1;i<=max;i++){
		tosend.sin_port = htons(i +4500);
		sendto(soc,tem,sizeof(struct msg_node),0,(struct sockaddr *)&tosend,len);
	}
	}
	

}
			
		}
	}
 free(tem);
}


int main(int argc, char *argv[]){

struct timeval timeout;
pthread_t thread1,t2=0;
 cordinator = atoi(argv[2]);
 max = cordinator;
 mynode=atoi(argv[1]);

 soc=socket(AF_INET,SOCK_DGRAM,0);


 timeout.tv_sec = 5;
 timeout.tv_usec = 0;

abc.sin_addr.s_addr = INADDR_ANY;
abc.sin_family = AF_INET;
abc.sin_port = htons(atoi(argv[1])+4500);
bind(soc,(struct sockaddr *)&abc,sizeof(abc));

setsockopt(soc, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));

tosend.sin_addr.s_addr = INADDR_ANY;
tosend.sin_family = AF_INET;
tosend.sin_port = htons(cordinator+4500);

struct msg_node *tem = malloc(sizeof(struct msg_node));

char elect_inti[100]="elect_inti";
char me_elected[100]="me_elected";
socklen_t len =sizeof(sender);

pthread_create( &thread1, NULL, fun, NULL);

while(1){
ssize_t bytesRead = recvfrom(soc,tem,sizeof(struct msg_node),0,(struct sockaddr *)&sender,&len);

if (bytesRead == -1) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                // Handle timeout (no data received within the specified time)
                printf("\nTimeout: No data received within the specified time. cord = %d\n",cordinator);
            } continue;
            }
printf("%s",tem->msg);

if(strcmp(elect_inti,tem->msg)==0){
	strcpy(tem->msg,"OK");
	tosend.sin_port = htons(tem->node_no+4500);
	sendto(soc,tem,sizeof(struct msg_node),0,(struct sockaddr *)&tosend,len);
	sleep(2);
	tem->node_no = mynode;
	strcpy(tem->msg,elect_inti);
	
	for(int i=mynode+1;i<=max;i++){
		tosend.sin_port = htons(i+4500);
		sendto(soc,tem,sizeof(struct msg_node),0,(struct sockaddr *)&tosend,len);
	}

	pthread_create( &t2, NULL, meelc, NULL);

	
	
	

}
if(strcmp(me_elected,tem->msg)==0){

	cordinator = tem->node_no ;

}

if(strcmp("alive",tem->msg)==0){
	printf("killing\n");
	tosend.sin_port = htons(tem->node_no +4500);
	strcpy(tem->msg,"salive");
	tem->node_no = mynode;
	sendto(soc,tem,sizeof(struct msg_node),0,(struct sockaddr *)&tosend,len);
	pthread_cancel( thread1);
	
pthread_create( &thread1, NULL, fun, NULL);
}
if(strcmp("salive",tem->msg)==0){
	printf("killing as alive \n");
	
	pthread_cancel( thread1);
	
pthread_create( &thread1, NULL, fun, NULL);
}

if(strcmp(tem->msg,"OK")==0){
	printf("killing as ok recieved \n");pthread_cancel( thread1);
	
pthread_create( &thread1, NULL, fun, NULL);
if(t2!=0){
pthread_cancel( t2);
t2=0;
}
}
}
//strcpy(msg,"abcd");
//sendto(soc,tem,sizeof(struct msg_node),0,(struct sockaddr *)&sender,len);

}
