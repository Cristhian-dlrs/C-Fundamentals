#include <stdio.h>

int main(void)
{
    int a;

    printf("Introduce in numero entero a: "); scanf("%d", &a);

    while(a > 0) {
        printf("%d\n", a);
        a -= 1;
    }

    return 0;
}