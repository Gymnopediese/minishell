/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:47:02 by bphilago          #+#    #+#             */
/*   Updated: 2023/03/30 15:37:43 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	ft_lstrm_first(t_list **lst, void *data)
{
	t_list	*last_lst;
	t_list	*current_lst;

	current_lst = *lst;
	last_lst = 0;
	while (current_lst)
	{
		if (current_lst->data == data)
		{
			if (last_lst)
				last_lst->next = current_lst->next;
			else
				*lst = current_lst->next;
			free(current_lst);
			return ;
		}
		last_lst = current_lst;
		current_lst = current_lst->next;
	}
	printf("\033[1;31m");
	printf("Warning, pointer not in list\n");
}

static void	ft_free_all(t_list **obj_lst, int exit_value)
{
	t_list	*temp;

	while (obj_lst && *obj_lst)
	{
		free((*obj_lst)->data);
		temp = (*obj_lst)->next;
		free(*obj_lst);
		*obj_lst = temp;
	}
	free(obj_lst);
	exit(exit_value);
}

static void	ft_malloc_ptr(t_list **malloc_lst, void **ptr,
		size_t size)
{
	t_list	*new_data;

	*ptr = malloc(size);
	if (!*ptr)
		finish("Error : can't allocate memory\n");
	new_data = ft_lstnew(*ptr);
	if (!new_data)
	{
		free(*ptr);
		finish("Error : can't allocate memory\n");
	}
	ft_lstadd_front(malloc_lst, new_data);
}

void	ft_mf(int op, void **ptr, size_t size)
{
	static t_list	**malloc_lst;

	if (!malloc_lst && op == MALLOC)
	{
		malloc_lst = malloc(sizeof(*malloc_lst));
		*malloc_lst = 0;
	}
	if (op == MALLOC && ptr != 0)
		ft_malloc_ptr(malloc_lst, ptr, size);
	if (op == FREE)
	{	
		ft_lstrm_first(malloc_lst, *ptr);
		free(*ptr);
		*ptr = 0;
	}
	if (op == FREE_ALL)
		ft_free_all(malloc_lst, size);
}
