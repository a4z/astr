// Copyright (c) 2024 a4z
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef A4Z_FILENAME_HPP
#define A4Z_FILENAME_HPP

#include "astr.hpp"

namespace a4z {

  constexpr char slash = on_windows() && !using_clang() ? '\\' : '/';

#define a4z_file_name_from(filename)                                           \
  []() constexpr {                                                             \
    constexpr const char* str = filename;                                      \
    constexpr auto len = a4z::cstr_len(str);                                   \
    constexpr auto start{a4z::find_nth_r_occurrence(filename, a4z::slash, 2)}; \
    constexpr std::size_t offset = (start == a4z::npos ? 0 : start);           \
    constexpr std::size_t offset_add = (start == a4z::npos ? 0 : 1);           \
    constexpr std::size_t astr_len =                                           \
        (start == a4z::npos ? len + 1 : len - start);                         \
    char data[astr_len] = {0};                                                 \
    for (std::size_t i = 0; i < astr_len; ++i) {                               \
      data[i] = *(str + offset + offset_add + i);                              \
    }                                                                          \
    return a4z::astr<astr_len>{data};                                          \
  }()

#define a4z_file_name() a4z_file_name_from(__FILE__)

}  // namespace a4z



#endif  // A4Z_FILENAME_HPP
