#define CS_HIGH GPIOA->BSRRL |= GPIO_Pin_4;
#define CS_LOW  GPIOA->BSRRH |= GPIO_Pin_4;

#define GO_IDLE_STATE            0              //Программная перезагрузка   
#define SEND_IF_COND             8              //Для SDC V2 - проверка диапазона напряжений   
#define READ_SINGLE_BLOCK        17             //Чтение указанного блока данных  
#define WRITE_SINGLE_BLOCK       24             //Запись указанного блока данных
#define SD_SEND_OP_COND	         41             //Начало процесса инициализации  
#define APP_CMD			 55             //Главная команда из ACMD <n> команд
#define READ_OCR		 58             //Чтение регистра OCR