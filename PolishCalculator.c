/////////////////////////
//  Polish Calculator
//  usage: number otherNumber Operator
//  EX: 2-3 == 2 3 -
/////////////////////////
//  4.4-4.6

#define MAXOPER 100
#define NUMBER '0'

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Stack and stack index
int sp = 0;
double val[MAXOPER];

//Helper Functons
int getch(void);
void ungetch(int);
int getOper(char []);
double pop(void);
void push(double);

int main() {

    int type;
    double oper;
    char s[MAXOPER];

    while ( (type = getOper(s) ) != EOF ) {
        switch(type) {
            case NUMBER:
                push( atof(s) );    /* atof = char to double */
                break;
            case '+':
                push( pop() + pop() );
                break;
            case '*':
                push( pop() * pop() );
                break;
            case '-':
                oper = pop();
                push( pop() - oper );
                break;
            case '/':
                oper = pop();
                if( oper > 0.0 ){
                    push( pop() / oper );
                } else {
                    printf("error: zero divisor\n");
                }
                break;
            case '%':
                oper = pop();
                if( oper > 0.0 ){
                    push( fmod(pop(), oper) );
                } else {
                    printf("error: zero divisor\n");
                }
                break;
            case '\n':
                printf( "\t%.8g\n", pop() );
                break;
            default:
                printf( "error: unknown command %s\n", s );
                break;
        }
    }
    return 0;
}

/*      push : internal stack       */
void push( double f ) {
    if ( sp < MAXOPER )
        val[sp++] = f;
    else 
        printf( "error: stack full, cannot push %g\n", f );
}
/*      pop : internal stack        */
double pop( void ) {
    if ( sp > 0 )
        return val[--sp];
    else 
        printf( "error: stack empty\n");
        return 0.0;
}

/*      getch : getchar with a buffer for ungetch       */
/*      ungetch : store the last getchar read so it is not skipped       */
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return ( bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if ( bufp >= BUFSIZE )
    printf("ingetch: too many characters\n");
    else
        buf[bufp++] = c;    
}

/*      getOper : returns last input (sign, or number)      */
int getOper( char s[] ) {
    int i, c;
    while ( (s[0] = c = getch()) == ' ' || c == '\t' )
        ;
    s[1] = '\0';
    i = 0;
    if( !isdigit(c) && c != '.' && c != '-' ) 
        return c;
    if ( c == '-' ) {
        if ( isdigit(c = getch() || c == '.' ) ) 
            s[++i] = c;
        else 
            if ( c != EOF ) {
                ungetch(c);
                return '-';
            }
    }
    if ( isdigit(c) )
        while ( isdigit( s[++i] = c = getch() ) )
            ;
    if ( c == '.' )
        while ( isdigit( s[++i] = c = getch() ) )
            ;
    s[i] = '0';
    if ( c != EOF )
        ungetch(c);
    return NUMBER; 
}
