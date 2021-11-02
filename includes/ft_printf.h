/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 10:57:15 by tkruger           #+#    #+#             */
/*   Updated: 2021/09/07 15:20:45 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_arg
{
	int				w;
	int				len;
	int				mfw;
	int				neg;
	int				zero;
	int				isprec;
	int				prec;
	int				hash;
	int				blank;
	int				plus;
	char			c;
	char			*s;
	unsigned long	ul;
	unsigned int	ui;
	int				i;
	int				r;
}					t_arg;

int		ft_printf(const char *s, ...);

int		flaggos(const char *s, va_list *args, t_arg *arg, int i);
int		args_to_arg(char c, va_list *args, t_arg *arg);
int		right_bound(char c, t_arg *arg);
int		left_bound(char c, t_arg *arg);
void	prezzo(char c, t_arg *arg);
int		zerro(char c, t_arg *arg);
int		write_go_brrrrr(char c, t_arg *arg, int w);
int		signs_go_brrrrr(char c, t_arg *arg, int w, int r);
int		putchar_int(char c, int w);
int		putstr_int(char *str, t_arg *arg, int w);
int		putubase_int(unsigned long n, int base, int uc, int w);
int		putsbase_int(long n, int base, int uc, int w);

#endif
