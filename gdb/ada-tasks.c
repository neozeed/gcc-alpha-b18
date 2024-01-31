/* file ada-tasks.c: Ada tasking control for GDB
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

#include <ctype.h> 
#include "defs.h" 
#include "command.h" 
#include "value.h"
#include "language.h"
#include "ada-tasks.h"

enum task_stage
{
  created,
  can_activate,
  active,
  await_dependents,
  passive,
  completing,
  complete,
  terminated
};

static char *task_stage_image[] =
{
  "Created",
  "Can_Activate",
  "Active",
  "Await_Dependents",
  "Passive",
  "Completing",
  "Complete",
  "Terminated"
};

enum accepting_state
{
  Not_Accepting,
  Trivial_Accept,
  Simple_Accept,
  Select_Wait
};

static char *accepting_state_image[] =
{
  "Not_Accepting",
  "Trivial_Accept",
  "Simple_Accept",
  "Select_Wait"
};

struct atcb
{
  void *ID;
  int entry_num;
  unsigned long thread;
  void *task_entry_point;
  void *task_arg;
  int stack_size;
  int base_priority;
  int new_base_priority;
  struct atcb* all_tasks_link;
  struct atcb* activation_link;
  struct atcb* activator;
  struct atcb* parent;
  int master_of_task;
  int master_within;
  int activation_count;
  int awake_count;
  int awaited_dependent_count;
  int terminating_dependent_count;
  int pending_atc_level;
  int atc_nesting_level;
  enum task_stage stage;
  int cancel_was_successful;
  enum accepting_state accepting;
  int aborting;
  int terminate_alternative;
  char * task_image;
};

enum task_state
{
  alive,
  dead
};

struct task_entry
{
  enum task_state state;
  value_ptr task_deref_val;
  void *task_ID;
  int task_num;
  struct task_entry *next_task;
};

static struct task_entry *task_list = NULL;
static int highest_task_num = 0;

static int add_task_entry (p_task_ID, p_task_deref_val)
     void *p_task_ID;
     value_ptr p_task_deref_val;
{
  struct task_entry *new_task_entry = NULL;
  struct task_entry *pt;

  highest_task_num++;
  new_task_entry = xmalloc (sizeof (struct task_entry));
  new_task_entry->task_num = highest_task_num;
  new_task_entry->task_ID = p_task_ID;
  new_task_entry->state = alive;
  new_task_entry->task_deref_val = p_task_deref_val;
  new_task_entry->next_task = NULL;
  pt = task_list;
  if (pt)
    {
      while (pt->next_task)
	pt = pt->next_task;
      pt->next_task = new_task_entry;
    }
  else task_list = new_task_entry;
  return new_task_entry->task_num;
}

static int get_entry_number (p_task_ID, p_task_deref_val)
     void *p_task_ID;
     value_ptr p_task_deref_val;
{
  struct task_entry *pt;

  pt = task_list;
  while (pt != NULL)
    {
      if (pt->task_ID == p_task_ID)
	{
	  pt->state = alive;
	  pt->task_deref_val = p_task_deref_val;
	  return pt->task_num;
	}
      pt = pt->next_task;
    }
  return 0;
}

static int get_simple_entry_number (p_task_ID)
     void *p_task_ID;
{
  struct task_entry *pt;

  pt = task_list;
  while (pt != NULL)
    {
      if (pt->task_ID == p_task_ID)
          return pt->task_num;
      pt = pt->next_task;
    }
  return -1;
}

static value_ptr get_entry_vptr (p_task_num)
     int p_task_num;
{
  struct task_entry *pt;

  pt = task_list;
  while (pt)
    {
      if (pt->task_num == p_task_num)
	return pt->task_deref_val;
      pt = pt->next_task;
    }
  return NULL;
}

void init_task_list()
{
  struct task_entry *pt, *old_pt;

  pt = task_list;
  while (pt)
    {
      old_pt = pt;
      pt = pt->next_task;
      free (old_pt);
    };
  task_list = NULL;

}

static void reinit_task_entries()
{
  struct task_entry *pt;
  
  pt = task_list;
  while (pt)
    {
      pt->state = dead;
      pt = pt->next_task;
    }
}

int valid_task_id (task)
     int task;
{
  return get_entry_vptr (task) != NULL;
}

int get_current_task ()
{
  register value_ptr val;
  void *self_id;
  int result;

  char *exp="system.task_debug.self()";

  if (current_language->la_language != language_ada)
    { 
      return -1; 
    } 
  
  /* first we get the current task running */

  val = parse_and_eval (exp);
  self_id = *(void **)VALUE_CONTENTS(val);

  return get_simple_entry_number (self_id);
}

/* Print detailled information about specified task */

static void
info_task (arg, from_tty)
     char *arg;
     int from_tty;
{
  if (current_language->la_language != language_ada) 
    { 
      printf_filtered ("The current language does not support tasks.\n"); 
      return; 
    } 

  printf_filtered ("Info Task (%d) not implemented yet\n", atoi(arg));
}

/* Print information about currently known tasks */

static void
info_tasks (arg, from_tty)
     char *arg;
     int from_tty;
{
  register value_ptr val;
  struct type *type;
  int task_number,current_task_number;
  struct atcb *temp_task;
  value_ptr deref_val;
  char *name;
  struct task_entry *pt;
  void *self_id;

  char *exp="system.task_debug.info_tasks()";
  char *self_exp="system.task_debug.self()";

  current_task_number = 0;
  task_number = 0;
  
  if (current_language->la_language != language_ada) 
    { 
      printf_filtered ("The current language does not support tasks.\n"); 
      return; 
    } 

  /* first we get the current task running */
  val = parse_and_eval (self_exp);
  self_id = *(void **)VALUE_CONTENTS(val);

  /* then we get a list of tasks created */
  val = parse_and_eval (exp);

  type = check_typedef (VALUE_TYPE (val));

  
  deref_val = value_at_lazy (TYPE_TARGET_TYPE (VALUE_TYPE (val)),           
			     unpack_long (VALUE_TYPE (val),                 
					  VALUE_CONTENTS (val)),NULL);

  temp_task = (struct atcb*)VALUE_CONTENTS(deref_val);
  reinit_task_entries();
  
  printf_filtered("TASK NAME       ID        STATE            THREAD\n"); 
  
  while (temp_task != NULL)
    {
      task_number = get_entry_number (temp_task->ID,deref_val);
      if (task_number == 0)
	task_number = add_task_entry (temp_task->ID,deref_val);
      if (current_task_number == 0)
	current_task_number = task_number;

      if (temp_task->all_tasks_link != NULL)
	{
	  deref_val = value_at (TYPE_TARGET_TYPE (type),
                                (CORE_ADDR)temp_task->all_tasks_link,NULL);
	  temp_task = (struct atcb*)VALUE_CONTENTS(deref_val);
	}
      else
	temp_task = NULL;
    }      

  pt = task_list;
  while (pt)
    {
      if (pt->state == alive)
	{
	  temp_task = (struct atcb*)VALUE_CONTENTS(pt->task_deref_val);
	  printf_filtered(temp_task->ID == self_id ? "*" : " ");
	  printf_filtered(" %-2d", pt->task_num);
	  
	  if (temp_task->task_image)
	    {
	      deref_val = value_at (TYPE_TARGET_TYPE (type),
				    (CORE_ADDR)temp_task->task_image,NULL);
	      name = (char *)VALUE_CONTENTS(deref_val);
	    }
	  else name = "";
	  
	  printf_filtered(" %-10s %-9p %-16s", name, temp_task->ID,
			  task_stage_image[temp_task->stage]);
	  
          if (temp_task->thread < 65536)
	     printf_filtered(" %-9d", (int)temp_task->thread);
          else
	     printf_filtered(" 0x%-9lx", temp_task->thread);
	  
	  printf_filtered("\n");
	}
      pt = pt->next_task;
    }

}

static void
info_tasks_command (arg, from_tty)
     char *arg;
     int from_tty;
{
   if (arg == NULL || *arg == '\000')
      info_tasks (arg, from_tty);
   else
      info_task (arg, from_tty);
}

static void
task_suspend_command (tidlist, from_tty)
     char *tidlist;
     int from_tty;
{
  char *cmd;
  char *p;

  if (tidlist == NULL || *tidlist == '\000')
    error ("Please specify a task ID list");

  for (cmd = tidlist; *cmd != '\000' && !isalpha(*cmd); cmd++);

  while (tidlist < cmd)
    {
      int start, end;
      char exp[50];
      register value_ptr val;
      register value_ptr tp;
      void *temp_task;
      

      start = strtol (tidlist, &p, 10);
      if (p == tidlist)
	error ("Error parsing %s", tidlist);
      tidlist = p;

      while (*tidlist == ' ' || *tidlist == '\t')
	tidlist++;

      if (*tidlist == '-')	/* Got a range of IDs? */
	{
	  tidlist++;	/* Skip the - */
	  end = strtol (tidlist, &p, 10);
	  if (p == tidlist)
	    error ("Error parsing %s", tidlist);
	  tidlist = p;

	  while (*tidlist == ' ' || *tidlist == '\t')
	    tidlist++;
	}
      else
	end = start;

      for (; start <= end; start++)
	{
	  tp = get_entry_vptr (start);
	  
	  
	  if (!tp)
	    {
	      warning ("Unknown task %d.", start);
	      continue;
	    }
	  
	  temp_task = (void *)VALUE_CONTENTS(tp);
	  
	  sprintf(exp, "system.task_debug.suspend_task(0x%p)", temp_task);
	  
	  val = parse_and_eval (exp);
	}
    }
}

static void
task_resume_command (tidlist, from_tty)
     char *tidlist;
     int from_tty;
{
  char *cmd;
  char *p;

  if (tidlist == NULL || *tidlist == '\000')
    error ("Please specify a task ID list");

  for (cmd = tidlist; *cmd != '\000' && !isalpha(*cmd); cmd++);

  while (tidlist < cmd)
    {
      int start, end;
      char exp[50];
      register value_ptr val;
      register value_ptr tp;
      void *temp_task;

      start = strtol (tidlist, &p, 10);
      if (p == tidlist)
	error ("Error parsing %s", tidlist);
      tidlist = p;

      while (*tidlist == ' ' || *tidlist == '\t')
	tidlist++;

      if (*tidlist == '-')	/* Got a range of IDs? */
	{
	  tidlist++;	/* Skip the - */
	  end = strtol (tidlist, &p, 10);
	  if (p == tidlist)
	    error ("Error parsing %s", tidlist);
	  tidlist = p;

	  while (*tidlist == ' ' || *tidlist == '\t')
	    tidlist++;
	}
      else
	end = start;

      for (; start <= end; start++)
	{
	  tp = get_entry_vptr (start);
	  
	  if (!tp)
	    {
	      warning ("Unknown task %d.", start);
	      continue;
	    }
	 
          temp_task = (void *)VALUE_CONTENTS(tp);
 
	  sprintf(exp, "system.task_debug.continue_task(0x%p)", temp_task);

	  val = parse_and_eval (exp);
	}
    }
}

void task_command(tidstr, from_tty)
     char *tidstr;
     int from_tty;
{
}

void
_initialize_tasks ()
{
  static struct cmd_list_element *task_cmd_list = NULL;
  static struct cmd_list_element *task_suspend_list = NULL;
  static struct cmd_list_element *task_resume_list = NULL;
  extern struct cmd_list_element *cmdlist;

  add_info (
        "tasks", info_tasks_command,
	"Without argument: list all known Ada tasks, with status information.\n"
	"info tasks n: print detailled information of task n.\n"
	"Caution: call this function only when debugging an Ada task !");

  add_prefix_cmd ("task", class_run, task_command,
                  "Use this command to switch between tasks.\n\
 The new task ID must be currently known.", &task_cmd_list, "task ", 1,
                  &cmdlist);


  add_prefix_cmd ("suspend", class_run, task_suspend_command,
	   "Suspend a list of tasks.",
	   &task_suspend_list, "suspend ", 1, &task_cmd_list);

  add_prefix_cmd ("resume", class_run, task_resume_command,
	   "Resume a list of tasks.",
	   &task_suspend_list, "resume ", 1, &task_cmd_list);
}
