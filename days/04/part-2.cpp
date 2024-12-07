
#include <cstdint>
#include <array>
#include <fstream>
#include <iostream>
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
  std::vector<std::string> map;
  for (std::string line;;) {
    std::getline(infile, line);
    if (infile.eof())
      break;
    map.push_back(line);
  }

  auto x_mas_count = 0;
  
  const auto H = static_cast<std::int32_t>(map.size());
  const auto W = static_cast<std::int32_t>(map[0].size());
  /// I'm a computer vision guy, let's use filters!
  /// '*' are wildcards and match anything
  const std::vector<std::array<std::string,3>> filters{
    {"M*S",
     "*A*",
     "M*S"},
    {"M*M",
     "*A*",
     "S*S"},
    {"S*M",
     "*A*",
     "S*M"},
    {"S*S",
     "*A*",
     "M*M"},
  };
  for (auto y = 1 ; y < H - 1; ++y) {
    for (auto x = 1 ; x < W - 1; ++x) {
      for (const auto& filter: filters) {
        auto good = true;
        for (auto dy = -1; dy <= 1; ++dy) {
          for (auto dx = -1; dx <= 1; ++dx) {
            if (const auto c = filter[dy+1][dx+1];
                c != '*' and map[y+dy][x+dx] != c) {
              good = false;
            }
          }
        }
        if (good) {
          ++x_mas_count;
          break;
        }
      }
    }
  }

  std::cout << "X-MAS appears " << x_mas_count << " times." << std::endl;

  return EXIT_SUCCESS;
}

