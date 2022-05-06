/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_type_handlers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:07:52 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/05 17:29:55 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	handle_str_arg(char c, char *str)
{
	if (c == 's')
	{
		if (str)
			return (handle_s(str));
		else
			return (write(1, "(null)", 6));
	}
	return (0);
}

int	handle_lint_arg(char c, long int dec)
{
	if (c == 'd' || c == 'i')
	{
		ft_putnbr(dec);
		return (num_len(dec));
	}
	if (c == 'u')
	{
		ft_putnbr((unsigned int)dec);
		return (num_len((unsigned int)dec));
	}
	if (c == 'x')
		return (handle_x(dec));
	if (c == 'X')
		return (handle_uppercase_x(dec));
	return (0);
}

int	handle_char_arg(char c, char b)
{
	if (c == 'c')
		write(1, &b, 1);
	return (1);
}
