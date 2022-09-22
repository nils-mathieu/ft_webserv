/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:38:44 by nmathieu          #+#    #+#             */
/*   Updated: 2022/09/22 21:40:50 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
    /// @brief Sets the signal handler up.
    void    setup_interrupted();

    /// @brief Determines whether the `SIGINT` signal has been recieved.
    bool    interrupted();

    /// @brief Resets the `interrupted` flag to `false`.
    void    reset_interrupted();
}
