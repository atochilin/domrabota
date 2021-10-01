#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main (void) 
{
    int a, b=2, t; // t - один остаток;
    int n=0; // количество остатков;
    int r[200], k=0; // k - это также количество остатков,
                       // мы будем использовать его, чтобы показать количество элементов во втором массиве;
    scanf ("%d", &a);
    int D=a;    
    while (a > 0)
    {
        t=a%b;
        k=n;
        r[k]=t;
        n+=1;
        a=a/b;
//        printf ("%d", t);
    }
    
    printf ("The number of remnants is %d", n);
    printf ("\n");
    printf ("The binary number of %d is ", D);
    for (int i=k-1; k>=0; k--)
    {
        printf ("%d", r[k]);
    }
    return 0;
}
