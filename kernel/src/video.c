#include <video.h>

void setColor(colors fg, colors bg)
{
    char fullString[9];
    char colorfgString[4];
    char colorbgString[4];

    itoa(colorbgString, (uint8_t)bg);
    itoa(colorfgString, (uint8_t)fg);


    concat(fullString, "\x1b[");
    concat(&fullString[strlen(fullString)], colorbgString);
    concat(&fullString[strlen(fullString)], ";");
    concat(&fullString[strlen(fullString)], colorfgString);
    concat(&fullString[strlen(fullString)], "m");

    term_write(fullString, strlen(fullString));
}

void scrollDown(uint8_t sAmount)
{
    char fullString[9];
    char amountNum[4];

    itoa(amountNum, (uint64_t)sAmount);
    concat(fullString, "\x1b[");
    concat(&fullString[strlen(fullString)], amountNum);
    concat(&fullString[strlen(fullString)], " S");
    term_write(fullString, strlen(fullString));
}