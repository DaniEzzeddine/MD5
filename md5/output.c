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

#include "ft_md5.h"

extern bool g_reverse;
extern bool g_quiet;

void			ft_md5print_hash(uint32_t *parts)
{
	uint8_t		*ptr;

	ptr = (uint8_t *)&parts[0];
	ft_printf("%02x%02x%02x%02x", ptr[0], ptr[1], ptr[2], ptr[3]);
	ptr = (uint8_t *)&parts[1];
	ft_printf("%02x%02x%02x%02x", ptr[0], ptr[1], ptr[2], ptr[3]);
	ptr = (uint8_t *)&parts[2];
	ft_printf("%02x%02x%02x%02x", ptr[0], ptr[1], ptr[2], ptr[3]);
	ptr = (uint8_t *)&parts[3];
	ft_printf("%02x%02x%02x%02x", ptr[0], ptr[1], ptr[2], ptr[3]);
}

static void		ft_md5print_string(uint32_t *parts, t_md5 *main)
{
	if (g_reverse)
	{
		ft_md5print_hash(parts);
		ft_printf(" \"%s\"\n", main->msg);
	}
	else
	{
		ft_printf("MD5 (\"%s\") = ", main->msg);
		ft_md5print_hash(parts);
		ft_putchar('\n');
	}
}

static void		ft_md5print_file(uint32_t *parts, t_md5 *main)
{
	if (g_reverse)
	{
		ft_md5print_hash(parts);
		ft_printf(" %s\n", main->file);
	}
	else
	{
		ft_printf("MD5 (%s) = ", main->file);
		ft_md5print_hash(parts);
		ft_putchar('\n');
	}
}

void			ft_md5print_output(uint32_t *parts, t_md5 *main)
{
	if (g_quiet && !main->flags.in)
	{
		ft_md5print_hash(parts);
		ft_putchar('\n');
		return ;
	}
	if (main->flags.file)
	{
		ft_md5print_file(parts, main);
	}
	else if (main->flags.string)
		ft_md5print_string(parts, main);
	else if (main->flags.in)
	{
		write(1, main->msg, main->input_size);
		ft_md5print_hash(parts);
		ft_printf("\n");
	}
	else
	{
		ft_md5print_hash(parts);
		ft_printf("\n");
	}
}
