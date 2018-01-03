/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:29:11 by ariard            #+#    #+#             */
/*   Updated: 2018/01/03 16:56:20 by ariard           ###   ########.fr       */
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
# include "elf.h"


/*
 * Nm
*/

#define	NM_NOPT		(1 << 1)
#define	NM_ROPT		(1 << 2)
#define NM_POPT		(1 << 3)
#define NM_GOPT		(1 << 4)
#define NM_AOPT		(1 << 5)
#define NM_OOPT		(1 << 6)
#define NM_uOPT		(1 << 7)
#define NM_UOPT		(1 << 8)
#define NM_JOPT		(1 << 9)

#define	ELF_NOTYPE	0
#define ELF_OBJECT	1
#define ELF_FUNC	2
#define ELF_SECTION	3
#define ELF_FILE	4
#define ELF_COMMON	5
#define ELF_TLS		6

#define EH_MAGIC_64	0x7f

struct s_data
{	
	t_flag		flag;	
	char		**av_data;
	t_list		*lstsym;
	int			filetype;
	char		*filename;
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
	char	*desc;
	int		value;
	int		index;
};

typedef struct s_sym		t_sym;


struct s_stabs
{
	char	value;
	char	*entry;
};

typedef struct s_stabs		t_stabs;


struct s_elfsect
{
	char 	*value;
	char	type;
};

typedef struct s_elfsect	t_elfsect;

/* MachO binary */

void		handle_64(char *ptr, t_data *data);
void		handle_32(char *ptr);
void		handle_fat(char *ptr);
void		parse_sections(struct segment_command_64 *segm,
			t_hashtab *tabsections, int *nsects);
void		parse_symtab(struct symtab_command *sym, char *ptr, t_data *data);
void		symtab_sort(t_list **lstsym, t_data *data);
void		symtab_del(t_list **lstsym, t_data *data);
int			print_sym(void *content, t_data *data);

/* Elf binary */

void		handle_64_elf(char *ptr, t_data *data);
void		parse_symtab_elf(char *ptr, struct elf64_shdr *section_header,
			t_data *data);
int			print_sym_elf(void *content, t_data *data);
int			sort_elf(t_sym *sym1, t_sym *sym2);

int			sections_match(const void *data_ref, const void *key);
int			sections_print(const void *data_ref);
void		sections_init(t_section *section);
	
void		sym_init(t_sym *sym);		

/*
 * Otool
*/

void		ft_hexdump(struct section_64 *sect, char *ptr, char *filename);

#endif
