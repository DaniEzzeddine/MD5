/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 20:17:54 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/21 20:17:55 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

static void	clear_the_mem(t_md5 *data, t_words *buffer, uint8_t *buff)
{
	if (!data->flags.string)
		free(data->msg);
	free(data);
	free(buff);
	free(buffer);
}

void		main_loop(t_words *buffer, uint32_t *chunks)
{
	uint32_t			i;
	uint32_t			f;
	uint32_t			g;
	uint32_t			temp;

	i = 0;
	while (i < 64)
	{
		if (i <= 15 && (f = funf(buffer)))
			g = i;
		else if (i <= 31 && (f = fung(buffer)))
			g = (5 * i + 1) % 16;
		else if (i <= 47 && (f = funh(buffer)))
			g = (3 * i + 5) % 16;
		else if (i <= 63 && (f = funi(buffer)))
			g = (7 * i) % 16;
		temp = buffer->word_d;
		buffer->word_d = buffer->word_c;
		buffer->word_c = buffer->word_b;
		buffer->word_b += LEFTROTATE(((buffer->word_a) +
							f + g_k[i] + chunks[g]), g_s[i]);
		buffer->word_a = temp;
		i++;
	}
}

void		reload_buffer(t_words *buffer, uint32_t *parts)
{
	parts[0] = (parts[0] + buffer->word_a);
	parts[1] = (parts[1] + buffer->word_b);
	parts[2] = (parts[2] + buffer->word_c);
	parts[3] = (parts[3] + buffer->word_d);
}

void		main_algo(t_md5 *data)
{
	t_words		*buffer;
	uint32_t	*temp;
	uint8_t		*buff;
	uint32_t	parts[4];
	int			offset;

	offset = 0;
	buffer = ft_memalloc(sizeof(t_words));
	md5_init_buffer(buffer);
	ft_bzero(parts, sizeof(uint32_t) * 4);
	ft_inithelper(parts, buffer, true);
	buff = append_padding_bits_and_length(data);
	while (offset < data->size)
	{
		temp = (uint32_t *)(buff + offset);
		ft_inithelper(parts, buffer, false);
		main_loop(buffer, temp);
		reload_buffer(buffer, parts);
		offset += 64;
	}
	ft_md5print_output(parts, data);
	clear_the_mem(data, buffer, buff);
	return ;
}
