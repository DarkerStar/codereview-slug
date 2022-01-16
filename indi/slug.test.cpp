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

#define BOOST_TEST_MODULE slug

#ifdef BOOST_TEST_DYN_LINK
#	include <boost/test/unit_test.hpp>
#else
#	include <boost/test/included/unit_test.hpp>
#endif // BOOST_TEST_DYN_LINK

#include <string_view>
#include <tuple>
#include <type_traits>

#include <indi/slug.hpp>

namespace test_types {

template <typename Char, typename Traits>
struct template_slug_policy
{
	using char_type = Char;
	using traits_type = Traits;

	static constexpr auto validate(std::basic_string_view<char_type, traits_type>) noexcept {}
};

using policies = std::tuple<
	template_slug_policy<char, std::char_traits<char>>,
	template_slug_policy<wchar_t, std::char_traits<wchar_t>>,
	template_slug_policy<char8_t, std::char_traits<char8_t>>,
	template_slug_policy<char16_t, std::char_traits<char16_t>>,
	template_slug_policy<char32_t, std::char_traits<char32_t>>
>;

} // namespace test_types

BOOST_AUTO_TEST_CASE_TEMPLATE(char_type, Policy, test_types::policies)
{
	BOOST_TEST((std::is_same_v<typename indi::basic_slug<Policy>::char_type, typename Policy::char_type>));
}
