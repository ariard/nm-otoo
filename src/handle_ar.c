/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:17:03 by ariard            #+#    #+#             */
/*   Updated: 2018/02/09 22:56:15 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		handle_ar(char *ptr, t_data *data)
{
	size_t	size;
	char	*name;
	char	*tmp;

	ptr += SARMAG;
	ptr += ft_atoi(((struct ar_hdr *)ptr)->ar_size) + sizeof(struct ar_hdr);
	while (ptr)
	{ 
		if (!ft_strncmp(ptr, ARMAG, SARMAG))
			break;
		tmp = ptr;
		size = ft_atoi(((struct ar_hdr *)ptr)->ar_size) + sizeof(struct ar_hdr);
		ptr += sizeof(struct ar_hdr);
		name = ptr;
		ptr += ft_strlen(ptr) + 1;
		while (!*ptr)
			ptr++;
		ft_printf("\n%s(%s):\n", data->filename, name);
		parse_archi(ptr, data);
		ptr = tmp + size;
	}
}
