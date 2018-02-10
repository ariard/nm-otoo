/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sym.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:22:18 by ariard            #+#    #+#             */
/*   Updated: 2018/02/10 20:21:00 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"


int			print_sym(void *content, t_data *data)
{
	t_sym	*sym;

	sym = content;
	if (((data->flag & NM_GOPT) && sym->type > 90) || (sym->type == 45 &&
		!(data->flag & NM_AOPT)))
		return (0);
	if ((data->flag & NM_uOPT) && (sym->type != 85 || sym->type != 117))
		return (0);
	if ((data->flag & NM_UOPT) && (sym->type == 85 || sym->type == 117))
		return (0);
	if (data->flag & NM_OOPT)
		ft_printf("%s: ", data->filename);
//	if ((data->filetype & MH_OBJECT) && sym->type != 'U')
//		ft_printf("%016llx", sym->value);
	if (sym->type != 'U')
		ft_printf("%0*llx", (data->bits == 64) ? 16 : 8, sym->value);
	else
		ft_printf("%*s", (data->bits == 64) ? 16 : 8, " ");
	if (data->flag & NM_JOPT)
		ft_printf("%s\n", sym->name);
	else if ((data->flag & NM_AOPT) && sym->type == 45)
		ft_printf(" %c %s %s\n", sym->type, sym->desc, sym->name);
	else 
		ft_printf(" %c %s\n", sym->type, sym->name);
	return (0);
}
