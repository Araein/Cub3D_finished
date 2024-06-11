/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:00:32 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/04/17 15:00:32 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3D_bonus.h"

int	check_char(char c, t_map *map, int type)
{
	if (type == 1)
	{
		if ((c == 'W' || c == 'E' || c == 'S' || c == 'N')
			&& map->player == '0')
		{
			map->player = c;
			return (2);
		}
		if (c == ' ' || c == '0' || c == '1')
			return (1);
	}
	else if (type == 2)
		if (c == ' ' || c == '1')
			return (1);
	return (-1);
}

int	check_inner_wall(t_map *map, int i, int j)
{
	if (j != 0)
		if (check_char(map->map[i][j - 1], map, 2) == -1)
			return (-1);
	if (j != (int)(ft_strlen(map->map[i]) - 1))
		if (check_char(map->map[i][j + 1], map, 2) == -1)
			return (-1);
	if (i != 0 && j < (int)ft_strlen(map->map[i - 1]))
	{
		if (check_char(map->map[i - 1][j], map, 2) == -1)
			return (-1);
	}
	if (map->map[i + 1] && j < (int)ft_strlen(map->map[i + 1]))
	{
		if (check_char(map->map[i + 1][j], map, 2) == -1)
			return (-1);
	}
	return (1);
}

int	check_wall_loop(t_map *map, int i, int j)
{
	if (i != 0 && j >= (int)ft_strlen(map->map[i - 1])
		&& map->map[i][j] == '0')
		return (-1);
	if (map->map[i + 1] && j >= (int)ft_strlen(map->map[i + 1])
		&& map->map[i][j] == '0')
		return (-1);
	if (i == 0 || !(map->map[i + 1]) || j == 0
		|| j + 1 == (int)ft_strlen(map->map[i]))
	{
		if (check_char(map->map[i][j], map, 2) == -1)
			return (-1);
	}
	return (1);
}

int	check_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map && map->map && map->map[i])
	{
		if (map->map[i][0] == '\n')
			return (-1);
		while (map->map && map->map[i][j])
		{
			if (check_wall_loop(map, i, j) == -1)
				return (-1);
			if (map->map[i][j] == ' ')
			{
				if (check_inner_wall(map, i, j) == -1)
					return (-1);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (1);
}

int	parse_map(t_map *map, int i, int j, int result)
{
	if (map)
	{
		while (map->map[++i])
		{
			if (!(map->map[i][0]))
				return (-1);
			while (map->map[i][j])
			{
				result = check_char(map->map[i][j], map, 1);
				if (result == -1)
					return (-1);
				if (result == 2)
				{
					map->player_x = i;
					map->player_y = j;
				}
				j++;
			}
			j = 0;
		}
		if (map->player == '0')
			return (-1);
		return (check_wall(map));
	}
	return (-1);
}
