/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:35:12 by gmillon           #+#    #+#             */
/*   Updated: 2022/03/25 18:57:26 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_strrev(char *s)
{
	int		i;
	int		x;
	int		end;
	char	tmp;

	i = 0;
	x = 0;
	while (s[i])
		i++;
	end = i - 1;
	while (x < i / 2)
	{
		tmp = s[x];
		s[x] = s[end];
		s[end] = tmp;
		x++;
		end--;
	}
	return (s);
}

static long	int	handle_negative(int n, int *minus)
{
	long int	copy;

	*minus = 0;
	copy = n;
	if (copy < 0)
	{
		*minus = 1;
		copy *= -1;
	}
	return (copy);
}

static long int	num_len(long int copy)
{
	int	len;

	len = 2;
	while (copy > 0)
	{
		copy = copy / 10;
		len++;
	}
	return (len);
}

char	*handle_zero(char *str)
{
	str[0] = 48;
	str[1] = 0;
	return (str);
}

char	*ft_itoa(int n)
{
	long int	copy;
	int			minus;
	char		*str;
	int			i;

	i = 0;
	copy = handle_negative(n, &minus);
	str = malloc(num_len(copy) * sizeof(char));
	if (!str)
		return (NULL);
	while (copy > 0)
	{
		str[i] = copy % 10 + 48;
		i++;
		copy = copy / 10;
	}
	if (minus)
	{
		str[i] = '-';
		i++;
	}
	if (n == 0)
		return (handle_zero(str));
	str[i] = 0;
	return (ft_strrev(str));
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("%s\n", ft_itoa(-1234));
// }