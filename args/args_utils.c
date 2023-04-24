/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:32:45 by albaud            #+#    #+#             */
/*   Updated: 2023/04/24 11:19:37 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_the_end(const t_slink *link)
{
	return (link->type == PIPE || link->type == AND
		|| link->type == OR);
}

int	is_redirection(const t_slink *link)
{
	return (link->type == LLEFT || link->type == RRIGHT
		|| link->type == LEFT || link->type == RIGHT);
}
