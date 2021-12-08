#pragma warning(push)
#pragma warning(disable : 4365)
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#pragma warning(pop)

struct Command
{
   std::string direction;
   int distance;
#pragma warning(suppress : 4820)
};

std::istream& operator>>(std::istream& input, Command& command)
{
   input >> command.direction >> command.distance;
   return input;
}

int main()
{
   std::ifstream input("input.txt");
   if (!input.is_open())
      return 1;
   std::vector<Command> commands;
   std::copy(std::istream_iterator<Command>(input), std::istream_iterator<Command>(), std::back_inserter(commands));
   input.close();

   int distance = 0, depth = 0;
   for (const auto& command : commands)
   {
      if (command.direction == "forward")
         distance += command.distance;
      else
         depth += (command.direction == "down" ? 1 : -1) * command.distance;
   }
   std::cout << distance * depth << std::endl;

   return 0;
}
