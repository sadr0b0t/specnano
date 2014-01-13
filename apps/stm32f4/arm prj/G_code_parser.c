#include <syniopsis.h>
#include <gcode.h>
#include "G_commands.h"

unsigned char   CheckCmd(void);
unsigned char   WordSynt(void);

unsigned char   CommandNum = 0; // Код команды
char            CommandT = 0;   // Тип команды (G или M)
char            Error_Status; // Флаг наличия ошибки обработчика

double x=0.0,y=0.0,z=0.0;

int             WordSyntStack;
int             WordSyntLen;
int             WordSyntnegFlag;

//********************************************************************************************
// Общая функция отлова ошибок
//********************************************************************************************
void catchError(int param, int code, char* msg){
  if(param){
    // Пока не надо
    //printf("Error Code %d: %s\n", code, msg);
    Error_Status = 1;
  }
}
//********************************************************************************************
// Вызовы имплементаций gcode команд
//********************************************************************************************
extern void GCommands(){
	switch(CommandNum)
	{
		case GCode_G01:
		    if(handler_g01)
		        catchError(handler_g01(setFlags, x, y, z, F), ERROR_CODE_G01, "");
			break;
		case GCode_G02:
			if(handler_g02)
		        catchError(handler_g02(setFlags, x, y, z, F, R), ERROR_CODE_G02, "");
			break;
		case GCode_G03:
			if(handler_g03)
		        catchError(handler_g03(setFlags, x, y, z, F, R), ERROR_CODE_G02, "");
			break;
		case GCode_G04:
			catchError(gcode_g04(setFlags), ERROR_CODE_G04, "");
			break;
		case GCode_G15:
			catchError(gcode_g15(setFlags, x, y, z), ERROR_CODE_G15, "");
			break;
		case GCode_G16:
			catchError(gcode_g16(setFlags, x, y), ERROR_CODE_G16, "");
			break;
			
		case GCode_G17:
			catchError(gcode_g17(setFlags), ERROR_CODE_G17, "");
			break;
		case GCode_G18:
			catchError(gcode_g18(setFlags), ERROR_CODE_G18, "");
			break;
		case GCode_G19:
			catchError(gcode_g19(setFlags), ERROR_CODE_G19, "");
			break;
			
		case GCode_G40:
			catchError(gcode_g40(setFlags, x, y, z, F), ERROR_CODE_G40, "");
			break;
		case GCode_G41:
			catchError(gcode_g41(setFlags, x, y, z, F, D), ERROR_CODE_G41, "");
			break;
		case GCode_G42:
			catchError(gcode_g42(setFlags, x, y, z, F, D), ERROR_CODE_G42, "");
			break;
		case GCode_G43:
			catchError(gcode_g43(setFlags, x, y, z, F, H, S, M), ERROR_CODE_G43, "");
			break;
		case GCode_G44:
			catchError(gcode_g44(setFlags, x, y, z, F, H, S, M), ERROR_CODE_G44, "");
			break;
		case GCode_G49:
			catchError(gcode_g49(setFlags, x, y, z), ERROR_CODE_G49, "");
			break;
		case GCode_G53:
			catchError(gcode_g53(setFlags), ERROR_CODE_G53 , "");
			break;
		case GCode_G70:
			catchError(gcode_g70(setFlags), ERROR_CODE_G70 , "");
			break;
		case GCode_G71:
			catchError(gcode_g71(setFlags), ERROR_CODE_G71 , "");
			break;
		case GCode_G80:
			catchError(gcode_g80(setFlags), ERROR_CODE_G80 , "");
			break;
		case GCode_G81:
			catchError(gcode_g81(setFlags, x, y, z, F, R), ERROR_CODE_G81 , "");
			break;
		case GCode_G82:
			catchError(gcode_g82(setFlags, x, y, z, F, R, P), ERROR_CODE_G82 , "");
			break;
		case GCode_G83:
			catchError(gcode_g83(setFlags, x, y, z, F, R, Q), ERROR_CODE_G83 , "");
			break;
		case GCode_G84:
			catchError(gcode_g84(setFlags, x, y, z, F, R, M), ERROR_CODE_G84 , "");
			break;
		case GCode_G90:
			catchError(gcode_g90(setFlags, x, y, z, F), ERROR_CODE_G90 , "");
			break;
		case GCode_G91:
			catchError(gcode_g91(setFlags), ERROR_CODE_G91 , "");
			break;
		case GCode_G94:
			catchError(gcode_g94(setFlags), ERROR_CODE_G94 , "");
			break;
		case GCode_G95:
			catchError(gcode_g95(setFlags), ERROR_CODE_G95 , "");
			break;
		default:
			break;
	};
}
//********************************************************************************************
// Начальная инициализация парсера
//********************************************************************************************
void Parser_Init(void){
  handler_g01 = &gcode_g01;
  handler_g02 = &gcode_g02;
  handler_g03 = &gcode_g03;
}
//********************************************************************************************
// Парсинг очередной строки
//********************************************************************************************
unsigned char Parse_Command(void){
  char  CommandChar;
  
  Error_Status = 0;
  CommandChar = fgetc();
  // Проверим тип команды
  switch(CommandChar){
  case 'G':
  case 'M':
    CommandT = CommandChar;
    if(CheckCmd())return 1;
    if(CommandT=='G'){
      GCommands();
    }else{
      MCommands();
    }
    if(Error_Status)return 1;
    break;
  default:
    // Что-то постороннее - выходим
    return 1;
    break;
  }
  // Всё хорошо - возвращаем ноль
  return 0;
}
//********************************************************************************************
//Функции грамматики лексического анализатора
//********************************************************************************************
unsigned char CheckCmd(void){
  unsigned char  MyChar;
  
  MyChar = fgetc();
  if((MyChar>'9')|(MyChar<'0'))return 1;
  CommandNum = 10*(MyChar-48);
  MyChar = fgetc();
  if((MyChar>'9')|(MyChar<'0'))return 1;
  CommandNum += MyChar-48;
  MyChar = fgetc();
  if(MyChar!=' ')return 1;
  return 0;
}
//********************************************************************************************
//Функции грамматики лексического анализатора
//********************************************************************************************
unsigned char WordSynt(void){
  char  CommandChar;
  CommandChar = fgetc();
  switch(CommandChar){
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    WordSyntStack *= 10;
    WordSyntStack += CommandChar - 48;
    WordSyntLen++;
    if(WordSynt()) return 1;
    break;
  case '-':
    WordSyntnegFlag = 1;
    if(WordSynt()) return 1;;
    break;
  case ' ':
    return 0;
  default:
    ungetc();
    return 1;
    break;
  };
  return 0;
}