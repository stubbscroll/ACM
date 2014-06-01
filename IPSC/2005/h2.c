/* solution for hidden messages, hard input
   algorithm is heavily editorial-assisted. the substitution cipher solver
   requires the file english-small.txt.
   part C solved manually on cut-out paper */

/* hints:
   HARD-A1 Count everything. Similar counts are (usually :) not just a
           coincidence.
   HARD-A2 The solution has to contain some letters. Where do they come from?
   HARD-A3 Not only the column is important.
   HARD-B1 Check letter frequencies.
   HARD-B2 If you are not fluent in English, maybe downloading some wordlist
           can help.
   HARD-B3 Not that many pairs of words match "dbfigepjb" and "gepjbhehp".
   HARD-C1 Use scissors.
   HARD-C2 Ever heard about the Phantom of the Opera? Does Pride and Prejudice
           ring a bell?
   HARD-C3 Think 3D, but solve in 2D.
*/

/* words received from parts A and B:

apple ball card five kitty letter line pizza scissors stamp

shadow starlight tiger total towel vienna wave world pinky sea
kiribati ketchup fifteen gutenberg sound werewolf divide book desert virgin
lightning bishop needle recall phantom shell test silver ender empress
sun bunny worm postcard brain page
*/

/* see h2.png for my solved (but slightly editorial-assisted) puzzle
   the solution is:
   fried cheese is a good dinner */

#include <stdio.h>
#include <string.h>

/* part A */

char sa[27][70]={
"#############################_###############################",
"#_##_#################################################_######",
"######################################_######################",
"#####################_######################################_",
"#####################_######_################################",
"####################################################_########",
"########_############_########_########################_#####",
"#####################__#####################################_",
"#############################_###############################",
"##########_################################################_#",
"#########################################################_###",
"##_#####################_##################_###_#############",
"##########_##############_#_#####_###########################",
"####################################################_########",
"##############################################_#_############",
"######################################_################_#####",
"###########################################################_#",
"#######_#############_#################_#############_######_",
"################################################_############",
"####################################################_########",
"##############################################_##############",
"####################################################_########",
"####################__######_################################",
"##########_################################################_#",
"##############################_#################_############",
"#####_##__################_###_#######__########_############",
"#############################_###############################"};

char ta[70]=
"do not submit this text you have to decode it first gjklpqrwz";

char ua[30][30];

char conv(char c,int add) {
	int a;
	if(c==' ') a=0;
	else a=c-'a'+1;
	a=(a+add)%27;
	if(a==0) return ' ';
	return a+'a'-1;
}

void solvea() {
	int i,j;
	for(i=0;i<27;i++) {
		for(j=0;ta[j];j++) if(sa[i][j]=='_') sa[i][j]=conv(ta[j],i);
	}
	for(i=0;i<27;i++) for(j=0;ta[j];j++) if(sa[i][j]!='#') putchar(sa[i][j]);
	puts("\n");
}

/* part B */

char sb[10][80]={
"jaggc fd qck rfh daa bjed ed wkdb f lgfeh dkodbebkbech reljai",
"na dkia mc jcla bjfb fgg ct qck rfh afdegq dcgsa bjed lfib ct bja licogau",
"okb ucia dbald fnfeb qck",
"bc dcgsa bja gfdb cha qck negg haam f dab ct ncimd",
"jaia bjaq rcua",
"",
"djfmcn dbfigepjb bepai bcbfg bcnag seahhf nfsa ncigm lehvq daf veieofbe",
"vabrjkl tetbaah pkbahoaip dckhm naiancgt mesema occv madaib seipeh",
"gepjbhehp oedjcl haamga iarfgg ljfhbcu djagg badb degsai ahmai axliadd",
"dkh okhhq nciu lcdbrfim oifeh lfpa"};

#define MAXW 400000
#define MAXS 40
char w[MAXW][MAXS];
char canon[MAXW][MAXS];
int nw;

void canonize(char *s,char *t) {
	char taken[26];
	int i,j,ix=1,c;
	memset(taken,-1,26);
	for(i=j=0;s[i];i++) {
		c=-1;
		if(s[i]>='A' && s[i]<='Z') c=s[i]-'A';
		if(s[i]>='a' && s[i]<='z') c=s[i]-'a';
		if(c>-1) {
			if(taken[c]==-1) taken[c]=ix++;
			t[j++]=taken[c];
		}
	}
	t[j]=0;
}

/* read wordlist from file and generate canonical representation */
void gencanon(char *filename) {
	FILE *f=fopen(filename,"r");
	char s[1000];
	if(!f) { puts("error"); return; }
	nw=0;
	while(fscanf(f,"%999s",s)==1) {
		if(nw>=MAXW) { puts("too many words"); return; }
		if(strlen(s)>MAXS-1) { puts("word too long"); return; }
		strcpy(w[nw],s);
		canonize(w[nw],canon[nw]);
		nw++;
	}
	fclose(f);
}

char tb[100][100];
int tn;
char ub[100][100];
char map[128];
char takento[26];

void replace() {
	int i,j;
	for(i=0;i<tn;i++) {
		for(j=0;j<tb[i][j];j++) if(map[(int)tb[i][j]]) ub[i][j]=map[(int)tb[i][j]];
		else ub[i][j]=' ';
		ub[i][j]=0;
	}
}

#define WRONG 5

int wrongwords() {
	int wrong=0,i,j,k,l;
	for(i=0;i<tn;i++) {
		l=strlen(ub[i]);
		for(k=0;k<nw;k++) if(l==strlen(w[k])) {
			/* abort at first match */
			for(j=0;w[k][j];j++) if(ub[i][j]!=' ' && ub[i][j]!=w[k][j]) goto next;
			goto ok;
		next:;
		}
		wrong++;
		if(wrong==WRONG) return 1;
	ok:;
	}
	return 0;
}

int btr(int at) {
	int i;
	while(map[at]) at++;
	if(at=='z'+1) return 1;
	for(i='a';i<='z';i++) if(!takento[i-'a']) {
		map[at]=i;
		replace(at);
		if(!wrongwords() && btr(at+1)) return 1;
		map[at]=0;
		replace(at);
	}
	return 0;
}

/* solve substitution cipher:
   check for unique word substitutions, and start from there. then,
   backtracking and prune on too many non-dictionary words */
void solveb() {
	int i,j,p,q,un;
	char z[100];
	memset(map,0,sizeof(map));
	memset(takento,0,sizeof(takento));
	map[' ']=' ';
	gencanon("english-small.txt");
	for(tn=i=0;i<10;i++) {
		for(p=0;sscanf(sb[i]+p,"%s%n",tb[tn],&q)==1;p+=q) {
			un=0;
			canonize(tb[tn],z);
			for(j=0;j<nw;j++) if(!strcmp(z,canon[j])) {
				if(un==1) {
					un=0;
					goto fail;
				}
				strcpy(ub[tn],w[j]);
				un++;
			}
			for(j=0;j<ub[tn][j];j++) map[(int)tb[tn][j]]=ub[tn][j],takento[(int)ub[tn][j]]=1;
		fail:
			tn++;
		}
	}
	for(i='a';i<='z';i++) if(map[i]) replace(i,map[i]);
	if(btr('a')) {
		for(i=0;i<10;i++) {
			for(j=0;sb[i][j];j++) putchar(map[(int)sb[i][j]]);
			putchar('\n');
		}
	} else puts("increase WRONG");
}

int main() {
	solvea();
	solveb();
	return 0;
}
