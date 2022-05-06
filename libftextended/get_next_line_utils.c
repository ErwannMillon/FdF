/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 04:23:11 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/10 04:59:34 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_slen(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != EOF))
		i++;
	return (i);
}

char	*buf_alloc(char *old)
{
	char		*new;
	static int	size = 1;
	int			i;

	i = 0;
	size += BUFFER_SIZE;
	new = malloc(size + 1);
	if (!new)
		return (NULL);
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = 0;
	free(old);
	return (new);
}

int	check_nl(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strncat(char *dest, char *src, int n)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (dest[i])
		i++;
	while (src[j] && j < n && (src[j] != EOF))
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = 0;
	return (dest);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len, int tofree)
{
	size_t	i;
	char	*sub;

	i = 0;
	while (s[start + i] && i < len)
		i++;
	sub = malloc((i + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	if (tofree)
		free(s);
	return (sub);
}
