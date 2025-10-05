module;

#include <iostream>
#include <string>
#include <fstream>
#include <cstddef>
#include <ctime>
#include <cassert>
#include <cstdarg>
#include <cstdlib>
#include <source_location>

#include "log_background_settings.hpp"
#include "console_custom_output.hpp"
#include "global.hpp"

//----------------------------------------------------------------------------------------------

#ifdef SAVE_HTML_STYLE
    #define ON_TAB(...) __VA_ARGS__
#else // SAVE_HTML_STYLE
    #define ON_TAB(...)
#endif // SAVE_HTML_STYLE

//----------------------------------------------------------------------------------------------

export module logger;

//----------------------------------------------------------------------------------------------

const std::string default_log_file_name    = "log.html"                              ;
const std::string path_to_log_file         = "../log/"                               ; // from 'build' directory
const std::string full_path_to_default_log = path_to_log_file + default_log_file_name; // from 'build' directory
const std::string html_extension           = ".html"                                 ;

//----------------------------------------------------------------------------------------------

export enum class LoggerBackground
{
    plain   ,
    image   ,
    gradient,
};

//----------------------------------------------------------------------------------------------

export enum class LogColor : char
{
    White ,
    Red   ,
    Green ,
    Pink  ,
    Yellow,
    Black ,
    Blue  ,
};

//----------------------------------------------------------------------------------------------

export enum class LogCallPlace : bool
{
    No  = false,
    Yes = true ,
};

//----------------------------------------------------------------------------------------------

export class Logger
{
    public:
        // dafault ctor. background type = plain
        Logger(const std::string& logger_file_name,                                     const LogCallPlace& need_log_code_place = LogCallPlace::No, const std::source_location& location = std::source_location::current());
        Logger(                                                                         const LogCallPlace& need_log_code_place = LogCallPlace::No, const std::source_location& location = std::source_location::current()); // same ctor, but with default name

        // ctor with choice of background type. BUT here you cant to choose image on background
        Logger(const std::string& logger_file_name, const LoggerBackground& background, const LogCallPlace& need_log_code_place = LogCallPlace::No, const std::source_location& location = std::source_location::current());
        Logger(                                     const LoggerBackground& background, const LogCallPlace& need_log_code_place = LogCallPlace::No, const std::source_location& location = std::source_location::current()); // same ctor, but with default name

        // ctor for background with image
        Logger(const std::string& logger_file_name, std::string_view path_to_image,     const LogCallPlace& need_log_code_place = LogCallPlace::No, const std::source_location& location = std::source_location::current());
        Logger(const LoggerBackground&  background, std::string_view path_to_image,     const LogCallPlace& need_log_code_place = LogCallPlace::No, const std::source_location& location = std::source_location::current()); // same ctor, but with default name

        // dtor
       ~Logger();

        // not allowed to copy logger
        Logger          (const Logger&) = delete;
        Logger operator=(const Logger&) = delete;
        Logger operator=(      Logger&) = delete;

        // logger public methods    
        template <typename... Args>
        void log                  (                       const Args&... args);
        template <typename... Args>
        void logc                 (const LogColor& color, const Args&... args);

        void logc_in_line_begin   (const LogColor& color = LogColor::White);
        void log_in_line_begin    ();
        template <typename... Args>
        void log_in_line          (                       const Args&... args);
        void log_in_line_end      ();

        void title                (const std::string& title, LogColor color = LogColor::White);

        void code_place           (const std::source_location& location = std::source_location::current());

        void set_color            (const LogColor& color);

        void log_endl             ();

    private:
        // logger private variables
        std::ofstream     log_file_       ;
        LogColor          current_color_  ;

        // logger private methods
        template <typename... Args>
        void write_in_html(const Args&... args);

        std::string get_color_in_str_for_html(const LogColor& color);

        void date();

        void log_call_place_if_need(const LogCallPlace& need_to_log_call_place, const std::source_location location, std::string_view message = "");
        void check_that_open_success(const std::string& log_file_name);

        [[noreturn]]
        void failed_open_log_file(const std::string& file);
};

// ctors 
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

Logger::Logger(const std::string& log_file_name, const LogCallPlace& need_to_log_call_place, const std::source_location& location) :
log_file_(path_to_log_file + log_file_name + html_extension),
current_color_(LogColor::White)
{
    check_that_open_success(log_file_name);

    write_in_html(PLAIN_BACKGROUND_HTML_SETTINGS);

    date();
    log_call_place_if_need(need_to_log_call_place, location, "");
    log_endl();
}

//----------------------------------------------------------------------------------------------

Logger::Logger(const LogCallPlace& need_to_log_call_place, const std::source_location& location) :
log_file_(full_path_to_default_log),
current_color_(LogColor::White)
{
    check_that_open_success(default_log_file_name);
    
    write_in_html(PLAIN_BACKGROUND_HTML_SETTINGS);

    date();
    log_call_place_if_need(need_to_log_call_place, location, "");
    log_endl();
}

//----------------------------------------------------------------------------------------------

Logger::Logger(const std::string& log_file_name, const LoggerBackground& background, const LogCallPlace& need_to_log_call_place, const std::source_location& location) :
log_file_(path_to_log_file + log_file_name + html_extension),
current_color_(LogColor::White)
{
    check_that_open_success(log_file_name);

    switch (background)
    {
        case LoggerBackground::plain:
            write_in_html(PLAIN_BACKGROUND_HTML_SETTINGS);
            break;

        case LoggerBackground::gradient:
            write_in_html(GRADIENT_BACKGROUND_HTML_SETTINGS);
            break;

        case LoggerBackground::image:
            builtin_unreachable_wrapper("we cant parse it without path to image. this situation in another ctor");
            break;

        default:
            builtin_unreachable_wrapper("undefined 'LoggerBackground' value. maybe you add new type and forgot to add parsing of this new value");
            break;
    }

    date();
    log_call_place_if_need(need_to_log_call_place, location, "");
    log_endl();
}

//----------------------------------------------------------------------------------------------

Logger::Logger(const LoggerBackground& background, const LogCallPlace& need_to_log_call_place, const std::source_location& location) :
log_file_(full_path_to_default_log),
current_color_(LogColor::White)
{
    check_that_open_success(default_log_file_name);

    switch (background)
    {
        case LoggerBackground::plain:
            write_in_html(PLAIN_BACKGROUND_HTML_SETTINGS);
            break;

        case LoggerBackground::gradient:
            write_in_html(GRADIENT_BACKGROUND_HTML_SETTINGS);
            break;

        case LoggerBackground::image:
            builtin_unreachable_wrapper("we cant parse it without path to image. this situation in another ctor");
            break;

        default:
            builtin_unreachable_wrapper("undefined 'LoggerBackground' value. maybe you add new type and forgot to add parsing of this new value");
            break;
    }

    date();
    log_call_place_if_need(need_to_log_call_place, location, "");
    log_endl();
}

//----------------------------------------------------------------------------------------------

Logger::Logger(const std::string& log_file_name, std::string_view path_to_image, const LogCallPlace& need_to_log_call_place, const std::source_location& location) :
log_file_(path_to_log_file + log_file_name + html_extension),
current_color_(LogColor::White)
{
    check_that_open_success(log_file_name);
    
    write_in_html(IMAGE_BACKGROUND_HTML_SETTINGS(path_to_image));

    date();
    log_call_place_if_need(need_to_log_call_place, location, "");
    log_endl();
}

//----------------------------------------------------------------------------------------------

Logger::Logger(const LoggerBackground& background, std::string_view path_to_image, const LogCallPlace& need_to_log_call_place, const std::source_location& location) :
log_file_(full_path_to_default_log),
current_color_(LogColor::White)
{
    check_that_open_success(default_log_file_name);

    switch (background)
    {
        case LoggerBackground::image: break;

        case LoggerBackground::gradient:
        case LoggerBackground::plain:
        default: builtin_unreachable_wrapper("here can be only image type");
    }

    write_in_html(IMAGE_BACKGROUND_HTML_SETTINGS(path_to_image));

    date();
    log_call_place_if_need(need_to_log_call_place, location, "");
    log_endl();
}

// dtor
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

Logger::~Logger()
{
    date();
    write_in_html(HTML_END);
    log_file_.close();
}

// PUBLIC methods
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

template <typename... Args>
void Logger::logc(const LogColor& color, const Args&... args)
{
    set_color(color);
    write_in_html(ON_TAB("\t\t\t\t")"<p>", args..., "</p>" ON_TAB("\n"));
}

//----------------------------------------------------------------------------------------------

template <typename... Args>
void Logger::log(const Args&... args)
{
    write_in_html(ON_TAB("\t\t\t\t")"<p>", args..., "</p>" ON_TAB("\n"));
}

//----------------------------------------------------------------------------------------------

template <typename... Args>
void Logger::log_in_line(const Args&... args)
{
    write_in_html(args...);
}

//----------------------------------------------------------------------------------------------

void Logger::log_endl()
{
    write_in_html(ON_TAB("\t\t\t\t") "<p>\n</p>");
}

//----------------------------------------------------------------------------------------------

void Logger::logc_in_line_begin(const LogColor& color)
{
    set_color(color);
    write_in_html(ON_TAB("\t\t\t\t") "<p>");
}

//------------------c----------------------------------------------------------------------------

void Logger::log_in_line_begin()
{
    write_in_html(ON_TAB("\t\t\t\t") "<p>");
}

//----------------------------------------------------------------------------------------------

void Logger::log_in_line_end()
{
    write_in_html("</p>" ON_TAB("\n"));
}

//----------------------------------------------------------------------------------------------

void Logger::title(const std::string& title, LogColor color)
{
    static const size_t ScreenSize = 45; //count in char's, that size is like h2
    size_t title_len = title.size() + 2;

    size_t free_place_len = 0;
    if (title_len < ScreenSize - 2) free_place_len = (ScreenSize - (title_len + 2)) / 2;
    if (free_place_len > 0 && (ScreenSize - title_len) % 2 == 0) --free_place_len;

    set_color(color);

    write_in_html(ON_TAB("\t\t\t\t") "<h2>");

    for (size_t i = 0; i < free_place_len; i++)
        write_in_html("=");

    write_in_html(" ", title, " ");

    for (size_t i = 0; i < free_place_len; i++)
        write_in_html("=");

    write_in_html("</h2>" ON_TAB("\n"));
}

//----------------------------------------------------------------------------------------------

void Logger::set_color(const LogColor& color)
{
    if (color == current_color_) // жертуем одним сравнением, чтобы не делать дорогой write_in_html
        return;
    
    current_color_ = color;

    std::string color_html = get_color_in_str_for_html(color);

    write_in_html(ON_TAB("\t\t\t") "</span>" ON_TAB("\n") // end old color
                  ON_TAB("\t\t\t") "<span class=\"color ", color_html, "\">" ON_TAB("\n")
    );

    return;
}

//----------------------------------------------------------------------------------------------

void Logger::code_place(const std::source_location& code_place)
{
    logc(LogColor::Pink,
              code_place.file_name(), ":",
              code_place.line     (), ":",
              code_place.column   ()
    );

    logc(LogColor::Green,
            code_place.function_name()
    );
}

// private methods
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

template <typename... Args>
void Logger::write_in_html(const Args&... args)
{
    (log_file_ << ... << args);
}

//----------------------------------------------------------------------------------------------

void Logger::date()
{
    time_t raw_time;
    struct tm *time_info;
    static const size_t date_len = 64;
    char date[date_len] = {};

    time(&raw_time);
    time_info = localtime(&raw_time);
    strftime(date, date_len, "%H:%M:%S %Y-%m-%d", time_info);

    title(date);
}

//----------------------------------------------------------------------------------------------

void Logger::check_that_open_success(const std::string& log_file_name)
{
    if (log_file_.fail())
        failed_open_log_file(log_file_name); // exit 1
}

//----------------------------------------------------------------------------------------------

void Logger::log_call_place_if_need(const LogCallPlace& need_to_log_call_place, const std::source_location location, std::string_view message)
{
    if (need_to_log_call_place == LogCallPlace::No)
        return;

    if (message != "")
        log(message);

    code_place(location);
}

//----------------------------------------------------------------------------------------------

std::string Logger::get_color_in_str_for_html(const LogColor& color)
{
    switch (color)
    {
        case LogColor::Red:    return "red_text";
        case LogColor::Green:  return "green_text";
        case LogColor::Pink:   return "pink_text";
        case LogColor::Yellow: return "yellow_text";
        case LogColor::Black:  return "black_text";
        case LogColor::Blue:   return "blue_text";
        case LogColor::White:  return "";
        default:               builtin_unreachable_wrapper("undef color type. maybe you forgot to add something color");
    }

    builtin_unreachable_wrapper("we must return in switch");
    return "";
}

//----------------------------------------------------------------------------------------------

[[noreturn]]
void Logger::failed_open_log_file(const std::string& file)
{
    std::cerr << RED BOLD "Failed open log file: `" ITALIC <<  file << "'" RESET_CONSOLE_OUT << std::endl;
    exit(EXIT_FAILURE);
}

//----------------------------------------------------------------------------------------------
