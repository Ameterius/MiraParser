
<img width="250" height="145" alt="image" src="https://github.com/user-attachments/assets/f61b8f7e-4e6d-4867-b42a-0c3b3d5b4a47" />

# MiraParser

Simple CMD arg parser (powered by pure C)

```diff
Pros/Minuses:
+ simplicity
+ written in pure C

- human comments in code (or this a pros?)

@@ +- @@
! There is no direct support for short arguments (Implementation is possible via two parsers (which would require more careful handling))
```

# Functions
## Init. functions

```c
MiraParser * _MiraParser_open(char * argv[], int argc, char * prefix);
```
or

```c
MiraParser_Open(prefix)
```
###### Define: #define MiraParser_Open(prefix) _MiraParser_open((argv), (argc), (prefix))

Used to initialize the parser; the function with the _ prefix is needed in case your operating system provides a different input data format for programs


--

```c
MiraParser_Return * MiraParser_Value_Arg_Open();
```
Used to initialize variables for returning values (for arguments with values).


--

```c
void MiraParser_Free(MiraParser * parser);
```
Used to close the parser

--

```c
void MiraParser_Value_Arg_Free(MiraParser_Return * var);
```
Used to close the variable for returning values

--

```c
int MiraParser_Free_String_Return(MiraParser_Return * var);
```

Used to clean the string stored in the variable for returning values

>[!WARNING]
> if you only needed the variable for a short time, use only MiraParser_Value_Arg_Free.

## Argument checking functions
```c
int MiraParser_Arg(const char * arg, MiraParser * parser);
```
Returns 0 if such argument is present, 1 if absent. Use for validating the presence of an argument (In the expected argument, you must write the argument WITHOUT the prefix declared in MiraParser_open)

## Value retrieval functions

```c
int MiraParser_Value_Arg(const char* arg, MiraParser_Return * var, MiraParser_argument_type type, MiraParser * parser);
```
Parses an argument that implies a value. Value is written to var (In the expected argument, you must write the argument WITHOUT the prefix declared in MiraParser_open). To get the value, BEFORE closing MiraParser_Return use the following approach:
```c
MIRAPARSER_RETURN_INSTANCE->string/character/floating/integer
```

# Argument types
| Type (For MiraParser) | Type (For Humans) |
| :--- | :--- |
| `MIRAPARSER_INT_TYPE` | Integer |
| `MIRAPARSER_FLOAT_TYPE` | Float |
| `MIRAPARSER_STRING_TYPE` | String |
| `MIRAPARSER_CHAR_TYPE` | Character |
| `MIRAPARSER_NO_ACCEPT_VALUE` | No value (better use MiraParser_Arg) |

# Examples

[See there](https://github.com/Ameterius/MiraParser/tree/main/examples)
