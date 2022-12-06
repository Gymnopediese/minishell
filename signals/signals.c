/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:02:23 by bphilago          #+#    #+#             */
/*   Updated: 2022/12/06 14:28:07 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	void_signal(int sig)
{
	(void) sig;
}

void	new_line_signal(int sig)
{
	(void) sig;
	//tcsetattr(0);
}

void	connect_signals(void)
{
	signal(SIGINT, new_line_signal);
	signal(SIGQUIT, void_signal);
}
