// Build don't link:
// Special g++ Options: -pedantic-errors

const ci=10, *pc = &ci, *const cpc = pc, **ppc;
int i, *p, *const cp = &i;

main()
{
  ci = 1;	// ERROR - bad
  ci++;		// ERROR - bad
  *pc = 2;	// ERROR - bad
  cp = &ci;	// ERROR - bad
  cpc++;	// ERROR - bad
  p = pc;	// ERROR - bad
}
