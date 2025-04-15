#ifndef LOG_HPP
#define LOG_HPP

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include "lib/lib.hpp"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum LogColor : char
{
    White, 
    Red, 
    Green,
    Pink,
    Yellow,
    Black,
    Blue,
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void OpenLog();
void CloseLog();
void LogAdcPrint(const char* format, ...);
void LogTextColor(LogColor color);
void LogTextColorEnd();

void LogPrint(LogColor color, const char* format, ...);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define OPEN_LOG()  OpenLog()
#define CLOSE_LOG() CloseLog()

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define LOG_COLOR(color)      LogTextColor (color)
#define LOG_ADC_PRINT(...)    LogAdcPrint  (       __VA_ARGS__)
#define LOG_PRINT(color, ...) LogPrint     (color, __VA_ARGS__)

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define LOG_PLACE(color)                           LogPrint(color, "file [%s]\nline [%d]\nfunc [%s]\n",       __FILE__,       __LINE__,      __func__ )
#define LOG_PRINT_PLACE(color, file, line, func)   LogPrint(color, "file [%s]\nline [%d]\nfunc [%s]\n",         file  ,         line  ,        func   )
#define LOG_PRINT_PLACE(color, file, line, func)   LogPrint(color, "file [%s]\nline [%d]\nfunc [%s]\n", (place).file  , (place).line  , (place).func  )

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define LOG_ERROR(msg)   LogPrint(Red,    "Error: %s\n"  , msg)
#define LOG_WARNING(msg) LogPrint(Yellow, "Warning: %s\n", msg)

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define LOG_INT_ARRAY(color, array, iterator, alignment)    LogPrint(color, #array "[%"#alignment"lu] = '%d'", iterator, array[iterator])
#define LOG_CHAR_ARRAY(color, array, iterator, alignment)   LogPrint(color, #array "[%"#alignment"lu] = '%c'", iterator, array[iterator])
#define LOG_DOUBLE_ARRAY(color, array, iterator, alignment) LogPrint(color, #array "[%"#alignment"lu] = '%f'", iterator, array[iterator])
#define LOG_STRING_ARRAY(color, array, iterator, alignment) LogPrint(color, #array "[%"#alignment"lu] = '%s'", iterator, array[iterator])


#define LOG_NS() LogPrint(LogColor::White, "\n")
#define LOG_TB() LogPrint(LogColor::White, "\t")
#define LOG_SP() LogPrint(LogColor::White, " ")
#define LOG_N_SP(n) do { for (size_t log_n_spaces_counter = 0; log_n_spaces_counter < n; log_n_spaces_counter++) LogPrint(LogColor::White, " "); } while (0)

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif //LOG_HPP
