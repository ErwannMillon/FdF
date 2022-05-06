/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:07:37 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/05 18:28:42 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	str_seek(char *str)
{
	static int	i = 0;
	int			len;

	len = 0;
	while (str[i] && str[i] != '%')
	{
		write(1, &str[i], 1);
		i++;
	}
	if (str[i])
	{
		i++;
		if (str[i] && isformat(str[i]))
		{
			i++;
			return (str[i - 1]);
		}
		else
			return (-1);
	}
	else
	{
		i = 0;
		return (0);
	}
}

int	print_and_convert(va_list *list, int *len, char *str)
{
	char	x;

	x = str_seek((char *)str);
	while (x)
	{
		if (x != -1)
		{
			if (x == 's')
				*len += handle_str_arg(x, va_arg(*list, char *)) - 2;
			else if (x == 'p')
				*len += handle_p(va_arg(*list, unsigned long)) - 2;
			else if (x == 'i' || x == 'u' || x == 'd' || x == 'x' || x == 'X')
				*len += handle_lint_arg(x, (long int)(va_arg(*list, int))) - 2;
			else if (x == 'c')
				*len += handle_char_arg(x, va_arg(*list, int)) - 2;
			else if (x == '%')
				*len += (write(1, "%", 1)) - 2;
		}
		else
			return (-1);
		x = str_seek((char *)str);
	}
	return (1);
}

int	ft_printf(const char *str, ...)
{
	static va_list	list;
	int				len;

	va_start(list, (char *)str);
	len = ft_strlen((char *)str);
	if (print_and_convert(&list, &len, (char *)str) == -1)
		return (-1);
	va_end(list);
	return (len);
}
