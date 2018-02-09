/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 17:52:45 by ariard            #+#    #+#             */
/*   Updated: 2018/02/09 21:40:11 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		sort_alpha(t_sym *sym1, t_sym *sym2)
{
	if (!ft_strcmp(sym1->name, sym2->name))
		return ((sym1->value > sym2->value) ? 1 : -1);
	return (ft_strcmp(sym1->name, sym2->name));
}

int		sort_numeric(t_sym *sym1, t_sym *sym2)
{
	if (sym1->value == sym2->value)
		return (ft_strcmp(sym1->name, sym2->name));
	return ((sym1->value > sym2->value) ? 1 : -1);
}

void		symtab_sort(t_list **lstsym, t_data *data)
{
	if (data->flag & NM_POPT)
	   return ;	
	if (data->flag & NM_NOPT)
		lst_insert_sort(lstsym, sort_numeric);
	else
		lst_insert_sort(lstsym, sort_alpha);
	if (data->flag & NM_ROPT)
		ft_lst_reverse(lstsym);
}

char		ft_tolower2(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
