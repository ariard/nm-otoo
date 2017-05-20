/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_inser_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 17:59:14 by ariard            #+#    #+#             */
/*   Updated: 2017/05/19 18:56:53 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_list		*remove_elem(t_list *prev, t_list *remo)
{
	if (!prev || !remo)
		return (NULL);
	prev->next = remo->next;
	return (remo);
}

void		insert_elem(t_list *new_prev, t_list *ins)
{
	t_list	*tmp;
	
	if (!new_prev || !ins)
		return ;
	tmp = new_prev->next;
	new_prev->next = ins;
	ins->next = tmp;
}
					

void			ft_lst_insert_sort(t_list **head, 
				int (cmp)(void *elem1, void *elem2))
{
	t_list	**indirect;
	t_list	*ins;
	t_list	*prev;

	indirect = head;
	while (indirect && *indirect && (*indirect)->next)
	{
		ins = *head;
		DG("%s vs %s", ((t_sym *)(*indirect)->content)->name,
			((t_sym *)((*indirect)->next)->content)->name);
		if ((cmp)(*indirect, (*indirect)->next) > 0)
		{
			DG("outer match");
			while (ins->next)
			{
				DG("%s vs %s", ((t_sym *)(*indirect)->content)->name,
					((t_sym *)ins->content)->name);
				if ((cmp)(*indirect, ins->next) < 0)
				{
					DG("inner match");
					insert_elem(ins, remove_elem(prev, *indirect));
					indirect = head;
					break;
				}
				ins = ins->next;
			}
		}
		prev = *indirect;
		indirect = &(*indirect)->next;
	}
}
