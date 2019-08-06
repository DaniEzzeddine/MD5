/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:39:25 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/21 19:39:27 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"

extern bool g_reverse;
extern bool g_quiet;

void			ft_sha256print_hash(uint8_t *hash)
{
	int i;

	i = 0;
	while (i < 32)
	{
		ft_printf("%02x", hash[i]);
		i++;
	}
}

static void		ft_sha256print_string(uint8_t *hash, t_sha256 *main)
{
	if (g_reverse)
	{
		ft_sha256print_hash(hash);
		ft_printf(" \"%s\"\n", main->msg);
	}
	else
	{
		ft_printf("SHA256 (\"%s\") = ", main->msg);
		ft_sha256print_hash(hash);
		ft_putchar('\n');
	}
}

static void		ft_sha256print_file(uint8_t *hash, t_sha256 *main)
{
	if (g_reverse)
	{
		ft_sha256print_hash(hash);
		ft_printf(" %s\n", main->file);
	}
	else
	{
		ft_printf("SHA256 (%s) = ", main->file);
		ft_sha256print_hash(hash);
		ft_putchar('\n');
	}
}

void			ft_sha256print_output(t_sha256 *main, uint8_t *parts)
{
	if (g_quiet && !main->flags.in)
	{
		ft_sha256print_hash(parts);
		ft_putchar('\n');
		return ;
	}
	if (main->flags.file)
		ft_sha256print_file(parts, main);
	else if (main->flags.string)
		ft_sha256print_string(parts, main);
	else if (main->flags.in)
	{
		ft_printf("%s", main->msg);
		ft_sha256print_hash(parts);
		ft_printf("\n");
	}
	else
	{
		ft_sha256print_hash(parts);
		ft_printf("\n");
	}
}
