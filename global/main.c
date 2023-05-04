/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/05/04 12:37:10 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	put_slst(t_slst *lst)
{
	t_slink	*n;

	n = lst->first;
	ft_putendl("printing list");
	while (n)
	{
		ft_putendl(n->content);
		n = n->next;
	}
	ft_putendl("printing list done");
}

static void	free_argv(t_args *argv)
{
	free_slist(argv->right);
	free_slist(argv->rright);
	free(argv->args);
	free(argv->right);
	free(argv->rright);
	free(argv);
}

static int	is_variable_declaration(char *instruction)
{
	if (ft_strcontain(instruction, '='))
		return (1);
	else
		return (0);
}

int	try_builtins(t_args *argv)
{
	char	*temp;

	if (ft_strtablen(argv->args) == 0 || builtins(argv) == -1)
		return (0);
	temp = ft_itoa(errno); //malloc non protege
	add_vars("?", temp, 0);
	free(temp);
	return (1);
}

void	create_pipe(t_pipe *pipes, int index, int pipe_nbr)
{
	t_pipe	tmp;

	if (index == 0)
		pipes[index].input = STDIN_FILENO;
	if (pipe_nbr == 0 || index == pipe_nbr)
		pipes[index].output = STDOUT_FILENO;
	else
	{
		pipe((int *)&tmp);
		pipes[index].output = tmp.output;
		pipes[index + 1].input = tmp.input;
	}
}

int	try_execute(t_args *argv, t_pipe *pipes, int exec_nbr, int pipe_nbr)
{
	char	*temp;

	if (ft_strtablen(argv->args) == 0)
		return (0);
	errno = execute(argv, pipes, exec_nbr, pipe_nbr);
	temp = ft_itoa(errno); // TODO : malloc non protege
	add_vars("?", temp, 0);
	free(temp);
	return (1);
}

int	try_declare(t_args *argv)
{
	if (ft_strtablen(argv->args) == 1
		&& is_variable_declaration(argv->args[0])) 
	{
		declare_variable(argv->args[0], 0);
		return (1);
	}
	return (0);
}

static void	exec_line(t_slst *args, t_pipe *pipes, int exec_nbr)
{
	t_args	*argv;

	if (args->first == 0)
		return ;
	errno = 0;
	create_pipe(pipes, exec_nbr, args->pipe_nbr);
	if (exec_nbr == 0)
		argv = slst_to_tab(args, STDIN_FILENO); // On ne peut pas ecrire dans STDIN
	else
	{
		argv = slst_to_tab(args, pipes[exec_nbr - 1].output);
		if (args->pipe_nbr != 0 && exec_nbr != args->pipe_nbr)
			close(pipes[exec_nbr - 1].output);
	}
	argv->pipe = pipes[exec_nbr];
	if (try_builtins(argv) || try_declare(argv))
	{
		if (exec_nbr != 0)
			close(pipes[exec_nbr].input);
	}
	else
	{
		if (!try_execute(argv, pipes, exec_nbr, args->pipe_nbr))
			printf("ERRRRROOOORRR\n");// TODO Gerer l'erreur
	}
	priorities(args, argv, !errno);
	free_argv(argv);
	exec_line(args, pipes, exec_nbr + 1);
}

// A deplacer dans un autre fichier
char	*ft_safecpy(const char *src)
{
	int		i;
	int		len;
	char	*str;

	len = ft_strlen(src);
	str = ft_malloc(sizeof(*str) * (len + 1));
	i = -1;
	while (++i < len)
		str[i] = src[i];
	str[i] = 0;
	return (str);
}

void	close_pipe(t_pipe to_close) // TODO essayer de fermer le pipe d'avant quand un program termine
{
	if (to_close.input != STDIN_FILENO)
		close(to_close.input);
	if (to_close.output != STDOUT_FILENO)
		close(to_close.output);
}

int	wait_executions(void)
{
	int	wstatus;
	int	status_code;

	errno = 0;
	status_code = 0;
	while (wait(&wstatus) != -1)
	{
		if (WIFEXITED(wstatus))
			status_code = WEXITSTATUS(wstatus);
		// filename_injection(argv, fd[0]);
	}
	return (status_code);
}

int	main(__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv, __attribute__((unused))char **envp)
{	
	char	*prompt;
	t_slst	*list;
	t_pipe	*pipes;

	import_env(envp);
	//add_history("echo $PATH");
	//add_history("make && ./minishell");
	add_history("< test | cat -e");
	add_history("echo \"hello\" | grep \"hello\"");
	printf("welcome to our minishell :)\n");
	while (1)
	{
		connect_signals();
		prompt = readline("$> ");
		if (!prompt)
			finish("exit\n", 0);
		if (prompt[0] != 0)
		{
			add_history(prompt);
			list = parser(prompt); // TODO Est ce que list peut etre null ?
			pipes = ft_malloc(sizeof(*pipes) * (list->pipe_nbr + 1));
			exec_line(list, pipes, 0);
			wait_executions();
			free(list);
			free(pipes);
		}
		free(prompt);
	}
}
