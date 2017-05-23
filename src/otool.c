/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 21:59:11 by ariard            #+#    #+#             */
/*   Updated: 2017/05/23 21:32:04 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		get_section_text(struct segment_command_64 *segm, char *ptr,
				char *filename)
{
	struct section_64	*sect;
	int					segsects;

	segsects = segm->nsects;
	sect = (void *)segm + sizeof(struct segment_command_64);
	while (segsects--)
	{
		if (!ft_strcmp("__text", sect->sectname))
			ft_hexdump(sect, ptr, filename);
		sect = (void *)sect + sizeof(struct section_64);
	}
}

static void		get_segment(char *ptr, char *filename)
{
	int						ncmds;
	int						i;
	struct load_command		*lc;

	ncmds = ((struct mach_header_64 *)ptr)->ncmds;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			get_section_text((struct segment_command_64 *)lc, ptr,
				filename);
		lc = (void *)lc + lc->cmdsize;
	}
}
	
int		main(int ac, char **av)
{
	int		fd;
	int		i;
	char		*ptr;
	struct stat	buf;
	
	i = 1;
	while (i < ac && av[i])
	{
		if ((fd = open(av[i], O_RDONLY)) < 0)
			return (1);
		if (fstat(fd, &buf) < 0)
			return (1);
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (1);	
		get_segment(ptr, av[i]);
		if (munmap(ptr, buf.st_size) < 0)
			return (1);
		i++;
	}
	return (0);
}

//	-print offset + line in hex AND print 16 bytes in value
