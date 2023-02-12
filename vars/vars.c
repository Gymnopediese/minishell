/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:43:12 by albaud            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/12 11:38:39 by albaud           ###   ########.fr       */
=======
/*   Updated: 2023/02/09 11:30:04 by bphilago         ###   ########.fr       */
>>>>>>> parent of 4cf0605 (Vars upgarde !)
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
	vlst_add_front(vars, (t_var){strdup(name), strdup(data), 0});
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

char	*vars(const char *name, char *data, char commande)
{
	static t_vlink	*vars;
	t_vlink			*tmp;
	t_vlink			*prev; //changer pour fonction

	if (commande == VARS_PRINT)
		print_vars(vars);
	else if (commande == VARS_GET)
		return (get_var_value(name, vars));
	else if (commande == VARS_ADD)
		add_var(name, data, &vars);
	else if (commande == VARS_FREE)
	{
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
	else if (commande == VARS_DEL)
	{
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
					vars = vars->next;
				free(vars);
				return (0);
			}
			prev = tmp;
			tmp = tmp->next;
		}
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
	vars(declaration, &declaration[i + 1], VARS_ADD);
}
