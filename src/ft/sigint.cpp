/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:39:08 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 21:41:58 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigint.hpp"
#include "OsException.hpp"

#include <signal.h>

namespace ft
{
    static bool flag = false;

    static void handler(int)
    {
        flag = true;
    }

    void setup_interrupted()
    {
        struct sigaction act;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        act.sa_handler = handler;

        if (sigaction(SIGINT, &act, 0) != 0)
            throw OsException("failed to setup a SIGINT signal handler");
    }

    bool interrupted()
    {
        return flag;
    }

    void reset_interrupted()
    {
        flag = false;
    }
}
