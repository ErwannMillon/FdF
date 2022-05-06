/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:33:31 by gmillon           #+#    #+#             */
/*   Updated: 2022/03/25 18:36:58 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *dest, int c, size_t len)
{
	char		*destcast;
	size_t		i;

	i = 0;
	destcast = (char *)dest;
	while (i < len)
	{
		*destcast = (unsigned char)c;
		destcast++;
		i++;
	}
	return (dest);
}
