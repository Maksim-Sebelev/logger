#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "lib/log.hpp"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

FILE* LogFile = nullptr;
const char* LogName = "Log/log.html";

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void makeStyle      (const char* wayToImage, size_t nTabBefore);
static void makeTextSection (size_t nTabBefore);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static const char* GetHtmlColor(LogColor color);

static void fprintfInHtml         (const char* format, ...);
static void fprintfHtml           ();
static void fprintfBody           ();
static void fprintfBodyWithBracket();
static void fprintfBodyWithBracketEnd();
static void fprintfHtmlEnd        ();
static void fprintfHead           ();
static void fprintfHeadEnd        ();
static void fprintfStyle          ();
static void fprintfStyleEnd       ();
static void fprintfPre            ();
static void fprintfPreEnd         ();
static void fprintfNTab           (size_t nTab);
static void fprintfNSpace         (size_t nSpace);
static void fprintfNS             ();
static void fprintfNNS            (size_t nNS);
static void fprintfOpenBracket    ();
static void fprintfCloseBracket   ();
static void fprintfSemicolonPoint ();
static void fprintfColor          ();
static void fprintfTextSection    ();
static void fprintfTextSectionEnd ();
static void fprintfH1             ();
static void fprintfH1End          ();
static void fprintfP              ();
static void fprintfPEnd           ();
static void fprintfPEnd           ();
static void fprintfTitle          ();
static void fprintfTitleEnd       ();
static void fprintfPtext          ();
static void fprintfPtextEnd       ();

static void fprintfMetaWithArgs   (const char* format, ...);
static void fprintfMeta           ();

static void fprintfDivWithArgs    (const char* format, ...);
static void fprintfDiv            ();
static void fprintfDivEnd         ();


static void fprintfSpanWithArgs   (const char* format, ...);
static void fprintfSpan           ();
static void fprintfSpanEnd        ();

static void makeBackGroundImage(const char* wayToImage, size_t nTabBefore);
static void makeTextColor(size_t nTabBefore);

//=== background color ===//
const char* black_background     = "body { background-color: #121212; }                                                                          \n";
const char* gradient1_background = "body { background: linear-gradient(to right,  #0f2027, #203a43, #2c5364);}                               \n";
const char* gradient2_background = "body { background: linear-gradient(to bottom, #ffffff,#ffffff, #1948ff, #1948ff, #f92b03, #f92b03);} \n";

//=== text color ===//

const char* red_text_html_name    = "red_text";
const char* green_text_html_name  = "green_text";
const char* pink_text_html_name   = "pink_text";
const char* yellow_text_html_name = "yellow_text";
const char* blue_text_html_name   = "blue_text";
const char* black_text_html_name  = "black_text";

const char* red_text_rgb    = " { color: #ff4444; } \n";
const char* green_text_rgb  = " { color: #0bf80b; } \n";
const char* pink_text_rgb   = " { color: #f605c7; } \n";
const char* yellow_text_rgb = " { color: #ecc40b; } \n";
const char* blue_text_rgb   = " { color: #0c89e8; } \n"; 
const char* black_text_rgb  = " { color: #000000; } \n";

//=== ===//

void OpenLog()
{
    assert(LogName && "logName = nullptr");

    int sys_return = system("mkdir -p Log/");
    assert(sys_return == 0 && "failed make log dir");

    LogFile = fopen(LogName, "w");
    assert(LogFile && "failed open log file");

    fprintfHtml(); fprintfNS();

    makeStyle("../include/lib/backgrounds/anime_tyan.webp", 1);
    // makeStyle("../include/lib/backgrounds/senya.jpg", 1);

    makeTextSection(0);

    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CloseLog()
{
    fclose(LogFile);
    LogFile = nullptr;

    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void LogTextColor(LogColor color)
{
    static bool WasUsed = false;
    if (WasUsed)
    {
        fprintf(stderr, "wtf\n");
        LogTextColorEnd();
        WasUsed = false;
    }
    else
    {
        WasUsed = true;
    }
    
    const char* color_html = GetHtmlColor(color);

    fprintfNTab(3);
        fprintfSpanWithArgs("class=\"color %s\"", color_html); fprintfNS();
        
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void LogTextColorEnd()
{
    fprintfNTab(3); fprintfSpanEnd(); fprintfNS();

    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void LogAdcPrint(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    fprintfNTab(4); fprintfPtext(); vfprintf(LogFile, format, args); fprintfPtextEnd(); fprintfNS();

    fflush(LogFile);
    
    va_end(args);
    
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void LogPrint(LogColor color, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    
    const char* color_html = GetHtmlColor(color);
    fprintfNTab(3);
    fprintfSpanWithArgs("class=\"color %s\"", color_html); fprintfNS();
    
    fprintfNTab(4); fprintfPtext(); vfprintf(LogFile, format, args); fprintfPtextEnd(); fprintfNS();
    
    fflush(LogFile);
    
    va_end(args);
    
    fprintfNTab(3);
    fprintfSpanEnd(); fprintfNS();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


static void makeStyle(const char* wayToImage, size_t nTabBefore)
{
    fprintfNTab(nTabBefore);
    fprintfHead(); fprintfNS();
    
    fprintfNTab(nTabBefore + 1);
    fprintfMetaWithArgs("name=\"viewport\" content=\"width=device-width, initial-scale=1.0\""); fprintfNS();
    
    fprintfNTab(nTabBefore + 1);
    fprintfTitle(); fprintfInHtml("background image"); fprintfTitleEnd(); fprintfNS();
    
    fprintfNTab(nTabBefore + 1);
    fprintfStyle(); fprintfNS();
    
    makeBackGroundImage(wayToImage, nTabBefore + 2);        
    makeTextColor(nTabBefore + 2);
    
    fprintfNTab(nTabBefore + 2);
    fprintfStyleEnd(); fprintfNS();
    
    fprintfNTab(nTabBefore);
    fprintfHeadEnd(); fprintfNS();
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void makeTextSection(size_t nTabBefore)
{

    fprintfNTab(nTabBefore);
    fprintfNS(); fprintfBody(); fprintfNS();
    
    fprintfNTab(nTabBefore + 1);
        fprintfDivWithArgs("class=\"text-section\""); fprintfNS();
    }
    
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void makeBackGroundImage(const char* wayToImage, size_t nTabBefore)
{
    fprintfNTab(nTabBefore);
    fprintfBodyWithBracket(); fprintfNS();
    
            fprintfNTab(nTabBefore + 1);
                fprintfInHtml("margin: 0;\n");

            fprintfNTab(nTabBefore + 1);
                fprintfInHtml("padding: 0;\n");

            fprintfNTab(nTabBefore + 1);
                fprintfInHtml("height: 100vh;\n");

            fprintfNTab(nTabBefore + 1);
                fprintfInHtml("background-image: url('%s');\n", wayToImage);

            fprintfNTab(nTabBefore + 1);
                fprintfInHtml("background-size: cover;\n");

            fprintfNTab(nTabBefore + 1);
                fprintfInHtml("background-position: center;\n");

            fprintfNTab(nTabBefore + 1);
                fprintfInHtml("background-repeat: no-repeat;\n");

            fprintfNTab(nTabBefore + 1);
                fprintfInHtml("background-attachment: fixed;\n");

            fprintfNTab(nTabBefore + 1);
                fprintfInHtml("font-family: Arial, sans-serif;\n");

            fprintfNTab(nTabBefore + 1);
                fprintfInHtml("color: white;\n");

    fprintfNTab(nTabBefore);
    fprintfBodyWithBracketEnd(); fprintfNNS(2);

    
    fprintfNTab(nTabBefore);
    fprintfTextSection(); fprintfNS();

        fprintfNTab(nTabBefore + 1);
            fprintfInHtml("background-color: rgba(0, 0, 0, 0.5);\n");

        fprintfNTab(nTabBefore + 1);
            fprintfInHtml("padding: 30px;\n");

        fprintfNTab(nTabBefore + 1);
            fprintfInHtml("border-radius: 10px;\n");

        fprintfNTab(nTabBefore + 1);
            fprintfInHtml("max-width: 800px;\n");

        fprintfNTab(nTabBefore + 1);
            fprintfInHtml("margin: -10px auto;\n");

        fprintfNTab(nTabBefore + 1);
            // fprintfInHtml("backdrop-filter: blur(5px);\n");

    fprintfNTab(nTabBefore);
            fprintfTextSectionEnd();  fprintfNNS(2);


    fprintfNTab(nTabBefore);
        fprintfH1(); fprintfNS();
    
        fprintfNTab(nTabBefore + 1); 
            fprintfInHtml("text-align: center;\n");
        fprintfNTab(nTabBefore + 1); 
            fprintfInHtml("margin-bottom:105px;\n");

    fprintfNTab(nTabBefore);
            fprintfH1End(); fprintfNNS(2);
    
    fprintfNTab(nTabBefore);
    fprintfP(); fprintfNS();

    fprintfNTab(nTabBefore + 1);
        fprintfInHtml("line-height: 0.5;\n");

    fprintfNTab(nTabBefore + 1);
        fprintfInHtml("text-align: justify;\n");

    fprintfNTab(nTabBefore + 1);
        fprintfInHtml("margin: 10px 0;\n");

    fprintfNTab(nTabBefore);
            fprintfPEnd(); fprintfNNS(2);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void makeH1(size_t nTabBefore)
{
    fprintfNTab(nTabBefore);
    fprintfH1(); fprintfNS();
    
        fprintfNTab(nTabBefore + 1); 
            fprintfInHtml("text-align: center;\n");
        fprintfNTab(nTabBefore + 1); 
            fprintfInHtml("margin-bottom: 5px;\n");

    fprintfNTab(nTabBefore);
            fprintfH1End(); fprintfNNS(2);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void makeTextColor(size_t nTabBefore)
{
    fprintfNTab(nTabBefore);
    fprintfInHtml(".%s %s", red_text_html_name    , red_text_rgb    );

    fprintfNTab(nTabBefore);
    fprintfInHtml(".%s %s", green_text_html_name  , green_text_rgb  );
    
    fprintfNTab(nTabBefore);
    fprintfInHtml(".%s %s", yellow_text_html_name , yellow_text_rgb );
    
    fprintfNTab(nTabBefore);
    fprintfInHtml(".%s %s", blue_text_html_name   , blue_text_rgb   );

    fprintfNTab(nTabBefore);
    fprintfInHtml(".%s %s", black_text_html_name  , black_text_rgb  );

    fprintfNTab(nTabBefore);
    fprintfInHtml(".%s %s", pink_text_html_name   , pink_text_rgb   );

    fprintfNTab(nTabBefore);
    fprintfInHtml(".%s %s", red_text_html_name    , red_text_rgb    );

    fprintfNS();

    fprintfNTab(nTabBefore);
    fprintfInHtml(".color {\n");

    fprintfNTab(nTabBefore + 1);
    fprintfInHtml("padding: 0px 10px;\n");

    fprintfNTab(nTabBefore + 1);
    fprintfInHtml("margin: 1px 0;\n");

    fprintfNTab(nTabBefore + 1);
    fprintfInHtml("line-height: 0.5;\n");

    // fprintfNTab(nTabBefore + 1);
    // fprintfInHtml("border-radius: 3px;\n");
    
    // fprintfNTab(nTabBefore + 1);
    // fprintfInHtml("border-left: 3px solid currentColor;\n");



    fprintfNTab(nTabBefore);
    fprintfInHtml("}"); fprintfNNS(2);

    fprintfNTab(nTabBefore);
    fprintfInHtml(".color p {\n");

    fprintfNTab(nTabBefore);
    fprintfInHtml("white-space: pre;\n");

    fprintfNTab(nTabBefore + 1);
    fprintfInHtml("padding: 0;\n");

    fprintfNTab(nTabBefore + 1);
    fprintfInHtml("margin: 0;\n");

    fprintfNTab(nTabBefore + 1);
    fprintfInHtml("line-height: 1.1;\n");
    
    // fprintfNTab(nTabBefore + 1);
    // fprintfInHtml("border-left: 3px solid currentColor;\n");

    fprintfNTab(nTabBefore);
    fprintfInHtml("}"); fprintfNNS(2);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfInHtml(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    vfprintf(LogFile, format, args);
    fflush(LogFile);

    va_end(args);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfHtml()
{
    fprintf(LogFile, "<html>");
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfHtmlEnd()
{
    fprintf(LogFile, "</html>");
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfBody()
{
    fprintf(LogFile, "<body>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfBodyEnd()
{
    fprintf(LogFile, "</body>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfBodyWithBracket()
{
    fprintf(LogFile, "body {");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfBodyWithBracketEnd()
{
    fprintf(LogFile, "}");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfHead()
{
    fprintf(LogFile, "<head>");
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfHeadEnd()
{
    fprintf(LogFile, "</head>");
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfStyle()
{
    fprintf(LogFile, "<style>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfStyleEnd()
{
    fprintf(LogFile, "</style>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfPre()
{
    fprintf(LogFile, "<pre>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfPreEnd()
{
    fprintf(LogFile, "</pre>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfTitle()
{
    fprintf(LogFile, "<title>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfTitleEnd()
{
    fprintf(LogFile, "</title>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfMeta()
{
    fprintf(LogFile, "<meta>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfMetaWithArgs(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    fprintfInHtml("<meta ");

    vfprintf(LogFile, format, args);
    fflush(LogFile);

    fprintfInHtml(">");

    va_end(args);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfDivWithArgs(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    fprintfInHtml("<div ");

    vfprintf(LogFile, format, args);
    fflush(LogFile);

    fprintfInHtml(">");

    va_end(args);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfDiv()
{
    fprintf(LogFile, "<div>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfDivEnd()
{
    fprintf(LogFile, "</div>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfSpanWithArgs(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    fprintfInHtml("<span ");

    vfprintf(LogFile, format, args);
    fflush(LogFile);

    fprintfInHtml(">");

    va_end(args);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfSpan()
{
    fprintf(LogFile, "<span>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfSpanEnd()
{
    fprintf(LogFile, "</span>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfNTab(size_t nTab)
{
    for (size_t i = 0; i < nTab; i++) fprintf(LogFile, "\t");
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


static void fprintfNSpace(size_t nSpace)
{
    for (size_t i = 0; i < nSpace; i++) fprintf(LogFile, " ");
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfNS()
{
    fprintf(LogFile, "\n");
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfNNS(size_t nNS)
{
    for (size_t i = 0; i < nNS; i++) fprintf(LogFile, "\n");
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfOpenBracket()
{
    fprintf(LogFile, "{ ");
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfCloseBracket()
{
    fprintf(LogFile, " }");
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfSemicolonPoint()
{
    fprintf(LogFile, ";");
    return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfColor()
{
    fprintf(LogFile, "color: ");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfTextSection()
{
    fprintf(LogFile, ".text-section {");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfTextSectionEnd()
{
    fprintf(LogFile, "}");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfH1()
{
    fprintf(LogFile, "h1 {");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfH1End()
{
    fprintf(LogFile, "}");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfP()
{
    fprintf(LogFile, "p {");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfPEnd()
{
    fprintf(LogFile, "}");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfPtext()
{
    fprintf(LogFile, "<p>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void fprintfPtextEnd()
{
    fprintf(LogFile, "</p>");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static const char* GetHtmlColor(LogColor color)
{
    switch (color)
    {
        case LogColor::Red:    return red_text_html_name;
        case LogColor::Green:  return green_text_html_name;
        case LogColor::Pink:   return pink_text_html_name;
        case LogColor::Yellow: return yellow_text_html_name;
        case LogColor::Black:  return black_text_html_name;
        case LogColor::Blue:   return blue_text_html_name;
        case LogColor::White:  return "";
        default:               assert(0 && "undef color in log");
    }

    return "";
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

