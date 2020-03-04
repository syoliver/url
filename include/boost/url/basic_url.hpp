//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/url
//

#ifndef BOOST_URL_BASIC_URL_HPP
#define BOOST_URL_BASIC_URL_HPP

#include <boost/url/config.hpp>
#include <boost/url/url_base.hpp>
#include <boost/url/detail/storage.hpp>
#include <utility>

namespace boost {
namespace urls {

namespace detail {

template<class Allocator>
struct storage_member
{
    alloc_storage<Allocator> st_;

    explicit
    storage_member(
        Allocator const& alloc)
        : st_(alloc)
    {
    }
};

} // detail

template<class Allocator>
class basic_url
    : private detail::storage_member<Allocator>
    , public url_base
{
public:
    basic_url() noexcept
        : detail::storage_member<
            Allocator>(Allocator{})
        , url_base(static_cast<
            detail::storage&>(this->st_))
    {
    }

    explicit
    basic_url(
        string_view s,
        Allocator const& a = {})
        : detail::storage_member<
            Allocator>(a)
        , url_base(this->st_, s)
    {
    }

    explicit
    basic_url(
        Allocator const& a) noexcept
        : detail::storage_member<
            Allocator>(a)
        , url_base(this->st_)
    {
    }

    basic_url(
        basic_url&&) noexcept
    {
    }

    basic_url(
        basic_url const&)
    {
    }

    basic_url&
    operator=(
        basic_url const&)
    {
        return *this;
    }
};

using value = basic_url<
    std::allocator<char>>;

} // urls
} // boost

#endif
