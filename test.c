#include "log.h"

char* program_name;

int main(int argc, char const *argv[])
{
    INIT();
    pNameFile=(char*)"Server.log"; //задаем название файла логов
    loger(INFO, 0, "текст сообщения %d",12345);
    return 0;
}
