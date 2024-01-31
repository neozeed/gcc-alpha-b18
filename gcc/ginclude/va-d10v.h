/* GNU C stdarg/varargs support for the D10V */

/* Define __gnuc_va_list.  */
#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
typedef struct __va_list_tag {
  short *__va_arg_ptr;		/* start of the register save area */
  short __va_arg_num;		/* argument number */
} __va_list[1], __gnuc_va_list[1];

#endif /* not __GNUC_VA_LIST */

/* If this is for internal libc use, don't define anything but
   __gnuc_va_list.  */
#if defined (_STDARG_H) || defined (_VARARGS_H)

/* Common code for va_start for both varargs and stdarg.  This depends
   on the format of the CUMULATIVE_ARGS type.  On the d10v, we use just
   a single word that is the argument number.  */

#define __va_start_common(AP)						\
__extension__ ({							\
   (AP)->__va_arg_ptr = (short *) __builtin_saveregs ();		\
   (AP)->__va_arg_num = __builtin_args_info (0);			\
   (void)0;								\
})

#ifdef _STDARG_H /* stdarg.h support */

/* Calling __builtin_next_arg gives the proper error message if LASTARG is
   not indeed the last argument.  */
#define va_start(AP,LASTARG) \
  (__builtin_next_arg (LASTARG), __va_start_common (AP))

#else /* varargs.h support */

#define va_start(AP) __va_start_common (AP)
#define va_alist __builtin_va_alist
#define va_dcl register int va_alist; ...

#endif /* _STDARG_H */

/* Nothing needs to be done to end varargs/stdarg processing */
#define va_end(AP)

/* Values returned by __builtin_classify_type.  */
enum __type_class
{
  __no_type_class = -1,
  __void_type_class,
  __integer_type_class,
  __char_type_class,
  __enumeral_type_class,
  __boolean_type_class,
  __pointer_type_class,
  __reference_type_class,
  __offset_type_class,
  __real_type_class,
  __complex_type_class,
  __function_type_class,
  __method_type_class,
  __record_type_class,
  __union_type_class,
  __array_type_class,
  __string_type_class,
  __set_type_class,
  __file_type_class,
  __lang_type_class
};

/* Return whether a type is passed by reference.  Currently in the
   d10v, the 64 bit types (long long & long double) are passed
   by reference.  */
#define __va_64bit_p(TYPE) \
  ((__builtin_classify_type (*(TYPE *)0) == __integer_type_class && sizeof (TYPE) >= 8) \
   || (__builtin_classify_type (*(TYPE *)0) == __real_type_class && sizeof (TYPE) >= 8))

#define __va_by_reference_p(TYPE) __va_64bit_p(TYPE)

/* Return whether a type is an aggregate.  */
#define __va_aggregate_p(TYPE) (__builtin_classify_type (*(TYPE *)0) >= __record_type_class)

#define va_arg(AP,TYPE)							\
__extension__ (*({							\
  register TYPE *__ptr;							\
									\
  if (__va_by_reference_p (TYPE))					\
    __ptr = *(TYPE **)(void *)((AP)->__va_arg_ptr + (AP)->__va_arg_num++); \
									\
  else									\
    {									\
      if (__va_aggregate_p (TYPE)					\
	  && sizeof (TYPE) > 4						\
	  && (AP)->__va_arg_num < 4)					\
	(AP)->__va_arg_num = 4;						\
									\
      if (sizeof (TYPE) > 2 && (((AP)->__va_arg_num) & 1) != 0)		\
	(AP)->__va_arg_num++;						\
									\
      __ptr = (TYPE *)(((char *)(void *)				\
			((AP)->__va_arg_ptr + (AP)->__va_arg_num))	\
		       + (sizeof (TYPE) < 2));				\
      (AP)->__va_arg_num += (sizeof (TYPE) + 1) / 2;			\
    }									\
									\
  __ptr;								\
}))

#endif /* defined (_STDARG_H) || defined (_VARARGS_H) */
