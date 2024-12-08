
#include <cstdint>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
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

  /// Read and process input line by line
  std::vector<std::string> map;
  for (std::string line;;) {
    std::getline(infile, line);
    if (infile.eof())
      break;
    map.push_back(line);
  }

  const auto H = static_cast<std::int32_t>(map.size());
  const auto W = static_cast<std::int32_t>(map[0].size());

  /// Collect antenna locations per frequency
  std::map<char, std::vector<std::array<std::int32_t,2>>> map_frequency_to_antennas_xy;
  for (auto y = 0; y < H; ++y)
    for (auto x = 0; x < W; ++x)
      if (const auto c = map[y][x]; c != '.')
        map_frequency_to_antennas_xy[c].push_back({x,y});

  /// Collect antinodes per frequency / antenna set
  std::set<std::array<std::int32_t,2>> antinode_locations;
  for (const auto [_, antennas_xy]: map_frequency_to_antennas_xy) {
    for (auto i = 0u; i < antennas_xy.size() - 1; ++i) {
      const auto [ix, iy] = antennas_xy[i];
      for (auto j = i + 1; j < antennas_xy.size(); ++j) {
        const auto [jx, jy] = antennas_xy[j];
        {
          const auto x = 2 * ix - jx, y = 2 * iy - jy;
          if (x >= 0 and x < W and y >= 0 and y < H)
            antinode_locations.insert({x, y});
        }
        {
          const auto x = 2 * jx - ix, y = 2 * jy - iy;
          if (x >= 0 and x < W and y >= 0 and y < H)
            antinode_locations.insert({x, y});
        }
      }
    }
  }


  std::cout << "Unique antinode locations: " << antinode_locations.size() << std::endl;
  
  return EXIT_SUCCESS;
}

