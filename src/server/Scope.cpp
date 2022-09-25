/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scope.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:50:14 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/25 19:08:11 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scope.hpp"
#include "ft/log.hpp"
#include "ft/Color.hpp"

namespace ws
{
    Scope::Scope() :
        exact_location(false),
        location(),
        root(),
        added_methods(),
        removed_methods(),
        children(),
        outcomes()
    {}

    Scope::~Scope()
    {
        while (!this->outcomes.empty())
        {
            delete this->outcomes.back();
            this->outcomes.pop_back();
        }

        while (!this->children.empty())
        {
            delete this->children.back();
            this->children.pop_back();
        }
    }

    static bool starts_with(const char* a, const char* b)
    {
        while (*a && *b && *a == *b)
        {
            a++;
            b++;
        }
        return (*b == '\0');
    }

    bool Scope::try_respond(
        const RequestHeader& request,
        Responding& responding
    ) const
    {
        // This is kept around to truncate the aggregated location later.
        size_t  original_location_size = responding.location.size();
        Methods original_methods = responding.methods;
        ft::Str original_root = responding.root;

        responding.location.append((char*)this->location.data(), this->location.size());
        responding.methods |= this->added_methods;
        responding.methods &= ~this->removed_methods;

        if (!this->root.empty())
            responding.root = this->root;

        // ==========================================
        //  Check If One Of The Children Can Respond
        // ==========================================

        {
            std::vector<Scope*>::const_iterator  it = this->children.begin();
            while (it != this->children.end())
            {
                if ((*it)->try_respond(request, responding))
                {
                    responding.location.resize(original_location_size);
                    responding.methods = original_methods;
                    responding.root = original_root;
                    return (true);
                }

                it++;
            }
        }

        // ========================
        //  Try To Respond Ourself
        // ========================

        // ... if we are allowed to!
        if (!starts_with(request.uri.c_str(), responding.location.c_str()))
        {
            responding.methods = original_methods;
            responding.location.resize(original_location_size);
            responding.root = original_root;
            return (false);
        }

        if (
            this->exact_location
            && responding.location.size() != request.uri.size()
        )
        {
            responding.methods = original_methods;
            responding.location.resize(original_location_size);
            responding.root = original_root;
            return (false);
        }

        ft::log::trace()
            << "      scope `"
            << ft::log::Color::Yellow
            << responding.location
            << ft::log::Color::Reset
            << "` may respond"
            << std::endl;

        // Check if the method is allowed for this scope.
        if ((responding.methods & (Methods)request.method) == 0)
        {
            ft::log::trace()
                << "        method `"
                << ft::log::Color::Red
                << request.method
                << ft::log::Color::Reset
                << "` not allowed" << std::endl
                << "        "
                << ft::log::Color::Dim
                << "allowed methods:"
                << ft::log::Color::Green
                << responding.methods
                << ft::log::Color::Reset
                << std::endl;

            responding.status = StatusCode::MethodNotAllowed;
            responding.methods = original_methods;
            responding.location.resize(original_location_size);
            responding.root = original_root;
            return (false);
        }


        // Check if we have a defined outcome for this request.
        {
            std::vector<Outcome*>::const_iterator it = this->outcomes.begin();
            while (it != this->outcomes.end())
            {
                if ((*it)->try_respond(responding, request))
                {
                    responding.methods = original_methods;
                    responding.location.resize(original_location_size);
                    responding.root = original_root;
                    return (true);
                }

                it++;
            }
        }

        // =============================
        //  We Were Not Able To Respond
        // =============================

        responding.methods = original_methods;
        responding.location.resize(original_location_size);
        responding.root = original_root;
        return (false);
    }
}
