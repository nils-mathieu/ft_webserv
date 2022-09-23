/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:38:44 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/23 19:02:09 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
    namespace sigint {
        /// @brief Sets the signal handler up.
        void    initialize();

        /// @brief Determines whether the `SIGINT` signal has been recieved.
        bool    occured();

        /// @brief Resets the `interrupted` flag to `false`.
        void    reset();
    }
}
