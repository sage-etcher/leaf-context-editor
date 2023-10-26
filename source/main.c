/*
   source/main.c
   Leaf Context Editor main entry point source file.
 
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


/* include headers */
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "interpreter.h"


/* constants */
#define HELP_FILE "./HELP"
#define VERSION_FILE "./VERSION"


/* file static variables */
LEDSettings g_settings;


/* file static function prototypes */
static void exit_procedure (void);
static void print_file (char *filename);
static void exit_with_message (char *filename, int exit_code);
static void get_conargs (int argc, char **argv);


/* main program-entry-point */
int
main (int argc, char **argv)
{
    get_conargs (argc, argv);

    /* exit successfully */
    return EXIT_SUCCESS;
}



/* function definitions */
static void
exit_procedure (void)
{
    /* free any allocated memeory */
}


static void
print_file (char *filename)
{
    FILE *fp;
    char c;

    /* open the provided file */
    fp = fopen (filename, "r");
    if (fp == NULL)     /* if the open fails */
    {
        fprintf (stderr, "Error: could not open file \"%s\"\n", filename);
        exit_procedure ();
        exit (EXIT_FAILURE);
    }

    while ((c = fgetc (fp)) != EOF)
    {
        putchar (c);
    }

    fclose (fp); 

}


static void
exit_with_message (char *filename, int exit_code)
{
    print_file (filename);
    exit_procedure ();
    exit (exit_code);
}


static void
get_conargs (int argc, char **argv)
{
    int i,j;
    char *arg;
    bool reached_file;

    /* get options */
    for (i = 1; i < argc; i++)
    {
        /* current arguement */
        arg = argv[i];

        /* check if we reached the filename specifier */
        if ((arg[0] != '-') ||
            (strcmp (arg, "-") == 0))
        {
            reached_file = true;
            break;
        }
    
        /* check for long names */
        if (strcmp (arg, "--read-only") == 0)            /* long read only */
            g_settings.read_only = true;
        else if (strcmp (arg, "--line-numbers") == 0)    /* long show line numbers */
            g_settings.show_line_numbers = true;
        else if (strcmp (arg, "--no-line-numbers") == 0) /* long don't show line numbers */
            g_settings.show_line_numbers = false;
        else if (strcmp (arg, "--help") == 0)            /* long print help page */
            exit_with_message (HELP_FILE, EXIT_SUCCESS);
        else if (strcmp (arg, "--version") == 0)         /* long print version information */
            exit_with_message (VERSION_FILE, EXIT_SUCCESS);
        else            
        { 
            /* check for short names */
            for (j = 1; j < strlen (arg); j++)
            {
                /* check each character in arguement */
                if (arg[j] == 'R')                      /* short read only */
                    g_settings.read_only = true;
                else if (arg[j] == 'L')                 /* short show line numbers */
                    g_settings.show_line_numbers = true;
                else if (arg[j] == 'l')                 /* short don't show line nubmers */
                    g_settings.show_line_numbers = false;
                else if (arg[j] == 'h')                 /* short print help page */
                    exit_with_message (HELP_FILE, EXIT_SUCCESS);
                else                                    /* unrecognized command */
                    exit_with_message (HELP_FILE, EXIT_FAILURE);
            }
        }
    }
    
    /* if no file was reached, panic */
    if (! reached_file)
        exit_with_message (HELP_FILE, EXIT_FAILURE);

    /* get infile */
    g_settings.source_file = argv[i];
    i++;

    /* if no more arguements are provided, use same file for input and output */ 
    if (i < argc)
    {
        /* if more arguments are provided */

        /* expect the next arguement to be either "-o" or "--output", anything
        else should return an error */
        if (!((strcmp (argv[i], "-o") == 0) ||
              (strcmp (argv[i], "--output") == 0)))
        {
            exit_with_message (HELP_FILE, EXIT_FAILURE);
        }

        /* now we need to get the output file from the next arguement */
        i++;

        /* if no next arguement exists, panic */
        if (i >= argc)
        {
            exit_with_message (HELP_FILE, EXIT_FAILURE);
        }

        /* get the dest file */
        g_settings.dest_file = argv[i];
        i++;

        /* if excess arguements are provided, throw a soft warning */
        if (i < argc)
        {
            fprintf (stderr, "WARNING: Excess Arguements provided\n");
        }
    }

}


/* End of File */
