/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:26:53 by ariard            #+#    #+#             */
/*   Updated: 2018/02/09 19:04:49 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_cliopts		g_nm_opts[]=
{
	{'n', NULL, NM_NOPT, 0, NULL, 0},
	{'r', NULL, NM_ROPT, 0, NULL, 0},
	{'p', NULL, NM_POPT, 0, NULL, 0},
	{'g', NULL, NM_GOPT, 0, NULL, 0},
	{'a', NULL, NM_AOPT, 0, NULL, 0},
	{'o', NULL, NM_OOPT, 0, NULL, 0},
	{'u', NULL, NM_uOPT, 0, NULL, 0},
	{'U', NULL, NM_UOPT, 0, NULL, 0},
	{'j', NULL, NM_JOPT, 0, NULL, 0},
};

static void		data_init(t_data *data)
{
	data->flag = 0;
	data->av_data = NULL;
	data->lstsym = NULL;
	data->filetype = 0;
	data->filename = NULL;
	hashtab_init(&data->tabsections, 100, &ft_hash_string);
}

int				main(int argc, char **argv)
{
	int			fd;
	t_data		data;
	int			i;
	char		*ptr;
	struct stat buf;

	DG("nm start");
	data_init(&data);
	cliopts_get(argv, g_nm_opts, &data);
	i = data.av_data - argv;
	argv[i] = (argv[i]) ? argv[i] : "a.out";
	while (argv[i] && i <= argc)
	{
		data.filename = argv[i++];
		if (argc - (data.av_data - argv) > 1)
			ft_printf("\n%s:\n", data.filename);
		if ((fd = open(data.filename, O_RDONLY)) < 0)
			ft_dprintf(2, "nm : No such file %s\n", data.filename);
		if (fstat(fd, &buf) < 0)
			continue;
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			continue;
		parse_archi(ptr, &data);
		if (munmap(ptr, buf.st_size) < 0)
			continue;
	}
	return (0);
}
