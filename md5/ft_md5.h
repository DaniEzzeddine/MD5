/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:25:07 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/21 19:25:08 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H

# define FT_MD5_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include "../ft_ssl.h"
# define INIT_A 0x67452301
# define INIT_B 0xefcdab89
# define INIT_C 0x98badcfe
# define INIT_D 0x10325476
# define LEFTROTATE(x, c) ((x << c) | (x >> (32 - c)))

typedef struct			s_words
{
	uint32_t			word_a;
	uint32_t			word_b;
	uint32_t			word_c;
	uint32_t			word_d;
}						t_words;

typedef struct			s_md5flag
{
	bool				in;
	bool				quiet;
	bool				reverse;
	bool				string;
	bool				file;
}						t_md5flag;

typedef struct			s_md5
{
	char				*file;
	uint8_t				*msg;
	int					size;
	int					input_size;
	t_md5flag			flags;

}						t_md5;

extern int				g_s[64];
extern int				g_k[64];

uint32_t				funf(t_words *buffer);
uint32_t				fung(t_words *buffer);
uint32_t				funh(t_words *buffer);
uint32_t				funi(t_words *buffer);

void					ft_usage(void);
void					ft_md5print_output(uint32_t *parts, t_md5 *main);
void					check_for_q_r(char ch);
void					main_algo(t_md5 *msg);
uint8_t					*append_padding_bits_and_length(t_md5 *main_data);
void					main_loop(t_words *buffer, uint32_t *chunks);
void					ft_inithelper(uint32_t *parts,
						t_words *main, bool flag);
uint32_t				*break_the_msg_in_16(t_md5 *main);
void					md5_init_buffer(t_words	*buffer);
#endif
