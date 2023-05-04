/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:46:18 by bphilago          #+#    #+#             */
/*   Updated: 2023/05/04 13:18:12 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
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
