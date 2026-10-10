/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idsincer <idsincer@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 09:13:28 by idsincer          #+#    #+#             */
/*   Updated: 2026/10/10 09:34:13 by idsincer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node *create_node(int value)
{
	t_node	*new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
void	ft_stack_add_back(t_stack *stack, t_node *new)
{
	if (!stack || !new)
		return ;
	if (stack->size == 0)
	{
		stack->top = new;
		stack->bottom = new;
	}
	else
	{
		stack->bottom->next = new;
		new->prev = stack->bottom;
		stack->bottom = new;
	}
	stack->size++;
}
void	ft_stack_add_front(t_stack *stack, t_node *new)
{
	if (!stack || !new)
		return ;
	new->prev = NULL;
	new->next = stack->top;
	if (stack->top)
		stack->top->prev = new;
	else
		stack->bottom = new;
	stack->top = new;
	stack->size++;
}
