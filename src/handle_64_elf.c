/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_elf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:37:10 by ariard            #+#    #+#             */
/*   Updated: 2017/06/09 22:29:04 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		handle_64_elf(char *ptr, t_data *data)
{
	struct elf64_hdr	*header;
	struct elf64_shdr	*section_header;
	char				*strtab;
	int					i;

	(void)data;
	DG("in ELF file");
	header = (struct elf64_hdr *)ptr;
	section_header = (struct elf64_shdr *)(ptr + header->e_shoff);
	i = -1;
	strtab = ptr + (section_header + header->e_shstrndx)->sh_offset;
	while (++i < header->e_shnum)
	{
		printf("sect name %s\n", &strtab[section_header->sh_name]);
		section_header = section_header + 1;
	}
}


/*
 *
	printf("section header %llx\n", header->e_shoff);
	printf("index shstr %hu\n", header->e_shstrndx);
	printf("num %u\n", header->e_shnum);
	section_header = section_header + 1;
	i = *(ptr + 0x1a10);
	j = *(ptr + header->e_shoff + sizeof(struct elf64_shdr));
	printf("%x\n", i);
	printf("%x\n", section_h l leader->sh_name);
	i = *(ptr + 0x1a14);
	printf("%x\n", i);
*/
