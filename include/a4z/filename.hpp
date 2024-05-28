// Copyright (c) 2024 a4z
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef A4Z_FILENAME_HPP
#define A4Z_FILENAME_HPP

#include "astr.hpp"

#include <source_location>

namespace a4z {

  constexpr char slash = on_windows() ? '\\' : '/';

#define a4z_file_name							                                   \
	[]() consteval {							                                   \
		constexpr auto location = std::source_location::current();                 \
		constexpr std::string_view filename{ location.file_name() };               \
		constexpr auto start{a4z::find_nth_r_occurrence(filename, a4z::slash, 2)}; \
		static_assert( start != a4z::npos );							\
		return filename.substr( start + 1 );                                       \
    }                                                                              \

}  // namespace a4z

#endif  // A4Z_FILENAME_HPP
