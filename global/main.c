/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:15 by albaud            #+#    #+#             */
/*   Updated: 2023/04/24 14:08:00 by bphilago         ###   ########.fr       */
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

void	put_pipi(void)
{
	ft_putendl("printing pipi");
	ft_putia_clean(pipi()->fd, 2);
	//ft_putnbrn(pipi()->to_pipe);
	ft_putendl("printing pipi done");
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

static void	exec_line(t_slst *args)
{
	int		exec;
	char	*temp;
	t_args	*argv;

	wait(&exec);
	if (args->first == 0)
		return ;
	exec = 0;
	argv = slst_to_tab(args);
	//ft_putstra_clean(argv->args);
	if (builtins(argv) == -1)
	{
		exec = execute(argv);
		if (exec != -1 && exec != 127) // TODO : Esst ce que != est ok ?
		{
			temp = ft_itoa(exec); // TODO : malloc non protege
			add_vars("?", temp, 1); // TODO : export ou pas ?
			free(temp);
		}
		else if (ft_strtablen(argv->args) == 1) //TODO : tester si a un =
		{
			declare_variable(argv->args[0], 0); //TODO : export ou pas ?
		}
	}
	else
	{
		exec = errno;
		temp = ft_itoa(exec); //malloc non protege
		add_vars("?", temp, 1); //export ou pas ?
		free(temp);
	}
	priorities(args, argv, !exec);
	free_argv(argv);
	exec_line(args);
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

int	main(__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv, __attribute__((unused))char **envp)
{	
	char	*prompt;
	t_slst	*list;

	import_env(envp);
	pipi()->fd[0] = 0;
	pipi()->fd[1] = 1;
	pipi()->to_pipe = 0;
	//add_history("echo $PATH");
	//add_history("make && ./minishell");
	//add_history("echo salut | cat -e");
	printf("welcome to our minishell :)\n");
	while (1)
	{
		connect_signals();
		prompt = readline("$> ");
		if (!prompt)
			finish("", 0);
		if (prompt[0] != 0)
		{
			add_history(prompt);
			list = parser(prompt);
			exec_line(list);
			free(list);
		}
		free(prompt);
	}
}
