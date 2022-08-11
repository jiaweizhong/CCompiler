#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>

// init global var
static void init(){
    Line = 1;
    Putback = '\n';
}

// print out a usage if started incorrectly
static void usage(char *prog){
    fprintf(stderr, "Usage: %s infile\n", prog);
    exit(1);
}

// list of pritable tokens
char *tokstr[] = {"+", "-", "*", "/", "intlit"};

// print out details of each token found
static void scanfile(){
    struct token T;
    while(scan(&T)){
        printf("Token %s", tokstr[T.token]);
        if(T.token == T_INTLIT)
            printf(", value %d", T.intvalue);

        printf("\n");
    }
}

// main(): check args and print usage, if dont have arg, open up the input file and scanfile()
void main(int argc, char *argv[]){
    if(argc !=2 )
        usage(argv[0]);

    init();

    if((Infile = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    scanfile();
    exit(0);
}

