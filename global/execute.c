/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2023/04/25 16:27:08 by bphilago         ###   ########.fr       */
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

int	exute_process(t_args *argv, const char	*file, int *fd)
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
		printf("a merde\n");
	}
	else
		dup2(STDOUT_FILENO, STDOUT_FILENO);
	env = export_env();
	execve(file, argv->args, env);
	ft_putstr_fd("minishell: permission denied: ", 2); // TODO close les pipes
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	wait_execution(t_args *argv, int *fd)
{
	int	wstatus;
	int	status_code;

	errno = 0;
	status_code = 0;
	wait(&wstatus);
	if (WIFEXITED(wstatus))
		status_code = WEXITSTATUS(wstatus);
	close(fd[1]);
	close(pipi()->fd[1]);
	close(pipi()->fd[0]);
	filename_injection(argv, fd[0]);
	if (argv->end != PIPE)
		pipi()->to_pipe = 0;
	else
		pipi()->to_pipe = 1;
	close(fd[0]);
	return (status_code);
}

static void test(int t) // TODO faire propre
{
	(void) t;
	if (t == SIGQUIT)
		printf("Quit: 3");
	printf("\n");
}

// Execute "file" and return it's return value
int	execute(t_args *argv)
{
	int		pid;
	char	file[1024];
	int		fd[2];

	errno = 0;
	if (!get_executable(argv->args[0], file))
		return (127);
	pipe(fd);
	pid = fork();
	if (pid == 0)
		return (exute_process(argv, file, fd));
	else
	{
		signal(SIGINT, test);
		signal(SIGQUIT, test);
		return (wait_execution(argv, fd));
	}
}
