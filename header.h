/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:02:45 by albaud            #+#    #+#             */
/*   Updated: 2022/12/08 13:38:55 by albaud           ###   ########.fr       */
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
	int			export;
}	t_var;

typedef struct s_pipe
{
	int	fd[2];
	int	to_pipe;
}	t_pipe;

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
	int		end;
}	t_args;

# include "builtins/builtins.h"

// parser.c
int			is_symbole(char c);
t_slst		*parser(char *prompt);
// vars.c
char		*vars(const char *name, char *data);
// vars_list.c
t_vlink		*vlst_new(t_var content);
void		vlst_add_front(t_vlink **lst, t_var var);
// string_list.c
void		slst_add_front(t_slst *lst, char *str, int type, int level);
void		slst_add_back(t_slst *lst, char *str, int type, int level);
void		handle_buffer(t_buff *buffer, char *res);
void		handle_double_quote(char *prompt,
				int *index, t_buff *buffer, char *res);
void		handle_simple_quote(char *prompt,
				int *index, t_buff *buffer, char *res);
void		handle_var(char *prompt, int *index, t_buff *buffer, char *res);
void		put_slst(t_slst *lst);
t_args		*slst_to_tab(t_slst *args);
void		connect_signals(void);
void		declare_variable(char *declaration);
//builtins
void		parse_error(char a, char b);
int			execute(t_args *args);
int			filename_injection(t_args *args, int read_fd);
int			fd_injection(char *filename, int fd);
int			fd_fd_injection(int dst, int src);
int			wildcards(char *arg, t_slst *res);
int			mode(int m);
int			level(int m);
t_pipe		*pipi(void);
int			is_the_end(t_slink *link);
void		put_pipi(void);
int			is_redirection(t_slink *link);

#endif