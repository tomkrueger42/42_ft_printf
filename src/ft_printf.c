/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:11:57 by tomkrueger        #+#    #+#             */
/*   Updated: 2021/11/02 23:36:38 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;
	t_arg	arg;
	int		r;

	r = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			arg = (t_arg){0};
			s += flaggos(s + 1, &args, &arg, 0) + 2;
			arg.len += write_go_brrrrr(*(s - 1), &arg, 0);
			if (!arg.neg)
				r += right_bound(*(s - 1), &arg);
			else
				r += left_bound(*(s - 1), &arg);
		}
		else
		{
			r += write(1, s++, 1);
		}
	}
	va_end(args);
	return (r);
}

int	flaggos(const char *s, va_list *args, t_arg *arg, int i)
{
	while (s[i] != 'c' && s[i] != 's' && s[i] != 'p' && s[i] != 'i' && s[i]
		!= 'd' && s[i] != 'u' && s[i] != 'x' && s[i] != 'X' && s[i] != '%')
	{
		if (s[i] == '0' && !arg->mfw && !arg->isprec)
			arg->zero = 1;
		if (s[i] >= '0' && s[i] <= '9' && !arg->isprec)
			arg->mfw = arg->mfw * 10 + s[i] - '0';
		if (s[i] == '.')
			arg->isprec = 1;
		if (s[i] >= '0' && s[i] <= '9' && arg->isprec && arg->isprec++)
			arg->prec = arg->prec * 10 + s[i] - '0';
		if (s[i] == '-')
			arg->neg = 1;
		if (s[i] == '#')
			arg->hash = 1;
		if (s[i] == ' ')
			arg->blank = 1;
		if (s[i] == '+')
			arg->plus = 1;
		if (s[i] == '*' && !arg->isprec)
			arg->mfw = va_arg(*args, int);
		if (s[i++] == '*' && arg->isprec && arg->isprec++)
			arg->prec = va_arg(*args, int);
	}
	return (i + args_to_arg(s[i], args, arg));
}

int	args_to_arg(char c, va_list *args, t_arg *arg)
{
	if (arg->mfw < 0)
	{
		arg->mfw = -arg->mfw;
		arg->neg = 1;
	}
	if ((arg->zero && arg->neg) || (arg->zero && arg->isprec && arg->prec
			>= 0))
		arg->zero = 0;
	if (c == 'c')
		arg->c = va_arg(*args, int);
	else if (c == 's')
		arg->s = va_arg(*args, char *);
	else if (c == 'p')
		arg->ul = va_arg(*args, unsigned long);
	else if (c == 'i' || c == 'd')
		arg->i = va_arg(*args, int);
	else if (c == 'u' || c == 'x' || c == 'X')
		arg->ui = va_arg(*args, unsigned int);
	else if (c == '%')
		arg->c = '%';
	return (0);
}

int	right_bound(char c, t_arg *arg)
{
	if (!arg->i && zerro(c, arg))
		return (arg->r);
	prezzo(c, arg);
	if (arg->zero)
		signs_go_brrrrr(c, arg, 1, 0);
	while (arg->mfw - arg->prec - arg->len
		- signs_go_brrrrr(c, arg, 0, 0) > arg->r)
	{
		if (arg->zero)
			arg->r += write(1, "0", 1);
		else
			arg->r += write(1, " ", 1);
	}
	if (!arg->zero)
		signs_go_brrrrr(c, arg, 1, 0);
	arg->r += signs_go_brrrrr(c, arg, 0, 0);
	while (arg->isprec && arg->prec && (c == 'i' || c == 'd' || c == 'u' || c
			== 'x' || c == 'X') && arg->prec--)
		arg->r += write(1, "0", 1);
	arg->r += write_go_brrrrr(c, arg, !arg->w);
	while (c == 'c' && arg->mfw < -1 && arg->mfw++)
		arg->r += write(1, " ", 1);
	return (arg->r);
}

int	left_bound(char c, t_arg *arg)
{
	if (!arg->i && zerro(c, arg))
		return (arg->r);
	prezzo(c, arg);
	arg->r += signs_go_brrrrr(c, arg, 1, 0);
	while (arg->isprec && arg->prec && (c == 'i' || c == 'd' || c == 'u' || c
			== 'x' || c == 'X') && arg->prec--)
		arg->r += write(1, "0", 1);
	arg->r += write_go_brrrrr(c, arg, !arg->w);
	while (arg->mfw > arg->r)
	{
		if (arg->zero)
			arg->r += write(1, "0", 1);
		else
			arg->r += write(1, " ", 1);
	}
	while (c == 'c' && arg->mfw < -1 && arg->mfw++)
		arg->r += write(1, " ", 1);
	return (arg->r);
}
