main ()
{
  int i = 0;

  unsigned long int z = 0;

  do {
    z -= 0x00004000;
    i++;
    if (i > 0x00040000)
      abort ();
  } while (z > 0);

  exit (0);
}
