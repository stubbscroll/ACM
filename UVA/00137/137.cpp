#include <vector>
#include <string>
#include <set>
#include <map>
#include <deque>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cctype>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<double> vd;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef vector<pii> vpii;
typedef vector<pdd> vpdd;

#define fr(i,j,k) for(int i=j;i<k;++i)
#define fir(n) fr(i,0,n)
#define fjr(n) fr(j,0,n)
#define fkr(n) fr(k,0,n)
#define flr(n) fr(l,0,n)
#define frd(i,j,k) for(int i=j;i>=k;--i)

#define si size()
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)

#define all(x) x.begin(),x.end()
#define del(x,y) memset(x,y,sizeof(x))

#define INF 1000000000
#define EPS 1e-9

vvi makevvi(int r,int c,int v=0) { vvi a; vi b(c,v); fir(r) a.pb(b); return a; }

template<class T> inline void linetoeq(pair<T,T> a,pair<T,T> b,T &A,T &B,T &C) { A=b.second-a.second; B=a.first-b.first; C=A*a.first+B*a.second; }
template<class T> inline T det2d(T a1,T a2,T b1,T b2) { return a1*b2-a2*b1; }
int linesegintersect(pdd p1,pdd p2,pdd p3,pdd p4,pdd &c)
{
   double a1,a2,b1,b2,c1,c2,r1,r2,r3,r4;
   linetoeq(p1,p2,a1,b1,c1);
   r3=a1*p3.first+b1*p3.second-c1;
   r4=a1*p4.first+b1*p4.second-c1;
   if(fabs(r3)>EPS && fabs(r4)>EPS && (r3<0)==(r4<0)) return 0;
   linetoeq(p3,p4,a2,b2,c2);
   r1=a2*p1.first+b2*p1.second-c2;
   r2=a2*p2.first+b2*p2.second-c2;
   if(fabs(r1)>EPS && fabs(r2)>EPS && (r1<0)==(r2<0)) return 0;
   double det=det2d(a1,a2,b1,b2);
   if(fabs(det)<EPS) {
      if(fabs(p1.first-p1.second)<EPS) {
         #define SWAPP(p) swap(p.first,p.second)
         SWAPP(p1); SWAPP(p2); SWAPP(p3); SWAPP(p4);
         #undef SWAPP
         if(p1.first>p2.first) swap(p1,p2);
         if(p3.first>p4.first) swap(p3,p4);
         if(p1.first>p3.first) swap(p1,p3);
         return 2+(p2.first-p3.first>EPS);
      }
      return 2;
   } else {
      c=mp((b2*c1-b1*c2)/det,(a1*c2-a2*c1)/det);
      return 1;
   }
}

/* signed triangle area *2 */
// 18.02.2007, tested on srm 250 div 1 hard ok

inline double signedtrianglearea2(pdd a,pdd b,pdd c)
{
   return (b.first-a.first)*(c.second-a.second)-(c.first-a.first)*(b.second-a.second);
}

/* convex hull, O(n log n) */
// 18.02.2007, tested on srm 250 div 1 hard ok
// 18.02.2007, tested on srm 249 div 1 hard ok (worst case 4 ms)

pdd CP0;

bool convexcompare(const pdd &a,const pdd &b)
{
   pdd A=a,B=b;
   double aa=signedtrianglearea2(CP0,A,B);
   if(aa>EPS) return true;
   else if(aa<-EPS) return false;
   else {
      double x=fabs(a.first-CP0.first)-fabs(b.first-CP0.first);
      double y=fabs(a.second-CP0.second)-fabs(b.second-CP0.second);
      return(x>0 || y>0);
   }
}

vpdd convexhull2d(vpdd p)
{
   int m=0,n=p.si,j=2;
   if(!n) return p;
   fr(i,1,n) if(p[i].second<p[m].second || (p[i].second==p[m].second && p[i].first<p[m].first)) m=i;
   if(m) swap(p[0],p[m]);
   CP0=p[0];
   sort(p.begin()+1,p.end(),convexcompare);
   fr(i,2,n) if(fabs(signedtrianglearea2(CP0,p[j-1],p[i]))>EPS) p[j++]=p[i];
   p.resize(j); n=j;
   vpdd h;
   fir(min(2,n)) h.pb(p[i]);
   j=2;
   if(n<3) return h;
   while(j<n) {
      if(signedtrianglearea2(h[h.si-2],h[h.si-1],p[j])>EPS) h.pb(p[j++]);
      else h.pop_back();
   }
   return h;
}

/* check if point is inside polygon, returns true if strictly inside */
// 18.02.2007, tested on srm 250 div 1 hard ok
// 18.02.2007, tested on srm 187 div 2 hard ok

template<class T> bool pointinpolygon(T a,vector<T> b)
{
   int n=b.si,c=0;
   fir(n) {
      int ix=i,iy=(i+1)%n;
      if(b[ix].second>b[iy].second) swap(ix,iy);
      if(a.second>b[ix].second-EPS && a.second+EPS<b[iy].second && signedtrianglearea2(a,b[ix],b[iy])>EPS) c^=1;
   }
   return c==1;
}

/* calculate intersection of two convex polygons, lazy version */
// 18.02.2007, tested on srm 250 div 1 hard ok (worst case 2 ms)

template<class T> vector<pdd> convexpolygonintersect(vector<T> a,vector<T> b)
{
   vpdd p; int n=a.si,m=b.si;
   fir(n) fjr(m) {
      pdd c;
      if(linesegintersect(a[i],a[(i+1)%n],b[j],b[(j+1)%m],c)==1) p.pb(c);
   }
   fir(n) if(pointinpolygon(a[i],b)) p.pb(a[i]);
   fir(m) if(pointinpolygon(b[i],a)) p.pb(b[i]);
   return convexhull2d(p);
}

/* polygon area */
// 17.02.2007, tested on srm 166 div 2 hard ok (worst case 4 ms)
// 18.02.2007, tested on srm 250 div 1 hard ok
// 18.02.2007, tested on srm 249 div 1 hard ok
// 18.02.2007, tested on tccc2004-q1 medium ok (worst case 1 ms)

template<class T> inline double polygonarea(T p)
{
   int n=p.si; if(n<3) return 0; double a=(double)p[0].first*p[n-1].second-(double)p[0].second*p[n-1].first;
   fir(n-1) a+=(double)p[i+1].first*p[i].second-(double)p[i+1].second*p[i].first;
   return fabs(a)*.5;
}

int la,lb;
vpii a,b;

int main()
{
   int x,y;

   while(scanf("%d",&la),la) {
      a.clear(); b.clear();
      fir(la) {
         scanf("%d %d",&x,&y);
         a.pb(mp(x,y));
      }
      scanf("%d",&lb);
      fir(lb) {
         scanf("%d %d",&x,&y);
         b.pb(mp(x,y));
      }
      vpdd c=convexpolygonintersect(a,b);
      printf("%8.2f",polygonarea(a)+polygonarea(b)-2*polygonarea(c));
   }
   putchar('\n');
   return 0;
}
