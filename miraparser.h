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
#pragma once

typedef enum{
    MIRAPARSER_INT_TYPE = 1,
    MIRAPARSER_FLOAT_TYPE,
    MIRAPARSER_STRING_TYPE,
    MIRAPARSER_CHAR_TYPE,
    MIRAPARSER_NO_ACCEPT_VALUE = -1 // for arguments like --install (use MiraParser_Arg please)
}  MiraParser_argument_type;

typedef struct{
    int arguments_count; // littery argc
    char * prefix; // prefix for arg parse
    char ** arguments; // littery argv
} MiraParser;

// i'am tired of using `void *`
typedef struct{
    char character;
    char * string;
    float floating;
    int integer;
} MiraParser_Return;

// Creates a parser and writes the obtained command-line arguments
#define MiraParser_Open(prefix) _MiraParser_open((argv), (argc), (prefix))

// Creates a parser and writes the obtained command-line arguments (better use MiraParser_open)
MiraParser * _MiraParser_open(char * argv[], int argc, char * prefix);

// Returns 0 if such argument is present, 1 if absent. Use for validating the presence of N argument
//(In the expected argument, you must write the argument WITHOUT the prefix declared in MiraParser_open)
int MiraParser_Arg(const char * arg, MiraParser * parser);

/*
Parser-independent function

Required for arguments with values

Must be freed after finishing work with the argument
(via MiraParser_Value_Arg_Free)

It is permissible to use one instance for arguments, but it is necessary to work out the handling of the received data
*/
MiraParser_Return * MiraParser_Value_Arg_Open();

/*
Parses an argument that implies a value

Value is written to var

(In the expected argument, you must write the argument WITHOUT the prefix declared in MiraParser_open)

to get the value, BEFORE closing MiraParser_Return use the following approach
example:
MiraParser_Return * L = MiraParser_Value_Arg_Open();
MiraParser_Value_Arg("socks", L ,MIRAPARSER_INT_TYPE, PARSER_INSTANCE);
printf("socks total: %i\n", L->integer);
MiraParser_Value_Arg_Free(L);
*/
int MiraParser_Value_Arg(const char* arg,MiraParser_Return * var,MiraParser_argument_type type, MiraParser * parser);

/*
Clears the memory allocated for the string in var

Returns 0 on success, 1 on error

WARN

If you have ALREADY processed the string as needed and plan to finish working with the current MiraParser_Return
then call only MiraParser_Value_Arg_Free; 
there is no need to call MiraParser_Free_String_Return 
(this function is for long-term work with multiple strings, though it is still better to create different MiraParser_Return instances).
*/
int MiraParser_Free_String_Return(MiraParser_Return * var);

// Frees the Return (the memory allocated for it).
void MiraParser_Value_Arg_Free(MiraParser_Return * var);

/*
Frees the parser (the memory allocated for it).

! It is advisable to call this towards the end of parsing to avoid occupying memory !

!! Accessing a freed parser will cause a SEGFAULT !!
*/
void MiraParser_Free(MiraParser * parser);
