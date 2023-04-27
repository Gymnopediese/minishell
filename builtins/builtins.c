/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/04/27 16:25:32 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	builtins(t_args *argv)
{
	int	argc;

	argc = ft_strtablen(argv->args);
	if (ft_strcmp(argv->args[0], "echo") == 0)
		ft_echo(argv->args, argc, argv->pipes.output);
	else if (ft_strcmp(argv->args[0], "cd") == 0)
		ft_cd(argv->args, argc, argv->pipes.output);
	else if (ft_strcmp(argv->args[0], "pwd") == 0)
		ft_pwd(argv->args, argv->pipes.output);
	else if (ft_strcmp(argv->args[0], "export") == 0)
		ft_export(argv->args, argc, argv->pipes.output);
	else if (ft_strcmp(argv->args[0], "unset") == 0)
		ft_unset(argv->args, argc, argv->pipes.output);
	else if (ft_strcmp(argv->args[0], "env") == 0)
		ft_env(argv->args, argc, argv->pipes.output);
	else if (ft_strcmp(argv->args[0], "exit") == 0)
		ft_exit(argv->args, argc, argv->pipes.output);
	else
		return (-1);
	close_pipe(argv->pipes);
	return (1);
}
