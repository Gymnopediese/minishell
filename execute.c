/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2022/12/07 15:18:02 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


//utilise notre varibale path pour trouver une version valid de lexecutable demander
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
				return (ft_strdup(buff));
		}
		ft_free_pp((void **)paths);
	}
	return (0);
}



// Execute "file" and return it's return value
int	execute(t_slst *args)
{
	int			pid;
	int			wstatus;
	int			status_code;
	const char	*file;
	t_args		argv;
	int			fd[2];

	printf("Enter execute\n");
	errno = 0;
	file = get_executable(args->first->content);
	if (file == 0)
		return (1);

	pipe(fd);
	argv = slst_to_tab(args);
	write(1, "good\n", 5);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(argv.fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execve(file, argv.args, 0);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(" failed to execute\n", 2);
		return (1);
	}
	else
	{
		wait(&wstatus);
		close(fd[1]);
		dup2(0, STDIN_FILENO);
		dup2(1, STDOUT_FILENO);
		//fd_fd_injection(1, fd[0]);
		filename_injection(&argv, fd[0]);
		status_code = 0;
		if (WIFEXITED(wstatus))
			status_code = WEXITSTATUS(wstatus);
		return (status_code);
	}
	return (0);
}
