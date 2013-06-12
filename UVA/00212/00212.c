#include <stdio.h>
#define MP 100 /* max patients */

/* parameters */

int numroom; /* number of operation rooms (max 10) */
int numbed;  /* number of recovery room beds (max 30) */
int start;   /* starting hour for first surgery */
int trans;   /* minutes to transport patient from operation room to
                recovery room */
int roomprep;/* minutes to prepare operation room for next patient */
int bedprep; /* minutes to prepare recovery room bed for next patient */
int numpat;  /* number of surgery patients for the day (max 100) */

/* patient data */

char pat_name[MP][9]; /* name */
int  pat_sur[MP];     /* minutes required for surgery */
int  pat_rec[MP];     /* minutes required for recovery */

int  pat_room[MP];    /* operation room # */
int  pat_opb[MP];     /* operation begin */
int  pat_ope[MP];     /* operation end */
int  pat_bed[MP];     /* recovery bed # */
int  pat_recb[MP];    /* recovery begin */
int  pat_rece[MP];    /* recovery end */

int  pat_trans[MP];   /* minutes left of transportation */
int  pat_status[MP];  /* 0:need operation, 1:under operation, 2:under transport,
                         3:need recovery, 4:under recovery, 5:done */

/* rooms and beds */

int  room_pat[MP];    /* occupying patient */
int  room_occ[MP];    /* minutes room is occupied */
int  room_prep[MP];   /* minutes left of room preparing */
int  bed_pat[MP];     /* occupying patient */
int  bed_occ[MP];     /* minutes bed is occupied */
int  bed_prep[MP];    /* minutes left of bed preparing */

/* other vars */

int  clock;           /* time of day */
int  patdone;         /* patients done */

/* move patients to surgery, if rooms are available */
void move_to_surgery()
{
   int i,j;

   j=0;
   for(i=0;i<numroom;i++) {
      while(j<numpat && pat_status[j]!=0)
         j++;
      if(room_pat[i]==-1 && room_prep[i]==0 && j<numpat) {
         room_pat[i]=j;
         pat_room[j]=i;
         pat_opb[j]=clock;
         pat_status[j]=1;
         j++;
      }
   }
}

/* move patients to recreation */
void move_to_rec()
{
   int i,j,z;

   for(z=0;z<numroom;z++) {
      i=0;
      for(j=0;j<numpat;j++) {
         while(1) {
            if(i>=numpat) break;
            if(bed_prep[i]==0 && bed_pat[i]==-1) break;
            i++;
         }
         if(pat_room[j]==z && i<numbed && pat_status[j]==2) {
            bed_pat[i]=j;
            pat_bed[j]=i;
            pat_recb[j]=clock+trans;
            pat_status[j]=3;
            if(trans==0)
               pat_status[j]=4;
         }
      }
   }
}

/* let one minute of simulation time pass */
void elapse_time()
{
   int i;

   for(i=0;i<numroom;i++) {
      if(room_pat[i]!=-1)
         room_occ[i]++;
      if(room_prep[i]>0)
         room_prep[i]--;
   }
   for(i=0;i<numbed;i++) {
      if(bed_pat[i]!=-1 && pat_status[bed_pat[i]]==4)
         bed_occ[i]++;
      if(bed_prep[i]>0)
         bed_prep[i]--;
   }
   clock++;
   for(i=0;i<numpat;i++) {
      if(pat_status[i]==1) {
         /* under operation */
         pat_sur[i]--;
         if(pat_sur[i]==0) {
            room_pat[pat_room[i]]=-1;
            room_prep[pat_room[i]]=roomprep;
            pat_ope[i]=clock;
            pat_trans[i]=trans;
            pat_status[i]=2;
         }
      } else if(pat_status[i]==3) {
         /* under transport */
         pat_trans[i]--;
         if(pat_trans[i]==0)
            pat_status[i]=4;
      } else if(pat_status[i]==4) {
         /* under recovery */
         pat_rec[i]--;
         if(pat_rec[i]==0) {
            pat_status[i]=5;
            patdone++;
            pat_rece[i]=clock;
            bed_pat[pat_bed[i]]=-1;
            bed_prep[pat_bed[i]]=bedprep;
         }
      }
   }
}

int main()
{
   int i,first=1;
   char s[200];

   do {
      if(gets(s)==NULL) break;
      sscanf(s,"%d %d %d %d %d %d %d",&numroom,&numbed,&start,&trans,&roomprep,
         &bedprep,&numpat);
      for(i=0;i<numpat;i++) {
         gets(pat_name[i]);
         gets(s);
         sscanf(s,"%d %d",&pat_sur[i],&pat_rec[i]);
      }

      /* init */

      start*=60;
      clock=start;
      for(i=0;i<numpat;i++) {
         pat_room[i]=pat_bed[i]=-1;
         pat_status[i]=pat_trans[i]=0;
      }
      for(i=0;i<numroom;i++) {
         room_occ[i]=0;
         room_pat[i]=-1;
         room_prep[i]=0;
      }
      for(i=0;i<numbed;i++) {
         bed_occ[i]=0;
         bed_pat[i]=-1;
         bed_prep[i]=0;
      }
      patdone=0;

      /* start simulation */

      do {
         move_to_surgery();
         move_to_rec();
         elapse_time();
      } while(patdone<numpat);

      /* output */

      printf(" Patient          Operating Room          Recovery Room\n");
      printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n");
      printf(" ------------------------------------------------------\n");
      for(i=0;i<numpat;i++) {
         printf("%2d  %-9s %2d   %2d:%02d",i+1,pat_name[i],pat_room[i]+1,
            pat_opb[i]/60,pat_opb[i]%60);
         printf("   %2d:%02d     %2d   %2d:%02d   %2d:%02d\n",pat_ope[i]/60,
            pat_ope[i]%60,pat_bed[i]+1,pat_recb[i]/60,pat_recb[i]%60,
            pat_rece[i]/60,pat_rece[i]%60);
      }
      printf("\nFacility Utilization\n");
      printf("Type  # Minutes  %% Used\n");
      printf("-------------------------\n");
      for(i=0;i<numroom;i++)
         printf("Room %2d    %4d  %6.2f\n",i+1,room_occ[i],
            (float)room_occ[i]*100/(clock-start));
      for(i=0;i<numbed;i++)
         printf("Bed  %2d    %4d  %6.2f\n",i+1,bed_occ[i],
            (float)bed_occ[i]*100/(clock-start));
      putchar('\n');
      if(gets(s)==NULL) break;
   } while(1);
}
