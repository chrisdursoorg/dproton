//
// Created by chris on 5/30/18.
//

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "read_write.h"

int match_help(int argc, char* argv[]){

    for(int i = 1; i < argc; ++i)
        if(0 == strcmp(argv[i], "--help")
            || 0 == strcmp(argv[i], "-h"))
            return 1;
    return 0;
}


int main(int argc, char* argv[]) {

    if(argc != 2 || match_help(argc, argv)) {
        printf("USAGE dproton IO_FILE\n\n");
        printf("read IO_FILE in the following format, calculate the RESULTS and "
               "append those to the end of the same file\n");
        printf("\nIO_FILE format (line numbers for reference only):\n\n");

        printf("0 VALUE,DATA NAME,DATA TYPE,DESCRIPTION (all are GLOBAL vars)\n"
        "1 bg,a_type,char*2,\"Type of analysis (bg or ei)\"\n"
        "2 prot,b_type,char*4,\"Baryon type\"\n"
        "3 1,I_pot,integer,\"potential type 0 to 16\"\n"
        "4 0,n,integer,\"principle quantum number\"\n"
        "5 0,l,integer,\"angular momentum quantum number\"\n"
        "6 0,sp,integer,\"spin quantum number\"\n"
        "7 0,tau,integer,\"isospin quantum number\"\n"
        "8 15.5,eng,\"long double \",\"energy parameter to vary\"\n");

        return match_help(argc, argv) ? 0 : -1;
    }

    FILE* io = fopen(argv[1], "r+w");

    if(io == NULL) {
        printf("failed to open: '%s' exiting.", argv[1]);
        return -2;
    }

    char   a_type[3] = {0};
    char   b_type[5] = {0};
    int    I_pot     = -1;
    int    n         = -1;
    int    l         = -1;
    int    sp        = -1;
    int    toa       = -1;
    double eng       =  NAN;

    read_file(a_type, b_type, &I_pot, &n, &l, &sp, &toa, &eng, io);
    
#if 1
    printf("comment this out by replacing 1 above with 0\n");
    printf("a_type:   %s\n", a_type);
    printf("b_type:   %s\n", b_type);
    printf("I_pot:    %d\n", I_pot);
    printf("n:        %d\n", n);
    printf("l:        %d\n", l);
    printf("sp:       %d\n", sp);
    printf("toa:      %d\n", toa);
    printf("eng:      %g\n", eng);
#endif


    // make up calculation
    const int c_results_size = 300;
    double resultsArray[c_results_size];
    for(int i = 0; i < c_results_size; ++i)
      resultsArray[i] = sin(M_PI*2.*i/c_results_size);

    write_file(resultsArray, c_results_size, io);

    fclose(io);

    return 0;
}

