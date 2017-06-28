#ifndef T0946_UTF8_HPP_
#define T0946_UTF8_HPP_

#include <stdint.h>
#include <vector>
#include <string>
#include <exception>
#include <stdexcept>

namespace t0946 {
namespace utf8 {

inline int CountLeadingOnes(uint8_t n) {
  uint8_t cnt = 0;
  if ((n & 0xf0) == 0xf0) { cnt += 4; n <<= 4; }
  if ((n & 0xc0) == 0xc0) { cnt += 2; n <<= 2; }
  if ((n & 0x80) == 0x80) { cnt += 1; n <<= 1; }
  if ((n & 0x80) == 0x80) { cnt += 1; }
  return cnt;
}

inline uint8_t LeadingOnes(int n) {
  return (0xff00 >> n) & 0xff;
}

inline int UTF8Length(uint32_t n) {
  if ((n >> 7) == 0) return 1;
  if ((n >> 11) == 0) return 2;
  if ((n >> 16) == 0) return 3;
  if ((n >> 21) == 0) return 4;
  if ((n >> 26) == 0) return 5;
  if ((n >> 31) == 0) return 6;
  return 7;
}

// Code Point : UTF-8
// 0000 0000-0000 007F | 0xxxxxxx
// 0000 0080-0000 07FF | 110xxxxx 10xxxxxx
// 0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
// 0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

template <class I, class O>
void Decode(I it, I end, O out) {
  for (; it != end; ++it) {
    int count = CountLeadingOnes(static_cast<uint8_t>(*it));
    uint32_t u = static_cast<uint8_t>(*it & ~LeadingOnes(count+1));
    switch (count) {
      case 0:
        // 0xxxxxxx
        *out++ = u;
        break;
      case 2:
      case 3:
      case 4:
        // 110xxxxx or 1110xxxx or 11110xxx
        for (int i = 0; i < count - 1; ++i) {
          // 10xxxxxx
          ++it;
          if (it == end) throw std::runtime_error("Invalid UTF-8: unexpected end");
          int tcount = CountLeadingOnes(static_cast<uint8_t>(*it));
          if (tcount != 1) throw std::runtime_error("Invalid UTF-8: invalid trails");
          u = (u << 6) | static_cast<uint8_t>(*it & ~LeadingOnes(tcount+1));
        }
        if (count != UTF8Length(u)) throw std::runtime_error("Invalid UTF-8: non-shortest encoding");
        if (0x0010FFFF < u) throw std::runtime_error("Invalid UTF-8: invaid code point");
        // if (0xD800 <= u && u <= 0xDFFF) throw std::runtime_error("Invalid UTF-8: surrogate code point");
        *out++ = u;
        break;
      default:
        throw std::runtime_error("Invalid UTF-8: invalid head");
    }
  }
}

template <class O, class I>
O Decode(I it, I end) {
  O result;
  Decode(it, end, std::back_inserter(result));
  return result;
}

template <class I, class O>
void Encode(I it, I end, O out) {
  for (; it != end; ++it) {
    uint32_t u = *it;
    int count = UTF8Length(*it);
    switch (count) {
      case 1:
        // 0xxxxxxx
        *out++ = u;
        break;
      case 2:
      case 3:
      case 4:
        // 110xxxxx or 1110xxxx or 11110xxx
        *out++ = LeadingOnes(count) | ((u >> (6 * (count - 1))) & ~LeadingOnes(count + 1));
        for (int i = count-1; i > 0; --i) {
          // 10xxxxxx
          *out++ = LeadingOnes(1) | ((u >> (6 * (i - 1))) & ~LeadingOnes(2));
        }
      default:
        std::runtime_error("Invalid Unicode");
    }
  }
}

template <class O, class I>
O Encode(I it, I end) {
  O result;
  Encode(it, end, std::back_inserter(result));
  return result;
}

}  // namespace utf8
}  // namespace t0946

#endif  // T0946_UTF8_HPP_
