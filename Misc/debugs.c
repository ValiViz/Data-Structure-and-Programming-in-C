#include <stdio.h>
#define DEBUG

#pragma region Debugs
#define class struct
#define static

typedef int Color;
typedef const char* string;
const int BACK_BASE = 40;
const int FONT_BASE = 30;

static class {
    const Color 
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE;
} Colors = {
    0, 1, 2, 3, 4, 5, 6, 7
};

/// @brief Print a colored string to console
/// @param string content
/// @param fontColor font color
/// @param backgroundColor background color
void PrintColoredString(
    const char* string,
    Color fontColor,
    Color backgroundColor) 
{
    
    printf(
        "\033[%dm\033[%dm%s\033[0m", 
        FONT_BASE + fontColor, 
        BACK_BASE + backgroundColor,
        string
    );
}

void Log(string str)
{
    #ifdef DEBUG
    PrintColoredString("[INFO]", Colors.WHITE, Colors.BLACK);
    putchar(' ');
    PrintColoredString(str, Colors.YELLOW, Colors.BLACK);
    putchar('\n');
    #endif
}

void LogWarning(string str) 
{
    #ifdef DEBUG
    PrintColoredString("[WARNING]", Colors.BLACK, Colors.YELLOW);
    putchar(' ');
    PrintColoredString(str, Colors.YELLOW, Colors.BLACK);
    putchar('\n');
    #endif
}
void LogError(string str)
{
    #ifdef DEBUG
    PrintColoredString("[ERROR]", Colors.BLACK, Colors.RED);
    putchar(' ');
    PrintColoredString(str, Colors.RED, Colors.BLACK);
    putchar('\n');
    #endif
}

static class {
    // Log an INFO message to console
    void (*Log)(string);
    // Log a WARNING message to console
    void (*LogWarning)(string);
    // Log an ERROR message to console
    void (*LogError)(string);
} Debug = {
    Log, LogWarning, LogError
};
#undef class
#undef static
#pragma endregion Debugs

int main()
{
    Debug.Log("A log message");
    Debug.LogWarning("An warning message");
    Debug.LogError("An error message");
}