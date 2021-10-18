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

// How many milliseconds the program will wait until the next print ( DEFAULT = 100 )
#define CONF_SLEEP_TIMEMS 100
// How many times a color should be shown before switching to the next ( DEFAULT = 2 )
#define COLOR_SKIP 2

// BEWARE RICERS
// If you add extra colors make sure to
// a) Add it to the color enum
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

enum color {
    red,orange,yellow,green,cyan,blue,purple,pink
};

#define addcase(enum, defin)\
case enum:\
    cstr = "\e[38;2;"defin"m";\
    break;

unsigned long long t = 0;
void genColors(char *s) {
    char *cstr = malloc(20 * sizeof(char));
    for (int i = 0; i < strlen(s); i++) {
        enum color c = (((t + i) / COLOR_SKIP) % COLORS);
        
        switch (c) {
            //addcase(enum value, #define name)
            addcase(red,    RED);
            addcase(orange, ORANGE);
            addcase(yellow, YELLOW);
            addcase(green,  GREEN);
            addcase(cyan,   CYAN);
            addcase(blue,   BLUE);
            addcase(purple, PURPLE);
            addcase(pink,   PINK);
        }

        printf("%s%c",cstr,s[i]);
    }
}

int main(int carg, char **varg) {
    if (carg < 2) {
        printf("\e[1;31m[ERROR]\e[0m No arguments given.\n\tUSAGE: \e[34m%s \e[33m<text>\e[0m\n",varg[0]);
        return 1;
    }

    char *text = malloc(1024 * sizeof(char));
    
    // Similar to pythons str.join() method
    // Adds all the arguments together with spaces seperating them
    // EG: ./rbtext hello world > "hello world"
    for (int i = 1, j = 0; i < carg; i++) {
        for (int k = 0; k < strlen(varg[i]); k++, j++) {
            text[j] = varg[i][k];
        }
        
        text[j] = ' ';
        j++;
    }

    while (1) {
        printf("\r");
        genColors(text);
        printf("\e[0m");
        fflush(stdout);
        usleep(CONF_SLEEP_TIMEMS*1000);
        t += 1;
    }

    return 0;
}