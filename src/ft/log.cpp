/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:37:00 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/26 12:30:33 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/debug.hpp"
#include "log.hpp"
#include "LogLevel.hpp"
#include "Sink.hpp"

#include <stdint.h>
#include <iostream>

namespace ft
{
    namespace log
    {
        static LogLevel     _max_level;
        static Sink         _sink_stream;

        void initialize()
        {
            _max_level = Trace;
        }

        void set_max_level(LogLevel level)
        {
            _max_level = level;
        }

        static std::ostream& log_with_level(LogLevel level)
        {
            if (level > _max_level)
                return _sink_stream;
            else
                return std::clog;
        }

        std::ostream& details()
        {
            return log_with_level(Details);
        }

        std::ostream& trace()
        {
            return log_with_level(Trace);
        }

        std::ostream& info()
        {
            return log_with_level(Info);
        }

        std::ostream& warn()
        {
            return log_with_level(Warn);
        }

        std::ostream& error()
        {
            return log_with_level(Error);
        }
    }
}
