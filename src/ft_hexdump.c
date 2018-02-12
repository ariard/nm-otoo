/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 16:08:52 by ariard            #+#    #+#             */
/*   Updated: 2018/02/12 22:59:17 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		print_hex_text(void *a, int size)
{
	int		i;

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

void		ft_hexdump64(struct section_64 *sect, char *ptr, t_data *data,
		char *msg)
{
	uint64_t	address;
	int			size;
	void		*a;

	(void)data;
	ft_printf("%s\n", msg);
	address = sect->addr;
	size = sect->size;
	a = (void *)ptr + sect->offset;
	while (size > 0)
	{
		ft_printf("%016llx%s", address, "	");
		print_hex_text(a, size);
		address += 16;
		a += 16;
		size -= 16;
	}
}

void		ft_hexdump32(struct section *sect, char *ptr, t_data *data,
			char *msg)
{
	uint32_t	address;
	int			size;
	void		*a;

	(void)data;
	ft_printf("%s\n", msg);
	address = sect->addr;
	size = sect->size;
	a = (void *)ptr + sect->offset;
	while (size > 0)
	{
		ft_printf("%08llx%s", address, "	");
		print_hex_text(a, size);
		address += 16;
		a += 16;
		size -= 16;
	}
}
