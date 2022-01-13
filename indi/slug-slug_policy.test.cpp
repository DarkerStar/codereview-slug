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

#define BOOST_TEST_MODULE concept slug_policy

#ifdef BOOST_TEST_DYN_LINK
#	include <boost/test/unit_test.hpp>
#else
#	include <boost/test/included/unit_test.hpp>
#endif // BOOST_TEST_DYN_LINK

#include <string_view>

#include <boost/core/ignore_unused.hpp>

#include <indi/slug.hpp>

BOOST_AUTO_TEST_CASE(simple_policy)
{
	struct policy
	{
		using char_type = char;
		using traits_type = std::char_traits<char>;

		static constexpr auto validate(std::string_view) noexcept -> void {}
	};

	boost::ignore_unused<policy::char_type>();
	boost::ignore_unused<policy::traits_type>();

	BOOST_TEST(indi::slug_policy<policy>);
}

template <typename Char>
struct test_char_traits
{
	using char_type = Char;
	using int_type = typename std::char_traits<Char>::int_type;
	using off_type = typename std::char_traits<Char>::off_type;
	using pos_type = typename std::char_traits<Char>::pos_type;
	using state_type = typename std::char_traits<Char>::state_type;

	static constexpr auto assign(char_type& r, char_type const& a ) noexcept -> void
	{
		std::char_traits<Char>::assign(r, a);
	}

	static constexpr auto assign(char_type* p, std::size_t n, char_type a) -> char_type*
	{
		return std::char_traits<Char>::assign(p, n, a);
	}

	static constexpr auto eq(char_type a, char_type b) noexcept -> bool
	{
		return std::char_traits<Char>::eq(a, b);
	}

	static constexpr auto lt(char_type a, char_type b) noexcept -> bool
	{
		return std::char_traits<Char>::lt(a, b);
	}

	static constexpr auto move(char_type* dest, char_type const* src, std::size_t n) -> char_type*
	{
		return std::char_traits<Char>::move(dest, src, n);
	}

	static constexpr auto copy(char_type* dest, char_type const* src, std::size_t n) -> char_type*
	{
		return std::char_traits<Char>::copy(dest, src, n);
	}

	static constexpr auto compare(char_type const* s1, char_type const* s2, std::size_t n) -> int
	{
		return std::char_traits<Char>::compare(s1, s2, n);
	}

	static constexpr auto length(char_type const* s) -> std::size_t
	{
		return std::char_traits<Char>::length(s);
	}

	static constexpr auto find(char_type const* p, std::size_t n, char_type const& c) -> char_type const*
	{
		return std::char_traits<Char>::find(p, n, c);
	}

	static constexpr auto to_char_type(int_type c) noexcept -> char_type
	{
		return std::char_traits<Char>::to_char_type(c);
	}

	static constexpr auto to_int_type(char_type c) noexcept -> int_type
	{
		return std::char_traits<Char>::to_int_type(c);
	}

	static constexpr auto eq_int_type(int_type c1, int_type c2) noexcept -> bool
	{
		return std::char_traits<Char>::eq_int_type(c1, c2);
	}

	static constexpr auto eof() noexcept -> int_type
	{
		return std::char_traits<Char>::eof();
	}

	static constexpr auto not_eof(int_type e) noexcept -> int_type
	{
		return std::char_traits<Char>::not_eof(e);
	}
};

template <typename Char>
struct test_template_policy
{
	using char_type = Char;
	using traits_type = test_char_traits<Char>;

	static constexpr auto validate(std::basic_string_view<char_type, traits_type>) noexcept -> void {}
};

BOOST_AUTO_TEST_CASE(template_policy)
{
	BOOST_TEST(indi::slug_policy<test_template_policy<char>>);
	BOOST_TEST(indi::slug_policy<test_template_policy<wchar_t>>);
	BOOST_TEST(indi::slug_policy<test_template_policy<char8_t>>);
	BOOST_TEST(indi::slug_policy<test_template_policy<char16_t>>);
	BOOST_TEST(indi::slug_policy<test_template_policy<char32_t>>);
}
