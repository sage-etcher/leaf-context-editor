/*
   source/interpreter.h
   Leaf Context Editor command interpreter header file. 
 
   Copyright 2023 Leaf Software Foundation

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. 

*/


/* run once */
#pragma once
#ifndef __LED_INTERPRETER_HEADER__
#define __LED_INTERPRETER_HEADER__

/* include headers */
#include <stdio.h>
#include <stdbool.h>

#include "conio.h"
#include "fileio.h"


/* custom datatypes */
typedef struct LEDSettings
{
    char *source_file;
    char *dest_file;

    bool read_only;
    bool show_line_numbers;
} LEDSettings;


/* constants */
#define DEFAULT_SETTINGS (LEDSettings){NULL, NULL, false, true}


/* global variables */


/* external function prototypes */
void interpreter_test (void);


#endif /* end run once */


/* End of File */
