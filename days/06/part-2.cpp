
#include <cstdint>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
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
  auto x0 = 0, y0 = 0;
  Dir heading0 = Dir::N;
  for (auto yy = 0; yy < H; ++yy) {
    for (auto xx = 0; xx < W; ++xx) {
      if (const auto c = map[yy][xx]; c != '#' and c != '.') {
        y0 = yy, x0 = xx;
        heading0 = (c == '^' ? Dir::N :
                    c == '>' ? Dir::E :
                    c == 'v' ? Dir::S :
                               Dir::W);
        map[yy][xx] = '.';  /// Make this position a normal walkable tile
      }
    }
  }
  
  auto looping_obstructions = 0;
  /// Walk guard
  for (auto y_ob = 0; y_ob < H; ++y_ob) {
    for (auto x_ob = 0; x_ob < W; ++x_ob) {
      if (map[y_ob][x_ob] == '#' or (x_ob == x0 and y_ob == y0))
        continue;
      /// Place obstruction at position
      map[y_ob][x_ob] = '#';
      {
        auto x = x0, y = y0;
        auto heading = heading0;
        std::set<std::tuple<std::int32_t, std::int32_t, Dir>> visited;
        for (;;) {
          if (visited.contains({x, y, heading})) {
            ++looping_obstructions;
            break;
          }
          visited.insert({x, y, heading});
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
      }
      /// Remove obstruction for next iteration
      map[y_ob][x_ob] = '.';
    }
  }


  std::cout << "There are " << looping_obstructions << " possible obstructions leading to loops" << std::endl;

  return EXIT_SUCCESS;
}

