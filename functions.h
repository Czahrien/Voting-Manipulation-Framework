#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


#include <cstdio>
#ifdef _WIN32
#include <conio.h>
#else
#include <cstdlib>
#include <cstring>
#include <sys/select.h>
#include <termios.h>
// conio library emulation functions
// I do not take credit for these four functions, all credit goes to
// TODO: Figure out how to credit the guy who wrote these AND test them on Windows/Linux/Solaris platforms.
/**
 * Sets IO flags that allow for asynchronous single character extraction
 * from stdin.
 */
void set_conio_terminal_mode();
/**
 * Resets IO flags to default values.
 */
void reset_terminal_mode();
/**
 * Checks to see if there are characters waiting to be extracted from stdin.
 *
 * @return 1 if there is a character to be extracted, 0 otherwise.
 */
int kbhit();
/**
 * Obtains the oldest unconsumed character from stdin and consumes the character.
 * 
 * @return a single character
 */
int getch();
#endif

#endif