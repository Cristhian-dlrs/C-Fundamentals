#include <stdio.h>

int main(void)
{
    int a;

    printf("Introduzca un numero: "); scanf("%d", &a);

    if (a > 0) {
        printf("El valor de a es positivo\n");
    }
    else if(a == 0) {
        printf("El valor de a es nulo\n");
    }
    else if(a < 0) {
        printf("El valor de a es negativo\n");
    }

    return 0;
}