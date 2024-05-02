#include <stdio.h>
#include <math.h>

int main()
{
    float a = 100000, b = 100000;
    float c = -1;
    float d = a * a + b * b - 2 * a * b * c;
    printf("%.2llf", sqrt(d));

}