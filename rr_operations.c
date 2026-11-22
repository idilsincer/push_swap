/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsincer < idsincer@student.42istanbul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:54:34 by idsincer          #+#    #+#             */
/*   Updated: 2026/11/22 19:49:15 by idsincer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void rr(t_stack *stack)
{
	t_node	*last;

	if (!stack || stack->size < 2)
		return ;
	last = stack->bottom;
	stack->bottom = last->prev;
	stack->bottom->next = NULL;
	stack->top->prev = last;
	last->next = stack->top;
	last->prev = NULL;
	stack->top = last;
}
void	rra(t_stack *a, char flag)
{
	rr(a);
	if (flag == 0)
		write(1, "rra\n", 4);
}
void	rrb(t_stack *b, char flag)
{
	rr(b);
	if (flag == 0)
		write(1, "rrb\n", 4);
}
void	rrr(t_stack *a, t_stack *b)
{
	rra(a, 1);
	rrb(b, 1);
	write(1, "rrr\n", 4);
}
