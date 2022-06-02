#include <stdio.h>
#include <stdlib.h>

int k_ty_bit_n(int n, int k)
{
    return (n>>k-1)&1;
}

int prng(int ziarno)
{
    int n1,n2,n3,n4;
    int xor,wynik;

    if(ziarno> 63 || ziarno < 1)
    {
        return -1;
    }
    else
    {
        n1 = k_ty_bit_n(ziarno,0);
        n2 = k_ty_bit_n(ziarno,1);
        n3 = k_ty_bit_n(ziarno,5);
        n4 = k_ty_bit_n(ziarno,6);

        xor = n1^n2^n3^n4;

        for(int i=0;i<5;i++)
        {
            xor<<=1;
        }
        ziarno>>=1;

        wynik = ziarno^xor;

        if (wynik==1)
        {
            return 0;
        }
        printf("%d ",wynik);
        prng(wynik);
    }
}

int main()
{
    prng(1);
    return 0;
}