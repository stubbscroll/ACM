#include <stdio.h>
#include <string.h>

char str[][16]={"Spock","scissors","paper","rock","lizard"};

int tall(char *s) {
	if(!strcmp(s,"Spock")) return 0;
	if(!strcmp(s,"scissors")) return 1;
	if(!strcmp(s,"paper")) return 2;
	if(!strcmp(s,"rock")) return 3;
	if(!strcmp(s,"lizard")) return 4;
	printf("ERROR");
	return -1;
}

int beat[5][5];

void setbeat(char *s,char *t) {
	beat[tall(s)][tall(t)]=1;
}

int main() {
	int i,j,cases,last=-1,a;
	char s[128];
	for(i=0;i<5;i++) for(j=0;j<5;j++) beat[i][j]=0;
	setbeat("scissors","paper");
	setbeat("paper","rock");
	setbeat("rock","lizard");
	setbeat("lizard","Spock");
	setbeat("Spock","scissors");
	setbeat("scissors","lizard");
	setbeat("lizard","paper");
	setbeat("paper","Spock");
	setbeat("Spock","rock");
	setbeat("rock","scissors");
	
	scanf("%d",&cases);
	while(cases--) {
		scanf("%s",s);
		a=tall(s);
		for(i=0;i<5;i++) if(beat[i][a] && i!=last) {
			last=i;
			break;
		}
		printf("%s\n",str[last]);
	}
	return 0;
}
