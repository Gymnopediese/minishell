/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:57:20 by albaud            #+#    #+#             */
/*   Updated: 2023/04/24 12:51:11 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static t_slink	*p_and(t_slink *start, const t_slst *args)
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

static t_slink	*p_or(t_slink *start, const t_slst *args)
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

static void	free_t_slink(t_slink *to_free)
{
	free(to_free->content);
	to_free->content = 0;
	free(to_free);
}

static void	empty_t_lst(t_slink **start, t_slink *tmp)
{
	while (*start && !is_the_end(*start))
	{
		*start = (*start)->next;
		free_t_slink(tmp);
		tmp = *start;
	}
	if (*start != 0)
	{
		*start = (*start)->next;
		free_t_slink(tmp);
	}
}

void	priorities(t_slst *args, const t_args *argv, int success)
{
	t_slink	*start;
	t_slink	*tmp;

	start = args->first;
	tmp = start;
	if (argv->end == OR && success)
	{
		start = p_and(start, args);
		free_t_slink(tmp);
	}
	else if (argv->end == AND && !success)
	{
		start = p_or(start, args);
		free_t_slink(tmp);
	}
	else
		empty_t_lst(&start, tmp);
	args->first = start;
}
