
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ip_sym[15], stack[15];
int ip_ptr = 0, st_ptr = 0, len, i;
char temp[2], temp2[2];
char act[15];

void check(void);

int main()
{
    printf("\n\t SHIFT REDUCE PARSER\n");
    printf("\nGRAMMAR\n");
    printf("E -> E+E\n");
    printf("E -> E/E\n");
    printf("E -> E*E\n");
    printf("E -> a | b\n");

    printf("\nEnter the input symbol:\t");
    if (scanf("%14s", ip_sym) != 1)
        return 1;

    len = strlen(ip_sym);

    /* Add end marker */
    ip_sym[len] = '$';
    ip_sym[len + 1] = '\0';

    stack[0] = '$';
    stack[1] = '\0';

    printf("\nStack implementation table\n");
    printf("Stack\t\tInput symbol\tAction\n");
    printf("------------------------------------------\n");

    printf("%s\t\t%s\t\t---\n", stack, ip_sym);

    while (ip_sym[ip_ptr] != '$')
    {
        /* SHIFT operation */
        char ch = ip_sym[ip_ptr];

        stack[++st_ptr] = ch;
        stack[st_ptr + 1] = '\0';

        ip_ptr++;

        printf("%s\t\t%s\t\tshift %c\n",
               stack, ip_sym + ip_ptr, ch);

        check();
    }

    /* Final reductions */
    check();

    if (strcmp(stack, "$E") == 0 &&
        ip_sym[ip_ptr] == '$')
    {
        printf("%s\t\t$\t\tACCEPT\n", stack);
    }
    else
    {
        printf("%s\t\t$\t\tREJECT\n", stack);
    }

    return 0;
}

void check(void)
{
    int flag = 1;

    while (flag)
    {
        flag = 0;

        /* Reduce a or b to E */
        if (stack[st_ptr] == 'a' ||
            stack[st_ptr] == 'b')
        {
            char ch = stack[st_ptr];

            stack[st_ptr] = 'E';

            printf("%s\t\t%s\t\tE->%c\n",
                   stack, ip_sym + ip_ptr, ch);

            flag = 1;
        }

        /* Reduce E+E to E */
        if (st_ptr >= 3 &&
            strncmp(stack + st_ptr - 2, "E+E", 3) == 0)
        {
            stack[st_ptr - 2] = 'E';
            st_ptr -= 2;
            stack[st_ptr + 1] = '\0';

            printf("%s\t\t%s\t\tE->E+E\n",
                   stack, ip_sym + ip_ptr);

            flag = 1;
        }

        /* Reduce E/E to E */
        else if (st_ptr >= 3 &&
            strncmp(stack + st_ptr - 2, "E/E", 3) == 0)
        {
            stack[st_ptr - 2] = 'E';
            st_ptr -= 2;
            stack[st_ptr + 1] = '\0';

            printf("%s\t\t%s\t\tE->E/E\n",
                   stack, ip_sym + ip_ptr);

            flag = 1;
        }

        /* Reduce E*E to E */
        else if (st_ptr >= 3 &&
            strncmp(stack + st_ptr - 2, "E*E", 3) == 0)
        {
            stack[st_ptr - 2] = 'E';
            st_ptr -= 2;
            stack[st_ptr + 1] = '\0';

            printf("%s\t\t%s\t\tE->E*E\n",
                   stack, ip_sym + ip_ptr);

            flag = 1;
        }
    }
}


//input     a+b*a