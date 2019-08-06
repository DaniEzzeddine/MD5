/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 20:18:39 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/24 22:25:23 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		init_funcs(t_func *funcs)
{
	funcs[1] = &ft_md5;
	funcs[3] = &ft_sha256;
}

static t_func	get_func(int c)
{
	static t_func	*funcs;

	if (!funcs)
	{
		funcs = ft_memalloc(sizeof(*funcs) * 6);
		if (funcs)
			init_funcs(funcs);
	}
	return (funcs[c]);
}

t_func_lst		*make_lst(void)
{
	t_func_lst		*head;
	t_func_lst		*temp;

	head = ft_listnew(1, "md5");
	temp = ft_listnew(2, "sha224");
	ft_listpush(&head, temp);
	temp = ft_listnew(3, "sha256");
	ft_listpush(&head, temp);
	temp = ft_listnew(4, "base64");
	ft_listpush(&head, temp);
	temp = ft_listnew(5, "des");
	ft_listpush(&head, temp);
	return (head);
}

bool			check_argc(int argc)
{
	if (argc == 1)
		return (false);
	return (true);
}

int				main(int argc, char **argv)
{
	t_func_lst			*lst;
	t_func_lst			*temp;
	t_func				f;

	lst = make_lst();
	temp = lst;
	if (!check_argc(argc))
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	else if (lst)
	{
		while (ft_strcmp(argv[1], temp->content) && temp->next)
			temp = temp->next;
		f = get_func(temp->n);
		if (f)
			f(argc - 1, argv + 1);
		else
			ft_printf("usage: ft_ssl command [command opts] [command args]\n");
		free_lst(lst);
	}
	return (0);
}
