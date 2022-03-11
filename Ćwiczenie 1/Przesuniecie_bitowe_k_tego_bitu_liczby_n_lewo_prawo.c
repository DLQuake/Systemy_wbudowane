#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int n, k, lewo, prawo;

    printf("Podaj n: ");
    scanf("%d", &n);
    printf("Podaj k: ");
    scanf("%d", &k);

    lewo = n << k;
    prawo = n >> k;

    printf("\n%d\n", lewo);
    printf("\n%d\n", prawo);
    system("PAUSE");
    return 0;
}