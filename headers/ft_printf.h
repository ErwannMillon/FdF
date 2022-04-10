/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:07:44 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/06 21:44:56 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define FORMATS "cspdiuxX%"
# include <stdarg.h>
# include <stdlib.h>
# include "libft.h"
# include <unistd.h>

char		str_seek(char *str);
char		*base_convert(unsigned long int dec, char *str);
int			handle_s(char *s);
int			handle_c(char c);
int			handle_d(long int d);
int			handle_uppercase_x(long int dec);
int			handle_x(long int dec);
int			handle_p(unsigned long p);
int			handle_o(long int dec);
int			handle_lint_arg(char c, long int dec);
int			handle_str_arg(char c, char *str);
int			handle_char_arg(char c, char b);
void		ft_putnbr(long int nb);
void		ft_putstr(char *str);
int			ft_printf(const char *str, ...);
long int	num_len(long int copy);
char		*base_convert_neg(long long int dec, char *base);
int			indexformat(char c);
int			isformat(char c);
int			fs_num(char *str);

#endif