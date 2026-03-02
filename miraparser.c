/*
MIT License

Copyright (c) 2026 Ametero

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "miraparser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

MiraParser * _MiraParser_open(char * argv[], int argc, char * prefix){
    MiraParser * temp;
    temp = malloc(sizeof(MiraParser));
    temp->prefix = malloc(strlen(prefix) + 1);
    strcpy(temp->prefix, prefix);
    if(!temp){
        return NULL;
    }
    temp->arguments = malloc(sizeof(char*) * argc);
    for(int idx = 0; idx != argc; idx++){
        temp->arguments[idx] = malloc(strlen(argv[idx]) + 1);
        if(!temp->arguments[idx]){
            return NULL;
        }
        strcpy(temp->arguments[idx], argv[idx]);
    }
    temp->arguments_count = argc;
    return temp;
}
int MiraParser_Arg(const char * arg, MiraParser * parser){
    if(!parser){
        return 1;
    }
    
    for(int idx = 1; idx != parser->arguments_count; idx++){
        int localclearprefixshit = 0;
        if(strlen(parser->arguments[idx]) < strlen(parser->prefix)){
            // non-valid arg OR value
            continue;
        }
        if(!parser->arguments[idx]){
            return 1;
        }
        char * woprefix = malloc(strlen(parser->arguments[idx]) + 1);
        if(!woprefix){
            return 1;
        }
        strcpy(woprefix, parser->arguments[idx]); // skipping prefix
        for(int clearprefix = 0; clearprefix != strlen(parser->prefix); clearprefix++){
            localclearprefixshit++; // oops....
            woprefix++;
        }
        if(strcmp(woprefix, arg) == 0){
            //free(woprefix);
            /*
            free(): invalid pointer
            Aborted                    (core dumped) ./a.out -love Sydney
            */
            // я просто долбаёб, вроде как данный костыль чинит потенциальную (но при этом и потенциально малую) утечку память
            // - Ametero'z self critic
            for(int pointerrecovery = localclearprefixshit; pointerrecovery != 0; pointerrecovery--){
                woprefix--;
            }

            return 0; 
        }
        free(woprefix);
    }
    return 1;
}
int MiraParser_Value_Arg(const char* arg,MiraParser_Return * var,MiraParser_argument_type type, MiraParser * parser){
    if(!parser){
        return 1;
    }
    if(!var){
        return 1;
    }
    if(MiraParser_Arg(arg, parser) == 1){
        return 1;
    }
    /*
    The essence of this patch is that I'm too lazy to redo the initialization functionality

    Yes, yes, in PARSER_INSTANCE->arguments[SOME_COOL_IDX] there are dirty arguments (meaning with all possible prefixes)

    Basically, there's no point in doing anything here, after exams are over and when I figure out which college to go to, maybe I'll finish it
    text

        - Tired, but not burned out Ametero
    */
    
    char * tint = malloc(strlen(arg) + strlen(parser->prefix) + 16); // 16 reserve bytes ( >_< don't judge me )
    
    strcat(tint,parser->prefix);
    
    strcat(tint, arg);
    
    int idx = 0; // skipping 0 arg
    
    while(idx != parser->arguments_count){
        if(strcmp(tint, parser->arguments[idx]) == 0){
            // arg found
            free(tint);
            break;
        }
        else if(!parser->arguments[idx]){
            // non allocated memory
            free(tint);
            return 1;
        }
        else{
            idx++;
        }
        
    }
    if(!parser->arguments[idx + 1]){
        return 1;
    }
    switch(type){
        case MIRAPARSER_STRING_TYPE:
            /*
            Please don't ask me which function I wrote here previously
            Although in bash (and, like, in Windows too) this is already implemented at the argument processing level
            So... Yeah, what's your opinion about Lisa Minchi (yep, I play that gacha-grinder game)
            */
            if(!parser->arguments[idx + 1]){
                return 1;
            }
            
            if(!parser->arguments[idx+1]){
                return 1;
            }
            var->string = malloc(strlen(parser->arguments[idx+1])+ 1);
            
            if(!var->string){
                return 1;
            }
            strcpy(var->string, parser->arguments[idx + 1]);
            strcat(var->string, "\0");
            return 0;
            break;
        case MIRAPARSER_INT_TYPE:
            var->integer = atoi(parser->arguments[idx + 1]);
            return 0;
            break;
        case MIRAPARSER_CHAR_TYPE:
            var->character = parser->arguments[idx + 1][0];
            return 0;
            break;
        case MIRAPARSER_FLOAT_TYPE:
            var->integer = atof(parser->arguments[idx + 1]);
            return 0;
            break;
        default:
            return 1;
            break;
    }
    
}

int MiraParser_Free_String_Return(MiraParser_Return * var){
    if(!var){
        return 1;
    }
    if(!var->string){
        return 1;
    }
    free(var->string);
    return 0;
}

void MiraParser_Free(MiraParser * parser){
    for(int idx = 0; idx != parser->arguments_count; idx++){
        free(parser->arguments[idx]);
    }
    free(parser->prefix);
    free(parser->arguments);
    free(parser);
}

void MiraParser_Value_Arg_Free(MiraParser_Return * var){
    if(!var){
        return;
    }
    if(!var->string){
        free(var->string);
    }
    free(var);
}

MiraParser_Return * MiraParser_Value_Arg_Open(){
    MiraParser_Return * temp = malloc(sizeof(MiraParser_Return));
    if(!temp){
        return NULL;
    }
    // NO STRING ALLOCATION, ONLY IN MiraParser_Value_Arg
    return temp;
}
