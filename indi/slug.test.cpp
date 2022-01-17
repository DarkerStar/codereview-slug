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

template <typename Char>
struct test_char_traits
{
	using char_type = Char;
	using int_type = typename std::char_traits<Char>::int_type;
	using off_type = typename std::char_traits<Char>::off_type;
	using pos_type = typename std::char_traits<Char>::pos_type;
	using state_type = typename std::char_traits<Char>::state_type;

	using stdtraits_t = std::char_traits<Char>;

	static constexpr auto assign(char_type& r, char_type const& a) noexcept { return stdtraits_t::assign(r, a); }
	static constexpr auto assign(char_type* p, std::size_t n, char_type a) { return stdtraits_t::assign(p, n, a); }

	static constexpr auto eq(char_type a, char_type b) noexcept { return stdtraits_t::eq(a, b); }
	static constexpr auto lt(char_type a, char_type b) noexcept { return stdtraits_t::lt(a, b); }

	static constexpr auto move(char_type* dest, char_type const* src, std::size_t n) { return stdtraits_t::move(dest, src, n); }
	static constexpr auto copy(char_type* dest, char_type const* src, std::size_t n) { return stdtraits_t::copy(dest, src, n); }

	static constexpr auto compare(char_type const* s1, char_type const* s2, std::size_t n) { return stdtraits_t::compare(s1, s2, n); }

	static constexpr auto length(char_type const* s) { return stdtraits_t::length(s); }

	static constexpr auto find(char_type const* p, std::size_t n, char_type const& c) { return stdtraits_t::find(p, n, c); }

	static constexpr auto to_char_type(int_type c) noexcept { return stdtraits_t::to_char_type(c); }
	static constexpr auto to_int_type(char_type c) noexcept { return stdtraits_t::to_int_type(c); }

	static constexpr auto eq_int_type(int_type c1, int_type c2) noexcept { return stdtraits_t::eq_int_type(c1, c2); }

	static constexpr auto eof() noexcept { return stdtraits_t::eof(); }

	static constexpr auto not_eof(int_type e) noexcept { return stdtraits_t::not_eof(e); }
};

template <typename Char, typename Traits>
struct template_slug_policy
{
	using value_type = Char;
	using traits_type = Traits;

	static constexpr auto validate(std::basic_string_view<value_type, traits_type>) noexcept {}
};

using policies = std::tuple<
	template_slug_policy<char,     std::char_traits<char>>,
	template_slug_policy<wchar_t,  std::char_traits<wchar_t>>,
	template_slug_policy<char8_t,  std::char_traits<char8_t>>,
	template_slug_policy<char16_t, std::char_traits<char16_t>>,
	template_slug_policy<char32_t, std::char_traits<char32_t>>,
	template_slug_policy<char,     test_char_traits<char>>,
	template_slug_policy<wchar_t,  test_char_traits<wchar_t>>,
	template_slug_policy<char8_t,  test_char_traits<char8_t>>,
	template_slug_policy<char16_t, test_char_traits<char16_t>>,
	template_slug_policy<char32_t, test_char_traits<char32_t>>
>;

} // namespace test_types

BOOST_AUTO_TEST_CASE_TEMPLATE(value_type, Policy, test_types::policies)
{
	BOOST_TEST((std::is_same_v<typename indi::basic_slug<Policy>::value_type, typename Policy::value_type>));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(traits_type, Policy, test_types::policies)
{
	BOOST_TEST((std::is_same_v<typename indi::basic_slug<Policy>::traits_type, typename Policy::traits_type>));
}
