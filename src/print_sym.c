/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sym.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:22:18 by ariard            #+#    #+#             */
/*   Updated: 2017/05/20 21:38:30 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int			print_sym(void *content, t_data *data)
{
	t_sym	*sym;

	sym = content;
	if ((data->filetype & MH_OBJECT) && sym->type != 'U')
		ft_printf("%016llx", sym->value);
	else if (sym->type != 'U')
		ft_printf("0000001%09llx", sym->value);
	else
		ft_printf("%16s", " ");
	ft_printf(" %c %s\n", sym->type, sym->name);
	return (0);
}
