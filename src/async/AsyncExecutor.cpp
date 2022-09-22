/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AsyncExecutor.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:03:22 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 21:43:07 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/sigint.hpp"
#include "ft/OsException.hpp"
#include "AsyncExecutor.hpp"

#include <unistd.h>
#include <sys/epoll.h>

namespace ws
{
    AsyncExecutor::AsyncExecutor() :
        _entities()
    {
        int fd = epoll_create(1);

        if (fd == -1)
            throw ft::OsException("failed to initialize the executor");

        _epoll = fd;
    }

    AsyncExecutor::~AsyncExecutor()
    {
        close(this->_epoll);

        std::vector<Pollable*>::iterator it = this->_entities.begin();
        while (it != this->_entities.end())
        {
            delete *it;
            it++;
        }
    }

    void    AsyncExecutor::append(Pollable* pollable)
    {
        this->_entities.push_back(pollable);

        struct epoll_event ev;
        ev.events = pollable->interest();
        ev.data.ptr = (void*)pollable;

        if (
            epoll_ctl(
                this->_epoll,
                EPOLL_CTL_ADD,
                pollable->file_descriptor(),
                &ev
            )
            != 0
        )
        {
            throw ft::OsException("failed to register a `Pollable` instance");
        }
    }

    bool AsyncExecutor::poll_some(int timeout)
    {
        struct epoll_event  evs[32];

        // =============================================================
        //  1. call `epoll_wait` to determine what entity needs polling
        // =============================================================

        int count = epoll_wait(this->_epoll, evs, 32, timeout);

        if (ft::interrupted())
            return (true);

        if (count <= -1)
            throw ft::OsException("failed to wait on `Pollable` instances");

        if (count == 0)
            return (false);

        // ==================================================
        //  2. call `poll` on instances that have work to do
        // ==================================================

        for (int i = 0; i < count; i++)
        {
            Pollable* entity = (Pollable*)evs[i].data.ptr;

            if (entity->poll(evs[i].events))
            {
                // ===================================
                //  3. remove instances that are done
                // ===================================

                std::vector< Pollable* >::iterator    it;

                it = this->_entities.begin();
                while (it != this->_entities.end())
                {
                    if (*it == entity)
                    {
                        if (
                            epoll_ctl(
                                this->_epoll,
                                EPOLL_CTL_DEL,
                                entity->file_descriptor(),
                                0
                            )
                            != 0
                        )
                        {
                            throw ft::OsException("failed to remove a `Pollable` instance");
                        }

                        delete *it;
                        *it = this->_entities.back();
                        this->_entities.pop_back();

                        break;
                    }
                    it++;
                }
            }
        }

        return (true);
    }
}
