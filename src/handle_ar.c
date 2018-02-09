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
	size_t	size;
	size_t	file_size;

	(void)data;
	tmp = ptr + 8 + sizeof(struct ar_hdr);
	while (tmp)
	{
		file_size = ft_atoi(((struct ar_hdr *)tmp)->ar_size);
		tmp += sizeof(struct ar_hdr);
		size = write(1, (char *)tmp, ft_strlen(tmp));
		ft_printf("\n");
		tmp += size;
		while (!*tmp)
			tmp++;
		if ((unsigned int)tmp == MH_MAGIC_64)
			ft_printf("\n handle\n");
		tmp += file_size;
	}
}

// ptr + 8 + struct ar_hdr
//
// 	while (tmp)
// 		size = write(1, tmp, ft_strlen(tmp));
//		tmp += size
// 		if magic number == tmp
// 			ft_printf("handle");
// 		tmp += struct ar_hdr + ar_hdr->size
