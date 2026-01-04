#include "miraparser.h"
#include <stdio.h>


int main(int argc, char *argv[]) {
    MiraParser *parser = MiraParser_Open("--"); // init. parser
    MiraParser_Return *lazy = MiraParser_Value_Arg_Open(); // init. variable
    if(MiraParser_Arg("emote", parser) == 0){ // checking "--emote" arg
        printf("i'am will use this emotion: ");
        MiraParser_Value_Arg("emote", lazy, MIRAPARSER_STRING_TYPE, parser); // getting "--emote" value
        if(!lazy->string){ // validating string
            printf("(core dumped) *_*\n");
            return 1; // if string= NULL
        }
        // else
        printf("%s\n", lazy->string); // printing value
        MiraParser_Value_Arg_Free(lazy); // freeing variable
        MiraParser_Free(parser); // freeing parser
    }
    else{
        printf("Mira🩵\n"); // prints if no args
    }
}

/*
cmd output:
[ametero@AmeteroRaidenEi MiraParser]$ ./mira.out 
Mira🩵
[ametero@AmeteroRaidenEi MiraParser]$ ./mira.out --emote
i'am will use this emotion: (core dumped) *_*
[ametero@AmeteroRaidenEi MiraParser]$ ./mira.out --emote ">_<"
i'am will use this emotion: >_<
[ametero@AmeteroRaidenEi MiraParser]$ ./mira.out --emote UwU
i'am will use this emotion: UwU
[ametero@AmeteroRaidenEi MiraParser]$ ./mira.out --crash
Mira🩵
*/
