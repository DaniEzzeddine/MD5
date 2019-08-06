/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 20:17:54 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/24 21:35:35 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_sha256.h"

static void			make_hash(t_words *buffer, uint8_t *hash)
{
	int i;

	i = 0;
	while (i < 4)
	{
		hash[i] = (buffer->h0 >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4] = (buffer->h1 >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8] = (buffer->h2 >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (buffer->h3 >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (buffer->h4 >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (buffer->h5 >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (buffer->h6 >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (buffer->h7 >> (24 - i * 8)) & 0x000000ff;
		i++;
	}
}

static void			clear_the_mem(t_sha256 *data, t_words *buffer,
					uint8_t *buff)
{
	if (!data->flags.string)
		free(data->msg);
	free(data);
	free(buff);
	free(buffer);
}

static void			sha256_main_loop(t_words *buffer, uint32_t *parts,
					uint32_t *chunks)
{
	int					i;

	i = 0;
	ft_initparts(buffer, parts);
	while (i < 64)
	{
		ft_sha256_loop((&i), parts, chunks);
		parts[7] = parts[6];
		parts[6] = parts[5];
		parts[5] = parts[4];
		parts[4] = parts[3] + parts[8];
		parts[3] = parts[2];
		parts[2] = parts[1];
		parts[1] = parts[0];
		parts[0] = parts[8] + parts[9];
		i++;
	}
}

static void			sha256_reload_buffer(t_words *buffer, uint32_t *parts)
{
	buffer->h0 += parts[0];
	buffer->h1 += parts[1];
	buffer->h2 += parts[2];
	buffer->h3 += parts[3];
	buffer->h4 += parts[4];
	buffer->h5 += parts[5];
	buffer->h6 += parts[6];
	buffer->h7 += parts[7];
}

void				sha256_main_algo(t_sha256 *data, uint8_t *hash)
{
	t_words		*buffer;
	uint32_t	*temp;
	uint8_t		*buff;
	uint32_t	parts[9];
	size_t		offset;

	offset = 0;
	buffer = ft_memalloc(sizeof(t_words));
	init_buffer(buffer);
	ft_bzero(parts, sizeof(uint32_t) * 10);
	buff = sha256_append_bits(data);
	while (offset < data->size)
	{
		temp = break_the_msg_in_16(buff + offset);
		sha256_main_loop(buffer, parts, temp);
		sha256_reload_buffer(buffer, parts);
		offset += 64;
		free(temp);
	}
	make_hash(buffer, hash);
	ft_sha256print_output(data, hash);
	clear_the_mem(data, buffer, buff);
	return ;
}
