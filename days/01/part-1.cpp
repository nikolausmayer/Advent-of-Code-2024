
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>


int main(int argc, char* argv[])
{
  if (argc != 2) {
    return EXIT_FAILURE;
  }
  std::ifstream infile{argv[1]};
  if (not infile.is_open() or infile.bad()) {
    return EXIT_FAILURE;
  }

  /// get input
  std::vector<std::int32_t> left_list, right_list;
  for (;;) {
    std::int32_t left, right;
    infile >> left >> right;
    if (infile.eof()) {
      break;
    }
    left_list.push_back(left);
    right_list.push_back(right);
  }

  /// sort lists
  std::ranges::sort(left_list);
  std::ranges::sort(right_list);

  /// add up distances
  auto total_distance = 0;
  for (auto [left, right]: std::views::zip(left_list, right_list)) {
    total_distance += std::abs(left - right);
  }
  
  std::cout << "Total distance: " << total_distance << std::endl;

  return EXIT_SUCCESS;
}

