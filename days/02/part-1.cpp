
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

    std::istringstream line_stream{line};

    std::optional<std::int32_t> report_mode;
    auto good_report = true;
    std::int32_t n, m;
    line_stream >> n;
    for (;;) {
      line_stream >> m;
      if (not line_stream)
        break;
      if (m == n) {
        std::cout << "bad report: " << n << " == " << m << std::endl;
        good_report = false;
        break;
      }
      if (std::abs(n - m) > 3) {
        std::cout << "bad report: " << n << " <<>> " << m << std::endl;
        good_report = false;
        break;
      }

      if (not report_mode) {
        report_mode = (n < m);
      } else if (report_mode != (n < m)) {
        std::cout << "bad report: " << n << " -> " << m << " nonmonotonic" << std::endl;
        good_report = false;
        break;
      }
      std::swap(n, m);
    }
    safe_reports_count += good_report;
  }


  std::cout << "Number of safe reports: " << safe_reports_count << std::endl;

  return EXIT_SUCCESS;
}

