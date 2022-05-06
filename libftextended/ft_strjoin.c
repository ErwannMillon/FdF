/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:40:37 by gmillon           #+#    #+#             */
/*   Updated: 2022/03/25 19:09:30 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_strcpy_reti(char *dest, const char *src)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(src);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		totallen;
	char	*joined;
	int		i;
	int		k;

	k = 0;
	i = 0;
	totallen = ft_strlen(s1);
	totallen += ft_strlen(s2);
	joined = malloc(totallen + 1);
	if (!joined)
		return (NULL);
	i = ft_strcpy_reti(joined, s1);
	while (s2[k])
	{
		joined[i] = s2[k];
		i++;
		k++;
	}
	joined[i] = 0;
	return (joined);
}

// int main(void)
// {
// 	printf("%s\n", ft_strjoin("tripouille", "42"));
// }