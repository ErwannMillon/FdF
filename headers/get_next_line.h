/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 04:22:58 by gmillon           #+#    #+#             */
/*   Updated: 2022/04/10 04:58:56 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

char	*buf_alloc(char *old);
char	*ft_substr_free(char *s, unsigned int start, size_t len, int tofree);
int		check_nl(char *buffer);
int		check_eof(char *buffer);
char	*ft_strncat(char *dest, char *src, int n);
int		ft_slen(char *s);
char	*get_next_line(int fd);

#endif
