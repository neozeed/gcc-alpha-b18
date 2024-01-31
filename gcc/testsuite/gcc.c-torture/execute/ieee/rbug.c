double d (unsigned long long k)
{
  double x;

  x = (double) k;
  return x;
}

float s (unsigned long long k)
{
  float x;

  x = (float) k;
  return x;
}

float t (long long k)
{
  float x;

  x = (float) k;
  return x;
}

main ()
{
  unsigned long long int k;
  long long int l;
  double x;
  float y;

  /* CYGNUS LOCAL -- meissner/32bit doubles */
  if (sizeof (double) >= 8)
    {
      k = 0x8693ba6d7d220401ULL;
      x = d (k);
      k = (unsigned long long) x;
      if (k != 0x8693ba6d7d220800ULL)
	abort ();
    }
  /* END CYGNUS LOCAL -- meissner/32bit doubles */

  /* unsigned "negatives" */
  k = 0x8234508000000001ULL;
  x = s (k);
  k = (unsigned long long) x;
  if (k != 0x8234510000000000ULL)
    abort ();

  /* signed */
  l = 0x7134504000000001LL;
  x = t (l);
  l = (long long) x;
  if (l != 0x7134508000000000LL)
    abort ();

  /* signed, no function involved (optimizer issue) */
  l = 0x7234504000000001LL;
  y = (float)l;
  l = (long long) y;
  if (l != 0x7234508000000000LL)
    abort ();

  /* signed, no function involved, subsequent arithmetic (has failed!) */
  l = 0x7334504000000001LL;
  y = (float)l + 0.0;
  l = (long long) y;
  if (l != 0x7334508000000000LL)
    abort ();

  exit (0);
}
