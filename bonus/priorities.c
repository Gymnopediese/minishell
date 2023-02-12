/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:57:20 by albaud            #+#    #+#             */
/*   Updated: 2023/02/12 18:04:43 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_slink	*p_and(t_slink *start, t_slst *args)
{
	while (start && start->level >= args->first->level)
	{
		if (start->type == AND && start->level == args->first->level)
		{
			start = start->next;
			break ;
		}
		start = start->next;
	}
	return (start);
}


t_slink	*p_or(t_slink *start, t_slst *args)
{
	while (start && start->level >= args->first->level)
	{
		if (start->type == OR && start->level == args->first->level)
		{
			start = start->next;
			break ;
		}
		start = start->next;
	}
	return (start);
}


void	priorities(t_slst *args, t_args *argv, int success)
{
	t_slink	*start;

	start = args->first;
	if (argv->end == OR && success)
	{
		start = p_and(start, args);
	}
	else if (argv->end == AND && !success)
	{
		start = p_or(start, args);
	}
	else
	{
		while (start && !is_the_end(start))
			start = start->next;
		if (start != 0)
			start = start->next;
	}
	args->first = start;
}
