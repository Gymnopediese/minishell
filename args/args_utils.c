/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:32:45 by albaud            #+#    #+#             */
/*   Updated: 2022/12/08 13:32:57 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_the_end(t_slink *link)
{
	return (link->type == PIPE || link->type == AND
		|| link->type == OR);
}

int	is_redirection(t_slink *link)
{
	return (link->type == LLEFT || link->type == RRIGHT
		|| link->type == LEFT || link->type == RIGHT);
}
