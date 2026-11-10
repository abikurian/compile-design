%{
#include<stdio.h>
int line = 0;
int chars = 0;
int word = 0;
%}
%%
\n {line++;chars++;}
[ \t]+ {chars+= yyleng;}
[^\t\n ]+ {word++;chars+= yyleng;}
%%
int yywrap()
{
return 1;
}
int main()
{
printf("Enter the text: \n");
yylex();
printf(" the no of lines: %d\n",line);
printf(" the no of characters: %d\n",chars);
printf(" the no of words: %d\n",word);
return 0;
}