/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:26:53 by ariard            #+#    #+#             */
/*   Updated: 2017/05/16 18:46:57 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		data_init(t_data *data)
{
	data->lstsym = NULL;
	DG("going init hashtab");
	hashtab_init(&data->tabsections, 100, &ft_hash_string);
}

static void		parse_archi(char *ptr, t_data *data)
{
	unsigned int		magic_number;

	magic_number = *(unsigned int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr, data);
	if (magic_number == MH_MAGIC)
		handle_32(ptr);
	if (magic_number == FAT_CIGAM) 	
		handle_fat(ptr);
}

int				main(int ac, char **av)
{
	int			fd;
	t_data		data;
	int			i;
	char		*ptr;
	struct stat buf;

	DG("start");
	if (ac < 2)
	{
		ft_dprintf(2, "Argumnent needed");
		return (1);
	}
	data_init(&data);
	DG("data init");
	i = 1;
	while (i < ac && av[i])
	{
		if ((fd = open(av[i], O_RDONLY)) < 0)
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
