#include <iostream>
#include <vector>
#include <string>

#include "utf8.hpp"

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    std::vector<uint32_t> u32 = t0946::utf8::Decode<std::vector<uint32_t> >(line.begin(), line.end());
    std::vector<uint32_t> sparated;
    sparated.reserve(u32.size() * 2);
    for (size_t i = 0; i < u32.size(); ++i) {
      if (i > 0) {
        sparated.push_back(0x20);
      }
      sparated.push_back(u32[i]);
    }
    std::cout << t0946::utf8::Encode<std::string>(sparated.begin(), sparated.end()) << std::endl;
  }
}
