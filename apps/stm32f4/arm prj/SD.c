#include <stm32f4xx.h>
#include <stm32f4xx_spi.h>
#include <syniopsis.h>
#include <SD.h>

uint8_t  SDHC;
uint8_t  SD_Buff[512];

//********************************************************************************************
//function	 Возрат указателя на один символ в буферной строке
//return	 прочитанный символ
//********************************************************************************************
void ungetc(void){
  // Декрентируем указатель
  MyBuffPointer--;
}
//********************************************************************************************
//function	 Чтение очередного символа из буферной строки
//return	 прочитанный символ
//********************************************************************************************
char fgetc(void){
  char  ReadedChar;
  ReadedChar = MyBuff[MyBuffPointer];
  // Икрементируем указатель
  MyBuffPointer++;
  return ReadedChar;
}
//********************************************************************************************
//function	 ожидание осфобождения SD карты
//return	 0 - всё хорошо
//********************************************************************************************
uint8_t SD_WaitFree(){
  uint16_t    wait=0;

  CS_LOW;
  while(!MySPI_Read())               //пока карта занята,она выдает ноль
    if(wait++ > 0xfffe){CS_HIGH; return 0xff;}
  CS_HIGH;
  return 0;
}
//********************************************************************************************
//function	 запись выбранного сектора SD
//аrguments	 номер сектора, указатель на данные для записи
//return	 0 - сектор записан успешно
//********************************************************************************************
uint8_t SD_WriteSector(uint32_t BlockNumb,uint8_t *buff){
  uint8_t     response;
  uint16_t    i,wait=0;
 
  //послать команду "запись одного блока" с указанием его номера
  if( SD_sendCommand(WRITE_SINGLE_BLOCK, BlockNumb)) return 1;
 
  CS_LOW;
  MySPI_Send(0xfe);    
 
  //записать буфер сектора в карту
  for(i=0; i<512; i++) MySPI_Send(*buff++);
 
  MySPI_Send(0xff);                //читаем 2 байта CRC без его проверки
  MySPI_Send(0xff);
 
  response = MySPI_Read();
 
  if( (response & 0x1f) != 0x05) //если ошибка при приеме данных картой
  { CS_HIGH; return 1; }
 
  //ожидаем окончание записи блока данных
  while(!MySPI_Read())             //пока карта занята,она выдает ноль
  if(wait++ > 0xfffe){CS_HIGH; return 1;}
 
  CS_HIGH;
  MySPI_Send(0xff);   
  CS_LOW;         
 
  while(!MySPI_Read())               //пока карта занята,она выдает ноль
  if(wait++ > 0xfffe){CS_HIGH; return 1;}
  CS_HIGH;
 
  return 0;
}
//********************************************************************************************
//function	 чтение выбранного сектора SD
//аrguments	 номер сектора,указатель на буфер размером 512 байт
//return	 0 - сектор прочитан успешно
//********************************************************************************************
uint8_t SD_ReadSector(uint32_t BlockNumb,uint8_t *buff){ 
  uint16_t i=0;
 
  //послать команду "чтение одного блока" с указанием его номера
  if(SD_sendCommand(READ_SINGLE_BLOCK, BlockNumb)) return 1;  
  CS_LOW;
  //ожидание  маркера данных
  while(MySPI_Read() != 0xfe)                
  if(i++ > 0xfffe) {CS_HIGH; return 1;}       
 
  //чтение 512 байт	выбранного сектора
  for(i=0; i<512; i++) *buff++ = MySPI_Read();
 
  MySPI_Read(); 
  MySPI_Read(); 
  MySPI_Read(); 
 
  CS_HIGH;
 
  return 0;
}
//********************************************************************************************
//function	 инициализация карты памяти
//return	 0 - карта инициализирована
//********************************************************************************************
uint8_t SD_init(void){
  uint8_t   i;
  uint8_t   response;
  uint8_t   SD_version = 2;	          //по умолчанию версия SD = 2
  uint16_t  retry = 0 ;
 
  for(i=0;i<10;i++) MySPI_Read();      //послать свыше 74 единиц   
 
  //выполним программный сброс карты
  while(SD_sendCommand(GO_IDLE_STATE, 0)!=0x01)
    if(retry++>0x20)  return 1;
  MySPI_Read();
  MySPI_Read();
 
  retry = 0;                                     
  while(SD_sendCommand(SEND_IF_COND,0x000001AA)!=0x01)
  { 
    if(retry++>0xfe) 
    { 
      SD_version = 1;
      break;
    } 
  }
 
  retry = 0;                                     
  do
  {
    response = SD_sendCommand(APP_CMD,0); 
    response = SD_sendCommand(SD_SEND_OP_COND,0x40000000);
    retry++;
    if(retry>0xffe) return 1;                     
  }while(response != 0x00);                      
 
 
  //читаем регистр OCR, чтобы определить тип карты
  retry = 0;
  SDHC = 0;
  if (SD_version == 2)
  { 
    while(SD_sendCommand(READ_OCR,0)!=0x00)
	 if(retry++>0xfe)  break;
  }
 
  return 0; 
}
//********************************************************************************************
//function	 посылка команды в SD
//Arguments	 команда и ее аргумент
//return	 0xff - нет ответа
//********************************************************************************************
uint8_t SD_sendCommand(uint8_t cmd, uint32_t arg){
  uint8_t response, wait=0, tmp;     
 
  //для карт памяти SD выполнить корекцию адреса, т.к. для них адресация побайтная 
  if(SDHC == 0){
    if(cmd == READ_SINGLE_BLOCK || cmd == WRITE_SINGLE_BLOCK )arg = arg << 9;
  }
  //для SDHC корекцию адреса блока выполнять не нужно(постраничная адресация)	
 
  CS_LOW;
 
  //передать код команды и ее аргумент
  MySPI_Send(cmd | 0x40);
  MySPI_Send(arg>>24);
  MySPI_Send(arg>>16);
  MySPI_Send(arg>>8);
  MySPI_Send(arg);
 
  //передать CRC (учитываем только для двух команд)
  if(cmd == SEND_IF_COND){
    MySPI_Send(0x87);
  }else{
    MySPI_Send(0x95);
  }
 
  //ожидаем ответ
  while((response = MySPI_Read()) == 0xff)
  {
    if(wait++ > 0xfe) break;                //таймаут, не получили ответ на команду
  }
 
  //проверка ответа если посылалась команда READ_OCR
  if(response == 0x00 && cmd == 58)     
  {
    tmp = MySPI_Read();                      //прочитат один байт регистра OCR            
    if(tmp & 0x40) SDHC = 1;               //обнаружена карта SDHC 
    else           SDHC = 0;               //обнаружена карта SD
    //прочитать три оставшихся байта регистра OCR
    MySPI_Read(); 
    MySPI_Read(); 
    MySPI_Read(); 
  }
 
  MySPI_Read();
 
  CS_HIGH; 
 
  return response;
}
//********************************************************************************************
// Приём одного байта данных
//********************************************************************************************
uint8_t MySPI_Read(){
  return MySPI_Send(0xff);
}
//********************************************************************************************
// Отправка/приём одного байта данных
//********************************************************************************************
uint8_t MySPI_Send(uint8_t data){
  SPI1->DR = data; // запишем передаваемые данные в регистр данных SPI
  while( !(SPI1->SR & SPI_I2S_FLAG_TXE) ); // ждём завершения передачи
  while( !(SPI1->SR & SPI_I2S_FLAG_RXNE) ); // ждём завершения приёма
  while( SPI1->SR & SPI_I2S_FLAG_BSY ); // ждём освобождения SPI
  return SPI1->DR; // возвращаем принятые данные из регистра данных SPI
}
//********************************************************************************************
// Инициализация SPI
//********************************************************************************************
void init_SPI1(void){
  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;

  // Включаем тактирование для порта A
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* пины, используемые SPI1
  * PA5 = SCK
  * PA6 = MISO
  * PA7 = MOSI
  */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  // подключим выводы SPI1 к альтернативной функции пинов
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

  /* Для выборки кристала (Chip Select) используем пин 4 порта A (PA4)*/
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  CS_HIGH;      // установим CS в 1

  // Включим тактирование модуля SPI
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

  /* сконфигурируем SPI1 в Mode 0 
  * CPOL = 0 --> шина тактирования в состоянии 0 в режиме покоя
  * CPHA = 0 --> выборка данных по переднему фронту
  */
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // полнодуплексный режим, раздельные линии MOSI и MISO
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;     // работа в режиме мастера, вывод NSS всегда 1
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // 8-и битный пакет данных (может быть 16-и битным)
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;        // шина тактирования в состоянии 0 в режиме покоя
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;      // выборка данных по переднему фронту
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set; // внутреннее управление NSS, подтянуть внутри к 1
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128; // частота SPI = частота APB2 / 4
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// старший бит вперед
  SPI_Init(SPI1, &SPI_InitStruct); 

  SPI_Cmd(SPI1, ENABLE); // включить SPI1
}