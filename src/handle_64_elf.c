/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_elf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:37:10 by ariard            #+#    #+#             */
/*   Updated: 2017/06/09 20:20:32 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		handle_64_elf(char *ptr, t_data *data)
{
	struct elf64_hdr	*header;
	struct elf64_shdr	*section_header;
	struct elf64_shdr	*strtable;
	int					i;

	(void)data;
	DG("in ELF file");
	header = (struct elf64_hdr *)ptr;
	section_header = ((struct elf64_shdr *)((void *)ptr + header->e_shoff));
	printf("%llx", header->e_shoff);
	strtable = &section_header[header->e_shstrndx];
	i = 0;
	return ;
	while (i < header->e_shnum)
	{
//		printf("sect - name : %s\n", strtable[section_header->sh_name]);
		section_header = section_header + sizeof(section_header);
	}
}
