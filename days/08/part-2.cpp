
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
      /// All antenna locations are antinode locations!
      antinode_locations.insert({ix, iy});
      for (auto j = i + 1; j < antennas_xy.size(); ++j) {
        const auto [jx, jy] = antennas_xy[j];
        antinode_locations.insert({jx, jy});
        auto dx = ix - jx, dy = iy - jy;
        /// The raw difference vector may be not minimal, so we break it down
        for (auto div = 2; div <= dx and div <= dy; ++div)
          while (dx % div == 0 and dy % div == 0)
            dx %= div, dy %= div;
        /// Now scan in both directions from one of the two antennas
        for (const auto sign: {-1, 1}) {
          for (auto multiplier = 1;; ++multiplier) {
            const auto x = ix + sign * multiplier * dx,
                       y = iy + sign * multiplier * dy;
            if (x < 0 or x >= W or y < 0 or y >= H)
              break;
            antinode_locations.insert({x, y});
          }
        }
      }
    }
  }


  std::cout << "Unique antinode locations: " << antinode_locations.size() << std::endl;
  
  return EXIT_SUCCESS;
}

