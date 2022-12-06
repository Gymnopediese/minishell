/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2022/12/06 13:26:48 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Execute "file" and return it's return value
int	execute(const char *file, char *const *argv, char *const *envp)
{
	int	pid;
	int	wstatus;
	int	status_code;

	pid = fork();
	if (pid == 0) 
	{
		execve(file, argv, envp);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(" failed to execute\n", 2);
		return (1);
	}
	else
	{
		wait(&wstatus);
		status_code = 0;
		if (WIFEXITED(wstatus))
		{
			status_code = WEXITSTATUS(wstatus);
		}
		return (status_code);
	}
}
