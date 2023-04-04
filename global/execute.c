/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2023/04/04 13:31:07 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

//utilise notre varibale path pour trouver une version valid de lexecutable 
int	get_executable(char *exec, char buff[])
{
	char	**paths;
	int		i;

	i = -1;
	if (exec && exec[0] == '/')
	{
		if (access(exec, F_OK) == 0) // error no executable
		{
			ft_strcpy(buff, exec);
			return (1);
		}
		
	}
	else if (exec && exec[0] == '.' && exec[1] == '/')
	{
		if (access(&exec[2], F_OK) == 0)
		{
			ft_strcpy(buff, exec);
			return (1);
		}
	}
	else
	{
		paths = ft_split(get_vars_value("PATH"), ':');
		if (paths == 0)
			finish("Erreur : PATH null\n", 2);
		while (paths[++i])
		{
			ft_strcpy(buff, paths[i]);
			ft_strcat(buff, "/");
			ft_strcat(buff, exec);
			if (access(buff, F_OK) == 0)
			{
				ft_free_pp((void **)paths);
				return (1);
			}
		}
		ft_free_pp((void **)paths);
	}
	return (0);
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
	}
	else
		dup2(STDOUT_FILENO, STDOUT_FILENO);
	env = export_env();
	execve(file, argv->args, env);
	ft_free_pp((void **)env);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" failed to execute\n", 2);
	return (1);
}

void	free_args(t_args *argv)
{
	free_slist(argv->right);
	free_slist(argv->rright);
	free(argv->args);
	free(argv->right);
	free(argv->rright);
	free(argv);
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
	free_args(argv);
	return (status_code);
}

// Execute "file" and return it's return value
int	execute(t_args *args)
{
	int		pid;
	char	file[1024];
	int		fd[2];

	errno = 0;
	if (!get_executable(args->args[0], file))
		return (127);
	pipe(fd);
	ft_putstra_clean(args->args);
	pid = fork();
	if (pid == 0)
		return (exute_process(args, file, fd));
	else
	{
		return (wait_execution(args, fd));
	}
}
