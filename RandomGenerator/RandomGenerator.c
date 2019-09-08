#include <stdio.h>


//Simple Random Generator implementation in c
unsigned long int seed=1;
unsigned int lcg (){
    int a=16807;
    unsigned int m=0x7fffffff;
    seed=seed*a%m;
    return seed;
}

int main(){
unsigned int r=lcg();
unsigned int n=1;
while(lcg() != 16807){
    n=n+1;
}

    printf("%d",lcg());
    return 0;
}
