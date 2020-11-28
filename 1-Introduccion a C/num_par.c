#include <stdio.h>

int main (void)
{
    int a;

    printf("Introduzca un numero: "); scanf("%d", &a);

    if(a%2 == 0) {
        printf("El valor de a es par. \n");
    }
    else {
        printf("El valor de a es impar. \n");
    }

    return 0;
}