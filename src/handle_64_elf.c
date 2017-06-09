/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_elf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:37:10 by ariard            #+#    #+#             */
/*   Updated: 2017/06/09 18:45:43 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		handle_64_elf(char *ptr, t_data *data)
{
	struct elf64_hdr	*header;
	struct elf64_shdr	*section_header;
	int					i;

	header = (struct elf64_hdr *)ptr;
	section_header = ((struct elf64_shdr *)((void *)ptr + header->e_shoff));
	i = 0
	while (i < header->e_shnum)
	{
		printf("sect - name : %s\n", section_header->sh_name);
		section_header = section_header + sizeof(section_header);		
	}
}
