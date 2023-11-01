/*
   source/settings_struct.c
   Leaf Context Editor settings structure source file. 
 
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


#include "settings_struct.h"

/* include headers */
#include <stdbool.h>
#include <malloc.h>


/* global variables */


/* file static variables */


/* file static function prototypes */


/* function definitions */
LEDSettings
default_settings (void)
{
    LEDSettings s;

    /* filename strings */
    s.source_file       = NULL;
    s.dest_file         = NULL;

    /* configuration */
    s.read_only         = false;
    s.show_line_numbers = true;

    /* program runtime */
    s.abort_program     = false;
    s.exit_code         = EXIT_SUCCESS;

    return s;
}


void
free_settings (LEDSettings s)
{
    /* if source_file array is allocated, free it */
    if (s.source_file != NULL)
    {
        free (s.source_file);
    }

    /* if dest_file array is allocated, free it */
    if (s.dest_file != NULL)
    {
        free (s.dest_file);
    }
}


/* End of File */
