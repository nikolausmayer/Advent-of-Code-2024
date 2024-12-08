
#include <cstdint>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>


int main(int argc, char* argv[])
{
  if (argc != 2)
    return EXIT_FAILURE;
  std::ifstream infile{argv[1]};
  if (not infile.is_open() or infile.bad())
    return EXIT_FAILURE;

  /// Read and process input line by line
  auto total_calibration_sum = 0ull;
  for (std::string line;;) {
    std::getline(infile, line);
    if (infile.eof())
      break;

    auto test_value = 0ull;
    std::istringstream iss{line};
    iss >> test_value;
    std::vector<std::uint64_t> operands;
    iss.ignore(1);  /// Skip ":"
    for (auto v = 0ull;;) {
      iss >> v;
      if (not iss)
        break;
      operands.push_back(v);
    }

    //std::cout << test_value << " | "; for (auto v: operands) std::cout << v << ", "; std::cout << std::endl;

    bool good = false;
    [&](this const auto& self, auto so_far, auto index) {
      if (good)  /// short-circuit
        return;
      if (so_far == test_value and index == operands.size())
        good = true;
      if (index == operands.size() or so_far > test_value)
        return;
      const auto next = operands[index];
      self(so_far + next, index + 1);
      self(so_far * next, index + 1);
      //self(so_far * next, listview | std::views::drop(1));
    }(operands[0], 1u);

    if (good)
      total_calibration_sum += test_value;
  }

  std::cout << "Total calibration sum of possibly true equations: " << total_calibration_sum << std::endl;

  return EXIT_SUCCESS;
}

