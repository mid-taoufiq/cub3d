/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:20:33 by tibarike          #+#    #+#             */
/*   Updated: 2025/11/15 12:20:42 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_lstclear(t_garbage **lst)
{
	t_garbage	*crnt;
	t_garbage	*tmp;

	if (!lst)
		return ;
	crnt = *lst;
	while (crnt != NULL)
	{
		tmp = crnt;
		crnt = crnt->next;
		free(tmp->address);
		free(tmp);
	}
	*lst = NULL;
}

t_garbage	*ft_lstlast(t_garbage *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_garbage **lst, t_garbage *new)
{
	t_garbage	*last_n;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_n = ft_lstlast(*lst);
	last_n->next = new;
}

t_garbage	*ft_new_gb(void *ptr)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	new->address = ptr;
	new->next = NULL;
	return (new);
}

void	*ft_malloc(int size, t_garbage **garbage)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (perror("malloc"), NULL);
	ft_lstadd_back(garbage, ft_new_gb(ptr));
	return (ptr);
}
