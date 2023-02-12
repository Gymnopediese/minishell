/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:43:12 by albaud            #+#    #+#             */
/*   Updated: 2023/02/12 17:26:54 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_vlink	**get_vars(void)
{
	static t_vlink	*vars;

	return (&vars);
}

char	*get_var_value(const char *name)
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

void	export_var(char *name)
{
	t_vlink	*vars;

	vars = *get_vars();
	while (vars)
	{
		if (ft_strcmp((char *)vars->content.name, (char *)name) == 0)
		{
			vars->content.export = 1;
			return ;
		}
		vars = vars->next;
	}
	add_vars(name, "", 1);
}

void	add_vars(const char *name, char *data, int export)
{
	t_vlink	*link;
	t_vlink	**vars;

	vars = get_vars();
	link = *vars;
	if (get_var_value(name)[0] != '\0')
	{
		while (vars)
		{
			if (ft_strcmp((char *)link->content.name, (char *)name) == 0)
			{
				free(link->content.data);
				link->content.data = ft_strdup(data);
				link->content.export = export;
				return ;
			}
			link = link->next;
		}
	}
	vlst_add_front(vars, (t_var){strdup(name), strdup(data), export});
}

// char	*vars(const char *name, char *data, char commande)
// {
// 	static t_vlink	*vars;
// 	t_vlink			*tmp;
// 	t_vlink			*prev; //changer pour fonction

// 	if (commande == VARS_PRINT)
// 		print_vars(vars);
// 	else if (commande == VARS_GET)
// 		return (get_var_value(name, vars));
// 	else if (commande == VARS_ADD)
// 		add_var(name, data, &vars);
// 	else if (commande == VARS_FREE)
// 	{
// 		tmp = vars;
// 		while (tmp)
// 		{
// 			free(tmp->content.data);
// 			free((void *)tmp->content.name);
// 			tmp = vars->next;
// 			vars = tmp;
// 			ft_putstr("Free\n");
// 		}
// 	}
// 	else if (commande == VARS_DEL)
// 	{
// 		tmp = vars;
// 		prev = 0;
// 		while (tmp)
// 		{
// 			if (!ft_strcmp(vars->content.name, (char *)name))
// 			{
// 				free(tmp->content.data);
// 				free((void *)tmp->content.name);
// 				if (prev)
// 					prev->next = tmp->next;
// 				else
// 					vars = vars->next;
// 				free(vars);
// 				return (0);
// 			}
// 			prev = tmp;
// 			tmp = tmp->next;
// 		}
// 	}
// 	return (0);
// }

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
	add_vars(declaration, &declaration[i + 1], 1);
}
