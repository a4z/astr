// Copyright (c) 2024 a4z
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef A4z_ASTR_HPP
#define A4z_ASTR_HPP

#include <cstddef>
#include <limits>
#include <string_view>

namespace a4z {

  template <std::size_t N>
  struct astr {
    char data[N] = {0};

    constexpr astr() noexcept = default;

    constexpr explicit astr(const char (&arr)[N]) noexcept {
      for (std::size_t i = 0; i < N; ++i) {
        data[i] = *(arr + i);
      }
    }

    [[nodiscard]] constexpr const char* c_str() const noexcept {
      return &data[0];
    }

    [[nodiscard]] constexpr std::size_t size() const noexcept { return N - 1; }

    char* begin() noexcept { return &data[0]; }
    char* end() noexcept { return &data[N - 1]; }

    [[nodiscard]] const char* begin() const noexcept { return &data[0]; }
    [[nodiscard]] const char* end() const noexcept { return &data[N - 1]; }

    [[nodiscard]] const char* cbegin() const noexcept { return &data[0]; }
    [[nodiscard]] const char* cend() const noexcept { return &data[N - 1]; }

    constexpr operator std::string_view() const noexcept {
      return std::string_view(data, size());
    }

    template <std::size_t T>
    constexpr auto last_n() const noexcept -> astr<T + 1> {
      static_assert(N > T,
                    "Wanted sized T cannot be greater than actual size N");
      astr<T + 1> result;
      constexpr std::size_t start = N - T - 1;  // N > T is asserted above
      std::copy(data + start, data + N, result.data);
      return result;
    }

    template <std::size_t T>
    constexpr auto first_n() const noexcept -> astr<T + 1> {
      static_assert(N > T,
                    "Wanted sized T cannot be greater than actual size N");
      astr<T + 1> result;
      constexpr std::size_t last = T;
      std::copy(data, data + last, result.data);
      return result;
    }
  };

  constexpr bool equal(char const* a, char const* b) {
    return *a == *b && (*a == '\0' || equal(a + 1, b + 1));
  }

  constexpr const char* next_c(const char* str) {
    return *(str + 1) == '\0' ? nullptr : str + 1;
  }

  template <char c>
  constexpr const char* first_char(const char* str, int idx) {
    return *(str + idx) == c      ? str + idx
           : *(str + idx) == '\0' ? nullptr
                                  : first_char<c>(str, idx + 1);
  }

  template <char c, std::size_t N>
  constexpr const char* first_char_in(const char (&str)[N]) {
    return first_char<c>(str, 0);
  }

  constexpr const char* first_not(char c, const char* str, int idx = 0) {
    return *(str + idx) != c      ? str + idx
           : *(str + idx) == '\0' ? nullptr
                                  : first_not(c, str, idx + 1);
  }

  constexpr const char* first_c(char c, const char* str, int idx) {
    return *(str + idx) == c      ? str + idx
           : *(str + idx) == '\0' ? nullptr
                                  : first_c(c, str, idx + 1);
  }

  constexpr const char* first_c_in(char c, const char* str) {
    return first_c(c, str, 0);
  }

  constexpr const char* last_c_in(char c, const char* str) {
    const auto* f = first_c_in(c, str);
    const auto* n = f;
    while (n != nullptr) {
      f = n++;
      n = first_c_in(c, n);
    }

    return f;
  }

  constexpr const char* last_char(char c, const char* str, int idx) {
    return *(str + idx) == c ? str + idx
           : idx == 0        ? nullptr
                             : last_char(c, str, idx - 1);
  }

  template <std::size_t N>
  constexpr const char* last_char_in(char c, const char (&str)[N]) {
    return last_char(c, str, N - 1);
  }

  constexpr std::size_t cstr_len(const char* str) {
    std::size_t len = 0;
    while (*(str + len) != '\0') {
      ++len;
    }
    return len;
  }

  constexpr auto npos = std::numeric_limits<std::size_t>::max();

  template <std::size_t N>
  constexpr std::size_t find_nth_r_occurrence(const char (&str)[N],
                                              char ch,
                                              std::size_t n) {
    std::size_t count = 0;
    for (std::size_t i = N; i-- > 0;) {
      if (str[i] == ch) {
        ++count;
        if (count == n) {
          return i;
        }
      }
    }
    return npos;  // Not found
  }

  consteval bool on_windows() {
#ifdef _WIN32
    return true;
#else
    return false;
#endif
  }

}  // namespace a4z

#endif  // A4z_ASTR_HPP
