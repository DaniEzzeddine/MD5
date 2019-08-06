/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:46:08 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/21 19:46:09 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

uint32_t		funf(t_words *buffer)
{
	return ((buffer->word_b & buffer->word_c) |
			((~buffer->word_b) & buffer->word_d));
}

uint32_t		fung(t_words *buffer)
{
	return ((buffer->word_b & buffer->word_d) |
			((~buffer->word_d) & buffer->word_c));
}

uint32_t		funh(t_words *buffer)
{
	return (buffer->word_b ^ buffer->word_c ^ buffer->word_d);
}

uint32_t		funi(t_words *buffer)
{
	return (buffer->word_c ^ (((~buffer->word_d) |
			buffer->word_b)));
}
