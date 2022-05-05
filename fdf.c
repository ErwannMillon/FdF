/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:05:34 by gmillon           #+#    #+#             */
/*   Updated: 2022/05/05 20:48:10 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	char	*filepath;
	float	***tab;
	float	***xyztab;

	if (argc != 2)
	{
		ft_printf("Invalid number of args");
		exit(0);
	}
	filepath = argv[1];
	tab = str_arr_atoi(filepath);
	xyztab = copy_int_arr(tab, 0);
	draw_wireframe(tab, xyztab);
}
