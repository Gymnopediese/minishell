/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2023/05/04 13:37:30 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	default_signal(int t)
{
	(void) t;
	if (t == SIGQUIT)
		printf("Quit: 3");
	printf("\n");
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
		return (execute_proccess(argv, file, fd));
	else
	{
		signal(SIGINT, default_signal);
		signal(SIGQUIT, default_signal);
		return (wait_execution(argv, fd));
	}
}
