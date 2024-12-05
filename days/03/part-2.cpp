
#include <cassert>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <ranges>
#include <regex>
#include <sstream>
#include <vector>


int main(int argc, char* argv[])
{
  if (argc != 2)
    return EXIT_FAILURE;
  std::ifstream infile{argv[1]};
  if (not infile.is_open() or infile.bad())
    return EXIT_FAILURE;

  const std::regex re{R"(mul\((-?[0-9]+),(-?[0-9]+)\)|do\(\)|don't\(\))"};

  /// evaluate input line-by-line
  auto result = 0;
  auto enabled = true;
  for (std::string line;;) {
    std::getline(infile, line);
    if (infile.eof())
      break;
    //std::cout << line << std::endl;

    for (auto i = std::sregex_iterator(line.cbegin(), line.cend(), re); i != std::sregex_iterator(); ++i) {
      if ((*i).str() == "do()") {
        enabled = true;
      } else if ((*i).str() == "don't()") {
        enabled = false;
      } else if (enabled) {
        result += std::stoi((*i)[1].str()) * 
                  std::stoi((*i)[2].str());
      }
    }
  }

  std::cout << "Sum of multiplications: " << result << std::endl;

  return EXIT_SUCCESS;
}

