/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseBuf.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:09:37 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 00:07:00 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Slice.hpp"

#include <stdint.h>
#include <memory>

namespace ft
{
    /// @brief A growable buffer used for parsing.
    class ParseBuf
    {
        std::allocator<uint8_t>   _alloc;
        uint8_t*                  _data;
        size_t                    _cap;
        size_t                    _init;
        size_t                    _consumed;

    public:
        // ==============
        //  Constructors
        // ==============

        /// @brief Creates a new `ParseBuf` with the specified capacity.
        /// @param capacity
        explicit ParseBuf(size_t capacity);

        ~ParseBuf();

        // ==============
        //  Manipulation
        // =============

        /// @brief Returns the number of bytes that this @c ParseBuf instance
        /// can store.
        size_t              spare_capacity();

        /// @brief Returns a pointer to the first uninitialized byte of this
        /// buffer. Starting at that pointer, `spare_capacity()` bytes can be
        /// written.
        uint8_t*            read_buffer();

        /// @brief Assumes that this @c ParseBuf has been filled with `count`
        /// additional instances.
        ///
        /// @warning The provided count must remain bellow `spare_capacity()`.
        void                assume_filled(size_t count);

        /// @brief Makes sure that the buffer can store at least `capacity`
        /// bytes.
        void                reserve(size_t capacity);

        /// @brief Returns a slice over the initialized data.
        Slice<uint8_t>      slice();

        /// @brief Returns a slice over the initialized data.
        Slice<uint8_t>      slice(size_t start, size_t end);

        /// @brief Returns the number of available bytes.
        size_t              available();

        /// @brief Notifies this @c ParseBuf that `count` bytes have been
        /// properly parsed an can be recycled.
        ///
        /// @warning The provided count must remain bellow `available()`.
        void                consume(size_t count);

        /// @brief Gets a specific byte.
        uint8_t operator[](size_t index);
    };
}
