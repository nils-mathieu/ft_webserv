/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:39:08 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 19:02:35 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigint.hpp"
#include "OsException.hpp"

#include <signal.h>

namespace ft
{
    namespace sigint
    {
        static bool flag = false;

        static void handler(int)
        {
            flag = true;
        }

        void initialize()
        {
            struct sigaction act;
            sigemptyset(&act.sa_mask);
            act.sa_flags = 0;
            act.sa_handler = handler;

            if (sigaction(SIGINT, &act, 0) != 0)
                throw OsException("failed to setup a SIGINT signal handler");
        }

        bool occured()
        {
            return flag;
        }

        void reset()
        {
            flag = false;
        }
    }
}
