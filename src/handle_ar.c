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
	char	*tmp;
	char	*base;
	size_t	file_size;

	tmp = ptr + 8;
	file_size = ft_atoi(((struct ar_hdr *)tmp)->ar_size);
	tmp += sizeof(struct ar_hdr) + file_size;
	DG("S : %d", file_size);
	while (*tmp)
	{
		file_size = ft_atoi(((struct ar_hdr *)tmp)->ar_size);
		tmp += sizeof(struct ar_hdr);
		base = tmp;
		ft_printf("\n%s(%s):\n", data->filename, tmp);
		tmp += ft_strlen(tmp);
		while (!*tmp)
			tmp++;
		if (*(unsigned int *)tmp == MH_MAGIC_64)
			parse_archi(tmp, data);	
		tmp = base + file_size;
	}
}
