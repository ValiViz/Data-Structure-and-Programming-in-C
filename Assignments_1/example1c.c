#include <stdio.h>
#define SPACE_ASKII 32
#define POSITIVE_SIGN 1

char scanf_without_space(char *site)
{
    do
    {
        scanf("%c", site);
    } while (*site == SPACE_ASKII);
    
}

int cal(int top_num, char now_cal_sign, int sign)
{
    int next_num;
    char next_cal_sign;
    switch (now_cal_sign)
    {
    case '*':
        scanf("%d", &next_num);
        scanf_without_space(&next_cal_sign);
        top_num *= next_num;
        return cal(top_num, next_cal_sign, sign);
    case '/':
        scanf("%d", &next_num);
        scanf_without_space(&next_cal_sign);
        top_num /= next_num;
        return cal(top_num, next_cal_sign, sign);
    case '+':
        scanf("%d", &next_num);
        scanf_without_space(&next_cal_sign);
        return top_num + sign * cal(next_num, next_cal_sign, 1);
    case '-':
        scanf("%d", &next_num);
        scanf_without_space(&next_cal_sign);
        return top_num - sign * cal(next_num, next_cal_sign, -1);
    case '=':
        return top_num;
    default:
        return EOF;
    }
}

int main()
{
    int top_num;
    char now_cal_sign;
    scanf("%d", &top_num);
    scanf_without_space(&now_cal_sign);
    int result = cal(top_num, now_cal_sign, POSITIVE_SIGN);
    printf("%d\n", result);

    return 0;
}