/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple_medium.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otasar <otasar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:08:18 by otasar            #+#    #+#             */
/*   Updated: 2026/11/22 15:08:18 by otasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/* Rotates s the shorter way until value is on top. */
static void	bring_to_top(t_data *d, t_stack *s, int value)
{
	t_node	*node;
	int		pos;
	t_op	code;

	node = s->top;
	pos = 0;
	while (node->value != value)
	{
		node = node->next;
		pos++;
	}
	if (s == &d->a && pos <= s->size / 2)
		code = RA;
	else if (s == &d->a)
		code = RRA;
	else if (pos <= s->size / 2)
		code = RB;
	else
		code = RRB;
	while (s->top->value != value)
		op(d, code);
}

/* a holds the biggest values, so its max is n - 1 */
static void	sort_three(t_data *d)
{
	if (d->a.top->value == d->n - 1)
		op(d, RA);
	else if (d->a.top->next->value == d->n - 1)
		op(d, RRA);
	if (d->a.top->value > d->a.top->next->value)
		op(d, SA);
}

/*
** Simple O(n^2): push the minimum to b until 3 are left,
** sort those 3, push everything back.
** The minimum of a is always b.size (b holds 0 .. b.size - 1).
*/
void	sort_simple(t_data *d)
{
	while (d->a.size > 3)
	{
		bring_to_top(d, &d->a, d->b.size);
		op(d, PB);
	}
	sort_three(d);
	while (d->b.size > 0)
		op(d, PA);
}

/* The maximum of b is always b.size - 1. */
static void	push_back_max(t_data *d)
{
	while (d->b.size > 0)
	{
		bring_to_top(d, &d->b, d->b.size - 1);
		op(d, PA);
	}
}

/*
** Medium O(n*sqrt(n)): push values in a window of size ~1.4*sqrt(n)
** to b. Small ones (<= i) go to the bottom of b, others stay on top.
** Then push the maximum of b back to a, one by one.
*/
void	sort_medium(t_data *d)
{
	int	range;
	int	i;

	range = 1;
	while (range * range < d->n)
		range++;
	range = range * 14 / 10;
	i = 0;
	while (d->a.size > 0)
	{
		if (d->a.top->value > i + range)
			op(d, RA);
		else
		{
			op(d, PB);
			if (d->b.top->value <= i)
				op(d, RB);
			i++;
		}
	}
	push_back_max(d);
}
