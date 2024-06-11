/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 21:52:25 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/06/01 19:19:12 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

int	ft_atoi(const char *str)
{
	int	signe;
	int	i;
	int	num;

	i = 0;
	signe = 1;
	num = 0;
	while (str && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str && str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * signe);
}

void	check_is_digit(char *string, int *i, int *j)
{
	while (string && ft_isdigit(string[*i]))
	{
		(*j)++;
		*i += 1;
	}
}

int	check_type_text(char *type_input, char *line, char c1, char c2)
{
	if (!(type_input) && ft_strlen(line) > 2 && line[0] == c1
		&& line[1] == c2 && line[2] == ' ')
		return (1);
	else
		return (0);
}

void	else_2_func_check_map(char *line, int *error, int fd)
{
	free(line);
	line = NULL;
	(void)fd;
	*error = 1;
}

void	check_map_norm(t_map *map, char *line, int *error, int fd)
{
	if (check_type_text(map->no_input, line, 'N', 'O'))
			map->no_input = line;
	else if (check_type_text(map->so_input, line, 'S', 'O'))
			map->so_input = line;
	else if (check_type_text(map->we_input, line, 'W', 'E'))
			map->we_input = line;
	else if (check_type_text(map->ea_input, line, 'E', 'A'))
			map->ea_input = line;
	else if (!(map->f_input) && ft_strlen(line) > 1 && line[0] == 'F'
		&& line[1] == ' ')
		map->f_input = line;
	else if (!(map->c_input) && ft_strlen(line) > 1 && line[0] == 'C'
		&& line[1] == ' ')
			map->c_input = line;
	else if (check_first_char(map, line) && all_data_here(map))
	{
		if (map->map_parsing_started == 1)
			map->number_of_line++;
		free(line);
	}
	else
		else_2_func_check_map(line, error, fd);
}
