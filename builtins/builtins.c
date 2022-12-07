/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2022/12/07 12:15:13 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	builtins(t_slst *args)
{
	if (ft_strcmp(args->first->content, "echo") == 0)
		ft_echo(args);
	else if (ft_strcmp(args->first->content, "cd") == 0)
		ft_cd(args);
	else if (ft_strcmp(args->first->content, "pwd") == 0)
		ft_pwd(args);
	else if (ft_strcmp(args->first->content, "export") == 0)
		ft_export(args);
	else if (ft_strcmp(args->first->content, "unset") == 0)
		ft_unset(args);
	else if (ft_strcmp(args->first->content, "env") == 0)
		ft_env(args);
	else if (ft_strcmp(args->first->content, "exit") == 0)
		exit(errno);
	else
		return (0);
	return (1);
}
