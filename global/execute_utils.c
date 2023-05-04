/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:54:02 by bphilago          #+#    #+#             */
/*   Updated: 2023/05/04 13:36:53 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	get_with_slash(const char *exec, char buff[])
{
	if (access(exec, X_OK) == 0)
	{
		ft_strcpy(buff, exec);
		return (1);
	}
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putstr_fd(exec, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

static int	get_with_dot_slash(const char *exec, char buff[])
{
	if (access(&exec[2], X_OK) == 0)
	{
		ft_strcpy(buff, exec);
		return (1);
	}
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putstr_fd(exec, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

static int	get_from_paths(const char *exec, char buff[])
{
	char	**paths;
	int		i;

	i = -1;
	paths = ft_split(get_vars_value("PATH"), ':');
	if (paths == 0)
		finish("Erreur : PATH null\n", 2);
	while (paths[++i])
	{
		ft_strcpy(buff, paths[i]);
		ft_strcat(buff, "/");
		ft_strcat(buff, exec);
		if (access(buff, X_OK) == 0)
		{
			ft_free_pp((void **)paths);
			return (1);
		}
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(exec, 2);
	ft_putchar_fd('\n', 2);
	ft_free_pp((void **)paths);
	return (0);
}

//utilise notre varibale path pour trouver une version valid de lexecutable 
int	get_executable(const char *exec, char buff[])
{
	if (exec && exec[0] == '/')
	{
		return (get_with_slash(exec, buff));
	}
	else if (exec && exec[0] == '.' && exec[1] == '/')
	{
		return (get_with_dot_slash(exec, buff));
	}
	return (get_from_paths(exec, buff));
}

int	execute_proccess(t_args *argv, const char	*file, int *fd)
{
	char	**env;

	close(fd[0]);
	if (argv->read || pipi()->to_pipe == 1)
	{
		dup2(pipi()->fd[0], STDIN_FILENO);
	}
	else
		dup2(0, STDIN_FILENO);
	if (argv->end == PIPE || argv->right->size || argv->rright->size)
	{
		dup2(fd[1], STDOUT_FILENO);
	}
	else
		dup2(STDOUT_FILENO, STDOUT_FILENO);
	env = export_env();
	execve(file, argv->args, env);
	ft_putstr_fd("minishell: permission denied: ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
	close(fd[1]);
	close(pipi()->fd[0]);
	close(pipi()->fd[1]);
	return (0);
}
