/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:43:26 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/23 13:24:28 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

void				md5_init_buffer(t_words *buffer)
{
	buffer->word_a = INIT_A;
	buffer->word_b = INIT_B;
	buffer->word_c = INIT_C;
	buffer->word_d = INIT_D;
}

uint8_t				*append_padding_bits_and_length(t_md5 *main_data)
{
	int			new_size;
	uint64_t	bits_len;
	uint8_t		*msg;

	new_size = main_data->size * 8 + 1;
	while (new_size % 512 != 448)
		new_size++;
	new_size /= 8;
	msg = ft_memalloc(new_size + 64);
	ft_memcpy(msg, main_data->msg, main_data->size);
	msg[main_data->size] = 0x80;
	bits_len = 8 * main_data->size;
	ft_memcpy(msg + new_size, &bits_len, 8);
	main_data->size = new_size;
	return (msg);
}

void				ft_inithelper(uint32_t *parts, t_words *main, bool flag)
{
	if (flag == true)
	{
		parts[0] = INIT_A;
		parts[1] = INIT_B;
		parts[2] = INIT_C;
		parts[3] = INIT_D;
		return ;
	}
	main->word_a = parts[0];
	main->word_b = parts[1];
	main->word_c = parts[2];
	main->word_d = parts[3];
}
