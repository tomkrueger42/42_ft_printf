/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:16:19 by tkruger           #+#    #+#             */
/*   Updated: 2021/11/02 23:36:22 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	prezzo(char c, t_arg *arg)
{
	if (c == 'i' || c == 'd' || c == 'u' || c == 'x' || c == 'X')
	{
		arg->prec -= arg->len;
		if (arg->prec < 0)
			arg->prec = 0;
	}
	if (c == 's' && (arg->prec < 0 || (arg->mfw && arg->isprec
				> 1 && arg->len < arg->prec)))
	{
		arg->isprec = 0;
		arg->prec = 0;
	}
	else if (c == 's' && arg->mfw > arg->prec && arg->isprec
		> 1 && arg->len >= arg->prec)
		arg->len = 0;
	if (c == 'c' && arg->mfw < 0)
		arg->prec *= (-1);
}

int	zerro(char c, t_arg *arg)
{
	if ((c == 'i' || c == 'd') && !arg->i && !arg->mfw
		&& arg->isprec >= 1 && !arg->prec)
	{
		return (1);
	}
	else if ((c == 'i' || c == 'd') && !arg->i && arg->mfw
		&& arg->isprec >= 1 && !arg->prec)
	{
		write(1, " ", 1);
		arg->w = 1;
		return (0);
	}
	else if ((c == 'u' || c == 'x' || c == 'X') && !arg->ui && !arg->mfw
		&& arg->isprec >= 1 && !arg->prec)
	{
		return (1);
	}
	else if ((c == 'u' || c == 'x' || c == 'X') && !arg->ui && arg->mfw
		&& arg->isprec >= 1 && !arg->prec)
	{
		write(1, " ", 1);
		arg->w = 1;
		return (0);
	}
	return (0);
}

int	write_go_brrrrr(char c, t_arg *arg, int w)
{
	if (c == 'c' || c == '%')
		return (putchar_int(arg->c, w));
	else if (c == 's')
		return (putstr_int(arg->s, arg, w));
	else if (c == 'p')
		return (putubase_int(arg->ul, 16, 0, w));
	else if (c == 'i' || c == 'd')
		return (putsbase_int(arg->i, 10, 0, w));
	else if (c == 'u')
		return (putubase_int(arg->ui, 10, 0, w));
	else if (c == 'x')
		return (putubase_int(arg->ui, 16, 0, w));
	else if (c == 'X')
		return (putubase_int(arg->ui, 16, 1, w));
	else
		return (0);
}

int	signs_go_brrrrr(char c, t_arg *arg, int w, int r)
{
	if (c == 'p' || (arg->hash && c == 'x'))
	{
		if (!w)
			return (2);
		r += write(1, "0x", 2);
	}
	if ((arg->hash && c == 'X'))
	{
		if (!w)
			return (2);
		r += write(1, "0X", 2);
	}
	else if (arg->plus && (arg->i >= 0 || arg->ul >= 0))
	{
		if (!w)
			return (1);
		r += write(1, "+", 1);
	}
	else if (arg->i < 0)
	{
		if (!w)
			return (1);
		r += write(1, "-", 1);
	}
	return (r);
}
