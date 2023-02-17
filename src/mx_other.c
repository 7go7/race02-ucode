#include "../inc/header.h"

int mx_max(int **grid, int ax, int ay, int He, int Wi, char **final)
{
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int d, x, y, k;
    bool stop = false;
    int max;
    int flag = 1;

    d = 0;
    grid[ay][ax] = 0;
    while (!stop || flag)
    {
        stop = true;
        for (y = 0; y < He; ++y)
            for (x = 0; x < Wi; ++x)
                if (grid[y][x] == d)
                {
                    for (k = 0; k < 4; ++k)
                    {
                        int iy = y + dy[k], ix = x + dx[k];
                        if (iy >= 0 && iy < He && ix >= 0 && ix < Wi &&
                            grid[iy][ix] == -2)
                        {
                            stop = false;
                            grid[iy][ix] = d + 1;
                        }
                    }
                }
        d++;
        flag = 0;
    }
    max = grid[0][0];
    for (int i = 0; i < He; ++i)
    {
        for (int j = 0; j < Wi; ++j)
        {
            if (grid[i][j] > max)
            {
                max = grid[i][j];
            }
        }
    }
    for (int i = 0; i < He; ++i)
    {
        for (int j = 0; j < Wi; ++j)
        {
            if (grid[i][j] == max)
            {
                if (final[i][j] == '*')
                {
                    final[i][j] = 'X';
                }
                else
                {
                    final[i][j] = 'D';
                }
            }
        }
    }
    return max;
}

int **mx_matrix(char *res, int *row, int *column)
{
    int i;
    int c = 0;
    int r = 0;

    for (i = 0; res[i] != '\0'; ++i)
    {
        if (res[i] == '\n')
        {
            ++r;
        }
    }
    c = (i - r) / r;

    int **mat = (int **)malloc(r * sizeof(int *));

    for (int i = 0; i < r; i++)
    {
        mat[i] = (int *)malloc(c * sizeof(int *));
    }
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            if (i == 0)
            {
                if (res[j] == '#')
                {
                    mat[i][j] = -1;
                }
                else if (res[j] == '.')
                {
                    mat[i][j] = -2;
                }
                else if (res[j] != ',' && res[j] != '\n')
                {
                    mx_printerr("map error\n");
                    exit(0);
                }
            }
            else
            {
                if (res[j + i * (c + 1)] == '#')
                {
                    mat[i][j] = -1;
                }
                else if (res[j + i * (c + 1)] == '.')
                {
                    mat[i][j] = -2;
                }
                else if (res[j + i * (c + 1)] != ',' && res[j + i * (c + 1)] != '\n')
                {
                    mx_printerr("map error\n");
                    exit(0);
                }
            }
        }
    }
    *column = c;
    *row = r;
    return mat;
}

char *mx_file_to_str(const char *filename)
{
    int file = open(filename, O_RDONLY);
    char s[1];
    int n = read(file, s, sizeof(s));
    int count = 0;

    while (n > 0)
    {
        if (s[0] == '#' || s[0] == '.' || s[0] == '\n')
        {
            ++count;
        }
        n = read(file, s, sizeof(s));
    }
    close(file);
    file = open(filename, O_RDONLY);
    char *res = (char *)malloc(sizeof(char) * count + 1);

    n = read(file, s, 1);

    for (int i = 0; i < count && n > 0; ++i)
    {
        if (s[0] == '.' || s[0] == '#' || s[0] == '\n')
        {
            res[i] = s[0];
            ++i;
        }
        n = read(file, s, 1);
        --i;
    }
    res[count] = '\0';
    close(file);
    return res;
}

char **mx_cmatrix(char *res, int *row, int *column)
{
    int i;
    int c = 0;
    int r = 0;

    for (i = 0; res[i] != '\0'; ++i)
    {
        if (res[i] == '\n')
        {
            ++r;
        }
    }
    c = (i - r) / r;

    char **mat = (char **)malloc(r * sizeof(char *));

    for (int i = 0; i < r; i++)
    {
        mat[i] = (char *)malloc(c * sizeof(char *));
    }
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            if (i == 0)
            {
                if (res[j] == '#')
                {
                    mat[i][j] = '#';
                }
                else if (res[j] == '.')
                {
                    mat[i][j] = '.';
                }
                else if (res[j] != ',' && res[j] != '\n')
                {
                    mx_printerr("map error\n");
                    exit(0);
                }
            }
            else
            {
                if (res[j + i * (c + 1)] == '#')
                {
                    mat[i][j] = '#';
                }
                else if (res[j + i * (c + 1)] == '.')
                {
                    mat[i][j] = '.';
                }
                else if (res[j + i * (c + 1)] != ',' && res[j + i * (c + 1)] != '\n')
                {
                    mx_printerr("map error\n");
                    exit(0);
                }
            }
        }
    }
    *row = r;
    *column = c;
    return mat;
}
