namespace N { // WARNING - namespaces mostly broken
  int i;
};

using namespace N; // ERROR - using not implemented

main() {
  return i;	// gets bogus error - XFAIL *-*-*
} // gets bogus error - XFAIL *-*-*
