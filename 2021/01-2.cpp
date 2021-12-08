#pragma warning(push)
#pragma warning(disable : 4365)
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#pragma warning(pop)

int main()
{
   std::ifstream input("input.txt");
   if (!input.is_open())
      return 1;
   std::vector<int> measurements;
   std::copy(std::istream_iterator<int>(input), std::istream_iterator<int>(), std::back_inserter(measurements));
   input.close();

   int countIncreasing = 0;
   int lineNumber = 0;
   int previous3 = 0, previous2 = 0, previous1 = 0;
   for (int current : measurements)
   {
      if (++lineNumber > 3 && previous2 + previous1 + current > previous3 + previous2 + previous1)
         ++countIncreasing;
      previous3 = previous2;
      previous2 = previous1;
      previous1 = current;
   }
   std::cout << countIncreasing << std::endl;

   return 0;
}
