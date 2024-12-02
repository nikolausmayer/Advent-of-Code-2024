
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <ranges>
#include <sstream>
#include <vector>


int main(int argc, char* argv[])
{
  if (argc != 2)
    return EXIT_FAILURE;
  std::ifstream infile{argv[1]};
  if (not infile.is_open() or infile.bad())
    return EXIT_FAILURE;

  /// evaluate input line-by-line
  auto safe_reports_count = 0;
  for (std::string line;;) {
    std::getline(infile, line);
    if (infile.eof())
      break;
    if (line.size() == 0)
      continue;


    /// I'm just gonna bruteforce this one
    std::vector<std::int32_t> levels;
    {
      std::istringstream line_stream{line};
      for (std::int32_t n;;) {
        line_stream >> n;
        if (not line_stream)
          break;
        levels.push_back(n);
      }
    }

    //for (auto l: levels) std::cout << l << " "; std::cout << std::endl;
    for (auto i = 0u; i <= levels.size(); ++i) {
      std::optional<std::int32_t> report_mode;
      auto good_report = true;
      auto levels_with_one_removed = levels;
      if (i != levels.size())
        levels_with_one_removed.erase(levels_with_one_removed.begin() + i);
      for (const auto [n, m]: levels_with_one_removed | std::views::adjacent<2>) {
        if (m == n) {
          good_report = false;
          break;
        }
        if (std::abs(n - m) > 3) {
          good_report = false;
          break;
        }

        if (not report_mode) {
          report_mode = (n < m);
        } else if (report_mode != (n < m)) {
          good_report = false;
          break;
        }
      }

      if (good_report) {
        //std::cout << "report safe after removing #" << i << " level " << levels[i] << std::endl;
        ++safe_reports_count;
        break;
      }
    }
  }


  std::cout << "Number of safe reports: " << safe_reports_count << std::endl;

  return EXIT_SUCCESS;
}

