// read_write.c
//
// input output code

#include <string.h>

#include "read_write.h"

int lineno = 0;

// read_cstr, read_int, read_double
//
// wraps getline to obtain a string of 'size', an int or a double
// respectively from the beginning of each line from opened file f
// as with getline *line_buf should be initialized to NULL and freed when
// all done.
//
// prints and exits on error
void   read_cstr(char *string, char **line_buf, FILE *f, int size);
int    read_int (char **line_buf, FILE *f);
double read_double(char** line_buf, FILE*f);

void
read_file(char* a_type, char* b_type, int* I_pot, int *n, int* l, int* sp, int* toa, double* eng, FILE* in){

  char* buf = NULL;
  
  read_cstr           (NULL,   &buf, in, 0);  // skip line 1
  read_cstr           (a_type, &buf, in, 2);
  read_cstr           (b_type, &buf, in, 4);
  *I_pot = read_int   (&buf, in);
  *n     = read_int   (&buf, in);
  *l     = read_int   (&buf, in);
  *sp    = read_int   (&buf, in);
  *toa   = read_int   (&buf, in);
  *eng   = read_double(&buf, in);

  free(buf);
}

void write_file(double* resultArray, int size, FILE* out){

  int r = fseek(out, 0, SEEK_END);
  if(r){
    printf("failed seeking to end of file ... exiting\n");
    exit(-6);
  }
  r = fprintf(out, "\n\nRESULTS\n");
  ++lineno;
  if(r < 0){
    printf("error writing result header (line %d) to file ... exiting\n", lineno);
    exit(-5);
  }
  
  for(int i = 0; i < size; ++i){
    int r = fprintf(out, "%g\n", resultArray[i]);
    ++lineno;
    if(r < 0 ){
      printf("error writing data (line %d) to file ... exiting\n", lineno);
      exit(-4);
    }
  }
  fflush(out);
}

int read_int(char **line_buf, FILE *f) {
    size_t linesize = 0;
    linesize = getline(line_buf, &linesize, f);

    if(linesize < 0){
        printf("failed reading line %d, exiting.", lineno);
        exit(-3);
    }

    ++lineno;
    return strtol(*line_buf, NULL, 10);
}

void read_cstr(char *result, char **line_buf, FILE *f, int size) {
    size_t linesize = 0;
    linesize = getline(line_buf, &linesize, f);

    if(linesize < size) {
        printf("failed reading line %d, exiting.", lineno);
        exit(-1);
    }
    ++lineno;
    if(result)
        memcpy(result,*line_buf, size);
}

double read_double(char** line_buf, FILE *f) {
    size_t linesize = 0;
    linesize = getline(line_buf, &linesize, f);

    if(linesize < 0){
        printf("failed reading line %d, exiting.", lineno);
        exit(-2);
    }

    ++lineno;
    return strtod(*line_buf, NULL);
}
