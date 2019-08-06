/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:45:13 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/21 19:45:14 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

extern bool g_quiet;
extern bool g_reverse;

void		check_for_q_r(char ch)
{
	if (ch == 'q')
		g_quiet = true;
	else if (ch == 'r')
		g_reverse = true;
	if (g_quiet)
		g_reverse = false;
}

void		ft_usage(void)
{
	ft_printf("%s\n", "usage: ./ft_ssl md5 [-pqrtx] [-s string] [files ...]");
}
