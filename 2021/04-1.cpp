#pragma warning(push)
#pragma warning(disable : 4365)
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <locale>
#include <numeric>
#include <optional>
#include <string>
#include <sstream>
#include <vector>
#pragma warning(pop)

constexpr std::size_t bingoRows = 5;
constexpr std::size_t bingoColumns = 5;

class BingoBoard final
{
public:
   #pragma warning(suppress : 5045)
   BingoBoard(std::ifstream& input) noexcept
   {
      for (std::size_t row = 0; row < m_board.size(); ++row)
      {
         std::copy_n(std::istream_iterator<int>(input), m_board[row].size(), std::begin(m_board[row]));
         m_sum = std::accumulate(std::begin(m_board[row]), std::end(m_board[row]), m_sum);
      }
   }

   BingoBoard(const BingoBoard&) noexcept = default;

   BingoBoard& operator=(const BingoBoard&) noexcept = delete;

   std::optional<int> GetScore(int number) noexcept
   {
      for (std::size_t row = 0; row < m_board.size(); ++row)
         for (std::size_t column = 0; column < m_board[row].size(); ++column)
            if (m_board[row][column] == number)
            {
               const auto rowCount = --m_rowCounts[row];
               const auto columnCount = --m_columnCounts[column];
               m_sum -= number;
               if (rowCount == 0 || columnCount == 0)
                  return m_sum * number;
               return {};
            }
      return {};
   }

private:
   std::array<std::array<int, bingoColumns>, bingoRows> m_board;
   std::array<int, bingoRows> m_rowCounts = { bingoColumns, bingoColumns, bingoColumns, bingoColumns, bingoColumns };
   std::array<int, bingoColumns> m_columnCounts = { bingoRows, bingoRows, bingoRows, bingoRows, bingoRows };
   int m_sum = 0;
};

struct CommaReader final : public std::ctype<char>
{
   CommaReader() noexcept : std::ctype<char>(get_table()) {};

   CommaReader(const CommaReader&) noexcept = delete;

   CommaReader& operator=(const CommaReader&) noexcept = delete;

   static const std::ctype_base::mask* get_table() noexcept
   {
      static std::vector<std::ctype_base::mask> rc(table_size, std::ctype_base::mask());
      rc[','] = std::ctype_base::space;
      return &rc[0];
   }
};

int main() noexcept
{
   std::ifstream input("input.txt");
   if (!input.is_open())
      return 1;

   std::string numbersLine;
   std::getline(input, numbersLine);
   std::istringstream numbersInput(numbersLine);
   numbersInput.imbue(std::locale(input.getloc(), new CommaReader()));
   std::vector<int> numbers;
   std::copy(std::istream_iterator<int>(numbersInput), std::istream_iterator<int>(), std::back_inserter(numbers));

   std::vector<BingoBoard> boards;
   for (;;)
   {
      std::string emptyLine;
      std::getline(input, emptyLine);
      if (input.eof())
         break;
      boards.emplace_back(input);
   }

   for (const auto number : numbers)
      for (auto& board : boards)
      {
         const auto score = board.GetScore(number);
         if (score.has_value())
         {
            std::cout << score.value() << std::endl;
            return 0;
         }
      }

   return 0;
}
