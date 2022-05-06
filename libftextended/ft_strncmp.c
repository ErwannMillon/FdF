/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:01:24 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/05 21:02:08 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1
		&& ((unsigned char)s1[i] == (unsigned char)s2[i]
			&& ((unsigned char)s1[i] && (unsigned char)s2[i])))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
