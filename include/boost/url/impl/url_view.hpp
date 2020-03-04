//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/url
//

#ifndef BOOST_URL_IMPL_URL_VIEW_HPP
#define BOOST_URL_IMPL_URL_VIEW_HPP

namespace boost {
namespace urls {

//----------------------------------------------------------

class url_view::segments_type::iterator
{
    friend segments_type;

    char const* s_;
    detail::parts const* pt_;
    std::size_t off_;
    std::size_t n_;

    BOOST_URL_DECL
    iterator(
        segments_type const* v,
        bool end) noexcept;

public:
    using value_type =
        segments_type::value_type;

    BOOST_URL_DECL
    iterator() noexcept;

    BOOST_URL_DECL
    value_type
    operator*() const noexcept;

    value_type
    operator->() const noexcept
    {
        return operator*();
    }

    bool
    operator==(
        iterator const& other) const noexcept
    {
        BOOST_ASSERT(
            pt_ != other.pt_ ||
            off_ != other.off_ || 
            n_ == other.n_);
        return
            pt_ == other.pt_ &&
            off_ == other.off_;
    }

    bool
    operator!=(
        iterator const& other) const noexcept
    {
        return !(*this == other);
    }

    BOOST_URL_DECL
    iterator&
    operator++() noexcept;

    iterator
    operator++(int) noexcept
    {
        auto tmp = *this;
        ++*this;
        return tmp;
    }

    BOOST_URL_DECL
    iterator&
    operator--() noexcept;

    iterator
    operator--(int) noexcept
    {
        auto tmp = *this;
        --*this;
        return tmp;
    }

private:
    inline
    void
    parse() noexcept;
};

//----------------------------------------------------------

class url_view::params_type::iterator
{
    friend params_type;

    char const* s_;
    detail::parts const* pt_;
    std::size_t off_;
    std::size_t nk_;
    std::size_t nv_;

    BOOST_URL_DECL
    iterator(
        params_type const* v,
        bool end) noexcept;

public:
    using value_type =
        params_type::value_type;

    BOOST_URL_DECL
    iterator() noexcept;

    BOOST_URL_DECL
    value_type
    operator*() const noexcept;

    value_type
    operator->() const noexcept
    {
        return operator*();
    }

    bool
    operator==(
        iterator const& other) const noexcept
    {
        BOOST_ASSERT(
            pt_ != other.pt_ ||
            off_ != other.off_ || (
                nk_ == other.nk_ &&
                nv_ == other.nv_));
        return
            pt_ == other.pt_ &&
            off_ == other.off_;
    }

    bool
    operator!=(
        iterator const& other) const noexcept
    {
        return !(*this == other);
    }

    BOOST_URL_DECL
    iterator&
    operator++() noexcept;

    iterator
    operator++(int) noexcept
    {
        auto tmp = *this;
        ++*this;
        return tmp;
    }

    BOOST_URL_DECL
    iterator&
    operator--() noexcept;

    iterator
    operator--(int) noexcept
    {
        auto tmp = *this;
        --*this;
        return tmp;
    }

private:
    inline
    void
    parse() noexcept;
};

//----------------------------------------------------------

template<class Allocator>
string_type<Allocator>
url_view::
params_type::
at( string_view key,
    Allocator const& a) const
{
    auto const it = find(key);
    if(it == end())
        out_of_range::raise();
    return it->value(a);
}

//----------------------------------------------------------

auto
url_view::
segments() const noexcept ->
    segments_type
{
    return segments_type(*this);
}

auto
url_view::
params() const noexcept ->
    params_type
{
    return params_type(*this);
}

} // urls
} // boost

#endif
