/* This file tests for an optimizer bug that affects machines like the Alpha,
   where only aligned accesses are allowed, and which uses a load-modify-store
   sequence to modify distinct variables on full (64-bit) words.

   This may not be completely minimized, but if your machine does NOT exhibit
   the bug, don't try to minimize it further (and maybe even then), as the
   sequence necessary to trigger the bug is trickier than it might appear.
   (This is a scheduler bug.)

   Details (alpha):

       The normal sequence to modify an isolated (simple scalar) variable
       of a type for which there aren't direct instructions (short, char)
       on the alpha is:

       ldq_u var <from some address; the address is maksed to quadword aligned)
       msk...    <to set the proper value (maybe several instructions) in
		  the proper place in the quadword).
       stq_u var <back to where it came from; presumably the variables NEAR
		 var, although stored again, weren't actually changed.)

     Bug:
       stores to locations near var (same quadword) were allowed to be
       between the ldq_u and stq_u, consequently causing the effect of
       those intermediate stores to be cancelled by the stq_u.

       In this testcase (on the compiler exhibiting the bug), three ldq_u's
       to the same quadword were executed, then the mods done, then the
       stq_s done.  (Actually, another stl was also inserted!)

       A correct compiler cannot allow stores between a ldq_u and the 
       corresponding stq_u unless it knows something about the addresses
       of the variables involved (for extern's, it can't, but it might
       be able to for stack variables.)
*/
      
struct _ffewhere_file_
  {
    unsigned int length;
    char text[1];
  };
typedef struct _ffewhere_file_ *ffewhereFile;

struct _ffewhere_line_
  {
    char content[1];
  };
typedef struct _ffewhere_line_ *ffewhereLine;


static char *input_filename;

struct _lextoken_
  {
    long int id_;		 
    int type;
  };
typedef struct _lextoken_ *ffelexToken;

static int lineno;
static ffewhereFile ffelex_current_wf_;
static ffelexToken ffelex_token_;

/* to force alignment */
static long double t;

/* The offendeded and offending variables */
static unsigned short int ffelex_number_of_tokens_;
static unsigned short ffelex_current_wl_;
static unsigned char ffelex_current_wc_;
static struct _ffewhere_line_ ffewhere_unknown_line_;

static unsigned long int ffelex_label_tokens_;
void ffelex_file_fixed (ffewhereFile wf)
{
  int disallow_continuation_line;
  int ignore_disallowed_continuation;
  int latest_char_in_file = 0;	 
  lineno = 0;
  input_filename = (( wf )->text) ;
  ffelex_current_wf_ = wf;
  disallow_continuation_line = 1 ;
  ignore_disallowed_continuation = 0 ;
  ffelex_token_->type = 0;
  ffelex_number_of_tokens_ = 1;
  ffelex_label_tokens_ = 0;
  ffelex_current_wl_ = 2;
  ffelex_current_wc_ = 3;
  latest_char_in_file = '\n';

}

main() {
  ffewhereFile wf;
  struct _lextoken_ lt;
  ffelex_token_ = &lt;
  ffelex_file_fixed(wf);
  if (ffelex_number_of_tokens_ != 1) abort();
  if (ffelex_current_wl_ != 2) abort();
  if (ffelex_current_wc_ != 3) abort();
  /* printf("%d %d %d\n", ffelex_number_of_tokens_, ffelex_current_wl_, ffelex_current_wc_); /* */
  exit(0);
}
