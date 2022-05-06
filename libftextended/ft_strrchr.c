/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:35:52 by gmillon           #+#    #+#             */
/*   Updated: 2022/03/25 18:41:57 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(char *str, int c)
{
	char	*result;

	result = NULL;
	while (*str)
	{
		if (*str == (char)c)
			result = str;
		str++;
	}
	if (*str == (char)c)
		result = str;
	return (result);
}
