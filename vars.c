/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:43:12 by albaud            #+#    #+#             */
/*   Updated: 2022/12/08 15:53:00 by ben              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_var_value(const char *name, t_vlink *vars)
{
	while (vars)
	{
		if (ft_strcmp((char *)vars->content.name, (char *)name) == 0)
			return (vars->content.data);
		vars = vars->next;
	}
	return ("");
}

void	add_var(const char *name, char *data, t_vlink **vars)
{
	t_vlink	*link;

	link = *vars;
	if (get_var_value(name, *vars)[0] != '\0')
	{
		while (vars)
		{
			if (ft_strcmp((char *)link->content.name, (char *)name) == 0)
			{
				free(link->content.data);
				link->content.data = ft_strdup(data);
				return ;
			}
			link = link->next;
		}
	}
	vlst_add_front(vars, (t_var){strdup(name), strdup(data), 0}); // Voir pour changer le 0
}

void	print_vars(t_vlink *vars)
{
	while (vars)
	{
		ft_putstr((char *)vars->content.name);
		ft_putstr("=");
		ft_putendl(vars->content.data);
		vars = vars->next;
	}
}

char	*vars(const char *name, char *data)
{
	static t_vlink	*vars;

	if (name == 0)
	{
		print_vars(vars);
	}
	else if (data == 0)
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
