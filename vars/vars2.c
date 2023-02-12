/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:01:40 by albaud            #+#    #+#             */
/*   Updated: 2023/02/12 17:01:49 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	print_vars(void)
{
	t_vlink	*vars;

	vars = *get_vars();
	while (vars)
	{
		ft_putstr((char *)vars->content.name);
		ft_putstr("=");
		ft_putendl(vars->content.data);
		vars = vars->next;
	}
}

void	free_vars(void)
{
	t_vlink		*vars;
	t_vlink		*tmp;

	vars = *get_vars();
	tmp = vars;
	while (tmp)
	{
		free(tmp->content.data);
		free((void *)tmp->content.name);
		tmp = vars->next;
		vars = tmp;
		ft_putstr("Free\n");
	}
}

void	del_vars(const char *name)
{
	t_vlink		*vars;
	t_vlink		*tmp;
	t_vlink		*prev;

	vars = *get_vars();
	tmp = vars;
	prev = 0;
	while (tmp)
	{
		if (!ft_strcmp(vars->content.name, (char *)name))
		{
			free(tmp->content.data);
			free((void *)tmp->content.name);
			if (prev)
				prev->next = tmp->next;
			else
				*get_vars() = vars->next;
			free(vars);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}