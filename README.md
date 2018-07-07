# dproton
Dave G’s Quark Work

You can download or even cut and paste from this repository or else I can show you how to use this as a source code repository to save and share your work.

## files
* .gitignore  ~ this is just about the repository and what files _appear_ to be part of it (you can ignore)
* CMakeLists.txt  ~ recall what I said about an IDE _just invoking a bunch of services_ this file is for the maker (it calls the compiler, you will add files to this as you progress or rather the IDE will on your behalf)
* README.md  ~ that is just *this* file you can read
* data.png  ~ image file you see down in the text below
* example.dat  ~ this is just the example input file
* example.dat-post-run ~ this is as per your design after the results of a calculation appended at the end(or rather a simple sign wave)
* main.c  ~ this was based off that original code created for you.  You will replace this.  See my notes about how to incorporate multiple source files in the same project below.
* read_write.c  ~ here is the input and output code as a separate file
* read_write.h  ~ an 'h' is for header, it contains among other things prototypes of functions ... plainly put they are only the stuff that c files need to know in order to compile and generally do not have code in them themselves.

## using multiple source files
The `main.c` file is largely just an example, but you'd want to understand the following lines (prefaced by `[filename:lineno]`) in order to use `read_write` functions and even break your own work into multiple files for organization.

in `main.c`

`[main.c:11] #include "read_write.h"`

brings in the header which contains the prototype functions

not that `read_write.c` also has the identical include, so as to be referencing the same prototypes

`[read_write.c:7] #include "read_write.h"`

Including multiple source files is that simple.  You need only split out your common prototypes and common data structures to a header file and then every other source file can compile to those common definitions.  Generally don't include any code or variables in the header file.

 Here's an example, where the externally defined function is called in main.
 
 `[main.c:60] read_file(a_type, b_type, &I_pot, &n, &l, &sp, &toa, &eng, io);`
 
 its defined here
 
 `[read_write.h:13] void read_file(char* a_type, char* b_type, int* I_pot, int *n, int* l, int* sp, int* toa, double* eng, 
 FILE* in);`
 
 and implemented here
 
```
[read_write.c:23-39]void
read_file(char* a_type, char* b_type, int* I_pot, int *n, int* l, int* sp, int* toa, double* eng, FILE* in)
...
```

All you have to do if you wanted to add a parameter is just change these three places and its done!

## Example of a plot
The following is the plot of the fake data I generated ( a sine wave).  I have changed the write_file routine to print 300 lines of output at the end, which is very easy to upload to `plot.ly` in order to get the following results.

The following is my command on the terminal but you could do just as well in your text editor:

`muadib:~ chris$ echo "DATA" > example.csv && tail -n 300 example.dat >> example.csv`

All that translates to is write DATA to a new file.  Then append it with the `tail` or last lines (in this case 300) of another file.

What I did next was 1) create an account on `plot.ly`, 2) "Imported" the `example.csv` file, and 3) Scatter plotted the Y-Axis DATA, then 4) Exported the resulting plot as `data.png`



![Image data.png](https://github.com/chrisdursoorg/dproton/raw/master/data.png)




 
