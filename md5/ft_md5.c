/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dezzeddi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 19:43:14 by dezzeddi          #+#    #+#             */
/*   Updated: 2018/06/21 19:43:15 by dezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

bool		g_quiet;
bool		g_reverse;
extern char	*g_optarg;
extern int	g_optind;

static int					ft_isfile(const char *name)
{
	DIR *directory;

	directory = opendir(name);
	if (directory != NULL)
	{
		closedir(directory);
		return (0);
	}
	if (errno == ENOTDIR)
		return (1);
	return (-1);
}

static int					ft_handle_string(char *msg)
{
	t_md5		*main_data;
	int			size;

	if (!msg)
		return (0);
	size = ft_strlen(msg);
	main_data = ft_memalloc(sizeof(t_md5));
	main_data->input_size = size;
	main_data->size = size;
	main_data->msg = (uint8_t*)msg;
	main_data->flags.string = true;
	main_algo(main_data);
	return (1);
}

static int					process_msg(int fd, t_md5 *data, bool p_or_f)
{
	int			n;
	uint8_t		buff[1024];
	uint8_t		*res;
	int			res_size;

	n = 1;
	res_size = 0;
	while (n)
	{
		n = read(fd, buff, 1024);
		if (n < 0)
			return (-1);
		ft_add_mem((&res), res_size, buff, n);
		res_size += n;
	}
	data->msg = res;
	data->input_size = res_size;
	data->size = res_size;
	if (!p_or_f)
		data->flags.in = true;
	else
		data->flags.file = true;
	return (1);
}

static int					ft_handle_file(char *file, bool p_or_f)
{
	int		fd;
	t_md5	*data;

	if (!p_or_f)
		fd = 0;
	else
	{
		if (!ft_isfile(file))
		{
			ft_printf("%s: Is a directory\n", file);
			return (0);
		}
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("%s: no such file or directory\n", file);
			return (0);
		}
	}
	data = ft_memalloc(sizeof(t_md5));
	data->file = file;
	process_msg(fd, data, p_or_f);
	close(fd);
	main_algo(data);
	return (1);
}

void						ft_md5(int argc, char **argv)
{
	char	ch;

	while ((ch = ft_getopt(argc, argv, ":prqs:")) != -1)
	{
		check_for_q_r(ch);
		if (ch == 's')
			ft_handle_string(g_optarg);
		else if (ch == 'p')
			ft_handle_file(g_optarg, false);
		else if (ch == ':')
		{
			g_optind--;
			while (g_optind < argc)
				ft_handle_file(argv[g_optind++], true);
		}
		else if (ch == '?')
		{
			ft_usage();
			return ;
		}
	}
}
