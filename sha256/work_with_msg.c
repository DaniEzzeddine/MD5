/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:43:26 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/24 21:51:16 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"

void					init_buffer(t_words *buffer)
{
	buffer->h0 = INIT_H0;
	buffer->h1 = INIT_H1;
	buffer->h2 = INIT_H2;
	buffer->h3 = INIT_H3;
	buffer->h4 = INIT_H4;
	buffer->h5 = INIT_H5;
	buffer->h6 = INIT_H6;
	buffer->h7 = INIT_H7;
}

static void				add_len(uint8_t *msg, t_sha256 *main)
{
	main->size = main->input_size * 8;
	msg[63] = main->size;
	msg[62] = main->size >> 8;
	msg[61] = main->size >> 16;
	msg[60] = main->size >> 24;
	msg[59] = main->size >> 32;
	msg[58] = main->size >> 40;
	msg[57] = main->size >> 48;
	msg[56] = main->size >> 56;
}

uint8_t					*sha256_append_bits(t_sha256 *main_data)
{
	int			new_size;
	uint8_t		*msg;

	new_size = main_data->input_size * 8 + 1;
	while (new_size % 512 != 448)
		new_size++;
	new_size /= 8;
	msg = ft_memalloc(new_size + 8);
	ft_memcpy(msg, main_data->msg, main_data->input_size);
	msg[main_data->input_size] = 0x80;
	add_len(msg + new_size + 8 - 64, main_data);
	main_data->size = new_size + 8;
	return (msg);
}

static void				extend_msg_in_48_words(uint32_t *w, int *i)
{
	uint32_t			s1;
	uint32_t			s2;

	s2 = 0;
	s1 = 0;
	while ((*i) < 64)
	{
		s1 = (ROTRIGHT(w[(*i) - 15], 7) ^
				(ROTRIGHT(w[(*i) - 15], 18) ^ (w[(*i) - 15] >> 3)));
		s2 = (ROTRIGHT(w[(*i) - 2], 17) ^
				ROTRIGHT(w[(*i) - 2], 19) ^ (w[(*i) - 2] >> 10));
		w[(*i)] = w[(*i) - 16] + s1 + w[(*i) - 7] + s2;
		(*i)++;
	}
}

uint32_t				*break_the_msg_in_16(uint8_t *buff)
{
	uint32_t		*w;
	int				i;
	int				j;

	w = ft_memalloc(sizeof(uint32_t) * 64);
	i = 0;
	j = 0;
	while (i < 16)
	{
		w[i] = (buff[j] << 24) | (buff[j + 1] << 16) |
			(buff[j + 2] << 8) | (buff[j + 3]);
		j += 4;
		i++;
	}
	extend_msg_in_48_words(w, &i);
	return (w);
}
