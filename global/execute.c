/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2023/05/04 11:23:27 by bphilago         ###   ########.fr       */
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

static int	execute_process(t_args *argv, const char *file)
{
	char	**env;

	env = export_env();
	dup2(argv->pipe.input, STDIN_FILENO);
	dup2(argv->pipe.output, STDOUT_FILENO);
	execve(file, argv->args, env);
	ft_putstr_fd("minishell: permission denied: ", 2); // TODO close les pipes
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
	close_pipe(argv->pipe);
	return (0);
}

static void tmp_signal(int s)
{
	if (s == SIGQUIT)
		printf("Quit: 3");
	printf("\n");
}

// Execute "file" and return it's return value
int	execute(t_args *argv, t_pipe *pipes, int exec_nbr, int pipe_nbr)
{
	int		pid;
	char	file[1024];

	errno = 0;
	if (!get_executable(argv->args[0], file))
		return (127);
	pid = fork();
	if (pid == 0)
	{
		if (pipe_nbr != 0 && exec_nbr != pipe_nbr)
			close(pipes[exec_nbr + 1].input);
		argv->pipe = pipes[exec_nbr];
		return (execute_process(argv, file));
	}
	else
	{
		signal(SIGINT, tmp_signal);
		signal(SIGQUIT, tmp_signal);
		if (exec_nbr != 0)
			close(pipes[exec_nbr].input);
		return (1);
	}
}
