/*
Rainbow Text (rbtext)
$ gcc -o rbtext rbtext.c
Created by Seelenlos <samoyo@protonmail.com>

NO WARRANTY OF ANY KIND.
NO LIABILITY TO CREATOR FOR ANY TYPE OF DAMAGE.
I DON'T CARE HOW YOU USE OR CONFIGURE THIS PROGRAM.
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

// How many milliseconds the program will wait until the next print
#define CONF_SLEEP_TIMEMS 75
// BEWARE RICERS
// If you add extra colors make sure to
// a) Add it to the color enum in the genColors function
// b) Add the case to the switch statement in the genColors function
// c) Update the COLORS definition with the new amount of colors
// FORMAT
// #define COLOR "R;G;B"
#define RED         "193;71;87"
#define ORANGE      "193;116;71"
#define YELLOW      "193;177;71"
#define GREEN       "149;193;71"
#define CYAN        "71;193;161"
#define BLUE        "71;165;193"
#define PURPLE      "155;71;193"
#define PINK        "193;71;153"
#define COLORS      8
// Keep track of how many ticks (characters read from char *s) have gone by
long long t;
void genColors(char *s) {
    for (int i = 0; i < strlen(s); i++,t++) {
        enum color {
            red,orange,yellow,green,cyan,blue,purple,pink
        };
        enum color c = ((t/2) & (COLORS-1));
        char *cstr = malloc(256*sizeof(char));
        
        switch (c) {
            case red:
                cstr = "\e[38;2;"RED"m";
                break;
            
            case orange:
                cstr = "\e[38;2;"ORANGE"m";
                break;
            
            case yellow:
                cstr = "\e[38;2;"YELLOW"m";
                break;
            
            case green:
                cstr = "\e[38;2;"GREEN"m";
                break;
            
            case cyan:
                cstr = "\e[38;2;"CYAN"m";
                break;
            
            case blue:
                cstr = "\e[38;2;"BLUE"m";
                break;
            
            case purple:
                cstr = "\e[38;2;"PURPLE"m";
                break;
            
            case pink:
                cstr = "\e[38;2;"PINK"m";
                break;

        }

        printf("%s%c",cstr,s[i]);
    }
}

int main(int carg, char **varg) {
    if (carg < 2) {
        printf("\e[1;31m[ERROR]\e[0m No arguments given.\n\tUSAGE: \e[34m%s \e[33m<text>\3[0m\n",varg[0]);
        return 1;
    }

    char *text = malloc(1024*sizeof(char));
    int t_ind = 0;

    // Similar to pythons str.join() method
    // Adds all the arguments together with spaces seperating them
    // EG: ./rbtext hello world > "hello world"
    for (int i = 1; i < carg; i++) {
        for (int j = 0; j < strlen(varg[i]); j++,t_ind++) {
            text[t_ind] = varg[i][j];
        }
        text[t_ind] = ' ';
        t_ind++;
    }

    while (1) {
        fflush(stdout);
        printf("%s","\r");
        genColors(text);
        fflush(stdout);
        usleep(CONF_SLEEP_TIMEMS*1000);
    }

    return 0;
}