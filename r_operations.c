/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_operations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsincer <idsincer@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:51:01 by idsincer          #+#    #+#             */
/*   Updated: 2026/10/18 17:22:54 by idsincer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	r(t_stack *stack) // 1 2 3 4 5 6 => 2 3 4 5 6 1
{
	t_node	*first;

	if (!stack || stack->size < 2)
		return ;
	first = stack->top;
	stack->top = first->next;
	stack->top->prev = NULL;
	stack->bottom->next = first;
	first->prev = stack->bottom;
	first->next = NULL;
	stack->bottom = first;
}
void	ra(t_stack *a, char flag)
{
	r(a);
	if (flag == 0)
		write(1, "ra\n", 3);
}
void	rb(t_stack *b, char flag)
{
	r(b);
	if (flag == 0)
		write(1, "rb\n", 3);
}
void	rr(t_stack *a, t_stack *b)
{
	ra(a, 1);
	rb(b, 1);
	write(1, "rr\n", 3);
}
