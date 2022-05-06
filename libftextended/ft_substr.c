/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:44:04 by gmillon           #+#    #+#             */
/*   Updated: 2022/03/25 18:44:07 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*sub;
	size_t		srclen;

	srclen = ft_strlen(s);
	i = 0;
	while (s[start + i] && i < len && (start + i < srclen))
		i++;
	sub = malloc((i + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len && (start + i < srclen))
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}

// #include <stdio.h>
// int main (void)
// {
// 	char *s = ft_substr("tripouille", 100, 1);

// 	printf("result:%d_\n", strcmp(s, ""));

// }