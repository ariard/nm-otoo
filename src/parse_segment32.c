/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 22:17:23 by ariard            #+#    #+#             */
/*   Updated: 2018/02/20 18:27:44 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void			sections_init(t_section *section)
{
	section->sectname = NULL;
	section->segname = NULL;
	section->key = NULL;
}

static void		sections_info(t_section *section, struct section *sect,
				char *key)
{
	section->sectname = sect->sectname;
	section->segname = sect->segname;
	section->key = ft_strdup(key);
}

void			parse_segment32(struct segment_command *segm,
				t_hashtab *tabsections, int *nsects, t_data *data)
{
	int					segsects;
	struct section		*sect;
	t_section			section;
	char				*key;

	EV(check_32(segm, data));
	segsects = segm->nsects;
	MC(sect = (void *)segm + sizeof(struct segment_command));
	while (segsects--)
	{
		sections_init(&section);
		key = ft_itoa(*nsects);
		*nsects += 1;
		sections_info(&section, sect, key);
		hashtab_insert(tabsections, ft_lstnew(&section, sizeof(t_section)),
			key, sections_match);
		ft_strdel(&key);
		MC(sect = (void *)sect + sizeof(struct section));
	}
}
