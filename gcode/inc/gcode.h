#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define GCode_G00 0
#define GCode_G01 1
#define GCode_G02 2
#define GCode_G03 3
#define GCode_G04 4
#define GCode_G15 15
#define GCode_G16 16
#define GCode_G17 17
#define GCode_G18 18
#define GCode_G19 19
#define GCode_G40 40
#define GCode_G41 41
#define GCode_G42 42
#define GCode_G43 43
#define GCode_G44 44
#define GCode_G49 49
#define GCode_G53 53
#define GCode_G70 70
#define GCode_G71 71
#define GCode_G80 80
#define GCode_G81 81
#define GCode_G82 82
#define GCode_G83 83
#define GCode_G84 84
#define GCode_G90 90
#define GCode_G91 91
#define GCode_G94 94
#define GCode_G95 95

#define GCode_M01 1
#define GCode_M02 2
#define GCode_M03 3

/* Error codes */
#define ERROR_CODE_G01 1
#define ERROR_CODE_G02 2
#define ERROR_CODE_G03 3
#define ERROR_CODE_G04 4
#define ERROR_CODE_G15 15
#define ERROR_CODE_G16 16
#define ERROR_CODE_G17 17
#define ERROR_CODE_G18 18
#define ERROR_CODE_G19 19
#define ERROR_CODE_G40 40
#define ERROR_CODE_G41 41
#define ERROR_CODE_G42 42
#define ERROR_CODE_G43 43
#define ERROR_CODE_G44 44
#define ERROR_CODE_G49 49
#define ERROR_CODE_G53 53
#define ERROR_CODE_G70 70
#define ERROR_CODE_G71 71
#define ERROR_CODE_G80 80
#define ERROR_CODE_G81 81
#define ERROR_CODE_G82 82
#define ERROR_CODE_G83 83
#define ERROR_CODE_G84 84
#define ERROR_CODE_G90 90
#define ERROR_CODE_G91 91
#define ERROR_CODE_G94 94
#define ERROR_CODE_G95 95

void catchError(int, int, char*);
extern void GCommands();
extern void MCommands();
extern int W();
extern double A();
extern void T();
extern int E();
extern int parse_start(FILE*);

/* G-commands handler delegates */
int (*handler_g01)(int*, double, double, double, double);
int (*handler_g02)(int*, double, double, double, double, double);

/* Result handler delegate for all g-commands */
int (*handler_gcommand_result)(double dx, double dy, double dz, double f);
