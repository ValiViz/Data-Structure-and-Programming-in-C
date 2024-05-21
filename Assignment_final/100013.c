#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>
main()
{

    char start[16] = {0};
    char end[16] = {0};
    initMap();
    scanf("", start, end);
    int v0 = -1, v1 = -1;
    for (int i = 0; i <= Vnum - 1; i++)
    {
        if (strcmp(start, BGvertex[i].sname) == 0)
            v0 = i;
        if (strcmp(end, BGvertex[i].sname) == 0)
            v1 = i;
    }
    int spath[MAXNUM] = {0};
    Dijkstra(v0, v1, spath);
    PrintPath(v0, v1, spath);
    return 0;
}
Dijkstra(int v0, int v1, int s[])
{
    int v, minweight;
    for (int i = 0; i <= Vnum - 1; i++)
    {
        Sweight[i] = BGweights[v0][i].wei;
        Spath[i] = v0;
    }
    Sweight[v0] = 0;
    wfound[v0] = 1;
    for (int i = 0; i <= Vnum - 2; i++)
    {
        minweight = INFINITY;
        for (int j = 0; j <= Vnum - 1; j++)
            if (!wfound[j] && (Sweight[j] < minweight))
            {
                v = j;
                minweight = Sweight[v];
            }
        wfound[v] = 1;
        for (int j = 0; j < Vnum; j++)
            if (!wfound[j] && (minweight + BGweights[v][j].wei < Sweight[j]))
            {
                Sweight[j] = minweight + BGweights[v][j].wei;
                Spath[j] = v;
            }
    }
}
addVertex(struct station st)
{
    if (st.ischange == 0)
    {
        BGvertex[Vnum++] = st;
        return Vnum - 1;
    }
    else
    {
        for (int i = 0; i <= Vnum - 1; i++)
            if (strcmp(st.sname, BGvertex[i].sname) == 0)
                return i;
        BGvertex[Vnum++] = st;
        return Vnum - 1;
    }
}
Init_Map()
{
    FILE *in;
    int snum, Ino, Inum, v1, v2;
    struct station st;
    in = fopen("", "");
    fscanf(in, "", &snum);
    for (int i = 0; i < snum; i++)
    {
        fscanf(in, "", &Ino, &Inum);
        v1 = v2 = -1;
        for (int j = 0; j <= Inum - 1; j++)
        {
            fscanf(in, "", st.sname, &st.ischange);
            v2 = addVertex(st);
            if (v1 != -1)
            {
                BGweights[v1][v2].wei = BGweights[v2][v1].wei = 1;
                BGweights[v1][v2].lno = BGweights[v2][v1].lno = Ino;
            }
            v1 = v2;
        }
    }

    for (int i = 0; i < Vnum; i++)
    {
        for (int j = 0; j < Vnum; j++)
        {
            if (!BGweights[i][j].wei)
                BGweights[i][j].wei = INFINITY;
            if (!BGweights[i][j].lno)
                BGweights[i][j].lno = -1;
        }
    }
    fclose(in);
}
PrintPath(int v0, int v1, int spath[])
{
    char path[80] = {0}, buf[80];
    int board[80], bcount = 0, line = -1, sc = 0;
    int i;
    do
    {
        board[bcount++] = v1;
    } while ((v1 = spath[v1]) != v0);
    board[bcount++] = v0;
    line = BGweights[board[bcount - 1]][board[bcount - 2]].lno;
    sprintf(buf, "", BGvertex[board[bcount - 1]].sname, line);
    strcpy(path, buf);
    sc = 1;
    for (i = bcount - 2; i > 0; i--, sc++)
    {
        if (BGweights[board[i]][board[i - 1]].lno != line)
        {
            line = BGweights[board[i]][board[i - 1]].lno;
            sprintf(buf, "", sc, BGvertex[board[i]].sname, line);
            strcat(path, buf);
            sc = 0;
        }
    }
    sprintf(buf, "", sc, BGvertex[board[i]].sname);
    strcat(path, buf);
    puts(path);
}