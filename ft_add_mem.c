/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:13:08 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/21 19:13:32 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		ft_add_mem(uint8_t **msg, int old_n, uint8_t *buff, int n)
{
	uint8_t	*res;

	if (!(*msg))
		(*msg) = ft_memalloc(n);
	res = ft_memalloc(n + old_n + 1);
	ft_memcpy(res, *msg, old_n);
	ft_memcpy((res + old_n), buff, n);
	free(*msg);
	*msg = res;
}

void		free_lst(t_func_lst *lst)
{
	while (lst)
	{
		free(lst->content);
		free(lst);
		lst = lst->next;
	}
}
