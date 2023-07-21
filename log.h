#ifndef MYLOG_H
#define MYLOG_H

//Логирование проводится в четыре уровня
//DEBUG - отладочная информация
//INFO - для штатных ситуаций 
//WARNING - для штатных ситуаций, но повышенной влажности 
//(ошибки не приводящие к выходу) ошибки другой стороны, таймауты
//ERROR - для нештатных ошибок
extern char* program_name;		    // для ошибок 

#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#define INIT()			( program_name = \
						strrchr( argv[ 0 ], '/' ) ) ? \
						program_name++ : \
						( program_name = argv[ 0 ] )


//Глобальная переменная для имени файла
char NameFile[64]={0};
//указатель на имя файла логов	
char * pNameFile=NameFile;
 //создаем файловый дискриптор для логов
FILE *flog;

//уровень логово
enum _LogType
{
    DEBUG,
    INFO,
    WARNING,
    ERROR
};
typedef enum _LogType LogType;

void print_time(FILE*);
void loger(LogType , int , const char* ,...);

void loger(LogType type, int er, const char* msg,...)
{
    va_list ap; 		            //создаем указатель на неопределенное колличество параметров
	va_start(ap, msg); 	            //связываем с первым необязательным параметром
    flog = fopen(pNameFile,"a+");   //Открывает текстовый файл логирования для чтения и записи (если файл не существует то он будет создан)
    if(flog)                        //проверяем открыт ли файл
	{
    print_time(flog);
    fprintf(flog," %s |", program_name);     //печатаем название программы
    switch (type)
    {
    case DEBUG:
        fprintf(flog, " DEBUG   |");           //печатаем уровень ошибки 
        break;
    case ERROR: 
        fprintf(flog, " ERROR   |");           //печатаем уровень ошибки 

        break;
    case INFO:
        fprintf(flog, " INFO    |");           //печатаем уровень ошибки 
        break;
    case WARNING:          
        fprintf(flog, " WARNING |");           //печатаем уровень ошибки 
        break;
    default:
        break;
    }
    vfprintf(flog, msg, ap);                //печатаем сообщение
    va_end(ap);
	if (er)                                                 //если ошибка имеет номер печатаем
		fprintf(flog, "| %s (%d)", strerror(er), er);
    }
    fprintf(flog," \n");                          //переводим на новую строку
    fclose(flog);                           //закрываем файл
	flog=0;                                 //обнуляем переменную
};

void print_time(FILE *fd)
{
    // переменные для хранения компонентов даты и времени
    int hours, minutes, seconds, day, month, year;
    // `time_t` - арифметический тип времени
    time_t now;
 
    // Получить текущее время
    // `time()` возвращает текущее время системы как значение `time_t`
    time(&now);
    
    char* times;
    
    // localtime преобразует значение `time_t` в календарное время и
    // возвращает указатель на структуру `tm` с ее членами
    // заполняется соответствующими значениями
    struct tm *local = localtime(&now);
 
    hours = local->tm_hour;         // получаем часы с полуночи (0-23)
    minutes = local->tm_min;        // получить минуты, прошедшие после часа (0-59)
    seconds = local->tm_sec;        // получаем секунды, прошедшие через минуту (0-59)
 
    day = local->tm_mday;            // получить день месяца (от 1 до 31)
    month = local->tm_mon + 1;      // получить месяц года (от 0 до 11)
    year = local->tm_year + 1900;   // получаем год с 1900
 
    // печатаем местное время
    fprintf(fd,"Дата %i-%i-%i Время %02d:%02d:%02d |",day,month,year, hours, minutes, seconds);
    
    return 0;
};

#endif