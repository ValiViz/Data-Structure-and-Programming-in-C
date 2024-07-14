#include <stdio.h>
#define MINERR 1E-6
int main()
{
    int count = 0, sub = 1;
    double err = 1.0 / sub, ans = 0;
    while(err > MINERR)
    {
        sub *= ++count;
        ans += err;
        err = 1.0 / sub;
    }
    printf("%lf\n", ans);
    return 0;
}