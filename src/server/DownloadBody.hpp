/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DownloadBody.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:00:12 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/28 13:50:12 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

#include <fstream>

namespace ws
{
    class DownloadBody : public Response
    {
    private:
        size_t          _written;
        std::ofstream   _stream;

    public:
        DownloadBody(const char* path);

        Connection::Flow recieve_body(ft::Str body_part, const RequestHeader& header);
    };
}
