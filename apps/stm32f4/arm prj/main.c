#include <stm32f4xx.h>
//#include <stm32f4xx_spi.h>
#include <syniopsis.h>
#include <ff.h>
#include <diskio.h>

#include <stdio.h>
#include "file_processing_method.h"
#include "gcode.h"
#include "G_commands.h"
#include "g01.h"
//#include "g02.h"
//#include "g03.h"

// Имя файла, из которого читаем команды
#define FileName        "0:proba.txt"
// Имя файла для лога
#define FileNameLog     "0:log.txt"

GPIO_InitTypeDef  GPIO_InitStructure;
TIM_TimeBaseInitTypeDef TimerStructure;
FATFS         FileSystem;
FIL           MyFile;
FIL           MyFileLog;
char          MyBuff[100];            // Буфер под очередную строку с командой
char          MyBuffPointer;          // Указатель на текущий символ буфера
char*         MyBuffAddr;             // Указатель на очередную прочитанную строку
uint8_t       GoodCommands = 0;       // Счетчик строк с "правильными" командами
uint8_t       BadCommands = 0;        // Счетчик "битых" строк
MovementPosition        MovP;

int handler_result_svg(double dx, double dy, double dz, double f) {
  //printf("%f,%f ", dx, dy);
}

//********************************************************************************************
// Основной модуль - вход в программу
//********************************************************************************************
void main(void)
{
  DWORD EOF_Identeficator;
  // Отладочная информация
  unsigned long FileSize;               // Размер файла
  unsigned int  LineCouter = 0;         // Счетчик строк, прочитанных из файла
  DSTATUS       res;                    // Результат работы функций FatFS

  handler_g01 = &gcode_g01;
  //handler_g02 = &gcode_g02;
  //handler_g03 = &gcode_g03;
  handler_gcommand_result = &handler_result_svg;
    
  // Начальная инициализация парсера
  //Parser_Init();
  
  MotorInit();
  
  __enable_irq(); //Глобальное включение прерывания
  
  // Инициализация SPI
  init_SPI1();
  
  // Инициализация диска
  res = disk_initialize(0);
  res = f_mount(0, &FileSystem);        // монтируем
  res = f_open (&MyFile, FileName, FA_READ);       //открываем файл
  res = f_open (&MyFileLog, FileNameLog, FA_WRITE | FA_CREATE_ALWAYS);       //открываем файл лога
  FileSize = f_size(&MyFile);           // проверка размера файла (не нужна, только для отладки)
  res = f_printf( &MyFileLog, "Парсер G-кодов.\n");
  res = f_printf( &MyFileLog, "Платформа: STM32\n");
  res = f_printf( &MyFileLog, "Разработчик: Харитонюк Дмитрий\n");
  res = f_printf( &MyFileLog, "Версия: 0.1.0.0 \n\n\n");
  res = f_printf( &MyFileLog, "Лог: \n\n");
  while(1){
    // Читаем очередную строку
    MyBuffAddr = (char*)(f_gets((TCHAR*)&MyBuff, (int)sizeof(MyBuff), &MyFile));
    MyBuffPointer = 0;
    EOF_Identeficator = f_eof(&MyFile);
    //if(EOF_Identeficator) break;  // Нет строки - выходим
    if(MyBuffAddr==0) break;
    LineCouter++;
    // если строка прочитана - скармливаем её парсеру
    if(parse_start()){
      // Говно ваша команда... )
      BadCommands++;
      // Не забываем зафиксировать в логе
      res = f_printf( &MyFileLog, "Строка №%d", LineCouter);
      res = f_printf( &MyFileLog, " содержит ошибки!\n");
    }else{
      // Строка с командой успешно обработана
      GoodCommands++;
      // Не забываем зафиксировать в логе
      res = f_printf( &MyFileLog, "Строка №%d", LineCouter);
      res = f_printf( &MyFileLog, " успешно обработана.\n");
    }
  }
  res = f_close (&MyFile);      // Закрываем файл
  res = f_close (&MyFileLog);      // Закрываем файл лога
  res = f_mount(0, 0);          // Отключаем диск
  
  // Затычка
  while(1);
}
//********************************************************************************************
// Функция задержки
//********************************************************************************************
void Delay(__IO uint32_t nCount){
  while(nCount--);
}