/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 22:17:03 by ariard            #+#    #+#             */
/*   Updated: 2018/02/20 14:49:32 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	otool_special(t_data *data)
{
	if (!data->bin && !(OT_HOPT & data->flag))
		ft_printf("Archive : %s\n", data->filename);
	if (!data->bin)
		data->flag |= OT_AOPT;
}

void		handle_ar(char *ptr, t_data *data)
{
	size_t	size;
	char	*name;
	char	*tmp;

	otool_special(data);
	MC(ptr += SARMAG);
	MC(ptr += ft_atoi(((struct ar_hdr *)ptr)->ar_size) + sizeof(struct ar_hdr));
	while (ptr && *ptr)
	{
		if (!ft_strncmp(ptr, ARMAG, SARMAG))
			break ;
		MC(tmp = ptr);
		size = ft_atoi(((struct ar_hdr *)ptr)->ar_size) + sizeof(struct ar_hdr);
		MC(ptr += sizeof(struct ar_hdr));
		name = ptr;
		MC(ptr += ft_strlen(ptr) + 1);
		while (ptr && !*ptr)
			ptr++;
		ft_printf("%s%s(%s):\n", (data->bin) ? "\n" : "", data->filename, name);
		parse_archi(ptr, data);
		ptr = tmp + size;
	}
}
