// g++ 1.36.1 bug 900114_01

// g++ fails to flag errors for all cases where the inner statement
// in a conditional or looping statement is a simple declarative statement.

// Cfront 2.0 catches all these errors.

// keywords: declarative statement, conditional statement, looping statement

// Update 10/17/94:  g++ is correct.  From the September 1994 WP, section 6.4:
//
// The  statement  in a selection-statement (both statements, in the else
// form  of  the  if  statement)  implicitly  defines   a   local   scope
// (_basic.scope_).   That  is, if the statement in a selection-statement
// is a single statement and not a compound-statement, it is as if it was
// rewritten  to  be  a compound-statement containing the original state-
// ment.  For example,
//         if (x)
//             int i;
// may be equivalently rewritten as
//         if (x) {
//             int i;
//	    }
// Thus after the if statement, i is no longer in scope.

// 06/08/95 -- so I assume we're keeping this because we think we should
//             do what Cfront 3.0 does and warns that the decl is the
//             only thing in the if/do/for statements?  -- B

int i;

void func ()
{

  if (i)
    int then_part;	// WARNING - XFAIL *-*-*
  else
    int then_part;	// WARNING - XFAIL *-*-*

  while (i)
    int while_body;	// WARNING - XFAIL *-*-*

  do
    int do_body;	// WARNING - XFAIL *-*-*
  while (i);

  for (;;)
    int for_body;	// WARNING - XFAIL *-*-*
}

int main () { return 0; }
