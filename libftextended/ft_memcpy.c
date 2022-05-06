/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:33:26 by gmillon           #+#    #+#             */
/*   Updated: 2022/03/31 15:15:54 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*destcast;
	char		*srccast;

	destcast = (char *)dest;
	srccast = (char *)src;
	i = 0;
	while (src && dest && i < n)
	{
		*destcast = *srccast;
		destcast++;
		srccast++;
		i++;
	}
	return (dest);
}

/*
#include <stdio.h>
int main(void)
{
    char str[22] = "hello bro";
    int a[2] = {34219824, 1234};
    char str2[22];
    int a2[2] = {1000, 1234};
    int n = 5;
    // printf("memset result: %s \n",str);
    // printf("my result: %s \n",str2);
    ft_memcpy(str2, str, n);

    // ft_bzero(a, n);

    // printf("in main: %p \n", &str2);

    // ft_memset(str2, '$', n);
    // ft_memset(a, '$', 2);
    // printf("%d \n",a2[0]);
    printf("ft result: %s \n",str2);
    // printf("rl result: %s \n",str);
    // printf("ft result: %d \n",a2[0]);
    // printf("rl result: %d \n",a[0]);




    // printf("%s", ft_memset(str, '$', 4));

}*/