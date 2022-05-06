/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:07:24 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/05 18:53:04 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	handle_uppercase_x(long int dec)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	if (dec < 0)
		str = base_convert_neg(dec * -1, "0123456789ABCDEF");
	else
		str = base_convert(dec, "0123456789ABCDEF");
	len = ft_strlen(str);
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	write(1, str, len);
	free(str);
	return (len);
}

int	handle_x(long int dec)
{
	char	*str;
	int		len;

	if (dec < 0)
		str = base_convert_neg(dec * -1, "0123456789abcdef");
	else
		str = base_convert(dec, "0123456789abcdef");
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}

int	handle_p(unsigned long int p)
{
	char	*str;
	char	*hex;
	int		len;

	hex = base_convert((unsigned long)p, "0123456789abcdef");
	str = ft_strjoin("0x", hex);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	free(hex);
	return (len);
}

int	handle_o(long int dec)
{
	char	*str;
	int		len;

	str = base_convert(dec, "01234567");
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
