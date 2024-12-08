
#include <cstdint>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
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

  const auto H = static_cast<std::int32_t>(map.size());
  const auto W = static_cast<std::int32_t>(map[0].size());
  enum class Dir : std::int32_t { N, E, S, W };
  const std::map<Dir, std::int32_t> map_heading_to_dx{{Dir::N,  0}, {Dir::E, 1}, {Dir::S,  0}, {Dir::W, -1}},
                                    map_heading_to_dy{{Dir::N, -1}, {Dir::E, 0}, {Dir::S,  1}, {Dir::W,  0}};

  /// Find initial guard position and heading
  auto x = 0, y = 0;
  Dir heading = Dir::N;
  for (auto yy = 0; yy < H; ++yy) {
    for (auto xx = 0; xx < W; ++xx) {
      if (const auto c = map[yy][xx]; c != '#' and c != '.') {
        y = yy, x = xx;
        heading = (c == '^' ? Dir::N :
                   c == '>' ? Dir::E :
                   c == 'v' ? Dir::S :
                              Dir::W);
        map[yy][xx] = '.';  /// Make this position a normal walkable tile
      }
    }
  }
  
  /// Walk guard
  std::set<std::array<std::int32_t,2>> visited;
  for (;;) {
    visited.insert({x, y});
    const auto xnext = x + map_heading_to_dx.at(heading),
               ynext = y + map_heading_to_dy.at(heading);
    if (xnext < 0 or xnext >= W or ynext < 0 or ynext >= H)
      break;
    if (map[ynext][xnext] == '.') {
      x = xnext, y = ynext;
    } else {
      heading = Dir{(std::to_underlying(heading) + 1) % 4};
    }
  }

  std::cout << "Guard visited " << visited.size() << " distinct positions." << std::endl;

  return EXIT_SUCCESS;
}

