/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:29:11 by ariard            #+#    #+#             */
/*   Updated: 2018/02/20 20:43:29 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <sys/mman.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/sysctl.h>

# include <inttypes.h>

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach/machine.h>
# include <mach-o/arch.h>

# include <ar.h>

# include "../libft/includes/libft.h"

# define NM_NOPT		(1 << 1)
# define NM_ROPT		(1 << 2)
# define NM_POPT		(1 << 3)
# define NM_GOPT		(1 << 4)
# define NM_AOPT		(1 << 5)
# define NM_OOPT		(1 << 6)
# define NM_MUOPT		(1 << 7)
# define NM_UOPT		(1 << 8)
# define NM_JOPT		(1 << 9)
# define NM_MAOPT		(1 << 10)

# define OT_DOPT		(1 << 1)
# define OT_HOPT		(1 << 2)
# define OT_FOPT		(1 << 3)
# define OT_AOPT		(1 << 4)

# define BIT(x, y)		((x) & (1<<(y)))

# define MMAP(x, y, z)	(x = mmap(0, y, PROT_READ, MAP_PRIVATE, z, 0))

# define MC(x)			if (sanitize(x, sizeof(x), data)) { return ; }
# define MBC(x)			if (sanitize(x, sizeof(x), data)) { break ; }
# define MCS2(x)		if (sanitize(x, sizeof(x), data)) { return (1) ; }
# define EV(x)			if (x) { return ; }

# define NOT_AR(x)		ft_strncmp(x, ARMAG, SARMAG)
		

struct	s_data
{
	t_flag			flag;
	char			**av_data;
	t_list			*lstsym;
	char			*filename;
	size_t			filesize;
	char			*origin;
	unsigned int	cpu;
	char			bits;
	char			bin;
	t_hashtab		tabsections;
};

typedef struct s_data		t_data;

struct	s_section
{
	char			*sectname;
	char			*segname;
	char			*key;
};

typedef struct s_section	t_section;

struct	s_sym
{
	char			type;
	char			*name;
	char			*desc;
	uint64_t		value;
	int				index;
	int				sect;
	int				d;
};

typedef struct s_sym		t_sym;

struct	s_stabs
{
	char			value;
	char			*entry;
};

typedef struct s_stabs		t_stabs;

struct	s_symtable
{
	int				symbol;
	int				member;
};

typedef struct s_symtable	t_symtable;

extern t_stabs				g_stabs[];

void	handle_64(char *ptr, t_data *data);
void	handle_32(char *ptr, t_data *data);
void	handle_fat(char *ptr, t_data *data);
void	handle_ar(char *ptr, t_data *data);

void	parse_archi(char *ptr, t_data *data);
void	parse_segment64(struct segment_command_64 *segm,
		t_hashtab *tabsections, int *nsects, t_data *data);
void	parse_segment32(struct segment_command *segm,
		t_hashtab *tabsections, int *nsects, t_data *data);
void	parse_symtab(struct symtab_command *sym, char *ptr,
		t_data *data);
void	parse_symtab32(struct symtab_command *sym, char *ptr,
		t_data *data);

void	sym_init(t_sym *sym);
void	symtab_sort(t_list **lstsym, t_data *data);
void	symtab_del(t_list **lstsym, t_data *data);
int		sym_resolve(int num, t_hashtab *tabsections);
int		print_sym(void *content, t_data *data);
void	sym_del(void *data_ref, size_t size);

int		sections_match(const void *data_ref, const void *key);
int		sections_print(const void *data_ref);
void	sections_init(t_section *section);
int		sections_del(void *data_ref);

char	check_32(struct segment_command *segm, t_data *data);
char	check_64(struct segment_command_64 *segm, t_data *data);
char	check_sym(struct symtab_command *tab, t_data *data);

int		print_debug(void *content, t_data *data);

void	ft_hexdump64(struct section_64 *sect, char *ptr, t_data *data,
		char *msg);
void	ft_hexdump32(struct section *sect, char *ptr, t_data *data,
		char *msg);
void	get_segment64(char *ptr, t_data *data);
void	get_segment32(char *ptr, t_data *data);
void	display_header(char *ptr, t_data *data);
void	display_header32(char *ptr, t_data *data);

char	sanitize(void *ptr, size_t size, t_data *data);

#endif
