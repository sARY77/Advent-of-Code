#pragma warning(push)
#pragma warning(disable : 4365)
#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <vector>
#pragma warning(pop)

constexpr auto numberOfBits = 12;

#pragma warning(suppress : 5045)
bool VerifyCommon(std::bitset<numberOfBits> bitset, std::bitset<numberOfBits> common, int setPos) noexcept
{
   for (int verifyPos = numberOfBits - 1; verifyPos > setPos; --verifyPos)
      if (bitset.test(static_cast<unsigned>(verifyPos)) != common.test(static_cast<unsigned>(verifyPos)))
         return false;
   return true;
}

void GetCommon(const std::vector<std::bitset<numberOfBits>>& bits, std::bitset<numberOfBits>& common, bool isMostCommon) noexcept
{
   for (int setPos = numberOfBits - 1; setPos >= 0; --setPos)
   {
      auto count = 0u, countOnes = 0u;
      for (const auto& bitset : bits)
         if (VerifyCommon(bitset, common, setPos))
         {
            ++count;
            if (bitset.test(static_cast<unsigned>(setPos)))
               ++countOnes;
         }
      const auto isOneMoreCommon = countOnes * 2 >= count;
      common.set(static_cast<unsigned>(setPos), count == 1 ? count == countOnes : (isMostCommon ? isOneMoreCommon : !isOneMoreCommon));
   }
}

int main() noexcept
{
   std::ifstream input("input.txt");
   if (!input.is_open())
      return 1;
   std::vector<std::bitset<numberOfBits>> bits;
   std::copy(std::istream_iterator<std::bitset<numberOfBits>>(input), std::istream_iterator<std::bitset<numberOfBits>>(), std::back_inserter(bits));
   input.close();

   std::bitset<numberOfBits> mostCommon, leastCommon;
   for (int setPos = numberOfBits - 1; setPos >= 0; --setPos)
   {
      GetCommon(bits, mostCommon, true /*isMostCommon*/);
      GetCommon(bits, leastCommon, false /*isMostCommon*/);
   }
   std::cout << mostCommon.to_ulong() * leastCommon.to_ulong() << std::endl;

   return 0;
}
