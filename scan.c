#include "defs.h"
#include "data.h"
#include "decl.h"

// return the position of c in string, -1 if string not found
static int chrpos(char *s, int c){
    char *p;
    p = strchr(s, c);
    return (p ? p - s : -1);
}


// get the next char from the input file
static int next(void){
    int c;

    if(Putback) {       // use the char put back if there is one
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile);   // read from the input file
    if('\n' == c)        // increment line count
        Line++;
    return c;
}

// put back an unwanted char
static void putback(int c){
    Putback = c;
}

// skip the past input that dont need to handle, e.g. whitespace, newline
// return to the first char we want to handle
static int skip(void) {
    int c;
    c = next();
    while(c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'){
        c = next();
    }
    return (c);
}

// scan & return int value from the input file, store the int as str
static int scanint(int c){
    int k, val = 0;
    // convert each char into an int
    while(( k = chrpos("0123456789", c)) >= 0) {
        val = val * 10 + k;
        c = next();
    }
    // put back non-int char
    putback(c);
    return val;
}

// scan and return the next token found in the input
// return 1 if token valid, 0 if no tokens left
int scan(struct token *t)
{
    int c;
    // skip whitespace
    c = skip();
    switch (c){
        case EOF:
            return (0);
            break;
        case '+':
            t->token = T_PLUS;
            break;
        case '-':
            t->token = T_MINUS;
            break;
        case '*':
            t->token = T_STAR;
            break;
        case '/':
            t->token = T_SLASH;
            break;        
        default:
            // scan value in if it's a digit
            if(isdigit(c)){
                t->intvalue = scanint(c);
                t->token = T_INTLIT;
                break;
            }
            printf("Unknown char %c on line %d\n", c, Line);
            exit(1);
    }

    return (1);
}

    

