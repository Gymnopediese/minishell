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

char	*get_executable(char *exec)
{
	char	**paths;
	int		i;
	char	buff[777];

	i = -1;
	if (exec && exec[0] == '.' && exec[1] == '/')
	{
		if (access(&exec[2], F_OK) == 0)
			return (exec);
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

char	**slst_to_tab(t_slst *args)
{
	char	**res;
	t_slink	*node;	
	int		i;

	i = -1;
	res = allok(sizeof(char *), args->size, 1);
	node = args->first;
	while (node)
	{
		res[++i] = node->content;
		node = node->next;
	}
	return (res);
}

// Execute "file" and return it's return value
int	execute(t_slst *args)
{
	int			pid;
	int			wstatus;
	int			status_code;
	const char	*file;

	errno = 0;
	file = get_executable(args->first->content);
	if (file == 0)
		return (1);

	ft_putendl((char *)file);
	pid = fork();
	if (pid == 0)
	{
		execve(file, slst_to_tab(args), 0);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(" failed to execute\n", 2);
		return (1);
	}
	else
	{
		wait(&wstatus);
		status_code = 0;
		if (WIFEXITED(wstatus))
			status_code = WEXITSTATUS(wstatus);
		return (status_code);
	}
	return (0);
}
