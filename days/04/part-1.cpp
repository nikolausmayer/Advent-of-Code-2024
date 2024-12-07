
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

  auto xmas_count = 0;
  
  const auto H = static_cast<std::int32_t>(map.size());
  const auto W = static_cast<std::int32_t>(map[0].size());
  /// Directions to search in
  const std::vector<std::array<int,2>> dxdy{
    {-1,-1}, { 0,-1}, { 1,-1},
    {-1, 0},          { 1, 0},
    {-1, 1}, { 0, 1}, { 1, 1},
  };
  for (auto y0 = 0 ; y0 < H; ++y0) {
    for (auto x0 = 0 ; x0 < W; ++x0) {
      for (const auto [dx,dy]: dxdy) {
        auto x = x0, y = y0;
        for (auto i = 0; i < 4; ++i) {
          if (x < 0 or x >= W or y < 0 or y >= H)  /// Bounds check
            break;
          if (map[y][x] != "XMAS"[i])  /// Word search
            break;
          xmas_count += (i == 3);  /// XMAS found!
          x += dx, y += dy;
        }
      }
    }
  }

  std::cout << "XMAS appears " << xmas_count << " times." << std::endl;

  return EXIT_SUCCESS;
}

