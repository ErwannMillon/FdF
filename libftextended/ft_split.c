/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:32:43 by gmillon           #+#    #+#             */
/*   Updated: 2022/03/25 18:34:03 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 1;
	while (s && s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			while ((s[i] != c) && s[i])
				i++;
		}
	}
	return (count);
}

static int	get_start_word(size_t *i, const char *s, char c)
{
	while (s[*i] == c && s[*i])
		*i = *i + 1;
	return (*i);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	size_t			i;
	size_t			start;
	size_t			count;

	count = 0;
	result = malloc(ft_count(s, c) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		start = get_start_word(&i, s, c);
		while (s[i] != c && s[i])
			i++;
		if (i != start)
		{
			result[count] = ft_substr(s, start, i - start);
			count++;
		}
		if (s[i])
			i++;
	}
	result[count] = NULL;
	return (result);
}
