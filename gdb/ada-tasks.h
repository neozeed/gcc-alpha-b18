/* file ada-tasks.h:    Ada tasking control for GDB
   Copyright 1997 Free Software Foundation, Inc.
   Contributed by Ada Core Technologies, Inc.

   This file is part of GDB.

   [$Id$], June 97
   Author: Roch-Alexandre Nomine Beguin
   Modified by: Arnaud Charlet, Roch-Alexandre Nomine Beguin

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

*/

#ifndef ADA_TASKS_H
#define ADA_TASKS_H 

extern int valid_task_id PARAMS ((int));
extern int get_current_task PARAMS ((void)); 
extern void init_task_list PARAMS ((void));

#endif /* ADA_TASKS_H */
