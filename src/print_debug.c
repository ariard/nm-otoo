/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 19:03:08 by ariard            #+#    #+#             */
/*   Updated: 2018/02/12 19:03:11 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		print_debug(void *content, t_data *data)
{
	t_sym	*sym;

	(void)data;
	sym = content;
	if (sym->type != 'U')
		ft_printf("%llx", sym->value);
	else
		ft_printf("%s", " ");
	ft_printf(" %c %s\n", sym->type, sym->name);
	if (sym->value == 0x100752b50)
		exit(0);
	return (0);
}
