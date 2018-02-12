/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sym.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:22:18 by ariard            #+#    #+#             */
/*   Updated: 2018/02/12 19:29:33 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		print_debugsym(t_sym *sym)
{
	int		l;
	char	*new;
	char	buff[10];

	l = ft_strlen(sym->desc);
	ft_bzero(buff, 10);
	ft_memset(buff, ' ', 5 - l);
	new = ft_strjoin(buff, sym->desc);
	ft_printf(" %c %02d %04d %s %s\n", sym->type, sym->sect, sym->d,
		new, sym->name);
	ft_strdel(&new);
}

int				print_sym(void *content, t_data *data)
{
	t_sym	*sym;

	sym = content;
	if (((data->flag & NM_GOPT) && sym->type > 90) || (sym->type == 45 &&
		!(data->flag & NM_AOPT)))
		return (0);
	if ((data->flag & NM_UOPT) && (sym->type == 85 || sym->type == 117))
		return (0);
	if ((data->flag & NM_MUOPT) && sym->type != 'U')
		return (0);
	if (data->flag & NM_OOPT || data->flag & NM_MAOPT)
		ft_printf("%s: ", data->filename);
	if (sym->type != 'U' && !(data->flag & NM_JOPT))
		ft_printf("%0*llx", (data->bits == 64) ? 16 : 8, sym->value);
	else if (!(data->flag & NM_MUOPT) && !(data->flag & NM_JOPT))
		ft_printf("%*s", (data->bits == 64) ? 16 : 8, " ");
	if (data->flag & NM_JOPT || data->flag & NM_MUOPT)
		ft_printf("%s\n", sym->name);
	else if ((data->flag & NM_AOPT) && sym->type == 45)
		print_debugsym(sym);
	else
		ft_printf(" %c %s\n", sym->type, sym->name);
	return (0);
}
