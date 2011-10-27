#include <stdio.h>
int main()
{
    int a = 7;
    int *aPtr;
    aPtr = &a;
    printf("%p\n", &a);
    printf("%p\n", aPtr);
    printf("%p\n", &aPtr);
    printf("%d\n", a);
    printf("%d\n", *aPtr);
    printf("%p\n", *&aPtr);
    printf("%p\n", &*aPtr);
    printf("%d\n", *&a);
    // printf("%d\n", &*a); <- Invalid type. should be %p not %d

    return 0;
 }
