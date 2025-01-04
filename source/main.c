#include <stdio.h>
#include <stdlib.h>

int main()
{
    char x;
    printf("Podaj funkcję jaką chcesz wykonać: ");
    int result = scanf("%c", &x);

    if(result==1)
    {
        printf("Funkcja %c\n", x);
    }
    else
    {
        printf("Niepoprawne dane");
    }




    return EXIT_SUCCESS;
}