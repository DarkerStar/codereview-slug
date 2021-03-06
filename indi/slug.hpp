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

//////////////////////////////////////////////////////////////////////////////
//
// Slugs =====================================================================
//
// Slugs - or tokens, or identifiers - are specially formatted strings used
// for specific technical purposes. Some examples include:
//
//  *   URL slugs used to improve SEO for web addresses
//  *   identifiers in scripts
//  *   special tokens in data or configuration files
//
// Plain strings could be used for any of these, but good programming practice
// recommends specific unique types for each purpose. Rather than creating
// different bespoke types each time, `indi::basic_slug` is a policy-based
// template that mostly eliminates the boilerplate.
//
// Slug policies =============================================================
//
// Slug policies are both the tags used to strongly differentiate slug types,
// and the description of what a specific slug is. The slug policy includes a
// validation function that checks whether the string content of a slug is
// okay.
//
// A minimal slug policy is a type that has two nested types:
//  *   `value_type`
//  *   `traits_type`
// and a static member function with the signature:
//  *   `validate(std::basic_string_view<value_type, traits_type>)`
//
//////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string_view>

namespace indi {
inline namespace v1 {

// concept slug_policy ///////////////////////////////////////////////////////
//
// Checks that a type is at least a minimal slug policy.
//
//////////////////////////////////////////////////////////////////////////////

template <typename T>
concept slug_policy = requires
{
	typename T::value_type;
	typename T::traits_type;

	T::validate(std::basic_string_view<typename T::value_type, typename T::traits_type>{});
};

template <
	typename Policy,
	typename Allocator = std::allocator<typename Policy::value_type>
>
class basic_slug
{
public:
	using value_type     = typename Policy::value_type;
	using traits_type    = typename Policy::traits_type;
	using allocator_type = Allocator;

	using size_type       = typename std::allocator_traits<Allocator>::size_type;
	using difference_type = typename std::allocator_traits<Allocator>::difference_type;

	using reference       = value_type&;
	using const_reference = value_type const&;

	using pointer       = typename std::allocator_traits<Allocator>::pointer;
	using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

	using iterator       = typename std::basic_string<value_type, traits_type, Allocator>::iterator;
	using const_iterator = typename std::basic_string<value_type, traits_type, Allocator>::const_iterator;

	using reverse_iterator       = typename std::basic_string<value_type, traits_type, Allocator>::reverse_iterator;
	using const_reverse_iterator = typename std::basic_string<value_type, traits_type, Allocator>::const_reverse_iterator;
};

} // inline namespace v1
} // namespace indi

#endif // include guard
