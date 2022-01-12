# What this project is

This project is a C++20 implementation of a policy-based “slug” class.

It is not intended to be a standalone project, and not intended for use in any
other projects. It exists only as a pseudo-project so that the slug class can
be reviewed independently.

# What are slugs?

Slugs, tokens, identifiers—whatever you want to call them—are specially
structured strings.

For example:

*   [Slugs for web URLs][wiki-slug] that start with an ASCII lower-case
    character, end with a lower-case letter or digit, contain only lower-case
    letters, digits, and the ASCII hyphen/minus but never have consecutive
    hyphen/minuses, and are between 1 and 64 characters long.
    *   A regex to test for these would look like
        `[a-z][a-z0-9]*(-[a-z0-9]+)*`, but you would also need to check for
        the maximum length.

*   C-like identifiers, that start with an upper or lower case ASCII letter or
    underscore, and then contain only upper/lower case letters, digits, and
    the underscore, but cannot have consecutive underscores.

Over the years, I have worked on *numerous* projects that involve some form of
slug/token/identifier, and good C++ practice suggests that these should be
unique types, not simply `std::string`.

# `indi::basic_slug<Policy, Allocator>`

`indi::basic_slug<Policy, Allocator>` is a class template that uses a policy
to create strongly typed slugs.

`indi::basic_slug<Policy, Allocator>` is basically nothing more than a wrapper
around `std::basic_string<Char, Traits, Allocator>` with constructors that
validate the input to make sure it is legal for the given slug type.

To use it, you first create a policy class that determines what counts as a
valid slug. For example:

```c++
struct url_slug_policy
{
    using char_type = char;
    using traits_type = std::char_traits<char>;

    constexpr auto validate(std::string_view s)
    {
        if (s.empty())
            throw std::invalid_argument{"url slug cannot be empty"};

        if (s.size() > 64)
            throw std::invalid_argument{"url slug must be 64 characters or less"};

        if (not is_ascii_lower_letter(s[0]))
            throw std::invalid_argument{"url slug must start with lower-case letter"};

        if (std::ranges::any_of(s, is_not_ascii_lower_letter_digit_or_dash))
            throw std::invalid_argument{"url slug contains illegal character"};

        if (s.contains("--"))
            throw std::invalid_argument{"url slug cannot contain consecutive dashes"};
    }
};
```

Then you can create your slug type:

```c++
using url_slug_type = indi::basic_slug<url_slug_policy>;

auto slug = url_slug_type{"this-is-a-slug"};

// this will throw an exception:
auto not_slug = url_slug_type{"not--slug"};
```

Slugs are easily convertible to strings and string views, so they can be used
with other APIs.


[wiki-slug]: https://en.wikipedia.org/wiki/Clean_URL#Slug
