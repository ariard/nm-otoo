/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sym.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:22:18 by ariard            #+#    #+#             */
/*   Updated: 2017/05/23 20:59:17 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"


int			print_sym(void *content, t_data *data)
{
	t_sym	*sym;

	sym = content;
	if (((data->flag & NM_GOPT) && sym->type > 95) || (sym->type == 95 &&
		!(data->flag & NM_AOPT)))
		return (0);
	if ((data->flag & NM_uOPT) && (sym->type != 85 || sym->type != 117))
		return (0);
	if ((data->flag & NM_UOPT) && (sym->type == 85 || sym->type == 117))
		return (0);
	if (data->flag & NM_OOPT)
		ft_printf("%s: ", data->filename);
	if ((data->filetype & MH_OBJECT) && sym->type != 'U')
		ft_printf("%016llx", sym->value);
	else if (sym->type != 'U')
		ft_printf("0000001%09llx", sym->value);
	else
		ft_printf("%16s", " ");
	if (data->flag & NM_JOPT)
		ft_printf("%s\n", sym->name);
	else if (data->flag & NM_AOPT)
		ft_printf(" %c %s %s\n", sym->type, sym->desc, sym->name);
	else 
		ft_printf(" %c %s\n", sym->type, sym->name);
	return (0);
}
