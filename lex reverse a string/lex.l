%{
#include <stdio.h>
%}

%%
[^\n]+ {
    int i;
    for(i = yyleng - 1; i >= 0; i--)
    {
        printf("%c", yytext[i]);
    }
}
\n      { printf("\n"); }
%%

int main()
{
    printf("Enter a string: ");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}