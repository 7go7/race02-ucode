#include "../inc/header.h"

int row, column;
int len;

int main(int argc, char const *argv[])
{
    if (argc != 6)
    {
        mx_printerr("usage: ./way_home [file_name] [x1] [y1] [x2] [y2]\n");
        exit(0);
    }
    int src = open(argv[1], O_RDONLY);
    if (src < 0)
    {
        mx_printerr("map does not exist\n");
        exit(0);
    }
    char s[1];
    int n = read(src, s, sizeof(s));
    if (n <= 0)
    {
        mx_printerr("map does not exist\n");
        exit(0);
    }

    int x1 = mx_atoi(argv[2]), x2 = mx_atoi(argv[4]);
    int y1 = mx_atoi(argv[3]), y2 = mx_atoi(argv[5]);

    char *str = mx_file_to_str(argv[1]);
    char **final = mx_cmatrix(str, &row, &column);
    int **mat = mx_matrix(str, &row, &column);
    int **mat1 = mx_matrix(str, &row, &column);
    if (x1 >= column || x2 >= column || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0 || y1 >= row || y2 >= row)
    {
        mx_printerr("points are out of map range\n");
        exit(0);
    }
    int px[row * column], py[row * column];

    if (!lee(mat, x1, y1, x2, y2, row, column, &len, px, py))
    {
        mx_printerr("route not found\n");
        exit(0);
    }
    int file1 = open("path.txt", O_WRONLY);
    if (file1 < 0)
    {
        file1 = open("path.txt", O_CREAT | O_WRONLY);
    }
    for (int i = 0; i < len; ++i)
    {
        final[py[i]][px[i]] = '*';
    }
    final[y2][x2] = '*';
    mx_max(mat1, x1, y1, row, column, final);
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            char s = final[i][j];
            write(file1, &s, 1);
        }
        write(file1, "\n", 1);
    }
    close(file1);
    mx_printstr("dist=");
    mx_printint(mx_max(mat1, x1, y1, row, column, final));
    mx_printstr("\n");
    mx_printstr("exit=");
    mx_printint(len);
    mx_printstr("\n");
    return 0;
}
