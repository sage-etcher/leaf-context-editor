/*
   source/main.c
   Leaf Context Editor main entry point source file.
 
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


/* include headers */
#include <stdlib.h>
#include <malloc.h>

#include "settings_struct.h"
#include "interpreter.h"


/* constants */


/* global veriables */
LEDSettings g_settings;


/* file static variables */


/* file static function prototypes */
static void exit_procedure (void);


/* main program-entry-point */
int
main (int argc, char **argv)
{
    g_settings = default_settings ();        /* load default settings configuration */
    con_get_settings (argc, argv);           /* get console arguement settings */
    if (g_settings.abort_program)
    {
        goto exit_one;
    }

    start_interpreter ();               /* start the interpreter loop */

    /* exit successfully */
exit_one:
    exit_procedure (); 
    return (g_settings.exit_code);
}


/* function definitions */
static void
exit_procedure (void)
{
    /* free any allocated memeory */
    free_settings (g_settings);
}


/* End of File */
