// Copyright (c) 2024 a4z
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef A4Z_TYPENAME_HPP
#define A4Z_TYPENAME_HPP

#include <cstddef>
#include "astr.hpp"

namespace a4z {

  template <typename T>
  constexpr const char* type_name_str() {
#if defined(_MSC_VER)
    return __FUNCSIG__;
#elif defined(__GNUC__) || defined(__clang__)
    return __PRETTY_FUNCTION__;
#else
    error("compiler not supported, feel free to add a PR")
#endif
  }

  template <typename T>
  constexpr auto type_name() {
#if defined(_MSC_VER)
    constexpr const char* thisname = __FUNCSIG__;
    constexpr auto ang = a4z::first_c_in('<', thisname);
    constexpr auto space = a4z::first_c_in(' ', ang);
    constexpr auto tstart =
        (space == nullptr) ? a4z::next_c(ang) : a4z::next_c(space);
    constexpr auto tend = a4z::last_c_in('>', thisname);

    // constexpr size_t len = tend - tstart; // very likely a distance

#elif defined(__GNUC__) || defined(__clang__)
    constexpr const char* thisname = __PRETTY_FUNCTION__;
    constexpr auto eq = a4z::first_c_in('=', thisname);
    constexpr auto past_eq = a4z::next_c(eq);
    constexpr auto tstart = a4z::first_not(' ', past_eq);
    constexpr auto tend = a4z::last_c_in(']', thisname);

#else
    error("compiler not supported, feel free to add a PR")
#endif

    constexpr auto dist = tend - tstart;
    static_assert(dist > 0);
    constexpr size_t data_len = static_cast<size_t>(dist) + 1;
    char data[data_len] = {0};
    for (size_t i = 0; i < data_len - 1; ++i) {
      data[i] = *(tstart + i);
    }
    return a4z::astr<data_len>{data};
  }

}  // namespace a4z

#endif  // A4Z_TYPENAME_HPP
