#include <iostream>
#include <cmath>
#pragma GCC optimize(2)
#include "windows.h"
using namespace std;
float sjd[2][20];
double dx,dy,x=7.5,y=0.9,pa=.01f,pb=.1f,sumy;
bool once=0;
float loss(){
    float sum=0;
    for(int ai=0;ai<20;ai++){
        sum+=((sjd[1][ai]-sjd[0][ai]*x-y)*(sjd[1][ai]-sjd[0][ai]*x-y));//L2¦»loss
    }
    sum/=20;
    //cout<<sum;
    if (once==0)
    {
        sumy=sum;
        
    }
    if (sumy<=sum&&!once)
    {
        pa=pa/10;
        pb=pb/10;
        once=1;
    }
    cout<<sum<<" "<<endl;
    return sum;
}
double ds;
int main(){
    freopen("tdin.in","r",stdin);
    for(int ai=0;ai<20;ai++){
        cin>>sjd[0][ai]>>sjd[1][ai];
    }
    
    while(loss()>.01f){
    	dx=0;
    	dy=0;
        for(int ai=0;ai<20;ai++){
            dx+=(-2*sjd[0][ai]*(sjd[1][ai]-sjd[0][ai]*x-y))/20;
        }
        

        for(int ai=0;ai<20;ai++){
            dy+=(-2*(sjd[1][ai]-sjd[0][ai]*x-y))/20;
        }    
		ds=sqrt(dx*dx+dy*dy);
		cout<<dx<<" "<<dy<<" "<<ds<<endl;
        x=x-(dx/ds)*pa;
        y=y-(dy/ds)*pb;
        //Sleep(1000);
    }
    cout<<x<<" "<<y;
    return 0;
} 
