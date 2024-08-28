//Compiler Design
//-----------------------------------------------
//1.Design and implement a lexical analyser  using C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int isKeyword(char buffer[])
{
char keywords[32][10] =
{"auto","break","case","char","const","co
ntinue","default",
"do","double","else","enum","extern","flo
at","for","goto",
"if","int","long","register","return","short","
signed",
"sizeof","static","struct","switch","typedef
","union",
"Unsigned","void","volatile","while"};
int i, flag = 0;
for(i = 0; i < 32; ++i){
if(strcmp(keywords[i], buffer) == 0){
flag = 1;
break;
}
}
return flag;
}
int main(){
char ch, buffer[15], operators[] =
"+-*/%=";
FILE *fp;
int i,j=0;
fp = fopen("program.txt","r");
if(fp == NULL){
printf("error while opening the file\n");
exit(0);
}

while((ch = fgetc(fp)) != EOF){
for(i = 0; i < 6; ++i){
if(ch == operators[i])
printf("%c is operator\n", ch);
}

If(isalnum(ch))
{
buffer[j++] = ch;
}
else if((ch == ' ' || ch == '\n') && (j !=
0)){
buffer[j] = '\0';
j = 0;
if(isKeyword(buffer) == 1)
printf("%s is keyword\n", buffer);
else
printf("%s is indentifier\n", buffer);
}
}
fclose(fp);
return 0;
}
//--------------------------------------------------
//2.Lex programs

//2a.Write a lex program to display the number of lines, words and characters in an input text

/*Lex Program to count numbers of lines, words, spaces and characters 

in a given statement*/
%{
#include<stdio.h>
int sc=0,wc=0,lc=0,cc=0;
%}

%%
[\n] { lc++; cc+=yyleng;}
[  \t] { sc++; cc+=yyleng;}
[^\t\n ]+ { wc++;  cc+=yyleng;}
%%

int main(int argc ,char* argv[ ])
{
	printf("Enter the input:\n");
	yylex();
	printf("The number of lines=%d\n",lc);
	printf("The number of spaces=%d\n",sc);
	printf("The number of words=%d\n",wc);
	printf("The number of characters are=%d\n",cc);
}

int yywrap( )
{
	return 1;
}
//--------------------------------------------------------
//2b.Write a LEX Program to check valid email address

%{
#include<stdio.h>
#include<stdlib.h>
int flag=0;
%}
%%
[a-z . 0-9]+@[a-z]+".com"|".in" { flag=1; }
%%
int main()
{
printf("Enter some input string:\n");
yylex();
if(flag==1)
printf("Accepted");
else
printf("Not Accepted");
}
int yywrap( )
{
	return 1;
//---------------------------------------------------------
//2c. Write a lex program to find out total number of vowels and consonants from the given input string.

/*Lex program to count the number of vowels & consonants from the given input string.*/
%{
	#include<stdio.h>
	int vow=0, con=0;
%}

%%
[ \t\n]+    ;
[aeiouAEIOU]+    {vow++;}
[^aeiouAEIOU]     {con++;}
%%

int main( )
{
	printf("Enter some input string:\n");
	yylex();
	printf("Number of vowels=%d\n",vow);
	printf("Number of consonants=%d\n",con);
}

int yywrap( )
{
	return 1;
}
//------------------------------------------------
//3.Familiarization of YACC

//3a.Generate a YACC specification to recognize a valid arithmetic expression that uses operators +, -, */ and parenthesis.

//LEX
%{

    #include "y.tab.h"

%}

%%

[a-zA-Z_][a-zA-Z_0-9]* return id;

[0-9]+(\.[0-9]*)?      return num;

[+/*]                  return op;

.                      return yytext[0];

\n                     return 0;

%%

int yywrap()

{

return 1;

}

//YACC
%{

    #include<stdio.h>

    int valid=1;   

%}

%token num id op

%%

start : id '=' s ';'

s :     id x       

      | num x       

      | '-' num x   

      | '(' s ')' x 

      ;

x :     op s        

      | '-' s       

      |             

      ;

%%

int yyerror()

{

    valid=0;

    printf("\nInvalid expression!\n");

    return 0;

}

int main()

{

    printf("\nEnter the expression:\n");

    yyparse();

    if(valid)

    {

        printf("\nValid expression!\n");

    }

}
//------------------------------------------
//3b.Generate a YACC specification to recognize a valid identifier which starts with a letter followed by any number of letters or digits.

//LEX
%{

    #include "y.tab.h"

%}

%%

[a-zA-Z_][a-zA-Z_0-9]* return letter;

[0-9]                       return digit;

.                      return yytext[0];

\n                     return 0;

%%

int yywrap()

{

return 1;

//YACC
%{

    #include<stdio.h>

    int valid=1;

%}

%token digit letter

%%

start : letter s

s :     letter s

      | digit s

      |

      ;

%%

int yyerror()

{

    printf("\nIts not a identifier!\n");

    valid=0;

    return 0;

}

int main()

{

    printf("\nEnter a name to tested for identifier ");

    yyparse();

    if(valid)

    {

        printf("\nIt is a identifier!\n");

    }

}

//-----------------------------------------------------------------------
//4.Implementation of Calculator using LEX and YACC

//LEX
%{

#include<stdio.h>

#include "y.tab.h"

extern int yylval;

%}



%%

[0-9]+ {

          yylval=atoi(yytext);

          return NUMBER;

       }

[\t] ;

[\n] return 0;

. return yytext[0];

%%

int yywrap()

{

return 1;

}

//YACC

%{

    #include<stdio.h>

    int flag=0;

   

%}

%token NUMBER



%left '+' '-'

%left '*' '/' '%'

%left '(' ')'

%%

ArithmeticExpression: E{

         printf("\nResult=%d\n",$$);

         return 0;

        };

E:E'+'E {$$=$1+$3;}

 |E'-'E {$$=$1-$3;}

 |E'*'E {$$=$1*$3;}

 |E'/'E {$$=$1/$3;}

 |E'%'E {$$=$1%$3;}

 |'('E')' {$$=$2;}

 | NUMBER {$$=$1;}

;

%%



void main()

{

   printf("\nEnter Any Arithmetic Expression which can have operations Addition, Subtraction, Multiplication, Divison, Modulus and Round brackets:\n");

   yyparse();

  if(flag==0)

   printf("\nEntered arithmetic expression is Valid\n\n");

 

}

void yyerror()

{

   printf("\nEntered arithmetic expression is Invalid\n\n");

   flag=1;

}
//-----------------------------------------------------------------------
//5.Write a program to convert NFA to DFA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int states;
int inputs;
int transts[10][10][10];
char nfa[10][10][10];
char dfa[10][10][10];
void main()
{
printf("Enter no. of states: ");
scanf("%d", &states);
printf("Enter no. of input symbols: ");
scanf("%d", &inputs);
for (int i = 0; i < inputs; i++)
{
printf("Enter NFA matrix for input
%c:\n", i + 'a');
for (int j = 0; j < states; j++)
for (int k = 0; k < states; k++)
scanf("%d", &transts[i][j][k]);
}
int row = 0;
char str[10];
for (int i = 0; i < states; i++)
for (int j = 0; j < states; j++)
for (int k = 0; k < inputs; k++)
if (transts[k][i][j] == 1)
{
sprintf(str, "q%d", j);
if (strcmp(nfa[i][k], str) != 0)
strcat(nfa[i][k], str);
row++;
}
char queue[20][10];
int front = 0;
int rear = 0;
int rows = 0;
for (int i = 0; i < 20; i++)
strcpy(queue[i], "");
strcpy(queue[rear], "q0");
rear++;
strcpy(dfa[rows][0], "q0");

while (strcmp(queue[front], "") != 0)
{
char newstate[20];
for (int i = 0; i < 20; i++)
strcpy(newstate, "");
for (int j = 0; j < inputs; j++)
{
for (int i = 0; i < 20; i++)
strcpy(newstate, "");
for (int i = 1; i < strlen(queue[front]); i
+= 2)

if (isdigit(queue[front][i]))
{
int n = queue[front][i] - '0';
for (int l = 1; l <
strlen(nfa[n][j]); l += 2)
{
int num1;
if (isdigit(nfa[n][j][l]))
num1 = nfa[n][j][l] - '0';
int flag2 = 0;
int num2;
for (int m = 1; m <
strlen(newstate); m += 2)
if
(isdigit(newstate[m]))
{
num2 = newstate[m] -

'0';

if (num1 == num2)
flag2 = 1;
}
if (flag2 == 0)
{
char temp[20];
sprintf(temp, "q%d",

num1);

strcat(newstate,

temp);
}
}
}
int tempst[20];
int tempin = 0;

for (int d = 0; d < strlen(newstate);
d++)

if (isdigit(newstate[d]))
tempst[tempin++] =

newstate[d] - '0';
for (int q = 0; q < tempin; q++)
for (int r = 0; r < tempin - q -

1; r++)

if (tempst[r] > tempst[r + 1])
{
int swap = tempst[r];
tempst[r] = tempst[r + 1];
tempst[r + 1] = swap;
}
char tempstr[20];
strcpy(newstate, "");
for (int q = 0; q < tempin; q++)
{
sprintf(tempstr, "q%d",

tempst[q]);

strcat(newstate, tempstr);
}
int flag = 0;
for (int a = 0; a < rear; a++)
if (strcmp(queue[a],

newstate) == 0)
flag = 1;
if (flag == 0)
{
strcpy(queue[rear],

newstate);

rear++;
strcpy(dfa[rows][j + 1],

newstate);

rows++;
strcpy(dfa[rows][0],

newstate);
}
strcpy(dfa[rows][j + 1], newstate);
}
front++;
}
printf("\nDFA:\n");
printf("%s|", "States");

for (int i = 0; i < inputs; i++)
printf("Input %c\t|", 'a' + i);
printf("\n");
printf("\n");
for (int i = 0; i <= rows; i++)
{
for (int j = 0; j < inputs + 1; j++)
printf("%s\t|", dfa[i][j]);
printf("\n");
}
}
//----------------------------------------------------
//6.Write a program to find First of any given grammar

#include <stdio.h>
#include <ctype.h>

void FIRST(char[], char);
void addToResultSet(char[], char);
int numOfProductions;
char productionSet[10][10];
void main()
{
	int i, j;
	char choice;
	char c, g;
	char result[20];
	printf("No of productions :");
	scanf(" %d", &numOfProductions);
	for (i = 0; i < numOfProductions; i++) // read production string eg: E=E+T
	{
    	printf("Enter production %d : ", i + 1);
    	scanf(" %s", productionSet[i]); // contains set of all productions
	}
	printf("FIRST OF : \n");
	for (i = 0; i < numOfProductions; i++)
	{
    	c = productionSet[i][0];
    	FIRST(result, c); // Compute FIRST; Get Answer in 'result' array
    	if (productionSet[i][2] != '$')
    	{
        	printf("(%c) ={", c);
        	for (j = 0; result[j] != '\0'; j++)
        	{
            	printf("%c ", result[j]);
        	}
        	printf("}\n");
    	}
	}
}
/*
Function FIRST:
Compute the elements in FIRST(c) and write them in Result Array.
*/
void FIRST(char *Result, char c)
{
	int i, j, k;
	char subResult[20];
	int foundEpsilon;
	subResult[0] = '\0';
	Result[0] = '\0';
	// If x is terminal, FIRST(x) = {x}.
	if (!(isupper(c)))
	{
    	addToResultSet(Result, c);
    	return;
	}
	// If X is non terminal Read each production
	for (i = 0; i < numOfProductions; i++)
	{
    	// Find production with X as LHS
    	if (productionSet[i][0] == c)
    	{
        	// If X → ε is a production, then add ε to FIRST(X).
        	if (productionSet[i][2] == '$')
            	addToResultSet(Result, '$');
        	// If X is a non-terminal, and X → Y1 Y2 … Yk is a production
        	else
        	{
            	j = 2;
            	while (productionSet[i][j] != '\0')
            	{
                	foundEpsilon = 0;
                	FIRST(subResult, productionSet[i][j]);
                	for (k = 0; subResult[k] != '\0'; k++)
                    	if (subResult[k] == '$' && productionSet[i][j+1]!='\0')
                    	{
                        	foundEpsilon = 1;
                    	}
                    	else
                    	addToResultSet(Result, subResult[k]);
                	// No ε found, no need to check next element
                	if (!foundEpsilon)
                    	break;
                	j++;
            	}
        	}
    	}
	}
	return;
}
//This code avoids multiple inclusion of elements
void addToResultSet(char Result[], char val)
{
	int k;
	for (k = 0; Result[k] != '\0'; k++)
    	if (Result[k] == val)
        	return;
	Result[k] = val;
	Result[k + 1] = '\0';
}
//-----------------------------------------------------------
//7.Design and implement a recursive descent parser for a given grammar.

/*
Recursive descent parser for a given grammar
Grammar -
S -> cAd
A -> a | ab

*/
#include <stdio.h>
#include <stdlib.h>

char input[10];
int i = 0, accept = 0;

void S();
void A();

void S()
{
    if (input[i] == 'c')
    {
        i++;
        A();
        if (input[i] == 'd' && input[i + 1] == '\0')
        {
            i++;
            accept = 1;
        }
    }
}

void A()
{
    if (input[i] == 'a')
    {
        i++;
        if (input[i] == 'b')
        {
         i++;
        }
    }
    else
    {
        printf("Rejected.\n");
        exit(0);
    }
}


void main()
{
    printf("Enter input string: ");
    scanf("%s", input);

    S();
    
    if (accept == 1)
        printf("Accepted.\n");
    else
        printf("Rejected.\n");
}
//---------------------------------------------------------
//8.Construct a Shift Reduce Parser for a given language.

/*Sample input for grammar:
S -> (L) | a
L -> L,S | S
[THE PRODUCTIONS MUST BE ENTERED WITHOUT ANY SPACES]

Enter no. of productions: 4
Enter the productions:
S=(L)
S=a  
L=L,S
L=S
Enter the input string: (a,(a,a))
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char productions[10][20], input[20], stack[20];
int input_ptr, stack_top, no_of_productions;

void main()
{
    input_ptr = 0;
    stack_top = -1;

    printf("Enter no. of productions: ");
    scanf("%d", &no_of_productions);
    printf("Enter the productions:\n");
    for (int i = 0; i < no_of_productions; i++)
        scanf("%s", productions[i]);
    printf("Enter the input string: ");
    scanf("%s", input);
    printf("%-20s%-20s%-20s\n", "Stack", "Input", "Action");

    // The loop runs only if either reduction can be done with stack content, or shifting can be done with input
    int shift, reduce;
    do
    {
        // Variables shift and reduce is set to 1 if any of the operations can be done
        shift = 0;
        reduce = 1;

        // Accept the string if bottom of the stack contains only the starting symbol and the input buffer is empty
        if (stack[0] == productions[0][0] && strlen(stack) == 1 && input[strlen(input) - 1] == ' ')
        {
            printf("String accepted.\n");
            exit(0);
        }

        int i;
        for (i = 0; i < no_of_productions; i++)
        {
            reduce = 1;
           
            /*
            Loop to check if the stack contents match the RHS of any production
            Stack iterations: Starting point - stack top; Ending point - bottom of the stack (index 0) (worst case)
            The stack iterations run as long as there are enough characters to process in the RHS of the production
            k >= 2: The RHS of the production begins at index 2
            After match, variable i will contain the index of the production
            */
            for (int j = stack_top, k = strlen(productions[i]) - 1; j >= 0, k >= 2; j--, k--)
            {
                // Character mismatch; no reduction
                if (stack[j] != productions[i][k])
                    reduce = 0;
            }

            if (reduce == 1)
                break;
        }

        if (reduce == 1)
        {
            int j, k;

            // Move to the index of the first symbol in the set of matched symbols in the stack
            for (j = stack_top, k = strlen(productions[i]) - 1; j >= 0, k >= 2; j--, k--)
                ;

            // Replace the first symbol with the starting symbol of the production
            // j + 1: After running the above loop, j points to one less than the postion we need to access
            stack[j + 1] = productions[i][0];

            // Replace the next character to \0 to mark the end of the stack (To avoid unnecessary code for stack content deletion)
            stack[j + 2] = '\0';

            // Decrement stack top with the number of characters reduced
            // -2: First two characters of the production are not processed (Starting symbol of the production and '=')
            // -1: To match zero-indexing
            stack_top -= strlen(productions[i]) - 2 - 1;

            printf("%-20s%-20sReduce to %s\n", stack, input, productions[i]);
        }
        else
        {
            if (input[input_ptr] != '\0')
            {
                shift = 1;
                stack_top++;
                stack[stack_top] = input[input_ptr];
                stack[stack_top + 1] = '\0';
                input[input_ptr] = ' ';
                input_ptr++;
                printf("%-20s%-20s%-20s\n", stack, input, "Shift");
            }
        }
    } while (shift == 1 || reduce == 1);

    printf("String rejected.\n");
}
//------------------------------------------------------------------------------
//9. Write a program to perform constant propagation

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
// The values of number assignment statements are stored in this array
// If the statement is a=50, the number 50 will be stored at index 97 (ASCII value of 'a')
int values[150];
void main()
{
int no_of_lines;
char lines[20][20];
printf("Enter no. of lines of the program: ");
scanf("%d", &no_of_lines);
printf("Enter the program:\n");
for (int i = 0; i < no_of_lines; i++)
scanf("%s", lines[i]);
for (int i = 0; i < no_of_lines; i++)
{
// Check if line is a number assignment statement (eg:- a=2); flag is set to 1 if not
int flag = 0;
for (int j = 2; j < strlen(lines[i]); j++)
{
if (isalpha(lines[i][j]))
flag = 1;
}
// Extract and store the number from the line
// j = 2: RHS of the expression begins at index 2
if (flag == 0)
{
int j;
char temp[20];
for (j = 2; j < strlen(lines[i]); j++)
temp[j - 2] = lines[i][j];
temp[j - 2] = '\0';
int value = atoi(temp);
values[lines[i][0]] = value;
}
// Arithmetic expression (eg:- b=a+c)
else
{
int operand1, operand2;
// Check if first operand is a variable or a constant
if (isalpha(lines[i][2]))
operand1 = values[lines[i][2]];
// Extract the constant from the line
else

{
int j;
char temp[20];
for (j = 2; isdigit(lines[i][j]); j++)
temp[j - 2] = lines[i][j];
temp[j - 2] = '\0';
operand1 = atoi(temp);
}
// Loop until the operator is found
int j;
char operator;
for (j = 2; isalnum(lines[i][j]); j++)
;
operator= lines[i][j];
// Check if second operand is a variable or a constant
if (isalpha(lines[i][j + 1]))
operand2 = values[lines[i][j + 1]];
// Extract the constant from the line
else
{
int k, index = 0;
char temp[20];
for (k = j + 1; isdigit(lines[i][k]); k++)
temp[index++] = lines[i][k];
temp[index++] = '\0';
operand2 = atoi(temp);
}
printf("Line %d after constant propagation: %c=%d%c%d\n", i + 1, lines[i][0], operand1,
operator, operand2);
switch (operator)
{
case '+':
printf("Result: %d\n", operand1 + operand2);
values[lines[i][0]] = operand1 + operand2;
break;
case '-':
printf("Result: %d\n", operand1 - operand2);
values[lines[i][0]] = operand1 - operand2;
break;
case '*':
printf("Result: %d\n", operand1 * operand2);
values[lines[i][0]] = operand1 * operand2;
break;
case '/':
printf("Result: %d\n", operand1 / operand2);
values[lines[i][0]] = operand1 / operand2;
break;
}
}
}
}
//--------------------------------------------------------------
//10. Implement Intermediate code generation for simple expressions.

#include <stdio.h>
#include <string.h>
char exprsn[20];
char temp_var = 'Z';
void main()
{
printf("Enter the expression: ");
scanf("%s", exprsn);
printf("Intermediate code:\n");
while (strlen(exprsn) > 3)
{
int flag = 0;
if (flag != 1)
{
for (int i = 0; i < strlen(exprsn); i++)
{
if (exprsn[i] == '/' || exprsn[i] == '*')
{
printf("%c=%c%c%c\n", temp_var, exprsn[i - 1], exprsn[i], exprsn[i + 1]);
exprsn[i - 1] = temp_var;
temp_var--;
for (int j = i; exprsn[j] != '\0'; j++)
exprsn[j] = exprsn[j + 2];
flag = 1;
break;
}
}
}
if (flag != 1)
{
for (int i = 0; i < strlen(exprsn); i++)
{
if (exprsn[i] == '+' || exprsn[i] == '-')
{
printf("%c=%c%c%c\n", temp_var, exprsn[i - 1], exprsn[i], exprsn[i + 1]);
exprsn[i - 1] = temp_var;
temp_var--;
for (int j = i; exprsn[j] != '\0'; j++)
exprsn[j] = exprsn[j + 2];
flag = 1;
break;
}
}
}
}
printf("%s\n", exprsn);
}

//------------------------------------------------------------------------
//11. Implement the back end of the compiler which takes the three address code and produces the 8086 assembly language instructions. The target assembly instructions can be simple move, add, sub, jump etc

#include<stdio.h>
#include<string.h>
void main(){
char icode[10][30],str[20],opr[10];
int i=0;
printf("Enter the set of intermediate codes:\n");
do
{
scanf("%s",icode[i]);
}
while(strcmp(icode[i++],"exit")!=0);
printf("\nTARGET CODE GENERATION\n");
i=0;
do{
strcpy(str,icode[i]);
switch(str[3]){
case '+':strcpy(opr,"ADD");
break;
case '-':strcpy(opr,"SUB");
break;
case '/':strcpy(opr,"MUL");
break;
}
printf("MOV %cR%d\n",str[2],i);
printf("%s%c,R%d\n",opr,str[4],i);
printf("MOV R %d,%c\n",i,str[0]); }
while(strcmp(icode[++i],"exit")!=0);
}
-----------------------------------------------------------------------------------------------



