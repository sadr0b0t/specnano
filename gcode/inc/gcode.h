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

void catchError(int, int);
extern void GCommands();
extern void MCommands();
extern int W();
extern double A();
extern void T();
extern int E();
extern void parse_start(FILE*);
