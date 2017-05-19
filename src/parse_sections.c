/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 22:17:23 by ariard            #+#    #+#             */
/*   Updated: 2017/05/16 21:34:15 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		sections_init(t_section *section)
{
	section->sectname = NULL;
	section->segname = NULL;
	section->key = NULL;
}

static void		sections_info(t_section *section, struct section_64 *sect,
				char *key)
{
	section->sectname = sect->sectname;
	section->segname = sect->segname;
	section->key = ft_strdup(key);
}

int				sections_match(const void *data_ref, const void *key)
{
	t_section	*section;

	section = (t_section *)data_ref; 
	if (!(ft_strcmp(section->key, (char *)key)))
		return (0);
	return (1);
}

int				sections_print(const void *data_ref)
{
	t_section	*section;

	section = (t_section *)data_ref;
	printf("sect:%s, seg:%s, key:%s\n", section->sectname, section->segname, section->key);
	return (0);
}

void			parse_sections(struct segment_command_64 *segm,
				t_hashtab *tabsections, int *nsects)
{
	int					segsects;
	struct section_64	*sect;
	t_section			section;
	char				*key;

	segsects = segm->nsects;
	sect = (void *)segm + sizeof(struct segment_command_64);
	while (segsects--)
	{
		DG("sectname : [%s], segname : %s and num %d", sect->sectname, sect->segname, *nsects);
		sections_init(&section);
		key = ft_itoa(*nsects);
		*nsects += 1;
		sections_info(&section, sect, key);
		hashtab_insert(tabsections, ft_lstnew(&section, sizeof(t_section)),
			key, sections_match);
		ft_strdel(&key);
		sect = (void *)sect + sizeof(struct section_64);
	}
}		
