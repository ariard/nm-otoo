/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 17:52:45 by ariard            #+#    #+#             */
/*   Updated: 2017/05/19 17:55:33 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	sort_alpha(void *elem1, void *elem2)
{
	t_sym	*sym1;
	t_sym	*sym2;

	if (!elem1 || !elem2)
		return (0);
	sym1 = (t_sym *)((t_list *)elem1)->content;
	sym2 = (t_sym *)((t_list *)elem2)->content;
	DG("comparaison %s vs %s", sym1->name, sym2->name);
	if (ft_strcmp(sym1->name, sym2->name) > 0)
		return (1);
	else if (ft_strcmp(sym1->name, sym2->name) == 0)
	{	
		if (sym1->value	< sym2->value)
			return (-1);
		else if (sym1->value > sym2->value)
			return (1);
		else
			return (0);
	}	
	return (-1);
}

int	Sort_num(void *elem1, void *elem2)
{
	t_sym	*sym1;
	t_sym	*sym2;

	if (!elem1 || !elem2)
		return (0);
	sym1 = (t_sym *)((t_list *)elem1)->content;
	sym2 = (t_sym *)((t_list *)elem2)->content;
	if (sym1->value < sym2->value)
		return (-1);
	else if (sym1->value > sym2->value)
		return (1);
	else
	{
		if (ft_strcmp(sym1->name, sym2->name) > 0)
			return (-1);
		else if (ft_strcmp(sym1->name, sym2->name) < 0)
			return (1);
		else
			return (0);
	}
}
		
void		symtab_sort(t_list *lstsym)
{
	ft_lst_insert_sort(&lstsym, sort_alpha);
}
