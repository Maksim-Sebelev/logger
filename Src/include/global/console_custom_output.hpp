#pragma once

//---------------------------------------------------------------------------------------------------------------

// reset all color and font setting for console output
#define RESET_CONSOLE_OUT "\e[0m"

//---------------------------------------------------------------------------------------------------------------

// set some colors for console color output
#define WHITE             "\e[0;37m"
#define BLUE              "\e[0;34m"
#define RED               "\x1b[31m"
#define GREEN             "\x1b[32m"
#define VIOLET            "\e[0;35m"
#define CYAN              "\e[0;36m"
#define YELLOW            "\e[0;33m"
#define RESET             "\x1b[0m"

//---------------------------------------------------------------------------------------------------------------

// set some console fonts
#define BOLD              "\e[1m" // Жирный       // да я плохо знаю английский, поэтому мне нужны такие подсказочки :)
#define DIM               "\e[2m" // Тонкий
#define ITALIC            "\e[3m" // Курсив
#define UNDERLINE         "\e[4m" // Подчеркнутый
#define BLINK             "\e[5m" // Мигающий
#define REVERSE           "\e[7m" // Инверсный цвет
#define HIDDEN            "\e[8m" // Скрытый
#define STRIKETHROUGH     "\e[9m" // Зачеркнутый

//---------------------------------------------------------------------------------------------------------------

