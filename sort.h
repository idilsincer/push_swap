/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otasar <otasar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:08:18 by otasar            #+#    #+#             */
/*   Updated: 2026/11/22 15:08:18 by otasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include "push_swap.h"
# include <limits.h>

typedef enum e_op
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
}	t_op;

typedef enum e_strategy
{
	ADAPTIVE,
	SIMPLE,
	MEDIUM,
	COMPLEX
}	t_strategy;

typedef enum e_loc
{
	TOP_A,
	BOT_A,
	TOP_B,
	BOT_B
}	t_loc;

typedef struct s_data
{
	t_stack		a;
	t_stack		b;
	int			*nums;
	int			n;
	long		pairs;
	long		mistakes;
	t_strategy	strategy;
	t_strategy	chosen;
	int			bench;
	long		total;
	long		count[11];
}	t_data;

void	parse_args(t_data *d, int argc, char **argv);
void	check_pairs(t_data *d);
void	build_stack(t_data *d);
void	free_all(t_data *d);
void	error_exit(t_data *d);
void	op(t_data *d, t_op code);
void	put_str(char *s);
void	put_nbr(long n);
void	print_bench(t_data *d);
void	sort_simple(t_data *d);
void	sort_medium(t_data *d);
void	sort_chunk(t_data *d, t_loc loc, int lo, int hi);

#endif
