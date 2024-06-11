/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:50:11 by dabey             #+#    #+#             */
/*   Updated: 2023/05/30 18:48:38 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

void	init_map_struct(t_map *map)
{
	map->number_of_line = 0;
	map->map_parsing_started = 0;
	map->no_input = NULL;
	map->so_input = NULL;
	map->we_input = NULL;
	map->ea_input = NULL;
	map->f_input = NULL;
	map->c_input = NULL;
	map->player_x = 0;
	map->player_y = 0;
	map->player = '0';
	map->map = NULL;
}

void	loop_fill_map(t_map *map, char **line, int *i, int fd)
{
	while ((get_next_line(fd, line)) > 0)
	{
		if (check_first_char(map, *line) && *line && *line[0] != '\n'
			&& *i < map->number_of_line && map->map_parsing_started == 1)
		{
			map->map[*i] = *line;
			(*i)++;
		}
		else
		{
			free(*line);
			*line = NULL;
		}
	}
}

int	fill_map(t_map *map, char *string)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	map->map = malloc (sizeof(char *) * (map->number_of_line + 1));
	if (map->map == NULL)
		return (-1);
	fd = open(string, O_RDONLY);
	if (fd < 0)
		return (free(map->map), map->map = NULL, -1);
	line = NULL;
	map->map_parsing_started = 0;
	loop_fill_map(map, &line, &i, fd);
	map->map[i] = NULL;
	if (line && check_first_char(map, line) && line[0] != '\n'
		&& i < map->number_of_line)
		map->map[i] = line;
	else
		free (line);
	map->map[i + 1] = NULL;
	close(fd);
	return (1);
}

void	func_check_map(t_map *map, char **line, int *error, int fd)
{
	while ((get_next_line(fd, line)) > 0)
	{
		if (!(ft_strlen(*line) == 1 && *line[0] == '\n'))
			check_map_norm(map, *line, error, fd);
		else
		{
			free(*line);
			*line = NULL;
		}
	}
}

int	check_map(char *string, t_map *map)
{
	int		fd;
	char	*line;
	int		error;

	error = 0;
	line = NULL;
	init_map_struct(map);
	fd = open(string, O_RDONLY);
	if (fd < 0)
		return (-1);
	func_check_map(map, &line, &error, fd);
	if (check_first_char(map, line) && all_data_here(map))
			map->number_of_line++;
	free(line);
	line = NULL;
	close(fd);
	map->map_parsing_started = 0;
	if (error == 1 || fill_map(map, string) == -1)
		return (free(line), free_map(map), -1);
	if (parse_map(map, 0, 0, 0) == -1)
		return (free(line), free_map(map), -1);
	if (parse_data(map) == -1)
		return (free(line), free_map(map), -1);
	return (1);
}
