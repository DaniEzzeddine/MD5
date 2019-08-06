/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:45:13 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/24 22:15:16 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"

extern bool g_quiet;
extern bool g_reverse;

void		sha256_check_for_q_r(char ch)
{
	if (ch == 'q')
		g_quiet = true;
	else if (ch == 'r')
		g_reverse = true;
	if (g_quiet)
		g_reverse = false;
}

void		ft_sha256_loop(int *i, uint32_t *parts, uint32_t *chunks)
{
	uint32_t			s1;
	uint32_t			s0;
	uint32_t			ch;
	uint32_t			maj;

	s1 = (ROTRIGHT(parts[4], 6)) ^
		(ROTRIGHT(parts[4], 11)) ^ (ROTRIGHT(parts[4], 25));
	ch = (parts[4] & parts[5]) ^ ((~(parts[4])) & parts[6]);
	parts[8] = parts[7] + s1 + ch + g_shak[(*i)] + chunks[(*i)];
	s0 = (ROTRIGHT(parts[0], 2)) ^
		(ROTRIGHT(parts[0], 13)) ^ (ROTRIGHT(parts[0], 22));
	maj = (parts[0] & parts[1]) ^ (parts[0] & parts[2]) ^ (parts[1] & parts[2]);
	parts[9] = s0 + maj;
}

void		ft_initparts(t_words *buffer, uint32_t *parts)
{
	parts[0] = buffer->h0;
	parts[1] = buffer->h1;
	parts[2] = buffer->h2;
	parts[3] = buffer->h3;
	parts[4] = buffer->h4;
	parts[5] = buffer->h5;
	parts[6] = buffer->h6;
	parts[7] = buffer->h7;
	parts[8] = 0;
	parts[9] = 0;
	return ;
}

void		check_fd(char *file, int fd)
{
	if (fd == -1)
		ft_printf("%s: Is a directory\n", file);
	exit(0);
}

void		ft_usage(void)
{
	ft_printf("usage: ./ft_ssl md5 [-pqrtx] [-s string] [files ...]\n");
	exit(0);
}
