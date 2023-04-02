/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:43:12 by albaud            #+#    #+#             */
/*   Updated: 2023/03/30 16:40:00 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_vlink	**get_vars(void)
{
	static t_vlink	*vars;

	return (&vars);
}

char	*get_vars_value(const char *name)
{
	t_vlink	*vars;

	vars = *get_vars();
	while (vars)
	{
		if (ft_strcmp((char *)vars->content.name, (char *)name) == 0)
			return (vars->content.data);
		vars = vars->next;
	}
	return ("");
}

void	add_vars(const char *name, char *data, char export)
{
	t_vlink	*link;
	t_vlink	**vars;

	vars = get_vars();
	link = *vars;
	if (get_vars_value(name)[0] != '\0')
	{
		while (vars)
		{
			if (ft_strcmp((char *)link->content.name, (char *)name) == 0)
			{
				ft_mf(FREE, (void *)&link->content.data, 0);
				link->content.data = ft_safecpy(data);
				link->content.export |= export;
				return ;
			}
			link = link->next;
		}
	}
	vlst_add_front(vars, (t_var){ft_safecpy(name), ft_safecpy(data), export});
}


void	del_vars(const char *name)
{
	t_vlink		*vars;
	t_vlink		*tmp;
	t_vlink		*prev;

	printf("Enter del vars\n");
	vars = *get_vars();
	tmp = vars;
	prev = 0;
	while (tmp)
	{
		if (!ft_strcmp(vars->content.name, (char *)name))
		{
			ft_mf(FREE, (void **)&tmp->content.name, 0);
			ft_mf(FREE, (void **)&tmp->content.data, 0);
			if (prev)
				prev->next = tmp->next;
			else
				*get_vars() = vars->next;
			ft_mf(FREE, (void **)&vars, 0);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
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
		ft_mf(FREE, (void **)&tmp->content.data, 0);
		ft_mf(FREE, (void **)&tmp->content.name, 0);
		tmp = vars->next;
		ft_mf(FREE, (void **)&vars, 0);
		vars = tmp;
	}
}
