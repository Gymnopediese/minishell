/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:43:12 by albaud            #+#    #+#             */
/*   Updated: 2023/05/04 15:37:48 by bphilago         ###   ########.fr       */
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
				link->content.data = ft_safecpy(data);
				link->content.export |= export;
				return ;
			}
			link = link->next;
		}
	}
	vlst_add_front(vars, (t_var){ft_safecpy(name), ft_safecpy(data), export});
}

int	del_vars(char *name)
{
	t_vlink		*tmp;
	t_vlink		*prev;

	tmp = *get_vars();
	prev = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->content.name, name))
		{
			free(tmp->content.name);
			free(tmp->content.data);
			if (prev)
				prev->next = tmp->next;
			else
				*get_vars() = (*get_vars())->next;
			free(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
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
		free(tmp->content.name);
		tmp = vars->next;
		free(vars);
		vars = tmp;
	}
}
