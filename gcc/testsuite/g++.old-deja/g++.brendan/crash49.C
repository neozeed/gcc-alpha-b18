// Build don't link: 
// GROUPS passed old-abort
#include<iostream.h>

const /* int */ keys = 10;
const /* int */ key[keys] = {6, key[1], 2, keys, 1, 7, 6, key[2], key[8]};

void main()
{ // ERROR - return type for main
        for(int i = 0; i < keys;) cout << key[i++] << " ";
        endl(cout);
}
