#pragma once

//----------------------------------------------------------------------------------------------

#include <fstream>
#include <string>
#include <source_location>

//----------------------------------------------------------------------------------------------

// #define SAVE_HTML_STYLE

//----------------------------------------------------------------------------------------------

#ifdef SAVE_HTML_STYLE
    #define ON_TAB(...) __VA_ARGS__
#else // SAVE_HTML_STYLE
    #define ON_TAB(...)
#endif // SAVE_HTML_STYLE

//----------------------------------------------------------------------------------------------

enum class LoggerBackground
{
    plain   ,
    image   ,
    gradient,
};

//----------------------------------------------------------------------------------------------

enum class LogColor : char
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

enum class LogCallPlace : bool
{
    No  = false,
    Yes = true ,
};

//----------------------------------------------------------------------------------------------

class Logger
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
        
        // not allow to copy logger
        Logger          (const Logger&) = delete;
        Logger operator=(const Logger&) = delete;
        Logger operator=(      Logger&) = delete;


        // logger public methods    
        template <typename... Args>
        void log                  (                const Args&... args);
        
        template <typename... Args>
        void logc                 (const LogColor& color, const Args&... args);

        void logc_in_line_begin   (const LogColor& color = LogColor::White);
        void log_in_line_begin    ();
    
        template <typename... Args>
        void log_in_line          (const Args&... args);
        void log_in_line_end      ();

        void title                (const std::string& title, LogColor color = LogColor::White);
        
        void code_place           (const std::source_location& location = std::source_location::current());
        
        void set_color            (const LogColor& color);
    
        void log_endl             ();

    private:
        // logger private variables
        std::ofstream     log_file_       ;
        LoggerBackground  background_type_;
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

//----------------------------------------------------------------------------------------------

template <typename... Args>
void Logger::write_in_html(const Args&... args)
{
    (log_file_ << ... << args);
}

//----------------------------------------------------------------------------------------------

template <typename... Args>
void Logger::logc(const LogColor& color, const Args&... args)
{
    set_color(color);
    write_in_html(ON_TAB("\t\t\t\t")"<p>", args..., "</p>" ON_TAB(, "\n"));
}

//----------------------------------------------------------------------------------------------

template <typename... Args>
void Logger::log(const Args&... args)
{
    write_in_html(ON_TAB("\t\t\t\t")"<p>", args..., "</p>" ON_TAB(, "\n"));
}

//----------------------------------------------------------------------------------------------

template <typename... Args>
void Logger::log_in_line(const Args&... args)
{
    write_in_html(args...);
}

//----------------------------------------------------------------------------------------------
