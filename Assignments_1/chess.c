#include <stdio.h>

int chess[21][21];

int test(int i, int j)
{
    if(chess[i][j] != 0)
    {
        if(chess[i][j] == chess[i][j + 1] && 
           chess[i][j] == chess[i][j + 2] &&
           chess[i][j] == chess[i][j + 3] &&
          (chess[i][j-1] == 0 || chess[i][j + 4] == 0))
        {
            printf("%d:%d,%d", chess[i][j], i, j);
            return 1;
        }
        if(chess[i][j] == chess[i + 1][j] && 
           chess[i][j] == chess[i + 2][j] &&
           chess[i][j] == chess[i + 3][j] &&
          (chess[i - 1][j] == 0 || chess[i + 4][j] == 0))
        {
            printf("%d:%d,%d", chess[i][j], i, j);
            return 1;
        }
        if(chess[i][j] == chess[i + 1][j + 1] && 
           chess[i][j] == chess[i + 2][j + 2] &&
           chess[i][j] == chess[i + 3][j + 3] &&
          (chess[i - 1][j - 1] == 0 || chess[i + 4][j + 4] == 0))
        {
            printf("%d:%d,%d\n", chess[i][j], i, j);
            return 1;
        }
    }
    if(chess[i][j + 3] != 0 &&
       chess[i][j + 3] == chess[i + 1][j + 2] && 
       chess[i][j + 3] == chess[i + 2][j + 1] &&
       chess[i][j + 3] == chess[i + 3][j] &&
      (chess[i - 1][j + 4] == 0 || chess[i + 4][j - 1] == 0))
        {
            printf("%d:%d,%d\n", chess[i][j + 3], i, j + 3);
            return 1;
        }
    

    return 0;
}

int main()
{
    for(int i = 0; i < 21; i++)
    {
        chess[i][0] = chess[i][20] = chess[0][i] = chess[20][i] = 3;
    }

    for(int i = 1; i <= 19; i++)
    for(int j = 1; j <= 19; j++)
    scanf("%d", &chess[i][j]);

    for(int i = 1; i <= 16; i++)
    for(int j = 1; j <= 16; j++)
    if(test(i, j)) return 0;

    printf("No\n");
    return 0;
}