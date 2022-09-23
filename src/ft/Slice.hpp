/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Slice.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:47:42 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 02:19:57 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <algorithm>
#include <ostream>
#include <limits>

namespace ft
{
    template< typename T >
    class Slice
    {
    public:
        typedef T*              iterator;
        typedef const T*        const_iterator;

    private:
        T*      _start;
        T*      _end;

    public:
        // ==============
        //  Constructors
        // ==============

        /// @brief Creates an empty slice.
        Slice() :
            _start(0),
            _end(0)
        {}

        /// @brief Creates a new @c Slice instance from `start` and `end`
        /// pointers.
        ///
        /// @param start A pointer to the first element of the slice.
        /// @param end A pointer to the first element that's not part of the
        /// slice.
        Slice(T* start, T* end) :
            _start(start),
            _end(end)
        {}

        /// @brief Creates a new @c Slice instance from a pointer and a size.
        ///
        /// @param start A pointer to the slice.
        /// @param len The size of the slice.
        Slice(T* start, size_t len) :
            _start(start),
            _end(start + len)
        {}

        // ======
        //  Data
        // ======

        const T*    data() const
        {
            return (this->_start);
        }

        T*          data()
        {
            return (this->_start);
        }

        size_t      size() const
        {
            return (this->_end - this->_start);
        }

        // ===========
        //  Iterators
        // ===========

        iterator        begin()
        {
            return (this->_start);
        }

        const_iterator  begin() const
        {
            return (this->_start);
        }

        iterator        end()
        {
            return (this->_end);
        }

        const_iterator  end() const
        {
            return (this->_end);
        }

        // ==============
        //  Manipulation
        // ==============

        /// @brief Takes a slice of this slice ;)
        Slice       slice(size_t start, size_t end)
        {
            return Slice(this->_start + start, this->_start + end);
        }

        /// @brief Trims the start of this slice.
        Slice       trim_left(bool (*predicate)(const T&))
        {
            T*      it = this->begin();

            while (it != this->end() && (*predicate)(*it))
                it++;
            return Slice(it, this->end());
        }

        /// @brief Trims the end of this slice.
        Slice       trim_right(bool (*predicate)(const T&))
        {
            T*      it = this->end();

            while (--it != this->begin() && (*predicate)(*it));
            return (Slice(this->begin(), ++it));
        }

        /// @brief Trims this slice.
        Slice       trim(bool (*predicate)(const T&))
        {
            return this->trim_left(predicate).trim_right(predicate);
        }

        // ===========
        //  Operators
        // ===========

        T&          operator[](size_t index)
        {
            return *(this->_start + index);
        }

        const T&    operator[](size_t index) const
        {
            return *(this->_start + index);
        }

        bool        operator==(Slice<T> other) const
        {
            return std::equal(this->begin(), this->end(), other->begin(), other->end());
        }

        bool        operator!=(Slice<T> other) const
        {
            return !(*this == other);
        }
    };

    /// @brief A string that knows its length.
    typedef Slice<uint8_t> Str;

    /// @brief Creates a new @c Str from the provided null-terminated string.
    Str make_str(const char *s, size_t max = SIZE_MAX);

    /// @brief Parses a @c T from the provided slice.
    template< typename T >
    const uint8_t*  parse_str(Str str, T& ret)
    {
        const uint8_t*  it = str.begin();

        ret = static_cast<T>(0);
        while (it != str.end() && '0' <= *it && *it <= '9')
        {
            T to_add = static_cast<T>(*it - '0');

            if (ret > (std::numeric_limits<T>::max() - to_add) / static_cast<T>(10))
                return (0);
            ret = ret * static_cast<T>(10) + to_add;
            it++;
        }
        return (it);
    }

    bool            operator==(Str a, const char *str);
    bool            operator!=(Str a, const char *str);

    std::ostream&   operator<<(std::ostream& s, Str other);
}
