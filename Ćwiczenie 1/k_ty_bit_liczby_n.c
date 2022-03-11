#include <stdio.h>
#include <stdlib.h>

int k_ty_bit_n(int n, int k)
{
    return (n>>k-1)&1;
}

int main()
{
    int n, k;

    printf("Podaj n: ");
    scanf("%d", &n);
    printf("Podaj k: ");
    scanf("%d", &k);

    printf("\n%d\n", k_ty_bit_n(n,k));
    system("PAUSE");
    return 0;
}