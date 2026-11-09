
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char prods[][10] = {
    "E=TR",
    "R=+TR",
    "R=#",
    "T=FY",
    "Y=*FY",
    "Y=#",
    "F=(E)",
    "F=i"
};

int n = 8;
char firsts[256][20], follows[256][20];

void add_sym(char *set, char c)
{
    if (c != '\0' && !strchr(set, c))
    {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

void get_first(char c, char *res)
{
    if (!isupper((unsigned char)c))
    {
        add_sym(res, c);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (prods[i][0] == c)
        {
            if (prods[i][2] == '#')
            {
                add_sym(res, '#');
            }
            else
            {
                get_first(prods[i][2], res);
            }
        }
    }
}

void get_follow(char c, char *res)
{
    if (c == prods[0][0])
    {
        add_sym(res, '$');
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 2; prods[i][j]; j++)
        {
            if (prods[i][j] == c)
            {
                char next = prods[i][j + 1];

                if (next)
                {
                    char temp[20] = "";
                    get_first(next, temp);

                    for (int k = 0; temp[k]; k++)
                    {
                        if (temp[k] != '#')
                        {
                            add_sym(res, temp[k]);
                        }
                        else
                        {
                            get_follow(prods[i][0], res);
                        }
                    }
                }
                else if (c != prods[i][0])
                {
                    get_follow(prods[i][0], res);
                }
            }
        }
    }
}

int main()
{
    char non_terminals[] = "ERTYF";

    for (int i = 0; i < 5; i++)
    {
        get_first(non_terminals[i],
                  firsts[(int)non_terminals[i]]);

        printf("First(%c) = { ",
               non_terminals[i]);

        for (int j = 0;
             firsts[(int)non_terminals[i]][j]; j++)
        {
            printf("%c, ",
                   firsts[(int)non_terminals[i]][j]);
        }

        printf("}\n");
    }

    printf("\n------------------------------------------\n\n");

    for (int i = 0; i < 5; i++)
    {
        get_follow(non_terminals[i],
                   follows[(int)non_terminals[i]]);

        printf("Follow(%c) = { ",
               non_terminals[i]);

        for (int j = 0;
             follows[(int)non_terminals[i]][j]; j++)
        {
            printf("%c, ",
                   follows[(int)non_terminals[i]][j]);
        }

        printf("}\n");
    }

    return 0;
}
