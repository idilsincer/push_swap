/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otasar <otasar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:08:18 by otasar            #+#    #+#             */
/*   Updated: 2026/11/22 15:08:18 by otasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

/*
** disorder = mistakes / pairs
** disorder < 0.2  <=>  mistakes * 5 < pairs
** disorder < 0.5  <=>  mistakes * 2 < pairs
** 5 numbers or less: every strategy uses sort_simple (base case).
*/
static void	run_strategy(t_data *d)
{
	if (d->strategy != ADAPTIVE)
		d->chosen = d->strategy;
	else if (d->mistakes * 5 < d->pairs)
		d->chosen = SIMPLE;
	else if (d->mistakes * 2 < d->pairs)
		d->chosen = MEDIUM;
	else
		d->chosen = COMPLEX;
	if (d->mistakes == 0)
		return ;
	if (d->n <= 5 || d->chosen == SIMPLE)
		sort_simple(d);
	else if (d->chosen == MEDIUM)
		sort_medium(d);
	else
		sort_chunk(d, TOP_A, 0, d->n - 1);
}

int	main(int argc, char **argv)
{
	t_data	d;

	parse_args(&d, argc, argv);
	if (d.n > 0)
	{
		check_pairs(&d);
		build_stack(&d);
		run_strategy(&d);
		if (d.bench)
			print_bench(&d);
	}
	free_all(&d);
	return (0);
}
