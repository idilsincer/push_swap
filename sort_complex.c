/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otasar <otasar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:08:18 by otasar            #+#    #+#             */
/*   Updated: 2026/11/22 15:08:18 by otasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static int	peek(t_data *d, t_loc loc)
{
	if (loc == TOP_A)
		return (d->a.top->value);
	if (loc == BOT_A)
		return (d->a.bottom->value);
	if (loc == TOP_B)
		return (d->b.top->value);
	return (d->b.bottom->value);
}

/*
** Moves one element in 3 steps:
** 1) if it is at a bottom, bring it to the top (rra / rrb)
** 2) if it must change stack, push it (pb / pa)
** 3) if its target is a bottom, send it there (ra / rb)
*/
static void	move(t_data *d, t_loc from, t_loc to)
{
	if (from == BOT_A)
		op(d, RRA);
	if (from == BOT_B)
		op(d, RRB);
	if ((from == TOP_A || from == BOT_A) && (to == TOP_B || to == BOT_B))
		op(d, PB);
	if ((from == TOP_B || from == BOT_B) && (to == TOP_A || to == BOT_A))
		op(d, PA);
	if (to == BOT_A)
		op(d, RA);
	if (to == BOT_B)
		op(d, RB);
}

/* to[0]: small third, to[1]: middle third, to[2]: big third */
static void	set_targets(t_loc from, t_loc *to)
{
	to[0] = BOT_B;
	to[1] = TOP_B;
	to[2] = TOP_A;
	if (from == TOP_A)
		to[2] = BOT_A;
	if (from == TOP_B || from == BOT_B)
		to[1] = BOT_A;
	if (from == BOT_B)
		to[0] = TOP_B;
}

/* Splits the chunk lo..hi in 3 parts, then sorts big, middle, small. */
static void	split(t_data *d, t_loc loc, int lo, int hi)
{
	t_loc	to[3];
	int		t1;
	int		t2;
	int		i;

	set_targets(loc, to);
	t1 = lo + (hi - lo + 1) / 3;
	t2 = lo + 2 * (hi - lo + 1) / 3;
	i = 0;
	while (i < hi - lo + 1)
	{
		if (peek(d, loc) >= t2)
			move(d, loc, to[2]);
		else if (peek(d, loc) >= t1)
			move(d, loc, to[1]);
		else
			move(d, loc, to[0]);
		i++;
	}
	sort_chunk(d, to[2], t2, hi);
	sort_chunk(d, to[1], t1, t2 - 1);
	sort_chunk(d, to[0], lo, t1 - 1);
}

/*
** Complex O(n log n): sorts the values lo..hi found at loc
** and leaves them sorted on top of a.
** If the chunk is a whole stack, its bottom is also its top.
*/
void	sort_chunk(t_data *d, t_loc loc, int lo, int hi)
{
	if (loc == BOT_A && d->a.size == hi - lo + 1)
		loc = TOP_A;
	if (loc == BOT_B && d->b.size == hi - lo + 1)
		loc = TOP_B;
	if (hi - lo + 1 >= 3)
	{
		split(d, loc, lo, hi);
		return ;
	}
	move(d, loc, TOP_A);
	if (hi > lo)
		move(d, loc, TOP_A);
	if (hi > lo && d->a.top->value > d->a.top->next->value)
		op(d, SA);
}
