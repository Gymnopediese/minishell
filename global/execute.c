/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2022/12/09 11:49:05 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

//utilise notre varibale path pour trouver une version valid de lexecutable 
char	*get_executable(char *exec)
{
	char	**paths;
	int		i;
	char	buff[777];

	i = -1;
	if (exec && exec[0] == '.' && exec[1] == '/')
	{
		if (access(&exec[2], F_OK) == 0)
			return (exec);//todot else erno; paths
	}
	else
	{
		paths = ft_split(vars("PATH", 0), ':');
		if (paths == 0)
			ft_garbage_colector(0, 1, 1);
		while (paths[++i])
		{
			strcpy(buff, paths[i]); //todo ft_strcpy
			ft_strcat(buff, "/");
			ft_strcat(buff, exec);
			if (access(buff, F_OK) == 0)
			{
				ft_free_pp((void **)paths);
				return (ft_strdup(buff));
			}
		}
		ft_free_pp((void **)paths);
	}
	return (0);
}

int	exute_process(t_args *argv, const char	*file, int *fd)
{
	close(fd[0]);
	if (argv->read || pipi()->to_pipe == 1)
		dup2(pipi()->fd[0], STDIN_FILENO);
	else
		dup2(0, STDIN_FILENO);
	if (argv->end == PIPE || argv->right->size || argv->rright->size)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(STDOUT_FILENO, STDOUT_FILENO);
	execve(file, argv->args, 0);
	ft_putstr_fd(file, 2);
	ft_putendl_fd(" failed to execute\n", 2);
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

// Execute "file" and return it's return value
int	execute(t_args *args)
{
	int			pid;
	const char	*file;
	int			fd[2];

	errno = 0;
	file = get_executable(args->args[0]);
	if (file == 0)
		return (-1);
	pipe(fd);
	ft_putstra_clean(args->args);
	pid = fork();
	if (pid == 0)
		return (exute_process(args, file, fd));
	else
		return (wait_execution(args, fd));
}
