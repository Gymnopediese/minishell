/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2022/12/06 14:16:20 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_unset(t_slst *argv)
{
	errno = 0;
	if (argv->size == 2)
		vars(argv->first->next->content, ""); //TODO true_delete
	if (errno)
		ft_putendl_fd(strerror(errno), 2);
}
