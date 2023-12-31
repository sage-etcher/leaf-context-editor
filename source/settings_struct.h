/*
   source/settings_struct.h
   Leaf Context Editor settings structure header file. 
 
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
#ifndef __LED_SETTINGS_STRUCT_HEADER__
#define __LED_SETTINGS_STRUCT_HEADER__

/* include headers */
#include <stdbool.h>
#include <malloc.h>


/* custom datatypes */
typedef struct LEDSettings
{
    char *source_file;
    char *dest_file;

    bool read_only;
    bool show_line_numbers;

    bool abort_program;
    int  exit_code;
} LEDSettings;


/* global variables */
extern LEDSettings g_settings;


/* external function prototypes */
LEDSettings default_settings (void);
void free_settings (LEDSettings s);


#endif /* end run once */


/* End of File */
