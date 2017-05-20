/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 21:59:11 by ariard            #+#    #+#             */
/*   Updated: 2017/05/20 22:30:26 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	ft_hexdump(char *ptr, int offset)
{
	int	j;
	
	j = 0;
	while (offset--)
	{
		while (j < 16)
		{
			ft_printf("%x ", *ptr);
			ptr = (void *)ptr + 1;
		}
	}
}

int	 main(int ac, char **av)
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
		if (munmap(ptr, buf.st_size) < 0)
			return (1);
		i++;
	}
	return (0);
}

//	otool
//	-get sections text offset		
//	-go here
//	-print offset + line in hex AND print 16 bytes in value
