/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:42:12 by gmillon           #+#    #+#             */
/*   Updated: 2022/03/25 19:10:19 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;

	end = ft_strlen(s1) - 1;
	start = 0;
	while (s1[start] && in_set(s1[start], set))
		start++;
	while (s1[end] && in_set(s1[end], set))
		end--;
	end++;
	if (end - start > 0)
		result = ft_substr(s1, start, (end - start));
	else if (end == 1)
		return (ft_strdup((char *)s1));
	else
		return (ft_strdup(""));
	return (result);
}

// #include <stdio.h>
// int main (void)
// {
// 	printf("%s\n", ft_strtrim("m", "tg"));
// }
