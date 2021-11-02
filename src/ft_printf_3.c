/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:16:36 by tkruger           #+#    #+#             */
/*   Updated: 2021/11/02 23:36:50 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	putchar_int(char c, int w)
{
	if (w)
		return (write(1, &c, 1));
	return (1);
}

int	putstr_int(char *str, t_arg *arg, int w)
{
	int	r;
	int	p;

	r = 0;
	p = arg->prec;
	if (!str && !w)
		return (6);
	if (!str && w)
		return (write(1, "(null)", 6));
	while (str[r])
	{
		if (arg->isprec && !p)
			break ;
		if (w)
			r += write(1, &str[r], 1);
		else
			r++;
		p--;
	}
	return (r);
}

int	putubase_int(unsigned long n, int base, int uc, int w)
{
	char	a;
	int		r;

	r = 0;
	if (n / base > 0)
		r += putubase_int(n / base, base, uc, w);
	if (n % base <= 9)
		a = n % base + '0';
	else if (uc)
		a = n % base + 'A' - 10;
	else
		a = n % base + 'a' - 10;
	if (w)
		return (r + write(1, &a, 1));
	return (r + 1);
}

int	putsbase_int(long n, int base, int uc, int w)
{
	char	a;
	int		r;

	r = 0;
	if (n < 0)
		n = -n;
	if (n / base > 0)
		r += putsbase_int(n / base, base, uc, w);
	if (n % base <= 9)
		a = n % base + '0';
	else if (uc)
		a = n % base + 'A' - 10;
	else
		a = n % base + 'a' - 10;
	if (w)
		return (r + write(1, &a, 1));
	return (r + 1);
}
