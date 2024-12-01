
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
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

  /// count occurrences in right list
  std::map<std::int32_t, std::int32_t> occurrences_in_right;
  for (auto i: right_list) {
    ++occurrences_in_right[i];
  }

  /// add up score
  auto similarity_score = 0;
  for (auto i: left_list) {
    similarity_score += i * occurrences_in_right[i];
  }

  std::cout << "Similarity score: " << similarity_score << std::endl;

  return EXIT_SUCCESS;
}

