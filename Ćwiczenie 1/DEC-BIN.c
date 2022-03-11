#include <stdio.h>

void binary(unsigned n)
{
    unsigned i;
    for (i = 1 << 31; i > 0; i >>= 1)
    {
        (n & i) ? printf("1") : printf("0");
    }
}

int main()
{
    int i;
    printf("Podaj liczbę: ");
    scanf("%d", &i);

    binary(i);
    printf("\n");
    system("PAUSE");
    return 0;
}