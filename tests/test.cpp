#include <iostream>
#include "console_custom_output.hpp"

import logger;

int MAIN()
{
    Logger log(LoggerBackground::gradient, LogCallPlace::Yes);

    log.log("мое любимое число = ", 13);
    log.log_endl();;

    log.logc(LogColor::Blue, "something blue");
    log.code_place();

    log.title("SOME TITLE", LogColor::Pink);

    log.set_color(LogColor::Green);

    log.log_in_line_begin();

    log.log_in_line("something", "MI", " fuck this place ");
    log.log_in_line("PT");

    log.log_in_line_end();

    log.logc(LogColor::Yellow, "something");
    log.logc(LogColor::Yellow, "mipt");

    log.set_color(LogColor::Green);

    log.logc(LogColor::Blue, "something");
    log.logc(LogColor::Blue, "mipt");

    
    return 0;
}

int main()
{
    MAIN();
    return 0;
}