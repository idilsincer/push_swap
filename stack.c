/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otasar <otasar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:08:18 by otasar            #+#    #+#             */
/*   Updated: 2026/11/22 15:08:18 by otasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static int	rank_of(t_data *d, int i)
{
	int	rank;
	int	j;

	rank = 0;
	j = 0;
	while (j < d->n)
	{
		if (d->nums[j] < d->nums[i])
			rank++;
		j++;
	}
	return (rank);
}

void	build_stack(t_data *d)
{
	t_node	*node;
	int		i;

	i = 0;
	while (i < d->n)
	{
		node = malloc(sizeof(t_node));
		if (!node)
			error_exit(d);
		node->value = rank_of(d, i);
		node->next = NULL;
		node->prev = d->a.bottom;
		if (d->a.bottom)
			d->a.bottom->next = node;
		else
			d->a.top = node;
		d->a.bottom = node;
		d->a.size++;
		i++;
	}
}

void	check_pairs(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (i < d->n)
	{
		j = i + 1;
		while (j < d->n)
		{
			if (d->nums[i] == d->nums[j])
				error_exit(d);
			if (d->nums[i] > d->nums[j])
				d->mistakes++;
			d->pairs++;
			j++;
		}
		i++;
	}
}

void	free_all(t_data *d)
{
	t_node	*next;

	while (d->a.top)
	{
		next = d->a.top->next;
		free(d->a.top);
		d->a.top = next;
	}
	free(d->nums);
}

void	error_exit(t_data *d)
{
	free_all(d);
	write(2, "Error\n", 6);
	exit(1);
}
