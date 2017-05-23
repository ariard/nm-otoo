/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 16:08:52 by ariard            #+#    #+#             */
/*   Updated: 2017/05/23 21:31:34 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		print_hex_text(int address, void *a, int size)
{
	int		i;

	ft_printf("%016llx         ", address);
	if (size > 16)
		i = 16;
	else
		i = size;
	while (i--)
	{
		ft_printf("%02x ", *(unsigned char *)a);
		a++;
	}
	ft_printf("\n");
}

void		ft_hexdump(struct section_64 *sect, char *ptr, char *filename)
{			
	int		address;
	int		size;
	void	*a;
	
	ft_printf("%s:\n", filename);
	ft_printf("Contents of (__TEXT, __text) section\n");
	address = sect->addr; 
	size = sect->size;
	a = (void *)ptr + sect->offset;
	while (size > 0)
	{
		print_hex_text(address, a, size);
		DG("address is %x", address);
		address += 16;
		a += 16;
		size -= 16;
	}
}
