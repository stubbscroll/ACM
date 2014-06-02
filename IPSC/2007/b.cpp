#include <string>
#include <vector>

using namespace std;

#define pb(x) push_back(x)
#define si size()
#define EMPTY 123456789

string s;
char t[1000];
vector<int> log;

int main()
{
   int i,v,tall,j;
   while(1) {
      s="";
      while(1) {
         if(gets(t)==NULL) break;
         if(string(t)=="NEW STORY") break;
         s+=" "+string(t);
      }
      if(s=="") break;
      log.clear();
      for(tall=v=i=0;s[i];) {
         // check for the word "empty"
         string x="";
         if(i && !isalpha(s[i-1]) && isalpha(s[i])) {
            int j=i;
            while(s[j] && isalpha(s[j])) x+=tolower(s[j++]);
            if(x=="empty") { log.pb(EMPTY); }
         }
         if(isdigit(s[i])) {
            tall=1;
            v=v*10+s[i]-48;
            i++;
         } else if(tall) {
            tall=0;
            string z="";
            // retrieve until we have match
            while(s[i] && s[i]==' ') i++;
            while(1) {
               // add one word
               if(!s[i]) { printf("no match: %s %s\n",z.c_str(),s.c_str()); break; }
               while(s[i] && isalpha(s[i])) z+=tolower(s[i++]);
               while(s[i] && (s[i]==' ' || !isalnum(s[i]))) i++;
               if(z=="people came in") { log.pb(v); break; }
               else if(z=="newcomers") { log.pb(v); break; }
               else if(z=="people boarded") { log.pb(v); break; }
               else if(z=="pairs of lungs joined") { log.pb(v); break; }
               else if(z=="got in") { log.pb(v); break; }
               else if(z=="in") { log.pb(v); break; }
               else if(z=="people got in") { log.pb(v); break; }
               else if(z=="eager passengers jumped in") { log.pb(v); break; }
               else if(z=="people who were already waiting on the bus stop boarded") { log.pb(v); break; }
               else if(z=="people got on") { log.pb(v); break; }
               else if(z=="boarded") { log.pb(v); break; }
               else if(z=="people left") { log.pb(-v); break; }
               else if(z=="left") { log.pb(-v); break; }
               else if(z=="got off") { log.pb(-v); break; }
               else if(z=="came out") { log.pb(-v); break; }
               else if(z=="seats were emptied") { log.pb(-v); break; }
               else if(z=="travellers left") { log.pb(-v); break; }
               else if(z=="travellers jumped out") { log.pb(-v); break; }
               else if(z=="people got off") { log.pb(-v); break; }
               else if(z=="passengers got out") { log.pb(-v); break; }
               else if(z=="out") { log.pb(-v); break; }
               else if(z=="of them left") { log.pb(-v); break; }
               else if(z=="managed to escape") { log.pb(-v); break; }
               if(z.si>100) { printf("nomatch: %s\n",z.c_str());
                  return 0; }
               z+=" ";
            }
//            printf("%d ",log[log.si-1]);
            v=0;
         } else i++;
      }
      log.pb(EMPTY);
      // check story for negativity, first: find empty
      for(i=0;i<log.si;i++) if(log[i]==EMPTY) {
         int num=0;
         for(j=i-1;j>=0;j--) {
            if(log[j]!=EMPTY) num-=log[j];
            if(num<0) goto illegal;
            if(log[j]==EMPTY && num) goto illegal;
         }
         num=0;
         for(j=i+1;j<log.si;j++) {
            if(log[j]!=EMPTY) num+=log[j];
            if(num<0) goto illegal;
            if(log[j]==EMPTY && num) goto illegal;
         }
         break;
      }
      puts("YES");
      goto done;
   illegal:
      puts("NO");
   done:;
   }
   return 0;
}
