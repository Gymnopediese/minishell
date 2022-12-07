/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2022/12/06 14:16:20 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_echo(t_slst *args)
{
	t_slink	*start;
	int		nline;

	nline = 1;
	start = args->first->next;
	if (start && ft_strcmp(start->content, "-n") == 0 && nline--)
		start = start->next;
	while (start)
	{
		ft_putstr(start->content);
		if (start->next)
			ft_putstr(" ");
		start = start->next;
	}
	if (nline)
		ft_putendl("");
}
