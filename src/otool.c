/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 21:59:11 by ariard            #+#    #+#             */
/*   Updated: 2018/02/12 20:45:22 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_cliopts		g_ot_opts[] =
{
	{'d', NULL, OT_DOPT, 0, NULL, 0},
	{'h', NULL, OT_HOPT, 0, NULL, 0},
	{'f', NULL, OT_FOPT, 0, NULL, 0},
};

static void		data_init(t_data *data)
{
	data->flag = 0;
	data->av_data = NULL;
	data->lstsym = NULL;
	data->filename = NULL;
	data->cpu = 16777223;
	data->bits = 0;
	data->bin = 0;
	hashtab_init(&data->tabsections, 100, &ft_hash_string);
}

static int		get_filesize(char *name, struct stat *buf, int *fd)
{
	if ((*fd = open(name, O_RDONLY)) < 0)
		ft_dprintf(2, "otool : No such file %s\n", name);
	return (fstat(*fd, buf));
}

int				main(int argc, char **argv)
{
	t_data		data;
	int			i;
	int			fd;
	char		*ptr;
	struct stat buf;

	data_init(&data);
	cliopts_get(argv, g_ot_opts, &data);
	i = data.av_data - argv;
	while (argv[i] && i <= argc)
	{
		data.filename = argv[i++];
		if (get_filesize(data.filename, &buf, &fd) < 0)
			continue;
		if (MMAP(ptr, buf.st_size, fd) == MAP_FAILED)
			continue;
		parse_archi(ptr, &data);
		if (munmap(ptr, buf.st_size) < 0)
			continue;
		close(fd);
	}
	return (0);
}
