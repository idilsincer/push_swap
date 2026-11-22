/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otasar <otasar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:08:18 by otasar            #+#    #+#             */
/*   Updated: 2026/11/22 15:08:18 by otasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static void	put_count(char *name, long n)
{
	put_str(name);
	put_str(":  ");
	put_nbr(n);
	put_str("  ");
}

static void	print_counts(t_data *d)
{
	put_str("[bench] ");
	put_count("sa", d->count[SA]);
	put_count("sb", d->count[SB]);
	put_count("ss", d->count[SS]);
	put_count("pa", d->count[PA]);
	put_count("pb", d->count[PB]);
	put_str("\n[bench] ");
	put_count("ra", d->count[RA]);
	put_count("rb", d->count[RB]);
	put_count("rr", d->count[RR]);
	put_count("rra", d->count[RRA]);
	put_count("rrb", d->count[RRB]);
	put_count("rrr", d->count[RRR]);
	put_str("\n");
}

static void	put_strategy(t_data *d)
{
	if (d->strategy == SIMPLE)
		put_str("Simple / ");
	else if (d->strategy == MEDIUM)
		put_str("Medium / ");
	else if (d->strategy == COMPLEX)
		put_str("Complex / ");
	else
		put_str("Adaptive / ");
	if (d->chosen == SIMPLE)
		put_str("O(n²)\n");
	else if (d->chosen == MEDIUM)
		put_str("O(n√n)\n");
	else
		put_str("O(n log n)\n");
}

/* pct = disorder * 10000, so 4993 is printed as 49.93% */
void	print_bench(t_data *d)
{
	long	pct;

	pct = 0;
	if (d->pairs > 0)
		pct = d->mistakes * 10000 / d->pairs;
	put_str("[bench] disorder:  ");
	put_nbr(pct / 100);
	put_str(".");
	if (pct % 100 < 10)
		put_str("0");
	put_nbr(pct % 100);
	put_str("%\n[bench] strategy:  ");
	put_strategy(d);
	put_str("[bench] total_ops:  ");
	put_nbr(d->total);
	put_str("\n");
	print_counts(d);
}
