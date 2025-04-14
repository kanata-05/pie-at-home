#ifndef BELLARD_PI_H
#define BELLARD_PI_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define mulMod(a,b,m) fmod((double)(a)*(double)(b),(m))

int invMod(int x,int y){
    int q,u,v,a,c,t;
    u=x;v=y;c=1;a=0;
    do{
        q=v/u;
        t=c;c=a-q*c;a=t;
        t=u;u=v-q*u;v=t;
    }while(u!=0);
    a=a%y;if(a<0)a+=y;
    return a;
}

int powMod(int a,int b,int m){
    int r=1,aa=a;
    while(1){
        if(b&1)r=mulMod(r,aa,m);
        b>>=1;if(b==0)break;
        aa=mulMod(aa,aa,m);
    }
    return r;
}

int isPrime(int n){
    if(n<2)return 0;
    if(n==2)return 1;
    if(n%2==0)return 0;
    int r=(int)sqrt(n);
    for(int i=3;i<=r;i+=2)
        if(n%i==0)return 0;
    return 1;
}

int nextPrime(int n){
    do{n++;}while(!isPrime(n));
    return n;
}

double computePi(int start){
    int av,a,vmax,N,n,num,den,k,kq,kq2,t,v,s,i;
    double sum=0.0;
    N=(int)((start+20)*log(10)/log(2));

    for(a=3;a<=2*N;a=nextPrime(a)){
        vmax=(int)(log(2*N)/log(a));
        av=1;for(i=0;i<vmax;i++)av*=a;
        s=0;num=1;den=1;v=0;kq=1;kq2=1;
        for(k=1;k<=N;k++){
            t=k;
            if(kq>=a){
                do{t/=a;v--;}while(t%a==0);
                kq=0;
            }
            kq++;
            num=mulMod(num,t,av);

            t=2*k-1;
            if(kq2>=a){
                if(kq2==a){
                    do{t/=a;v++;}while(t%a==0);
                }
                kq2-=a;
            }
            den=mulMod(den,t,av);
            kq2+=2;

            if(v>0){
                t=invMod(den,av);
                t=mulMod(t,num,av);
                t=mulMod(t,k,av);
                for(i=v;i<vmax;i++)t=mulMod(t,a,av);
                s+=t;
                if(s>=av)s-=av;
            }
        }
        t=powMod(10,start-1,av);
        s=mulMod(s,t,av);
        sum=fmod(sum+(double)s/(double)av,1.0);
    }
    return sum;
}

void computePiRange(int start,int count,char* out){
    #pragma omp parallel for
    for(int i=0;i<count;i++){
        double res=computePi(start+i);
        out[i]='0'+(int)(res*10);
    }
    out[count]='\0';
}


#endif
