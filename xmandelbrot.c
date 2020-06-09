/* compile : gcc -L/usr/X11R6/lib -lX11 xmandelbrot.c -o xmandelbrot */

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define WIDTH     256
#define HEIGHT    256
#define NMAX     1000
#define NCOL_R      8
#define NCOL_G      8
#define NCOL_B      8


#define JULIASET


int   main(int argc, char **argv);
void  setcolorcell     (void);
void  draw_graph       (void);
int   recurs           (double, double);

Display *dp;
Window   wp;
GC      *gcp;
double   xmin, xmax, ymin, ymax;
#ifdef JULIASET
double   creal, cimag;
#endif

int main(int argc, char **argv)
{
   XEvent  event;
   XSetWindowAttributes ap;

   if(argc<5){ printf("xmandelbrot xmin xmax ymin ymax\n"); exit(0); }
   xmin = atof(argv[1]);
   xmax = atof(argv[2]);
   ymin = atof(argv[3]);
   ymax = atof(argv[4]);
#ifdef JULIASET
   creal = atof(argv[5]);
   cimag = atof(argv[6]);
#endif

   if ((gcp=(GC *)malloc(sizeof(GC *)*NCOL_R*NCOL_G*NCOL_B))==NULL){exit(-1);}

   dp = XOpenDisplay(NULL);
   wp = XCreateSimpleWindow(dp,RootWindow(dp,0),0,0,WIDTH,HEIGHT,1,WhitePixel(dp,0),BlackPixel(dp,0));

   ap.backing_store=Always;
   XChangeWindowAttributes(dp,wp,CWBackingStore,&ap);
   XSelectInput(dp,wp,ButtonPressMask|ButtonReleaseMask);
   setcolorcell();
   XMapWindow(dp,wp);
   XFlush(dp);

   draw_graph();
   while(True){
     XNextEvent(dp, &event);
     if(event.type == ButtonPress) break;
   }
   return 0;
}

void setcolorcell()
{
   XColor col;
   int i,j,k,n,di,dj,dk;

   di = 0xffff/NCOL_R;
   dj = 0xffff/NCOL_G;
   dk = 0xffff/NCOL_B;

   col.red  =0;
   col.blue =0;
   col.green=0;
   gcp[0] = XCreateGC(dp,wp,0,NULL);
   XAllocColor(dp,DefaultColormap(dp,0),&col);
   XSetForeground(dp,gcp[0],col.pixel);

   n=0;
   for(i=0;i<NCOL_R;i++){
     for(j=0;j<NCOL_G;j++){
       for(k=0;k<NCOL_B;k++){

         col.red   = 0xffff - di*i;
         col.blue  = 0xffff - dj*j;
         col.green = 0xffff - dk*k;

         gcp[n] = XCreateGC(dp,wp,0,NULL);
         XAllocColor(dp,DefaultColormap(dp,0),&col);
         XSetForeground(dp,gcp[n],col.pixel);

         n++;
       }
     }
   }
}

void draw_graph()
{
   int i,j,k,nc;
   double dx,dy;

   nc = NCOL_R*NCOL_G*NCOL_B-1;
   dx = (xmax-xmin)/WIDTH;
   dy = (ymax-ymin)/HEIGHT;
   for(i=0;i<WIDTH;i++){
     for(j=0;j<HEIGHT;j++){
       k = (double)recurs(dx*i + xmin,dy*j + ymin)/NMAX*nc;
       XDrawPoint(dp,wp,gcp[k],i,j);
     }
   }
}

int recurs(double x, double y)
{
   int n=0;
   double zr=0.0,zi=0.0,tr,ti;

#ifdef JULIASET
   zr = x;
   zi = y;
#endif

   for(n=0;n<NMAX;n++){
#ifdef JULIASET
     tr = zr*zr-zi*zi + creal;
     ti = 2*zr*zi     + cimag;
#else
     tr = zr*zr-zi*zi + x;
     ti = 2*zr*zi     + y;
#endif
     if( (tr*tr+ti*ti)>2.0 ) break;
     zr = tr;
     zi = ti;
   }

   return(n);
}
