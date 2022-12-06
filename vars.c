/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:43:12 by albaud            #+#    #+#             */
/*   Updated: 2022/12/06 14:35:59 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_var(const char *name, char *data, t_vlink **vars)
{
	vlst_add_front(vars, (t_var){strdup(name), strdup(data)});
}

char	*get_var_value(const char *name, t_vlink *vars)
{
	while (vars)
	{
		if (ft_strcmp((char *)vars->content.name, (char *)name) == 0)
			return (vars->content.data);
		vars = vars->next;
	}
	return (0);
}

char	*vars(const char *name, char *data)
{
	static t_vlink	*vars;

	if (data == 0)
	{
		return (get_var_value(name, vars));
	}
	else
	{
		add_var(name, data, &vars);
	}
	return (0);
}

void	declare_variable(char *declaration)
{
	int	i;

	i = -1;

	while (declaration[++i] && declaration[i] != '=')
		;
	if (!declaration[i])
		return ;
	declaration[i] = 0;
	ft_putendl(declaration);
	ft_putendl(&declaration[i + 1]);
	vars(declaration, &declaration[i + 1]);
}
