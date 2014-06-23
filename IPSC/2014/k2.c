/* solution for knowledge test, hard input
   algorithm: hardcode most of the knowledge, then look up */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char g[133][133];
int r,c;

int cluer[2][666];
int cluec[2][666];
char clue[2][666][300];
char answer[2][666][300];
int n[2];

int hexdigit(char c) {
	if(c>='A') return c-'A'+10;
	if(c>='a') return c-'a'+10;
	return c-'0';
}

int hex(char *s) {
	return hexdigit(s[0])*16+hexdigit(s[1]);
}

/* find length of answer of clue i,j */
int getlen(int i,int j) {
	int l=0,x=cluer[i][j],y=cluec[i][j];
	while(x<r && y<c && g[x][y]!='.') {
		l++;
		if(i==0) y++;
		else x++;
	}
	return l;
}

/* given word s, check if it is consistent with partially filled word at i,j */
int wordcanfit(int i,int j,char *s) {
	int l=getlen(i,j),x=cluer[i][j],y=cluec[i][j];
	if(l!=strlen(s)) return 0;
	l=0;
	while(x<r && y<c && g[x][y]!='.') {
		if(g[x][y]!='#' && s[l]!=g[x][y]) return 0;
		l++;
		if(i==0) y++;
		else x++;
	}
	return 1;
}

void applyword(int i,int j,char *s) {
	int x=cluer[i][j],y=cluec[i][j],l=0;
	while(x<r && y<c && g[x][y]!='.') {
		g[x][y]=s[l++];
		if(i==0) y++;
		else x++;
	}
}

char *findright(char *p,char *q) {
	int lv=1;
	char *z=p+1;
	while(lv) {
		if(*z=='(') lv++;
		else if(*z==')') lv--;
		z++;
		if(z>q) puts("parse error, wrong parenthesis");
	}
	return z;
}

int parse(char *p,char *q) {
	int num=0,prev=0;
	char *z,op=0;
	while(1) {
		if(isdigit(*p)) {
			num=0;
			while(isdigit(*p)) num=num*10+*(p++)-'0';
		} else if(*p=='(') {
			z=findright(p,q);
			num=parse(p+1,z-1);
			p=z;
		} else puts("parse error, expected ( or digit");
		if(op=='+') num+=prev;
		else if(op=='-') num=prev-num;
		else if(op=='*') num*=prev;
		else if(op=='/') num=prev/num;
		if(p==q) return num;
		prev=num;
		op=*(p++);
		if(op!='+' && op!='-' && op!='/' && op!='*') puts("parse error, expected operator");
	}
}

/* chemical elements */
/* list from http://en.wikipedia.org/wiki/Periodic_table */

#define CHEM 119

char chem[CHEM][2][30]={
	{"",""},          /* name, symbol */
	{"hydrogen","H"}, /* 1 */
	{"helium","He"},
	{"lithium","Li"},
	{"beryllium","Be"},
	{"boron","B"},
	{"carbon","C"},
	{"nitrogen","N"},
	{"oxygen","O"},
	{"fluorine","F"},
	{"neon","Ne"},
	{"sodium","Na"}, /* 11 */
	{"magnesium","Mg"},
	{"aluminum","Al"}, /* NB, needs US spelling */
	{"silicon","Si"},
	{"phosphorus","P"},
	{"sulfur","S"},
	{"chlorine","Cl"},
	{"argon","Ar"},
	{"potassium","K"},
	{"calcium","Ca"},
	{"scandium","Sc"}, /* 21 */
	{"titanium","Ti"},
	{"vanadium","V"},
	{"chromium","Cr"},
	{"manganese","Mn"},
	{"iron","Fe"},
	{"cobalt","Co"},
	{"nickel","Ni"},
	{"copper","Cu"},
	{"zinc","Zn"},
	{"gallium","Ga"}, /* 31 */
	{"germanium","Ge"},
	{"arsenic","As"},
	{"selenium","Se"},
	{"bromine","Br"},
	{"krypton","Kr"},
	{"rubidium","Rb"},
	{"strontium","Sr"},
	{"yttrium","Y"},
	{"zirconium","Zr"},
	{"niobium","Nb"}, /* 41 */
	{"molybdenum","Mo"},
	{"technetium","Tc"},
	{"ruthenium","Ru"},
	{"rhodium","Rh"},
	{"palladium","Pd"},
	{"silver","Ag"},
	{"cadmium","Cd"},
	{"indium","In"},
	{"tin","Sn"},
	{"antimony","Sb"}, /* 51 */
	{"tellurium","Te"},
	{"iodine","I"},
	{"xenon","Xe"},
	{"cesium","Cs"}, /* NB, needs US spelling */
	{"barium","Ba"},
	{"lanthanum","La"},
	{"cerium","Ce"},
	{"praseodymium","Pr"},
	{"neodymium","Nd"},
	{"promethium","Pm"}, /* 61 */
	{"samarium","Sm"},
	{"europium","Eu"},
	{"gadolinium","Gd"},
	{"terbium","Tb"},
	{"dysprosium","Dy"},
	{"holmium","Ho"},
	{"erbium","Er"},
	{"thulium","Tm"},
	{"ytterbium","Yb"},
	{"lutetium","Lu"}, /* 71 */
	{"hafnium","Hf"},
	{"tantalum","Ta"},
	{"tungsten","W"},
	{"rhenium","Re"},
	{"osmium","Os"},
	{"iridium","Ir"},
	{"platinum","Pt"},
	{"gold","Au"},
	{"mercury","Hg"},
	{"thallium","Tl"}, /* 81 */
	{"lead","Pb"},
	{"bismuth","Bi"},
	{"polonium","Po"},
	{"astatine","At"},
	{"radon","Rn"},
	{"francium","Fr"},
	{"radium","Ra"},
	{"actinium","Ac"},
	{"thorium","Th"},
	{"protactinium","Pa"}, /* 91 */
	{"uranium","U"},
	{"neptunium","Np"},
	{"plutonium","Pu"},
	{"americium","Am"},
	{"curium","Cm"},
	{"berkelium","Bk"},
	{"californium","Cf"},
	{"einsteinium","Es"},
	{"fermium","Fm"},
	{"mendelevium","Md"}, /* 101 */
	{"nobelium","No"},
	{"lawrencium","Lr"},
	{"rutherfordium","Rf"},
	{"dubnium","Db"},
	{"seaborgium","Sg"},
	{"bohrium","Bh"},
	{"hassium","Hs"},
	{"meitnerium","Mt"},
	{"darmstadtium","Ds"},
	{"roentgenium","Rg"}, /* 111 */
	{"copernicium","Cn"},
	{"",""},
	{"flerovium","Fl"},
	{"",""},
	{"livermorium","Lv"},
	{"",""},
	{"",""}
};

int ischemical(char *s) {
	return !strncmp(s,"Chemical",8);
}

void solvechemical(int i,int j) {
	int a,k;
	char *p,*q,s[100];
	if((p=strstr(clue[i][j],"atomic number "))) {
		p+=14;
		if(!isdigit(p[0])) {
			q=p;
			while(!isspace(*q)) q++;
			a=parse(p,q);
		} else a=strtol(p,0,10);
		strcpy(answer[i][j],chem[a][0]);
	} else if((p=strstr(clue[i][j],"symbol "))) {
		p+=7;
		sscanf(p,"%99s",s);
		for(k=0;k<CHEM;k++) if(!strcmp(chem[k][1],s)) {
			strcpy(answer[i][j],chem[k][0]);
			return;
		}
		printf("unknown chemical symbol %s\n",s);
	} else printf("unknown clue %s",clue[i][j]);
}

/* pokemon */
/* list from https://en.wikipedia.org/wiki/List_of_Pok%C3%A9mon */
/* list is generated by kpokemon.c from the above webpage */

#define POKEMON 720

char pokemon[POKEMON][2][30]={
	{"",""},             /* name, evolution from */
	{"bulbasaur",""},
	{"ivysaur","bulbasaur"},
	{"venusaur","ivysaur"},
	{"charmander",""},
	{"charmeleon","charmander"},
	{"charizard","charmeleon"},
	{"squirtle",""},
	{"wartortle","squirtle"},
	{"blastoise","wartortle"},
	{"caterpie",""},
	{"metapod","caterpie"},
	{"butterfree","metapod"},
	{"weedle",""},
	{"kakuna","weedle"},
	{"beedrill","kakuna"},
	{"pidgey",""},
	{"pidgeotto","pidgey"},
	{"pidgeot","pidgeotto"},
	{"rattata",""},
	{"raticate","rattata"},
	{"spearow",""},
	{"fearow","spearow"},
	{"ekans",""},
	{"arbok","ekans"},
	{"pikachu","pichu"},
	{"raichu","pikachu"},
	{"sandshrew",""},
	{"sandslash","sandshrew"},
	{"nidoran",""},
	{"nidorina","nidoran"},
	{"nidoqueen","nidorina"},
	{"nidoran",""},
	{"nidorino","nidoran"},
	{"nidoking","nidorino"},
	{"clefairy","cleffa"},
	{"clefable","clefairy"},
	{"vulpix",""},
	{"ninetales","vulpix"},
	{"jigglypuff","igglybuff"},
	{"wigglytuff","jigglypuff"},
	{"zubat",""},
	{"golbat","zubat"},
	{"oddish",""},
	{"gloom","oddish"},
	{"vileplume","gloom"},
	{"paras",""},
	{"parasect","paras"},
	{"venonat",""},
	{"venomoth","venonat"},
	{"diglett",""},
	{"dugtrio","diglett"},
	{"meowth",""},
	{"persian","meowth"},
	{"psyduck",""},
	{"golduck","psyduck"},
	{"mankey",""},
	{"primeape","mankey"},
	{"growlithe",""},
	{"arcanine","growlithe"},
	{"poliwag",""},
	{"poliwhirl","poliwag"},
	{"poliwrath","poliwhirl"},
	{"abra",""},
	{"kadabra","abra"},
	{"alakazam","kadabra"},
	{"machop",""},
	{"machoke","machop"},
	{"machamp","machoke"},
	{"bellsprout",""},
	{"weepinbell","bellsprout"},
	{"victreebel","weepinbell"},
	{"tentacool",""},
	{"tentacruel","tentacool"},
	{"geodude",""},
	{"graveler","geodude"},
	{"golem","graveler"},
	{"ponyta",""},
	{"rapidash","ponyta"},
	{"slowpoke",""},
	{"slowbro","slowpoke"},
	{"magnemite",""},
	{"magneton","magnemite"},
	{"farfetch",""},
	{"doduo",""},
	{"dodrio","doduo"},
	{"seel",""},
	{"dewgong","seel"},
	{"grimer",""},
	{"muk","grimer"},
	{"shellder",""},
	{"cloyster","shellder"},
	{"gastly",""},
	{"haunter","gastly"},
	{"gengar","haunter"},
	{"onix",""},
	{"drowzee",""},
	{"hypno","drowzee"},
	{"krabby",""},
	{"kingler","krabby"},
	{"voltorb",""},
	{"electrode","voltorb"},
	{"exeggcute",""},
	{"exeggutor","exeggcute"},
	{"cubone",""},
	{"marowak","cubone"},
	{"hitmonlee","tyrogue"},
	{"hitmonchan","tyrogue"},
	{"lickitung",""},
	{"koffing",""},
	{"weezing","koffing"},
	{"rhyhorn",""},
	{"rhydon","rhyhorn"},
	{"chansey",""},
	{"tangela",""},
	{"kangaskhan",""},
	{"horsea",""},
	{"seadra","horsea"},
	{"goldeen",""},
	{"seaking","goldeen"},
	{"staryu",""},
	{"starmie","staryu"},
	{"mr",""},
	{"scyther",""},
	{"jynx","smoochum"},
	{"electabuzz","elekid"},
	{"magmar","magby"},
	{"pinsir",""},
	{"tauros",""},
	{"magikarp",""},
	{"gyarados","magikarp"},
	{"lapras",""},
	{"ditto",""},
	{"eevee",""},
	{"vaporeon","eevee"},
	{"jolteon","eevee"},
	{"flareon","eevee"},
	{"porygon",""},
	{"omanyte",""},
	{"omastar","omanyte"},
	{"kabuto",""},
	{"kabutops","kabuto"},
	{"aerodactyl",""},
	{"snorlax",""},
	{"articuno",""},
	{"zapdos",""},
	{"moltres",""},
	{"dratini",""},
	{"dragonair","dratini"},
	{"dragonite","dragonair"},
	{"mewtwo",""},
	{"mew",""},
	{"chikorita",""},
	{"bayleef","chikorita"},
	{"meganium","bayleef"},
	{"cyndaquil",""},
	{"quilava","cyndaquil"},
	{"typhlosion","quilava"},
	{"totodile",""},
	{"croconaw","totodile"},
	{"feraligatr","croconaw"},
	{"sentret",""},
	{"furret","sentret"},
	{"hoothoot",""},
	{"noctowl","hoothoot"},
	{"ledyba",""},
	{"ledian","ledyba"},
	{"spinarak",""},
	{"ariados","spinarak"},
	{"crobat","golbat"},
	{"chinchou",""},
	{"lanturn","chinchou"},
	{"pichu",""},
	{"cleffa",""},
	{"igglybuff",""},
	{"togepi",""},
	{"togetic","togepi"},
	{"natu",""},
	{"xatu","natu"},
	{"mareep",""},
	{"flaaffy","mareep"},
	{"ampharos","flaaffy"},
	{"bellossom","gloom"},
	{"marill",""},
	{"azumarill","marill"},
	{"sudowoodo",""},
	{"politoed","poliwhirl"},
	{"hoppip",""},
	{"skiploom","hoppip"},
	{"jumpluff","skiploom"},
	{"aipom",""},
	{"sunkern",""},
	{"sunflora","sunkern"},
	{"yanma",""},
	{"wooper",""},
	{"quagsire","wooper"},
	{"espeon","eevee"},
	{"umbreon","eevee"},
	{"murkrow",""},
	{"slowking","slowpoke"},
	{"misdreavus",""},
	{"unown",""},
	{"wobbuffet",""},
	{"girafarig",""},
	{"pineco",""},
	{"forretress","pineco"},
	{"dunsparce",""},
	{"gligar",""},
	{"steelix","onix"},
	{"snubbull",""},
	{"granbull","snubbull"},
	{"qwilfish",""},
	{"scizor","scyther"},
	{"shuckle",""},
	{"heracross",""},
	{"sneasel",""},
	{"teddiursa",""},
	{"ursaring","teddiursa"},
	{"slugma",""},
	{"magcargo","slugma"},
	{"swinub",""},
	{"piloswine","swinub"},
	{"corsola",""},
	{"remoraid",""},
	{"octillery","remoraid"},
	{"delibird",""},
	{"mantine",""},
	{"skarmory",""},
	{"houndour",""},
	{"houndoom","houndour"},
	{"kingdra","seadra"},
	{"phanpy",""},
	{"donphan","phanpy"},
	{"porygon","porygon"},
	{"stantler",""},
	{"smeargle",""},
	{"tyrogue",""},
	{"hitmontop","tyrogue"},
	{"smoochum",""},
	{"elekid",""},
	{"magby",""},
	{"miltank",""},
	{"blissey","chansey"},
	{"raikou",""},
	{"entei",""},
	{"suicune",""},
	{"larvitar",""},
	{"pupitar","larvitar"},
	{"tyranitar","pupitar"},
	{"lugia",""},
	{"ho",""},
	{"celebi",""},
	{"treecko",""},
	{"grovyle","treecko"},
	{"sceptile","grovyle"},
	{"torchic",""},
	{"combusken","torchic"},
	{"blaziken","combusken"},
	{"mudkip",""},
	{"marshtomp","mudkip"},
	{"swampert","marshtomp"},
	{"poochyena",""},
	{"mightyena","poochyena"},
	{"zigzagoon",""},
	{"linoone","zigzagoon"},
	{"wurmple",""},
	{"silcoon","wurmple"},
	{"beautifly","silcoon"},
	{"cascoon","wurmple"},
	{"dustox","cascoon"},
	{"lotad",""},
	{"lombre","lotad"},
	{"ludicolo","lombre"},
	{"seedot",""},
	{"nuzleaf","seedot"},
	{"shiftry","nuzleaf"},
	{"taillow",""},
	{"swellow","taillow"},
	{"wingull",""},
	{"pelipper","wingull"},
	{"ralts",""},
	{"kirlia","ralts"},
	{"gardevoir","kirlia"},
	{"surskit",""},
	{"masquerain","surskit"},
	{"shroomish",""},
	{"breloom","shroomish"},
	{"slakoth",""},
	{"vigoroth","slakoth"},
	{"slaking","vigoroth"},
	{"nincada",""},
	{"ninjask","nincada"},
	{"shedinja","nincada"},
	{"whismur",""},
	{"loudred","whismur"},
	{"exploud","loudred"},
	{"makuhita",""},
	{"hariyama","makuhita"},
	{"azurill",""},
	{"nosepass",""},
	{"skitty",""},
	{"delcatty","skitty"},
	{"sableye",""},
	{"mawile",""},
	{"aron",""},
	{"lairon","aron"},
	{"aggron","lairon"},
	{"meditite",""},
	{"medicham","meditite"},
	{"electrike",""},
	{"manectric","electrike"},
	{"plusle",""},
	{"minun",""},
	{"volbeat",""},
	{"illumise",""},
	{"roselia",""},
	{"gulpin",""},
	{"swalot","gulpin"},
	{"carvanha",""},
	{"sharpedo","carvanha"},
	{"wailmer",""},
	{"wailord","wailmer"},
	{"numel",""},
	{"camerupt","numel"},
	{"torkoal",""},
	{"spoink",""},
	{"grumpig","spoink"},
	{"spinda",""},
	{"trapinch",""},
	{"vibrava","trapinch"},
	{"flygon","vibrava"},
	{"cacnea",""},
	{"cacturne","cacnea"},
	{"swablu",""},
	{"altaria","swablu"},
	{"zangoose",""},
	{"seviper",""},
	{"lunatone",""},
	{"solrock",""},
	{"barboach",""},
	{"whiscash","barboach"},
	{"corphish",""},
	{"crawdaunt","corphish"},
	{"baltoy",""},
	{"claydol","baltoy"},
	{"lileep",""},
	{"cradily","lileep"},
	{"anorith",""},
	{"armaldo","anorith"},
	{"feebas",""},
	{"milotic","feebas"},
	{"castform",""},
	{"kecleon",""},
	{"shuppet",""},
	{"banette","shuppet"},
	{"duskull",""},
	{"dusclops","duskull"},
	{"tropius",""},
	{"chimecho",""},
	{"absol",""},
	{"wynaut",""},
	{"snorunt",""},
	{"glalie","snorunt"},
	{"spheal",""},
	{"sealeo","spheal"},
	{"walrein","sealeo"},
	{"clamperl",""},
	{"huntail","clamperl"},
	{"gorebyss","clamperl"},
	{"relicanth",""},
	{"luvdisc",""},
	{"bagon",""},
	{"shelgon","bagon"},
	{"salamence","shelgon"},
	{"beldum",""},
	{"metang","beldum"},
	{"metagross","metang"},
	{"regirock",""},
	{"regice",""},
	{"registeel",""},
	{"latias",""},
	{"latios",""},
	{"kyogre",""},
	{"groudon",""},
	{"rayquaza",""},
	{"jirachi",""},
	{"deoxys",""},
	{"turtwig",""},
	{"grotle","turtwig"},
	{"torterra","grotle"},
	{"chimchar",""},
	{"monferno","chimchar"},
	{"infernape","monferno"},
	{"piplup",""},
	{"prinplup","piplup"},
	{"empoleon","prinplup"},
	{"starly",""},
	{"staravia","starly"},
	{"staraptor","staravia"},
	{"bidoof",""},
	{"bibarel","bidoof"},
	{"kricketot",""},
	{"kricketune","kricketot"},
	{"shinx",""},
	{"luxio","shinx"},
	{"luxray","luxio"},
	{"budew",""},
	{"roserade","roselia"},
	{"cranidos",""},
	{"rampardos","cranidos"},
	{"shieldon",""},
	{"bastiodon","shieldon"},
	{"burmy",""},
	{"wormadam","burmy"},
	{"mothim","burmy"},
	{"combee",""},
	{"vespiquen","combee"},
	{"pachirisu",""},
	{"buizel",""},
	{"floatzel","buizel"},
	{"cherubi",""},
	{"cherrim","cherubi"},
	{"shellos",""},
	{"gastrodon","shellos"},
	{"ambipom","aipom"},
	{"drifloon",""},
	{"drifblim","drifloon"},
	{"buneary",""},
	{"lopunny","buneary"},
	{"mismagius","misdreavus"},
	{"honchkrow","murkrow"},
	{"glameow",""},
	{"purugly","glameow"},
	{"chingling",""},
	{"stunky",""},
	{"skuntank","stunky"},
	{"bronzor",""},
	{"bronzong","bronzor"},
	{"bonsly",""},
	{"mime",""},
	{"happiny",""},
	{"chatot",""},
	{"spiritomb",""},
	{"gible",""},
	{"gabite","gible"},
	{"garchomp","gabite"},
	{"munchlax",""},
	{"riolu",""},
	{"lucario","riolu"},
	{"hippopotas",""},
	{"hippowdon","hippopotas"},
	{"skorupi",""},
	{"drapion","skorupi"},
	{"croagunk",""},
	{"toxicroak","croagunk"},
	{"carnivine",""},
	{"finneon",""},
	{"lumineon","finneon"},
	{"mantyke",""},
	{"snover",""},
	{"abomasnow","snover"},
	{"weavile","sneasel"},
	{"magnezone","magneton"},
	{"lickilicky","lickitung"},
	{"rhyperior","rhydon"},
	{"tangrowth","tangela"},
	{"electivire","electabuzz"},
	{"magmortar","magmar"},
	{"togekiss","togetic"},
	{"yanmega","yanma"},
	{"leafeon","eevee"},
	{"glaceon","eevee"},
	{"gliscor","gligar"},
	{"mamoswine","piloswine"},
	{"porygon","porygon"},
	{"gallade","kirlia"},
	{"probopass","nosepass"},
	{"dusknoir","dusclops"},
	{"froslass","snorunt"},
	{"rotom",""},
	{"uxie",""},
	{"mesprit",""},
	{"azelf",""},
	{"dialga",""},
	{"palkia",""},
	{"heatran",""},
	{"regigigas",""},
	{"giratina",""},
	{"cresselia",""},
	{"phione",""},
	{"manaphy",""},
	{"darkrai",""},
	{"shaymin",""},
	{"arceus",""},
	{"victini",""},
	{"snivy",""},
	{"servine","snivy"},
	{"serperior","servine"},
	{"tepig",""},
	{"pignite","tepig"},
	{"emboar","pignite"},
	{"oshawott",""},
	{"dewott","oshawott"},
	{"samurott","dewott"},
	{"patrat",""},
	{"watchog","patrat"},
	{"lillipup",""},
	{"herdier","lillipup"},
	{"stoutland","herdier"},
	{"purrloin",""},
	{"liepard","purrloin"},
	{"pansage",""},
	{"simisage","pansage"},
	{"pansear",""},
	{"simisear","pansear"},
	{"panpour",""},
	{"simipour","panpour"},
	{"munna",""},
	{"musharna","munna"},
	{"pidove",""},
	{"tranquill","pidove"},
	{"unfezant","tranquill"},
	{"blitzle",""},
	{"zebstrika","blitzle"},
	{"roggenrola",""},
	{"boldore","roggenrola"},
	{"gigalith","boldore"},
	{"woobat",""},
	{"swoobat","woobat"},
	{"drilbur",""},
	{"excadrill","drilbur"},
	{"audino",""},
	{"timburr",""},
	{"gurdurr","timburr"},
	{"conkeldurr","gurdurr"},
	{"tympole",""},
	{"palpitoad","tympole"},
	{"seismitoad","palpitoad"},
	{"throh",""},
	{"sawk",""},
	{"sewaddle",""},
	{"swadloon","sewaddle"},
	{"leavanny","swadloon"},
	{"venipede",""},
	{"whirlipede","venipede"},
	{"scolipede","whirlipede"},
	{"cottonee",""},
	{"whimsicott","cottonee"},
	{"petilil",""},
	{"lilligant","petilil"},
	{"basculin",""},
	{"sandile",""},
	{"krokorok","sandile"},
	{"krookodile","krokorok"},
	{"darumaka",""},
	{"darmanitan","darumaka"},
	{"maractus",""},
	{"dwebble",""},
	{"crustle","dwebble"},
	{"scraggy",""},
	{"scrafty","scraggy"},
	{"sigilyph",""},
	{"yamask",""},
	{"cofagrigus","yamask"},
	{"tirtouga",""},
	{"carracosta","tirtouga"},
	{"archen",""},
	{"archeops","archen"},
	{"trubbish",""},
	{"garbodor","trubbish"},
	{"zorua",""},
	{"zoroark","zorua"},
	{"minccino",""},
	{"cinccino","minccino"},
	{"gothita",""},
	{"gothorita","gothita"},
	{"gothitelle","gothorita"},
	{"solosis",""},
	{"duosion","solosis"},
	{"reuniclus","duosion"},
	{"ducklett",""},
	{"swanna","ducklett"},
	{"vanillite",""},
	{"vanillish","vanillite"},
	{"vanilluxe","vanillish"},
	{"deerling",""},
	{"sawsbuck","deerling"},
	{"emolga",""},
	{"karrablast",""},
	{"escavalier","karrablast"},
	{"foongus",""},
	{"amoonguss","foongus"},
	{"frillish",""},
	{"jellicent","frillish"},
	{"alomomola",""},
	{"joltik",""},
	{"galvantula","joltik"},
	{"ferroseed",""},
	{"ferrothorn","ferroseed"},
	{"klink",""},
	{"klang","klink"},
	{"klinklang","klang"},
	{"tynamo",""},
	{"eelektrik","tynamo"},
	{"eelektross","eelektrik"},
	{"elgyem",""},
	{"beheeyem","elgyem"},
	{"litwick",""},
	{"lampent","litwick"},
	{"chandelure","lampent"},
	{"axew",""},
	{"fraxure","axew"},
	{"haxorus","fraxure"},
	{"cubchoo",""},
	{"beartic","cubchoo"},
	{"cryogonal",""},
	{"shelmet",""},
	{"accelgor","shelmet"},
	{"stunfisk",""},
	{"mienfoo",""},
	{"mienshao","mienfoo"},
	{"druddigon",""},
	{"golett",""},
	{"golurk","golett"},
	{"pawniard",""},
	{"bisharp","pawniard"},
	{"bouffalant",""},
	{"rufflet",""},
	{"braviary","rufflet"},
	{"vullaby",""},
	{"mandibuzz","vullaby"},
	{"heatmor",""},
	{"durant",""},
	{"deino",""},
	{"zweilous","deino"},
	{"hydreigon","zweilous"},
	{"larvesta",""},
	{"volcarona","larvesta"},
	{"cobalion",""},
	{"terrakion",""},
	{"virizion",""},
	{"tornadus",""},
	{"thundurus",""},
	{"reshiram",""},
	{"zekrom",""},
	{"landorus",""},
	{"kyurem",""},
	{"keldeo",""},
	{"meloetta",""},
	{"genesect",""},
	{"chespin",""},
	{"quilladin","chespin"},
	{"chesnaught","quilladin"},
	{"fennekin",""},
	{"braixen","fennekin"},
	{"delphox","braixen"},
	{"froakie",""},
	{"frogadier","froakie"},
	{"greninja","frogadier"},
	{"bunnelby",""},
	{"diggersby","bunnelby"},
	{"fletchling",""},
	{"fletchinder","fletchling"},
	{"talonflame","fletchinder"},
	{"scatterbug",""},
	{"spewpa","scatterbug"},
	{"vivillon","spewpa"},
	{"litleo",""},
	{"pyroar","litleo"},
	{"flab",""},
	{"floette","flab"},
	{"florges","floette"},
	{"skiddo",""},
	{"gogoat","skiddo"},
	{"pancham",""},
	{"pangoro","pancham"},
	{"furfrou",""},
	{"espurr",""},
	{"meowstic","espurr"},
	{"honedge",""},
	{"doublade","honedge"},
	{"aegislash","doublade"},
	{"spritzee",""},
	{"aromatisse","spritzee"},
	{"swirlix",""},
	{"slurpuff","swirlix"},
	{"inkay",""},
	{"malamar","inkay"},
	{"binacle",""},
	{"barbaracle","binacle"},
	{"skrelp",""},
	{"dragalge","skrelp"},
	{"clauncher",""},
	{"clawitzer","clauncher"},
	{"helioptile",""},
	{"heliolisk","helioptile"},
	{"tyrunt",""},
	{"tyrantrum","tyrunt"},
	{"amaura",""},
	{"aurorus","amaura"},
	{"sylveon","eevee"},
	{"hawlucha",""},
	{"dedenne",""},
	{"carbink",""},
	{"goomy",""},
	{"sliggoo","goomy"},
	{"goodra","sliggoo"},
	{"klefki",""},
	{"phantump",""},
	{"trevenant","phantump"},
	{"pumpkaboo",""},
	{"gourgeist","pumpkaboo"},
	{"bergmite",""},
	{"avalugg","bergmite"},
	{"noibat",""},
	{"noivern","noibat"},
	{"xerneas",""},
	{"yveltal",""},
	{"zygarde",""},
	{"diancie",""},
};

int ispokemon(char *s) {
	return strstr(s,"Pokemon")!=0;
}

void solvepokemon(int i,int j) {
	int a,k;
	char *p,s[100],*q;
	if((p=strstr(clue[i][j],"number #"))) {
		p+=8;
		if(!isdigit(p[0])) {
			q=p;
			while(!isspace(*q)) q++;
			a=parse(p,q);
		} else a=strtol(p,0,10);
		if(a) strcpy(answer[i][j],pokemon[a][0]);
	} else if((p=strstr(clue[i][j],"evolves from "))) {
		p+=13;
		sscanf(p,"%98s",s);
		for(k=0;s[k];k++) s[k]=tolower(s[k]);
		for(k=0;k<POKEMON;k++) if(!strcmp(s,pokemon[k][1])) {
			strcpy(answer[i][j],pokemon[k][0]);
			return;
		}
		printf("couldn't find pokemon that evolves from %s\n",s);
	} else if((p=strstr(clue[i][j],"evolves into "))) {
		p+=13;
		sscanf(p,"%98s",s);
		for(k=0;s[k];k++) s[k]=tolower(s[k]);
		for(k=0;k<POKEMON;k++) if(!strcmp(s,pokemon[k][0])) {
			strcpy(answer[i][j],pokemon[k][1]);
			return;
		}
		printf("couldn't find pokemon that evolves into %s\n",s);
	} else printf("unknown clue %s",clue[i][j]);
}

/* u.s presidents */
/* http://en.wikipedia.org/wiki/List_of_us_presidents */

#define PRESIDENT 44

/* i'm lazy and have years as strings */
char president[PRESIDENT][5][30]={
	{"george","","washington","1789","1797"}, /* first name, middle name, last name, start and end years in office */
	{"john","","adams","1797","1801"},
	{"thomas","","jefferson","1801","1809"},
	{"james","","madison","1809","1817"},
	{"james","","monroe","1817","1825"},
	{"john","quincy","adams","1825","1829"},
	{"andrew","","jackson","1829","1837"},
	{"martin","van","buren","1837","1841"},
	{"william","henry","harrison","1841","1841"},
	{"john","","tyler","1841","1845"},
	{"james","k.","polk","1845","1849"},
	{"zachary","","taylor","1849","1850"},
	{"millard","","fillmore","1850","1853"},
	{"franklin","","pierce","1853","1857"},
	{"james","","buchanan","1857","1861"},
	{"abraham","","lincoln","1861","1865"},
	{"andrew","","johnson","1865","1869"},
	{"ulysses","s.","grant","1869","1877"},
	{"rutherford","b.","hayes","1877","1881"},
	{"james","a.","garfield","1881","1881"},
	{"chester","a.","arthur","1881","1885"},
	{"grover","","cleveland","1885","1889"},
	{"benjamin","","harrison","1889","1893"},
	{"grover","","cleveland","1893","1897"},
	{"william","","mckinley","1897","1901"},
	{"theodore","","roosevelt","1901","1909"},
	{"william","howard","taft","1909","1913"},
	{"woodrow","","wilson","1913","1921"},
	{"warren","g.","harding","1921","1923"},
	{"calvin","","coolidge","1923","1929"},
	{"herbert","clark","hoover","1929","1933"},
	{"franklin","d.","roosevelt","1933","1945"},
	{"harry","s.","truman","1945","1953"},
	{"dwight","d.","eisenhower","1953","1961"},
	{"john","f.","kennedy","1961","1963"},
	{"lyndon","b.","johnson","1963","1969"},
	{"richard","","nixon","1969","1974"},
	{"gerald","","ford","1974","1977"},
	{"jimmy","","carter","1977","1981"},
	{"ronald","","reagan","1981","1989"},
	{"george","h. w.","bush","1989","1993"},
	{"bill","","clinton","1993","2001"},
	{"george","w.","bush","2001","2009"},
	{"barack","","obama","2009","2014"}
};

int ispresident(char *s) {
	return strstr(s,"President")!=0;
}

void solvepresident(int i,int j) {
	int k,a,b,y,ix,cnt;
	char *p;
	char s[111],t[111],u[111];
	ix=(strstr(clue[i][j],"First")==0)*2;
	if((p=strstr(clue[i][j],"held the office in "))) {
		p+=19;
		y=strtol(p,0,10);
		/* find within interval (unique) */
		for(k=0;k<PRESIDENT;k++) {
			a=strtol(president[k][3],0,10);
			b=strtol(president[k][4],0,10);
			if(a<y && y<b) {
				strcpy(answer[i][j],president[k][ix]);
				return;
			}
		}
		/* find boundary */
		for(cnt=k=0;k<PRESIDENT;k++) {
			a=strtol(president[k][3],0,10);
			b=strtol(president[k][4],0,10);
			if((a==y || b==y) && strlen(president[k][ix])==getlen(i,j)) {
				if(wordcanfit(i,j,president[k][ix])) {
					/* hardcode very nasty case: two different presidents are
					   eligible, but they share the same first name! */
					if(cnt==1 && !strcmp(s,president[k][ix])) continue;
					strcpy(s,president[k][ix]);
					cnt++;
				}
			}
		}
		if(cnt>1) return;
		else if(cnt==1) {
			strcpy(answer[i][j],s);
			return;
		}
		printf("len %d, no year matches %s",getlen(i,j),clue[i][j]);
	} else if((p=strstr(clue[i][j],"before "))) {
		p+=7;
		strcpy(t,p);
		while(strlen(t) && t[strlen(t)-1]=='\n') t[strlen(t)-1]=0;
		for(k=0;t[k];k++) t[k]=tolower(t[k]);
		for(cnt=k=0;k<PRESIDENT;k++) {
			strcpy(s,president[k][0]);
			if(president[k][1][0]) strcat(s," "),strcat(s,president[k][1]);
			strcat(s," "); strcat(s,president[k][2]);
			if(!strcmp(t,s) && strlen(president[k-1][ix])==getlen(i,j)) {
				if(wordcanfit(i,j,president[k-1][ix])) {
					strcpy(u,president[k-1][ix]);
					cnt++;
				}
			}
		}
		if(cnt>1) return;
		else if(cnt==1) strcpy(answer[i][j],u);
		else printf("warning no-one found %s",clue[i][j]);
		return;
	} else if((p=strstr(clue[i][j],"after "))) {
		p+=6;
		strcpy(t,p);
		while(strlen(t) && t[strlen(t)-1]=='\n') t[strlen(t)-1]=0;
		for(k=0;t[k];k++) t[k]=tolower(t[k]);
		for(cnt=k=0;k<PRESIDENT;k++) {
			strcpy(s,president[k][0]);
			if(president[k][1][0]) strcat(s," "),strcat(s,president[k][1]);
			strcat(s," "); strcat(s,president[k][2]);
			if(!strcmp(t,s) && strlen(president[k+1][ix])==getlen(i,j)) {
				if(wordcanfit(i,j,president[k+1][ix])) {
					strcpy(u,president[k+1][ix]);
					cnt++;
				}
			}
		}
		if(cnt>1) return;
		else if(cnt==1) strcpy(answer[i][j],u);
		else printf("warning no-one found %s",clue[i][j]);
	} else printf("error in clue %s",clue[i][j]);
}

/* colours, taken from http://cloford.com/resources/colours/500col.htm */

int iscolour(char *s) {
	return strstr(s,"Color")!=0;
}

void solvecolour(int i,int j) {
	char *p;
	int r,g,b,f1,f2;
	if((p=strstr(clue[i][j],"["))) {
		p++;
		sscanf(p,"%d,%d,%d",&r,&g,&b);
	} else if((p=strstr(clue[i][j],"#"))) {
		p++;
		r=hex(p);
		g=hex(p+2);
		b=hex(p+4);
	} else printf("unknown colour format %s",clue[i][j]);
	if(r+g+b==0) strcpy(answer[i][j],"black");
	else if(r==255 && g==0 && b==0) strcpy(answer[i][j],"red");
	else if(r==0 && g==255 && b==0) strcpy(answer[i][j],"lime");
	else if(r==0 && g==0 && b==255) strcpy(answer[i][j],"blue");
	else if(r==255 && g==255 && b==0) strcpy(answer[i][j],"yellow");
	else if(r==255 && g==0 && b==255) strcpy(answer[i][j],"magenta");
	else if(r==255 && g==255 && b==255) strcpy(answer[i][j],"white");
	else if(r==0 && g==255 && b==255) {
		/* nasty case, two possible colours */
		f1=wordcanfit(i,j,"aqua");
		f2=wordcanfit(i,j,"cyan");
		if(f1 && !f2) strcpy(answer[i][j],"aqua");
		if(!f1 && f2) strcpy(answer[i][j],"cyan");
	}
	else if(r==0 && g==128 && b==128) strcpy(answer[i][j],"teal");
	else if(r==128 && g==128 && b==0) strcpy(answer[i][j],"olive");
	else if(r==192 && g==192 && b==192) strcpy(answer[i][j],"silver");
	else if(r==128 && g==128 && b==128) strcpy(answer[i][j],"gray");
	else if(r==0 && g==128 && b==0) strcpy(answer[i][j],"green");
	else if(r==0 && g==0 && b==128) strcpy(answer[i][j],"navy");
	else if(r==128 && g==0 && b==0) strcpy(answer[i][j],"maroon");
	else if(r==128 && g==0 && b==128) strcpy(answer[i][j],"purple");
	else printf("unknown colour %d %d %d\n",r,g,b);
}

/* other */

void solveother(int i,int j) {
	/* topcoder handle of michal forisek */
	if(strstr(clue[i][j],"TopCoder")) strcpy(answer[i][j],"misof");
	/* capital of slovakia */
	else if(strstr(clue[i][j],"Slovakia")) strcpy(answer[i][j],"bratislava");
	/* do you like this contest? depends on the number of letters */
	else if(strstr(clue[i][j],"Do you")) strcpy(answer[i][j],getlen(i,j)==2?"no":"yes");
	else printf("unknown clue %s",clue[i][j]);
}

void solve() {
	int i,j;
	for(i=0;i<2;i++) {
		for(j=0;j<n[i];j++) {
			if(ischemical(clue[i][j])) solvechemical(i,j);
			else if(ispokemon(clue[i][j])) solvepokemon(i,j);
			else if(ispresident(clue[i][j])) solvepresident(i,j);
			else if(iscolour(clue[i][j])) solvecolour(i,j);
			else solveother(i,j);
		}
	}
}

int apply() {
	int i,j,r=0;
	for(i=0;i<2;i++) for(j=0;j<n[i];j++) {
		if(answer[i][j][0]) {
			r++;
			if(!wordcanfit(i,j,answer[i][j])) {
				printf("fatal error, %s doesn't fit at %d %d (%s)\n",answer[i][j],i,j,clue[i][j]);
				return 0;
			}
			applyword(i,j,answer[i][j]);
		}
	}
	return r;
}

int main() {
	int i,j,q,prev,cur;
	char s[999];
	fgets(s,998,stdin); sscanf(s,"%d %d",&r,&c);
	for(i=0;i<r;i++) fgets(g[i],132,stdin);
	for(i=0;i<2;i++) {
		fgets(s,998,stdin); sscanf(s,"%d",&n[i]);
		for(j=0;j<n[i];j++) {
			fgets(s,998,stdin);
			sscanf(s,"%d %d %n",&cluer[i][j],&cluec[i][j],&q);
			strcpy(clue[i][j],s+q);
			answer[i][j][0]=0;
		}
	}
	cur=0;
	do prev=cur,solve(),cur=apply(); while(prev<cur);
	for(i=0;i<r;i++) printf("%s",g[i]);
	for(i=0;i<r;i++) for(j=0;j<c;j++) if(g[i][j]=='#') {
		puts("error, crossword not finished");
		for(i=0;i<2;i++) for(j=0;j<n[i];j++) if(!answer[i][j][0]) printf("%s",clue[i][j]);
		return 0;
	}
	return 0;
}
