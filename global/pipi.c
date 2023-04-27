/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 20:39:24 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 16:55:52 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_pipe	**get_pipes(void)
{
	static t_pipe	*pipes;

	return (&pipes);
}

t_pipe	get_pipe_nbr(int index)
{
	return ((*get_pipes())[index]); // TODO Est ce qu'on gere si pipes est null ?
}

void	set_pipes(int pipe_nbr) // TODO Penser a free les pipes
{
	t_pipe	**pipes;
	int		tmp_pip[2];
	int		i;

	pipes = get_pipes();
	free(*pipes);
	*pipes = ft_malloc(sizeof(**pipes) * (pipe_nbr + 1));
	(*pipes)[0].input = STDIN_FILENO;
	i = -1;
	while (++i < pipe_nbr)
	{
		pipe(tmp_pip);
		(*pipes)[i].output = tmp_pip[1];
		(*pipes)[i + 1].input = tmp_pip[0];
	}
	(*pipes)[pipe_nbr].output = STDOUT_FILENO;
}
