/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 16:08:52 by ariard            #+#    #+#             */
/*   Updated: 2017/05/21 17:17:00 by ariard           ###   ########.fr       */
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

void		ft_hexdump(struct section_64 *sect, char *ptr)
{			
	int		address;
	int		size;
	void	*a;
	
	DG("name %s", sect->sectname);
	DG("addres %x", sect->addr);
	DG("size %x and dec %d", sect->size, sect->size);
	DG("offset %d", sect->offset);
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
