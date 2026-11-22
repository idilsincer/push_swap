/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_operations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsincer < idsincer@student.42istanbul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:45:16 by idsincer          #+#    #+#             */
/*   Updated: 2026/11/22 19:47:29 by idsincer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	p(t_stack *src, t_stack *dest)
{
	t_node	*first;

	if (!src || !dest || dest->size == 0)
		return ;
	first = dest->top;
	dest->top = first->next;
	if (dest->top)
		dest->top->prev = NULL;
	else
		dest->bottom = NULL;
	dest->size--;
	first->next = src->top;
	first->prev = NULL;
	if (src->top)
		src->top->prev = first;
	else
		src->bottom = first;
	src->top = first;
	src->size++;
	return (1);
}
void	pa(t_stack *a, t_stack *b)
{
	if (p(a, b))
		write(1, "pa\n", 3);
}
void	pb(t_stack *a, t_stack *b)
{
	if (p(b, a))
		write(1, "pb\n", 3);
}
