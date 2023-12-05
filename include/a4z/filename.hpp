#ifndef A4Z_FILENAME_HPP
#define A4Z_FILENAME_HPP

#include "astr.hpp"

namespace a4z {


  constexpr char slash = on_windows() ? '\\' : '/';

#define a4z_file_name                                                          \
  []() consteval {                                                             \
    constexpr const char* str = __FILE__;                                      \
    constexpr auto len = a4z::cstr_len(str);                                   \
    constexpr auto start{a4z::find_nth_r_occurrence(__FILE__, a4z::slash, 2)}; \
    static_assert(start != a4z::npos);                                         \
    constexpr std::size_t astr_len = len - start;                              \
    char data[astr_len];                                                       \
    for (std::size_t i = 0; i < astr_len; ++i) {                               \
      data[i] = *(str + start + i + 1);                                        \
    }                                                                          \
    return a4z::astr<astr_len>{data};                                          \
  }

}  // namespace a4z

#endif  // A4Z_FILENAME_HPP
