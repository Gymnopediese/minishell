/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/03/21 11:31:15 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	builtins(t_args *args)
{
	int	fd[2];
	int	argc;

	argc = ft_strtablen(args->args);
	if (args->end == PIPE || args->right->size || args->rright->size)
		pipe(fd);
	else
		fd[1] = 1;
	if (ft_strcmp(args->args[0], "echo") == 0)
		ft_echo(args->args, argc, fd[1]);
	else if (ft_strcmp(args->args[0], "cd") == 0)
		ft_cd(args->args, argc, fd[1]);
	else if (ft_strcmp(args->args[0], "pwd") == 0)
		ft_pwd(args->args, argc, fd[1]);
	else if (ft_strcmp(args->args[0], "export") == 0)
		ft_export(args->args, argc, fd[1]);
	else if (ft_strcmp(args->args[0], "unset") == 0)
		ft_unset(args->args, argc, fd[1]);
	else if (ft_strcmp(args->args[0], "env") == 0)
		ft_env(args->args, argc, fd[1]);
	else if (ft_strcmp(args->args[0], "exit") == 0)
		del_vars(args->args[1]);
	else if (ft_strcmp(args->args[0], "exit") == 0)
		exit(errno);
	else
		return (-1);
	if (args->end == PIPE || args->right->size || args->rright->size)
	{
		close(fd[1]);
		filename_injection(args, fd[0]);
		close(fd[0]);
	}
	return (1);
}
