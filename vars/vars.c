/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:43:12 by albaud            #+#    #+#             */
/*   Updated: 2023/03/21 13:15:40 by bphilago         ###   ########.fr       */
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
				free(link->content.data);
				link->content.data = ft_strdup(data);
				link->content.export |= export;
				return ;
			}
			link = link->next;
		}
	}
	vlst_add_front(vars, (t_var){ft_strdup(name), ft_strdup(data), export});
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
			free(vars); //free avec le garbage collector
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
		free(tmp->content.data);
		free((void *)tmp->content.name);
		tmp = vars->next;
		vars = tmp;
		ft_putstr("Free\n");
	}
}
