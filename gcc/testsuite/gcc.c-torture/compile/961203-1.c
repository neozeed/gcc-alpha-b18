struct s {
  char a[0x321000*4];
  int x:30, y:30;
};

int
main ()
{
  struct s* p;

  p = (struct s*) 0;
  if (p->x == p->y)
    exit (1);
}
