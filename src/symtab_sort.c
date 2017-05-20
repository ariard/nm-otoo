/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 17:52:45 by ariard            #+#    #+#             */
/*   Updated: 2017/05/20 20:06:03 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int	sort_alpha(t_sym *sym1, t_sym *sym2)
{
	return (ft_strcmp(sym1->name, sym2->name));
}

void		symtab_sort(t_list **lstsym)
{
	lst_insert_sort(lstsym, sort_alpha);
}
