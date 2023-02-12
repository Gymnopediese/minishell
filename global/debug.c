/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:39:47 by albaud            #+#    #+#             */
/*   Updated: 2023/02/12 18:13:13 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	debug_history(void)
{
	add_history("cat Makefile | wc");
	add_history("ls > test >> test | cat -e");
	add_history("norminette | grep -v OK");
	add_history("echo -n salut");
	add_history("(ls asd && ls) || ls");
	add_history("|||");
	add_history("echo $USER");
	add_history("echo $PATH");
}

void	put_slst(t_slst *lst)
{
	t_slink	*n;

	n = lst->first;
	ft_putendl("printing list");
	while (n)
	{
		ft_putendl(n->content);
		n = n->next;
	}
	ft_putendl("printing list done");
}

void	put_pipi(void)
{
	ft_putendl("printing pipi");
	ft_putia_clean(pipi()->fd, 2);
	ft_putnbrn(pipi()->to_pipe);
	ft_putendl("printing pipi done");
}
