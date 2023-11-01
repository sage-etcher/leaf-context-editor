/*
   source/utilities.c
   Leaf Context Editor's general utilities source file.

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


#include "utilities.h"

/* include headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* function definitions */
char *
string_dup (const char *src)
{
    size_t len = strlen (src) + 1;
    char *dest = malloc (len * sizeof (char));
    if (dest == NULL)
    {
        fprintf (stderr, "failed to allocated memory in string_dup procedure\n");
        exit (EXIT_FAILURE);
    }
    memcpy (dest, src, len * sizeof (char));

    return dest;
}


/* End of File */
