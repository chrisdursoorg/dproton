// read_write.h
//

#ifndef READ_WRITE_H
#define READ_WRITE_H

#include <stdio.h>
#include <stdlib.h>

// read_file
//
// from a newly opend file (f) read the input parameters advancing the file to the end of input
void read_file(char* a_type, char* b_type, int* I_pot, int *n, int* l, int* sp, int* toa, double* eng, FILE* in);


// write_file
//
// concatinate to file out the resultArray
void write_file(double* resultArray, int size, FILE* out);


#endif
