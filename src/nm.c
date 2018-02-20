/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:26:53 by ariard            #+#    #+#             */
/*   Updated: 2018/02/20 15:35:48 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_cliopts		g_nm_opts[] =
{
	{'n', NULL, NM_NOPT, 0, NULL, 0},
	{'r', NULL, NM_ROPT, 0, NULL, 0},
	{'p', NULL, NM_POPT, 0, NULL, 0},
	{'g', NULL, NM_GOPT, 0, NULL, 0},
	{'a', NULL, NM_AOPT, 0, NULL, 0},
	{'o', NULL, NM_OOPT, 0, NULL, 0},
	{'u', NULL, NM_MUOPT, 0, NULL, 0},
	{'U', NULL, NM_UOPT, 0, NULL, 0},
	{'j', NULL, NM_JOPT, 0, NULL, 0},
	{'A', NULL, NM_MAOPT, 0, NULL, 0},
};

static void		data_init(t_data *data)
{
	data->flag = 0;
	data->av_data = NULL;
	data->lstsym = NULL;
	data->filename = NULL;
	data->filesize = 0;
	data->origin = NULL;
	data->cpu = 16777223;
	data->bits = 0;
	data->bin = 1;
	hashtab_init(&data->tabsections, 100, &ft_hash_string);
}

static int		get_filesize(char *name, struct stat *buf, int *fd)
{
	if ((*fd = open(name, O_RDONLY)) < 0)
		ft_dprintf(2, "nm : No such file %s\n", name);
	return (fstat(*fd, buf));
}

static void		launch_parser(char *ptr, t_data *data, size_t filesize)
{
	data->filesize = filesize;
	data->origin = ptr;
	parse_archi(ptr, data);
}

static void		check_arg(int i, int argc, char **argv)
{
	if (i == argc)
	{
		if (argc > 1)
		{
			ft_dprintf(2, "nm : option isn't recognized");
			exit(0);
		}
		argv[i] = "a.out";
	}
}

int				main(int argc, char **argv)
{
	t_data		data;
	int			i;
	int			fd;
	char		*ptr;
	struct stat buf;

	data_init(&data);
	cliopts_get(argv, g_nm_opts, &data);
	i = (data.av_data) ? data.av_data - argv : argc;
	check_arg(i, argc, argv);
	while (argv[i] && i <= argc)
	{
		data.filename = argv[i++];
		if (get_filesize(data.filename, &buf, &fd) < 0)
			continue;
		if (MMAP(ptr, buf.st_size, fd) == MAP_FAILED)
			continue;
		if ((argc - (data.av_data - argv) > 1) && ft_strncmp(ptr, ARMAG, SARMAG))
			ft_printf("\n%s:\n", data.filename);
		launch_parser(ptr, &data, buf.st_size);
		if (munmap(ptr, buf.st_size) < 0)
			continue;
		close(fd);
	}
	return (0);
}
