/*
   source/input_output.c
   Leaf Context Editor general input/output source file, handles both file 
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


#include "input_output.h"

/* include headers */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "settings_struct.h"
#include "utilities.h"


/* file static function prototypes */
static bool reached_source_file (const char *arguement);
static bool out_file_specifier  (const char *arguement);
static bool long_setting_name   (const char *arguement);
static bool short_setting_name  (const char *arguement);
static int  conargs_get_config  (int start, int max, char **arg_list);
static int  conargs_get_source  (int start, int max, char **arg_list);
static int  conargs_get_dest    (int start, int max, char **arg_list);


/* function definitions */
void
file_print (const char *filename)
{
    FILE *fp;
    char c;

    /* open the provided file */
    fp = fopen (filename, "r");
    if (fp == NULL)     /* if the open fails */
    {
        fprintf (stderr, "Error: could not open file \"%s\"\n", filename);
        return;
    }

    while ((c = fgetc (fp)) != EOF)
    {
        putchar (c);
    }

    fclose (fp); 

}


void
file_print_exit (const char *filename, int exit_code)
{
    file_print (filename);
    g_settings.abort_program = true;
    g_settings.exit_code     = exit_code;
}


static bool
reached_source_file (const char *arguement)
{
    /* use the standard input buffer as file in */
    if (strcmp (arguement, "-") == 0)
        return true;

    /* if arguement isn't a solo "-", but begins with a '-' character, it is
    recognized as a command/config, NOT a source file */
    if (arguement[0] == '-')
        return false;

    /* for anything that is explicitly mentioned in a guard statement, assume
    to be the source file */
    return true;
}


static bool
long_setting_name (const char *arguement)
{
    /* sets value in settins structure and return if a match was found */

    /* if-else train of string compares */
    if (strcmp (arguement, "--read-only") == 0)
    {
        g_settings.read_only = true;
        return true;
    }
    else if (strcmp (arguement, "--line-numbers") == 0)
    {
        g_settings.show_line_numbers = true;
        return true;
    }
    else if (strcmp (arguement, "--no-line-numbers") == 0)
    {
        g_settings.show_line_numbers = false;
        return true;
    }
    else if (strcmp (arguement, "--help") == 0)
    {
        file_print_exit (HELP_FILE, EXIT_SUCCESS);
        return true;
    }
    else if (strcmp (arguement, "--version") == 0)
    {
        file_print_exit (VERSION_FILE, EXIT_SUCCESS);
        return true;
    }

    /* no match found */
    return false;
}


static bool
short_setting_name (const char *arguement)
{
    int i;
    size_t len = strlen (arguement); 


    /* start at index of 1 to skip the preceeding '-' char */
    for (i = 1; i < len; i++)
    {
        /* check each character in arguement */
        switch (arguement[i])
        {
        case 'R':
            g_settings.read_only = true;
            break;
        case 'L':
            g_settings.show_line_numbers = true;
            break;
        case 'l':
            g_settings.show_line_numbers = false;
            break;
        case 'h':
            file_print_exit (HELP_FILE, EXIT_SUCCESS);
            return true; /* stop checking */
            break;       /* unreachable */
        default: /* no match found */
            return false;
            break;
        }
    }

    /* if an unknown character is found, it will exit false from the switch
    statement, so if we get to this point, we know all the precceeding 
    characters were vaid */
    return true;
}


static int 
conargs_get_config (int start, int max, char **arg_list)
{
    int index; 

    for (index = start; index < max; index++)
    {
        /* check if we should abort */
        if (g_settings.abort_program)
        {
            break;
        }

        /* check if we have reached the source file */
        if (reached_source_file (arg_list[index]))
        {
            break;
        }

        /* check if the arguement matches any long names */
        if (long_setting_name (arg_list[index]))
        {   /* if the string is a valid long name, stop, and goto next arg */
            continue;
        }

        /* check if the arguement matches any short names */
        if (short_setting_name (arg_list[index]))
        {   /* if string is valid short name(s), stop, and goto next arg */
            continue;
        }


        /* if no match is found and the argument isn't the source file,
        print help screen and abort program */
        file_print_exit (HELP_FILE, EXIT_FAILURE);
        break; 
    }

    return index;
}


static int 
conargs_get_source (int start, int max, char **arg_list)
{
    int index = start;
    
    /* make sure that there is atleast 1 element left in arg_list */
    if (start >= max)
    {
        /* no source file present, throw error */
        file_print_exit (HELP_FILE, EXIT_FAILURE);
        return index;
    }

    /* copy filename into settings variable */
    g_settings.source_file = string_dup (arg_list[index]);

    /* return */
    return (index + 1);
}


static bool
out_file_specifier (const char *arguement)
{
    /* if the arguement matches, return true */
    if ((strcmp (arguement, "-o") == 0) ||
        (strcmp (arguement, "--output") == 0))
    {
        return true;
    }

    /* otherwise ret false */
    return false;
}

static int 
conargs_get_dest (int start, int max, char **arg_list)
{
    int index = start;

    /* if we are already at the end of the array use source file for both 
    input and output */
    if (start >= max)
    {
        g_settings.dest_file = string_dup (g_settings.source_file);
        return index;
    }

    /* otherwise, more data is available to parse */
    
    /* if no outfile specifier is given, throw an error */
    /* also move to next index */
    if (! out_file_specifier (arg_list[index++]))
    {
        file_print_exit (HELP_FILE, EXIT_FAILURE);
        return index;
    }

    /* if we are at the end of the given data, yell */
    if (index >= max)
    {
        file_print_exit (HELP_FILE, EXIT_FAILURE);
        return index;
    }

    /* output file specifer is present and atleast 1 element is present after
    it. grab the first elements following and save it as a destination file */
    /* also move to the next index */
    g_settings.dest_file = string_dup (arg_list[index++]);

    return index; 
}


void
con_get_settings (int argc, char **argv)
{
    int index = 1;

    /* get configuration settings */
    index = conargs_get_config (index, argc, argv);
    if (g_settings.abort_program)
        return;
   
    /* get source file */
    index = conargs_get_source (index, argc, argv);
    if (g_settings.abort_program)
        return;
   
    /* get destination file */
    index = conargs_get_dest (index, argc, argv);
    if (g_settings.abort_program)
        return;

    /* if excess arguements are provided, throw a soft (NON FATAL) warning */
    if (index < argc)
    {
        fprintf (stderr, "WARNING: Excess Arguements provided\n");
    }

    return;
}


/* End of File */
