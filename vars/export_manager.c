/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:46:18 by bphilago          #+#    #+#             */
/*   Updated: 2023/04/27 15:20:38 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	print_vars(char export, int fd, int mode)
{
	t_vlink	*vars;

	vars = *get_vars();
	while (vars)
	{
		if (!export || vars->content.export)
		{		
			if (mode == 1)
				ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd((char *)vars->content.name, fd);
			ft_putchar_fd('=', fd);
			ft_putendl_fd(vars->content.data, fd);
		}
		vars = vars->next;
	}
}

void	export_var(const char *name)
{
	t_vlink	*link;

	link = *get_vars();
	while (link)
	{
		if (ft_strcmp((char *)link->content.name, (char *)name) == 0)
		{
			link->content.export = 1;
			return ;
		}
		link = link->next;
	}
	add_vars(name, "", 1);
}

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	declare_variable(char *declaration, char export)
{
	int	i;

	i = -1;
	if (!ft_isalpha(declaration[0]))
		return (0);
	while (declaration[++i] && declaration[i] != '=')
		;
	if (!declaration[i])
	{
		export_var(declaration);
		return (2);
	}
	declaration[i] = 0;
	add_vars(declaration, &declaration[i + 1], export);
	return (1);
}

void	import_env(char **env)
{
	int		i;

	i = -1;
	while (env[++i] != 0)
		declare_variable(env[i], 1);
}

void	free_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		free(env[i]);
	}
	free(env);
}

char	**export_env(void) //TODO split
{
	t_vlink	*current;
	t_vlink	**vars;
	int		size;
	int		i;
	char	**result;

	vars = get_vars();
	current = *vars;
	size = 0;
	while (current)
	{
		if (current->content.export)
			size += 1;
		current = current->next;
	}
	result = ft_malloc(sizeof(char *) * (size + 1));
	result[size] = 0;
	current = *vars;
	i = -1;
	while (current)
	{
		if (!current->content.export)
		{
			current = current->next;
			continue ;
		}
		++i;
		size = ft_strlen(current->content.name);
		*(result + i) = ft_malloc(sizeof(char *)
				* (size + ft_strlen(current->content.data) + 2));
		ft_strcpy(result[i], current->content.name);
		result[i][size] = '=';
		ft_strcpy(result[i] + size + 1, current->content.data);
		result[i][size + ft_strlen(current->content.data) + 1] = 0;
		current = current->next;
	}
	return (result);
}
