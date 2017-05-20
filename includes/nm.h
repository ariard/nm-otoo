/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:29:11 by ariard            #+#    #+#             */
/*   Updated: 2017/05/20 20:07:07 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <sys/mman.h>
# include <sys/stat.h>

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

# include "../libft/includes/libft.h"

struct s_data
{	
	t_list		*lstsym;
	t_hashtab	tabsections;
};	

typedef struct s_data		t_data;

struct s_section
{
	char		*sectname;
	char		*segname;
	char		*key;
};

typedef struct s_section	t_section;

struct s_sym
{
	char	type;
	char	*name;
	int		scope;
	int		sections;
	int		value;
};

typedef struct s_sym		t_sym;

void		handle_64(char *ptr, t_data *data);
void		handle_32(char *ptr);
void		handle_fat(char *ptr);
void		parse_sections(struct segment_command_64 *segm,
			t_hashtab *tabsections, int *nsects);
void		parse_symtab(struct symtab_command *sym, char *ptr, t_data *data);
void		symtab_sort(t_list **lstsym);	
int			print_sym(void *content);

int			sections_match(const void *data_ref, const void *key);
int			sections_print(const void *data_ref);

#endif
