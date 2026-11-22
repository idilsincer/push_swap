/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otasar <otasar@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:08:18 by otasar            #+#    #+#             */
/*   Updated: 2026/11/22 15:08:18 by otasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static void	ft_bzero(void *p, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)p)[i] = 0;
		i++;
	}
}

static int	str_equal(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

static int	read_flag(t_data *d, char *s)
{
	if (str_equal(s, "--simple"))
		d->strategy = SIMPLE;
	else if (str_equal(s, "--medium"))
		d->strategy = MEDIUM;
	else if (str_equal(s, "--complex"))
		d->strategy = COMPLEX;
	else if (str_equal(s, "--adaptive"))
		d->strategy = ADAPTIVE;
	else if (str_equal(s, "--bench"))
		d->bench = 1;
	else
		return (0);
	return (1);
}

static int	atoi_check(char *s, int *out)
{
	long	nb;
	int		sign;

	nb = 0;
	sign = 1;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	if (*s == '\0')
		return (0);
	while (*s >= '0' && *s <= '9')
	{
		nb = nb * 10 + (*s - '0');
		if (nb * sign > INT_MAX || nb * sign < INT_MIN)
			return (0);
		s++;
	}
	*out = nb * sign;
	return (*s == '\0');
}

void	parse_args(t_data *d, int argc, char **argv)
{
	int	i;

	ft_bzero(d, sizeof(t_data));
	d->nums = malloc(sizeof(int) * argc);
	if (!d->nums)
		error_exit(d);
	i = 1;
	while (i < argc)
	{
		if (!read_flag(d, argv[i]))
		{
			if (!atoi_check(argv[i], &d->nums[d->n]))
				error_exit(d);
			d->n++;
		}
		i++;
	}
}
