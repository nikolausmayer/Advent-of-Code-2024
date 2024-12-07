
#include <cstdint>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>


int main(int argc, char* argv[])
{
  if (argc != 2)
    return EXIT_FAILURE;
  std::ifstream infile{argv[1]};
  if (not infile.is_open() or infile.bad())
    return EXIT_FAILURE;

  /// read in input
  std::map<std::int32_t, std::set<std::int32_t>> map_page_to_mustbebefore;
  std::vector<std::vector<std::int32_t>> updates;
  for (std::string line;;) {
    std::getline(infile, line);
    if (infile.eof())
      break;
    if (line.size() == 0)  /// empty separation line between rules and updates
      continue;

    if (line[2] == '|') {
      /// Update
      map_page_to_mustbebefore[std::stoi(line.substr(3))].insert(std::stoi(line.substr(0, 2)));
    } else {
      /// Rule
      updates.push_back({});
      for (auto i = 0u; i < line.size() - 1; i += 3) {
        updates.back().push_back(std::stoi(line.substr(i, 2)));
      }
    }
  }

  //for (auto [m,as]: map_page_to_mustbebefore) {
  //  std::cout << m << ": [ ";
  //  for (auto a: as) std::cout << a << " ";
  //  std::cout << "]\n";
  //}
  //for (auto u: updates) {
  //  std::cout << "[ ";
  //  for (auto s: u) std::cout << s << " ";
  //  std::cout << "]\n";
  //}

  auto good_sum = 0;

  for (auto& update: updates) {
    auto good_update = true;
    for (auto i = 0u; i < update.size() - 1; ++i) {
loopstart:
      if (not map_page_to_mustbebefore.contains(update[i]))
        continue;
      for (auto page: map_page_to_mustbebefore[update[i]]) {
        for (auto j = i + 1; j < update.size(); ++j) {
          if (page == update[j]) {
            /// If two incorrectly ordered pages are found, swap them in the
            /// update list and restart the iteration
            good_update = false;
            std::swap(update[i], update[j]);
            goto loopstart;
          }
        }
      }
    }
    if (not good_update) {
      good_sum += update[update.size() / 2];
    }
  }

  std::cout << "Sum of reordered updates' middle page numbers: " << good_sum << std::endl;

  return EXIT_SUCCESS;
}

