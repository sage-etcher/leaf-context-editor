/*
   source/input_output.h
   Leaf Context Editor general input/output header file, handles both file 
   and terminal.
 
   Copyright 2023 Sage I. Hendricks

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
#ifndef __LED_INPUT_OUTPUT_HEADER
#define __LED_INPUT_OUTPUT_HEADER__

/* include headers */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "settings_struct.h"
#include "utilities.h"


/* constants */
#define HELP_FILE "./HELP"
#define VERSION_FILE "./VERSION"


/* external function prototypes */
void file_print       (const char *filename);
void file_print_exit  (const char *filename, int exit_code);
void con_get_settings (int argc, char **argv);


#endif /* end run once */


/* End of File */
