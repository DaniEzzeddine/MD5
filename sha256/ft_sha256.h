/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:25:07 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/24 22:18:44 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H

# define FT_SHA256_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include "../ft_ssl.h"
# define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))
# define INIT_H0  0x6A09E667
# define INIT_H1  0xBB67AE85
# define INIT_H2  0x3C6EF372
# define INIT_H3  0xA54FF53A
# define INIT_H4  0x510E527F
# define INIT_H5  0x9B05688C
# define INIT_H6  0x1F83D9AB
# define INIT_H7  0x5BE0CD19
# define LEFTROTATE(x, c) ((x << c) | (x >> (32 - c)))

typedef struct			s_words
{
	uint32_t			h0;
	uint32_t			h1;
	uint32_t			h2;
	uint32_t			h3;
	uint32_t			h4;
	uint32_t			h5;
	uint32_t			h6;
	uint32_t			h7;

}						t_words;

typedef struct			s_256flag
{
	bool				in;
	bool				quiet;
	bool				reverse;
	bool				string;
	bool				file;
}						t_256flag;

typedef struct			s_sha256
{
	char				*file;
	uint8_t				*msg;
	unsigned long long	size;
	int					input_size;
	t_256flag			flags;

}						t_sha256;

extern int				g_shak[64];

void					ft_sha256_usage(void);
void					ft_sha256_loop(int *i, uint32_t *parts,
						uint32_t *chunks);
void					ft_sha256print_output(t_sha256 *main, uint8_t *hash);
void					sha256_check_for_q_r(char ch);
void					sha256_main_algo(t_sha256 *msg, uint8_t *hash);
uint8_t					*sha256_append_bits(t_sha256 *main_data);
void					main_loop(t_words *buffer, uint32_t *chunks);
void					ft_initparts(t_words *buffer, uint32_t *parts);
uint32_t				*break_the_msg_in_16(uint8_t *buff);
void					init_buffer(t_words	*buffer);
void					check_fd(char *file, int fd);
#endif
