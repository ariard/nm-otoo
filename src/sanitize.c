/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 21:13:59 by ariard            #+#    #+#             */
/*   Updated: 2018/02/20 18:26:38 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

char	sanitize(void *ptr, size_t size, t_data *data)
{
	if (!ptr || ((char *)ptr < data->origin || (char *)ptr + size > data->origin
		+ data->filesize))
	{
		ft_dprintf(2, "%s : %s corrupted", (data->bin) ? "nm" : "otool",
			data->filename);
		return (1);
	}
	return (0);
}
