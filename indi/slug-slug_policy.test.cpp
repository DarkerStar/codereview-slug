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
