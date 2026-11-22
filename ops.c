/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otasar <otasar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:08:18 by otasar            #+#    #+#             */
/*   Updated: 2026/11/22 15:08:18 by otasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/*
** Runs one of Idil's operations (it prints its own name)
** and counts it for --bench.
*/
void	op(t_data *d, t_op code)
{
	d->count[code]++;
	d->total++;
	if (code == SA)
		sa(&d->a, 0);
	else if (code == PA)
		pa(&d->a, &d->b);
	else if (code == PB)
		pb(&d->a, &d->b);
	else if (code == RA)
		ra(&d->a, 0);
	else if (code == RB)
		rb(&d->b, 0);
	else if (code == RRA)
		rra(&d->a);
	else if (code == RRB)
		rrb(&d->b);
}

/* put_str and put_nbr write to stderr (only used by --bench) */
void	put_str(char *s)
{
	while (*s)
	{
		write(2, s, 1);
		s++;
	}
}

void	put_nbr(long n)
{
	char	c;

	if (n >= 10)
		put_nbr(n / 10);
	c = n % 10 + '0';
	write(2, &c, 1);
}
