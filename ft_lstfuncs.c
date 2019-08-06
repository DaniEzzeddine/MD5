/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <dezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 21:09:28 by dezzeddi          #+#    #+#             */
/*   Updated: 2017/06/12 01:36:18 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			ft_listadd(t_func_lst **alst, t_func_lst *new_lst)
{
	t_func_lst *temp;

	if (!alst)
		return ;
	temp = *alst;
	*alst = new_lst;
	(*alst)->next = temp;
}

t_func_lst		*ft_listnew(int n, char *content)
{
	t_func_lst	*new;

	new = (t_func_lst *)malloc(sizeof(t_func_lst));
	if (!new)
		return (NULL);
	new->next = NULL;
	if (!content)
		return (NULL);
	new->content = malloc(ft_strlen(content));
	ft_strcpy(new->content, content);
	new->n = n;
	return (new);
}

void			ft_listpush(t_func_lst **lst, t_func_lst *new_lst)
{
	t_func_lst	*current;

	if (!lst)
		return ;
	current = *lst;
	if (!current)
	{
		*lst = new_lst;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new_lst;
}
