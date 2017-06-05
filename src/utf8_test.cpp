#include <utility>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "utf8.hpp"

namespace t0946 {
namespace utf8 {

class UTF8ValidTest : public ::testing::TestWithParam<std::pair<std::string, uint32_t> > {};

std::pair<std::string, uint32_t> kValids[] = {
  std::make_pair(std::string("\x00", 1), 0x0000),
  std::make_pair("\x01", 0x0001),
  std::make_pair("\x7f", 0x007f),
  std::make_pair("\xc2\x80", 0x0080),
  std::make_pair("\xdf\xbf", 0x07ff),
  std::make_pair("\xe0\xa0\x80", 0x0800),
  std::make_pair("\xef\xbf\xbf", 0xffff),
  std::make_pair("\xf0\x90\x80\x80", 0x00010000),
  std::make_pair("\xf4\x8f\xbf\xbf", 0x0010FFFF),
};

INSTANTIATE_TEST_CASE_P(UTF8ValidTestInstance,
                        UTF8ValidTest,
                        ::testing::ValuesIn(kValids));

TEST_P(UTF8ValidTest, valids) {
  std::pair<std::string, uint32_t> valid = GetParam();

  std::vector<uint32_t> u32 = Decode<std::vector<uint32_t> >(valid.first.begin(), valid.first.end());
  ASSERT_EQ(1u, u32.size());
  EXPECT_EQ(valid.second, u32[0]);

  std::string encoded = Encode<std::string>(u32.begin(), u32.end());
  EXPECT_EQ(valid.first, encoded);
}

class UTF8InvalidTest : public ::testing::TestWithParam<const char*> {};

const char* kInvalids[] = {
  "\xE0\x80",                   // U+0 non-shortest encoding
  "\xC0\x80\x80",               // U+0 non-shortest encoding
  "\xf0\x80\x80\x80",           // U+0 non-shortest encoding
  "\xf8\x80\x80\x80\x80",       // U+0 non-shortest encoding
  "\xfc\x80\x80\x80\x80\x80",   // U+0 non-shortest encoding

  "\xdf",                       // Unexpected end
  "\xef",                       // Unexpected end
  "\xef\xbf",                   // Unexpected end
  "\xf7",                       // Unexpected end
  "\xf7\xbf",                   // Unexpected end
  "\xf7\xbf\xbf",               // Unexpected end

  "\xdf\x20",                   // Invalid Trail
  "\xbf",                       // Invalid Head

  "\xf8\xa0\x80\x80",           // U+110000
  "\xf7\xbf\xbf\xbf",           // U+1FFFFF
  "\xf8\x88\x80\x80\x80",       // U+200000
  "\xf8\xbf\xbf\xbf\xbf",       // U+3FFFFFF
  "\xfc\x88\x80\x80\x80\x80",   // U+4000000
  "\xfd\xbf\xbf\xbf\xbf\xbf",   // U+7FFFFFFF

  "\xc0\xaf",                   // U+2F non-shortest encoding
  "\xe0\x80\xaf",               // U+2F non-shortest encoding
  "\xf0\x80\x80\xaf",           // U+2F non-shortest encoding
  // "\xed\xa0\x80",               // U+D800 surrogate
  // "\xed\xbf\xbf",               // U+DFFF surrogate
};

INSTANTIATE_TEST_CASE_P(UTF8InvalidTestInstance,
                        UTF8InvalidTest,
                        ::testing::ValuesIn(kInvalids));

TEST_P(UTF8InvalidTest, Invalids) {
  std::string invalid = GetParam();
  std::vector<uint32_t> u32;
  EXPECT_THROW(Decode(invalid.begin(), invalid.end(), std::back_inserter(u32)),
               std::runtime_error);
}

}  // namespace utf8
}  // namespace t0946
