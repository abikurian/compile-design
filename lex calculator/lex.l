%{
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double a,b;
char op;
%}
%%
[0-9]+(\.[0-9]+)? {if(!op) a=atof(yytext);
else b=atof(yytext);}
"+"|"-"|"*"|"/"|"^" {op= yytext[0];}
\n {
printf("Result = ");
if(op=='+') printf("%.2f\n",a+b);
if(op=='-') printf("%.2f\n",a-b);
if(op=='*') printf("%.2f\n",a*b);
if(op=='/') printf("%.2f\n",a/b);
if(op=='^') printf("%.2f\n",pow(a,b));
op = 0;
}
[ \t] ;
%%
int yywrap()
{
return 1;
}
int main()
{
printf("Enter the numbers:");
yylex();
return 0;
}
//to run
//lex filename.l
//gcc lex.yy.c -o a.out -ll -lm
//./a.out