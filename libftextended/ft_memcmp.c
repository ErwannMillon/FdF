/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:33:21 by gmillon           #+#    #+#             */
/*   Updated: 2022/03/25 18:58:09 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *p1, const void *p2, size_t size)
{
	unsigned char	*cast1;
	unsigned char	*cast2;
	size_t			i;

	i = 0;
	cast1 = (unsigned char *)p1;
	cast2 = (unsigned char *)p2;
	while (i < size)
	{
		if (!(cast1[i] == cast2[i]))
			return ((cast1[i] - cast2[i]));
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	char tab[] =    {0, 1, 9, 6, 5, 3, -32, 65, 84, 2, 32, 81, 2};
// 	char tabDub[] = {0, 1, 9, 6, 5, 3, 32, 65, 84, 2, 32, -81, 2};
// 	char randomStr[] = {0, -98, 65, 34, 21, 0, 84, 75, 65, 0, 32, 3, 0};
// 	char randomStrNd[] = {65, 2, 0, 4, 0, 87, 98, -65, 0, 2 ,7, 32, 0};
// 	printf("%d  %d\n", ft_memcmp(tab, tabDub, 8), memcmp(tab, tabDub, 8));
// }