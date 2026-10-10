/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsincer <idsincer@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 09:24:33 by idsincer          #+#    #+#             */
/*   Updated: 2026/10/10 10:02:57 by idsincer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*peek(t_stack *stack)
{
	if (!stack || !stack->top)
		return (NULL);
	return (stack->top);
}
void	push(t_stack *stack, t_node *node)
{
	if (!stack || !node)
		return ;
	node->prev = NULL;
	node->next = stack->top;
	if (stack->top)
		stack->top->prev = node;
	else
		stack->bottom = node;
	stack->top = node;
	stack->size++;
}
t_node	*pop(t_stack *stack)
{
	t_node	*new;

	if (!stack || !stack->top)
		return (NULL);
	new = stack->top;
	if (stack->size == 1)
    {
        stack->top = NULL;
        stack->bottom = NULL;
    }
    else
    {
        stack->top = new->next;
        stack->top->prev = NULL;
    }
	new->next = NULL;
    new->prev = NULL;
    stack->size--;
    return (new);
}
