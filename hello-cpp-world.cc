#include <iostream>
#include<list>
#include "week5/Ex050312.cc"

int main()
{
   using L1 = IntList<2,3,4>; 
   using L2 = IntCons<1, L1>::type;
   using L3 = Generate<3>::type;
   std::cout << L3::Tail::Tail::Head;
   return 0;
}