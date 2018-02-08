/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_archi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:19:15 by ariard            #+#    #+#             */
/*   Updated: 2018/02/08 21:02:28 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void	parse_archi(char *ptr, t_data *data)
{
	unsigned int		magic_number;

	magic_number = *(unsigned int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr, data);
	else if (magic_number == MH_MAGIC)
		handle_32(ptr);
	else if (magic_number == FAT_CIGAM) 	
		handle_fat(ptr);
	else if (magic_number &  EH_MAGIC_64)
		handle_64_elf(ptr, data);
}
