/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:20:54 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/21 19:20:55 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H

# define FT_SSL_H
# include "libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

extern char		*g_optarg;
extern int		g_optind;

typedef struct	s_func_lst
{
	char				*content;
	int					n;
	struct s_func_lst	*next;
}				t_func_lst;

void			ft_sha256(int argc, char **argv);
void			ft_md5(int argc, char **argv);
void			ft_listpush(t_func_lst **lst, t_func_lst *new_lst);
void			free_lst(t_func_lst *lst);
void			ft_listadd(t_func_lst **alst, t_func_lst *new_lst);
t_func_lst		*ft_listnew(int n, char	*content);
int				ft_getopt(int argc, char *const argv[], const char *optstr);
typedef void	(*t_func)(int, char **);
void			ft_add_mem(uint8_t **msg, int old_n, uint8_t *buff, int n);

#endif
