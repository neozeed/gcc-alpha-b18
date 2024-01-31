// excess errors test - XFAIL *-*-*
// Build don't link: 
// GROUPS passed old-abort
class A {};

class SimQuery
{
public:
  SimQuery();
  ~SimQuery();
  int SetMeshFile(char name[]);
protected:
  A& scaling;
  A* mesh;
};

SimQuery::SimQuery():scaling(A) {}// ERROR - .*

SimQuery::~SimQuery() {}

int SimQuery::SetMeshFile(char name[])
{
  mesh = new C;// ERROR - .*
}
