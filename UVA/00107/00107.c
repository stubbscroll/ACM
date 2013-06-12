#include <stdio.h>

int main()
{
   int h,w,i,j,iter,h2,w2,bad,toth,mul;

   while(1) {
      scanf("%d %d\n",&h,&w);
      if(h==0 && w==0)
         break;
      else if(h==1 && w==1) {
         printf("0 1\n");
         continue;
      } else if(h==1 && w==0) {
         printf("0 0\n");
         continue;
      } else if(h==w+1) {
         printf("1 %d\n",h+w);
         continue;
      }
      for(i=2;;i++)
         if(h%i==0 && w%(i-1)==0) {
/*            printf("try: %d %d\n",i,i-1);*/
            iter=0; bad=0;
            h2=h; w2=w;
            while(h2>1) {
               iter++;
               if(h2%i) bad=1;
               if(w2%(i-1)) bad=1;
               if(bad) break;
               h2/=i;
               w2/=(i-1);
            }
/*            printf("exp: %d %d %d %d %d\n",h,w,i,i-1,iter);*/
            if(h2>1 || w2>1) continue;
            if(bad) continue;
            w2=toth=0; mul=1;
            for(j=0;j<iter;j++) {
               toth+=w*mul;
               mul*=i;
               w/=(i-1);
               w2+=h2;
               h2*=(i-1);
            }
            toth+=h;
/*            printf("%d %d-",h,iter);*/
            printf("%d %d\n",w2,toth);
/*            printf("%d %d\n",h<3?h-1:(w-1)/(iter+1),h*iter-w*(iter-1));*/
            goto done;
         }
      w=i/0;
      printf("no answer found, bad input\n");
done:
      ;
   }
}
