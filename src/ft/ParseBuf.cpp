/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseBuf.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:19:37 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 13:39:35 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.hpp"
#include "ParseBuf.hpp"

namespace ft
{
    ParseBuf::ParseBuf(size_t capacity) :
        _alloc(),
        _data(0),
        _cap(0),
        _init(0),
        _consumed(0)
    {
        if (capacity)
        {
            this->_data = this->_alloc.allocate(capacity);
            this->_cap = capacity;
        }
    }

    ParseBuf::~ParseBuf()
    {
        if (this->_cap)
            this->_alloc.deallocate(this->_data, this->_cap);
    }

    size_t ParseBuf::spare_capacity()
    {
        return (this->_cap - this->_init);
    }

    uint8_t* ParseBuf::read_buffer()
    {
        return (this->_data + this->_init);
    }

    ft::Slice<uint8_t>  ParseBuf::spare_slice()
    {
        return ft::Slice<uint8_t>(this->_data + this->_init, this->_cap - this->_init);
    }

    void ParseBuf::assume_filled(size_t count)
    {
        assert(this->_init + count <= this->_cap, "`assumed_filled` overflows the capacity");
        this->_init += count;
    }

    void ParseBuf::reserve(size_t additional)
    {
        // FAST PATH: we don't have any capacity allocated.
        if (this->_cap == 0)
        {
            this->_data = this->_alloc.allocate(additional);
            return;
        }

        // This quantity is the number of bytes that are directly available.
        // We don't need to move the content of the buffer to actually have it.
        size_t available = this->_cap - this->_init;

        if (available >= additional)
            return;

        // This is the number of bytes we could have if we recycled the consumed
        // bytes.
        available += this->_consumed;

        if (available >= additional)
        {
            // That would be enough! We can avoid a reallocation.
            memmove(this->_data, this->_data + this->_consumed, this->_consumed);
            this->_init -= this->_consumed;
            this->_consumed = 0;
            return;
        }

        size_t new_cap = this->_init - this->_consumed + additional;

        uint8_t* new_data = this->_alloc.allocate(new_cap);
        memcpy(new_data, this->_data + this->_consumed, this->_init - this->_consumed);
        this->_alloc.deallocate(this->_data, this->_cap);

        this->_data = new_data;
        this->_cap = new_cap;
        this->_init -= this->_consumed;
        this->_consumed = 0;
    }

    Slice<uint8_t> ParseBuf::slice()
    {
        return Slice<uint8_t>(this->_data + this->_consumed, this->_init - this->_consumed);
    }

    Slice<uint8_t> ParseBuf::slice(size_t start, size_t end)
    {
        return Slice<uint8_t>(this->_data + this->_consumed + start, this->_data + this->_consumed + end);
    }

    size_t ParseBuf::available()
    {
        return (this->_init - this->_consumed);
    }

    void ParseBuf::consume(size_t count)
    {
        assert(this->_consumed + count <= this->_init, "`consume`d more bytes than available");
        this->_consumed += count;

        if (this->_consumed == this->_init)
        {
            this->_consumed = 0;
            this->_init = 0;
        }
    }

    void ParseBuf::clear()
    {
        this->_consumed = 0;
        this->_init = 0;
    }

    uint8_t ParseBuf::operator[](size_t index)
    {
        return *(this->_data + this->_consumed + index);
    }
}
