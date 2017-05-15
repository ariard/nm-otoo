/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:29:11 by ariard            #+#    #+#             */
/*   Updated: 2017/05/15 22:21:22 by ariard           ###   ########.fr       */
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
	t_hashtab		*tabsections;
}	

typedef struct s_data		t_data;

void		handle_64(char *ptr, t_data *data);
void		handle_32(char *ptr);
void		handle_fat(char *ptr);
void		parse_sections(char *ptr, t_data *data);



#endif
