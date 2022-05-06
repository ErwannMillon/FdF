/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:35:47 by gmillon           #+#    #+#             */
/*   Updated: 2022/03/25 18:41:55 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(char *str, char *to_find, size_t n)
{
	size_t	i;
	size_t	k;
	size_t	match;

	match = 0;
	i = 0;
	k = 0;
	if (to_find[0] == 0)
		return (str);
	while (str[i] && i < n)
	{
		k = 0;
		while (to_find[k] == str[i + k] && i + k < n)
		{
			if (to_find[k + 1] == 0)
				return (&str[i]);
			k++;
		}
		i++;
	}
	return (NULL);
}
