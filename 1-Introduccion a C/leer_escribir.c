#include <stdio.h>

int main(void)
{
    int a;
    float b;


    printf("Escribe el valor de a: "); scanf("%d", &a);
    printf("Escribe el valor de b: "); scanf("%f",&b);

    printf("El valor de a es %d y el valor de b es %8.1f\n", a, b);

    return 0;
}

