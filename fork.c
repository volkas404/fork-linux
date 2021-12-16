#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc , char* argv[]){
	int chan;
	int chansong[2];
	char chanyeu[100];
	pipe(chansong);
	chan=fork();
	if(chan>0){
		for(int i=1;i<argc;i++) write(chansong[1],argv[i],strlen(argv[i]));
		wait(NULL);
		read(chansong[0],chanyeu,100);
		printf("max = %s\n",chanyeu);
	}
	if(chan==0){
		char chandoi[1000];
		char *ghetyeu;
		int max=0;
		for(int i=1;i<argc;i++){
			read(chansong[0],chandoi,strlen(argv[i]));
			if(atoi(chandoi)>max) max=atoi(chandoi);
		}
		sprintf(ghetyeu,"%d",max);
		write(chansong[1],ghetyeu,100);
	}
}