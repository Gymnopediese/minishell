/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:46:18 by bphilago          #+#    #+#             */
/*   Updated: 2023/03/27 11:41:06 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	print_vars(char export)
{
	t_vlink	*vars;

	vars = *get_vars();
	while (vars)
	{
		if (!export || vars->content.export)
		{			
			ft_putstr((char *)vars->content.name);
			ft_putchar('=');
			ft_putendl(vars->content.data);
		}
		vars = vars->next;
	}
}

void	declare_variable(char *declaration, char export)
{
	int	i;

	i = -1;
	while (declaration[++i] && declaration[i] != '=')
		;
	if (!declaration[i])
		return ;
	declaration[i] = 0;
	printf("%s and %s\n", declaration, &declaration[i + 1]);
	add_vars(declaration, &declaration[i + 1], export);
}

void	import_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != 0)
		declare_variable(strdup(env[i]), 1);
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
	result = allok(size + 1, sizeof(char *), 1);
	result[size] = 0;
	current = *vars;
	i = -1;
	while (current && ++i >= 0)
	{
		if (!current->content.export)
			continue ;
		size = ft_strlen(current->content.name);
		result[i] = allok(size + ft_strlen(current->content.data) + 2,
				sizeof(char *), 1);
		ft_strcpy(result[i], current->content.name);
		result[i][size] = '=';
		ft_strcpy(result[i] + size + 1, current->content.data);
		result[i][size + ft_strlen(current->content.data) + 1] = 0;
		current = current->next;
	}
	return (result);
}
