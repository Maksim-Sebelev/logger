#include <iostream>

import logger;

int main()
{
    Logger log(LoggerBackground::gradient, LogCallPlace::Yes);

    log.logc(LogColor::Blue, "something blue");
    log.code_place();

    log.title("SOME TITLE", LogColor::Pink);

    log.set_color(LogColor::Green);

    log.log_in_line_begin();

    log.log_in_line("something", "mi", "");
    log.log_in_line("pt");

    log.log_in_line_end();

    log.logc(LogColor::Yellow, "something");
    log.logc(LogColor::Yellow, "mipt");

    log.set_color(LogColor::Green);

    log.logc(LogColor::Blue, "something");
    log.logc(LogColor::Blue, "mipt");

    return 0;
}