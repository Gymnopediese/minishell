/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:25:00 by albaud            #+#    #+#             */
/*   Updated: 2023/05/04 13:02:01 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../header.h"

int			builtins(t_args *args);
void		ft_cd(char **args, int argc, int fd);
void		ft_echo(char **args, int argc, int fd);
void		ft_pwd(char **args, int fd);
void		ft_unset(char **args, int argc, int fd);
void		ft_export(char **args, int argc, int fd);
void		ft_env(char **args, int argc, int fd);
void		ft_exit(char **args, int argc, int fd);

#endif