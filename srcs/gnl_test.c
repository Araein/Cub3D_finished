/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 00:34:08 by dabey             #+#    #+#             */
/*   Updated: 2023/06/01 19:19:30 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

int	test( int **r, char *buf)
{
	if (**r == -1)
		return (0);
	buf[**r] = 0;
	return (1);
}

int	test2( int **r, char *buf, char **str, int fd)
{
	if (ft_strchr(buf, '\n'))
		return (0);
	**r = read(fd, buf, BUFFER_SIZE);
	if (**r == -1)
	{
		free(*str);
		*str = NULL;
	}
	return (1);
}
