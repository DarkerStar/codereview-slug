/*****************************************************************************
*                                                                            *
* This file is part of project indi::slug.                                   *
*                                                                            *
* indi::slug is free software: you can redistribute it and/or modify it      *
* under the terms of the GNU General Public License as published by the      *
* Free Software Foundation, either version 3 of the License, or              *
* (at your option) any later version.                                        *
*                                                                            *
* indi::slug is distributed in the hope that it will be useful, but          *
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License    *
* for more details.                                                          *
*                                                                            *
* You should have received a copy of the GNU General Public License          *
* along with indi::slug. If not, see <https://www.gnu.org/licenses/>.        *
*                                                                            *
*****************************************************************************/

#ifndef INDI_INC_slug
#define INDI_INC_slug

#include <string_view>

namespace indi {
inline namespace v1 {

template <typename T>
concept slug_policy = requires
{
	typename T::char_type;
	typename T::traits_type;

	T::validate(std::basic_string_view<typename T::char_type, typename T::traits_type>{});
};

} // inline namespace v1
} // namespace indi

#endif // include guard
