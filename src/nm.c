/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:26:53 by ariard            #+#    #+#             */
/*   Updated: 2018/01/03 16:56:48 by ariard           ###   ########.fr       */
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

static void		parse_archi(char *ptr, t_data *data)
{
	unsigned int		magic_number;

	magic_number = *(unsigned int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr, data);
	else if (magic_number == FAT_CIGAM) 	
		handle_fat(ptr);
	else if (magic_number &  EH_MAGIC_64)
		handle_64_elf(ptr, data);
}

int				main(int argc, char **argv)
{
	int			fd;
	t_data		data;
	int			i;
	char		*ptr;
	struct stat buf;

	DG("nm start");
	if (argc < 2)
	{
		ft_dprintf(2, "Argumnent needed");
		return (1);
	}
	data_init(&data);
	cliopts_get(argv, g_nm_opts, &data);
	i = data.av_data - argv;
	while (i < argc && argv[i])
	{
		data.filename = argv[i];
		if ((fd = open(argv[i], O_RDONLY)) < 0)
			return (1);
		if (fstat(fd, &buf) < 0)
			return (1);
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (1);
		parse_archi(ptr, &data);
		if (munmap(ptr, buf.st_size) < 0)
			return (1);
		i++;
	}
	return (0);
}
