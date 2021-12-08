#pragma warning(push)
#pragma warning(disable : 4365)
#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>
#pragma warning(pop)

int main()
{
   constexpr auto numberOfBits = 12;

   std::ifstream input("input.txt");
   if (!input.is_open())
      return 1;
   std::vector<std::bitset<numberOfBits>> bits;
   std::copy(std::istream_iterator<std::bitset<numberOfBits>>(input), std::istream_iterator<std::bitset<numberOfBits>>(), std::back_inserter(bits));
   input.close();

   std::bitset<numberOfBits> gamma;
   for (std::size_t pos = 0; pos < numberOfBits; ++pos)
   {
      auto countOnes = 0u;
      for (const auto& bitset : bits)
         if (bitset.test(pos))
            ++countOnes;
      gamma.set(pos, countOnes * 2 > bits.size());
   }
   auto gammaRate = gamma.to_ulong();
   std::cout << gammaRate * gamma.flip().to_ulong() << std::endl;

   return 0;
}
