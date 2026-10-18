/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_operations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsincer <idsincer@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:02:46 by idsincer          #+#    #+#             */
/*   Updated: 2026/10/18 16:48:42 by idsincer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack *stack)
{
	t_node	*first;
	t_node	*second;
	int		tmp;

	if (!stack || stack->size < 2)
		return ;
	first = stack->top;
	second = stack->top->next;
	tmp = first->value;
	first->value = second->value;
	second->value = tmp;
}
void	sa(t_stack *a, char flag)
{
	swap(a);
	if (flag == 0)
		write(1, "sa\n", 3);
}
void	sb(t_stack *b, char flag)
{
	swap(b);
	if (flag == 0)
		write(1, "sb\n", 3);
}
void	ss(t_stack *a, t_stack *b)
{
	sa(a, 1);
	sb(b, 1);
	write(1, "ss\n", 3);
}
