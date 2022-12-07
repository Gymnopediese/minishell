/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:45 by albaud            #+#    #+#             */
/*   Updated: 2022/12/07 15:04:03 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "koflibc/sources.h"
# include <signal.h>
# include <termios.h>
# include <sys/errno.h>
// # include "/opt/homebrew/Cellar/readline/8.2.1/include/readline/readline.h"

enum
{
	TEXT,
	PIPE,
	LEFT,
	LLEFT,
	RIGHT,
	RRIGHT,
	OR,
	AND,
	PLEFT,
	PRIGHT,
};

typedef struct s_buff
{
	char	b[10001];
	int		i;
}	t_buff;

typedef struct s_var
{
	const char	*name;
	char		*data;
}	t_var;

typedef struct s_vlink
{
	t_var			content;
	struct s_vlink	*next;
}	t_vlink;

typedef struct s_slink
{
	char			*content;
	struct s_slink	*next;
	int				type;
	int				level;
}	t_slink;

typedef struct s_slst
{
	t_slink	*first;
	t_slink	*last;
	int		size;
}	t_slst;

typedef struct s_args
{
	char	**args;
	t_slst	*right;
	t_slst	*rright;
	int		fd[2];
	int		end;
}	t_args;

// parser.c
int			is_symbole(char c);
t_slst		*parser(char *prompt);
// vars.c
char		*vars(const char *name, char *data);
// vars_list.c
t_vlink		*vlst_new(t_var content);
void		vlst_add_front(t_vlink **lst, t_var var);
// string_list.c
t_slink		*slst_new(char *str);
void		slst_add_front(t_slst *lst, char *str, int type, int level);
void		slst_add_back(t_slst *lst, char *str, int type, int level);
void		handle_buffer(t_buff *buffer, char *res);
void		handle_double_quote(char *prompt,
				int *index, t_buff *buffer, char *res);
void		handle_simple_quote(char *prompt,
				int *index, t_buff *buffer, char *res);
void		handle_var(char *prompt, int *index, t_buff *buffer, char *res);

void		connect_signals(void);
void		declare_variable(char *declaration);
//builtins
int			builtins(t_slst *args);
void		ft_cd(t_slst *argv);
void		ft_echo(t_slst *args);
void		ft_pwd(t_slst *argv);
void		ft_unset(t_slst *argv);
void		ft_export(t_slst *args);
void		ft_env(t_slst *args);
t_slink		*slst_new(char *str);
void		parse_error(char a, char b);
int			execute(t_slst *args);
t_args		slst_to_tab(t_slst *args);
int			filename_injection(t_args *args, int read_fd);
int			fd_injection(char *filename, int fd);
int			fd_fd_injection(int dst, int src);

#endif