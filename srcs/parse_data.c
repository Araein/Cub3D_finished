/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:02:36 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/04/24 18:02:36 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

int	check_texture(char *string)
{
	int		fd;
	int		len;

	len = ft_strlen(string);
	if (string[len - 1] != 'm' || string[len - 2] != 'p'
		|| string[len - 3] != 'x' || string[len - 4] != '.')
		return (-1);
	fd = open(string, O_RDONLY);
	if (fd < 0)
		return (-1);
	else
		return (close(fd), 1);
}

int	check_num(char *string, int *i, int type, int j)
{
	char	*num;
	int		number;

	check_is_digit(string, i, &j);
	num = ft_substr(string, *i - j, j);
	if (!num)
		return (-1);
	number = ft_atoi(num);
	free(num);
	if (number < 0 || number > 255)
		return (-1);
	if (type == 1)
	{
		if (string[*i] == ',')
			*i += 1;
		else
			return (-1);
		if (*i >= (int) ft_strlen(string))
			return (-1);
		else
			return (number);
	}
	if (*i == (int) ft_strlen(string))
		return (number);
	return (-1);
}

int	check_rgb_type_1(t_map *map, char *string, int *i)
{
	map->rgb_c[0] = check_num(string, i, 1, 0);
	if (map->rgb_c[0] == -1)
		return (-1);
	map->rgb_c[1] = check_num(string, i, 1, 0);
	if (map->rgb_c[1] == -1)
		return (-1);
	map->rgb_c[2] = check_num(string, i, 2, 0);
	if (map->rgb_c[2] == -1)
		return (-1);
	return (1);
}

int	check_rgb(char *string, t_map *map, int type, int i)
{
	if (!string)
		return (-1);
	while (string[i] == ' ')
		i++;
	if (i == 1 || !(ft_isdigit(string[i])))
		return (-1);
	if (type != 1)
	{
		if (check_rgb_type_1(map, string, &i) == -1)
			return (-1);
	}
	else
	{
		map->rgb_floor[0] = check_num(string, &i, 1, 0);
		if (map->rgb_floor[0] == -1)
			return (-1);
		map->rgb_floor[1] = check_num(string, &i, 1, 0);
		if (map->rgb_floor[1] == -1)
			return (-1);
		map->rgb_floor[2] = check_num(string, &i, 2, 0);
		if (map->rgb_floor[2] == -1)
			return (-1);
	}
	return (1);
}

int	parse_data(t_map *map)
{
	if (check_rgb(map->c_input, map, 1, 1) == -1)
		return (-1);
	if (check_rgb(map->f_input, map, 2, 1) == -1)
		return (-1);
	map->ea_input = cut_texture(map->ea_input);
	if (!map->ea_input || check_texture(map->ea_input) == -1)
		return (-1);
	map->we_input = cut_texture(map->we_input);
	if (!map->we_input || check_texture(map->we_input) == -1)
		return (-1);
	map->no_input = cut_texture(map->no_input);
	if (!map->no_input || check_texture(map->no_input) == -1)
		return (-1);
	map->so_input = cut_texture(map->so_input);
	if (!map->so_input || check_texture(map->so_input) == -1)
		return (-1);
	return (1);
}
