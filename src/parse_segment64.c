/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 22:17:23 by ariard            #+#    #+#             */
/*   Updated: 2018/02/12 21:42:47 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

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
	if (section->sectname)
		DG("sect:%s, seg:%s, key:%s", section->sectname,
		section->segname, section->key);
	return (0);
}

int				sections_del(void *data_ref)
{
	t_section	*section;

	section = (t_section *)data_ref;
	section->sectname = NULL;
	section->segname = NULL;
	ft_strdel(&section->key);
	return (0);
}

void			parse_segment64(struct segment_command_64 *segm,
				t_hashtab *tabsections, int *nsects, t_data *data)
{
	int					segsects;
	struct section_64	*sect;
	t_section			section;
	char				*key;

	check_64(segm, data);
	segsects = segm->nsects;
	sect = (void *)segm + sizeof(struct segment_command_64);
	while (segsects--)
	{
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
