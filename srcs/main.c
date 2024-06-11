/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:40:52 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/05/30 17:24:47 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == FORWARD)
		move_up(cub, cub->map);
	if (keycode == BACKWARD)
		move_down(cub, cub->map);
	if (keycode == LEFT)
		move_left(cub, cub->map);
	if (keycode == RIGHT)
		move_right(cub, cub->map);
	if (keycode == ROTATE_LEFT)
		change_sight(cub, 1);
	if (keycode == ROTATE_RIGHT)
		change_sight(cub, 2);
	if (keycode == 65307)
		shutwindow(cub);
	return (0);
}

int	all_data_here(t_map *map)
{
	if (!map->no_input)
		return (-1);
	if (!map->so_input)
		return (-1);
	if (!map->we_input)
		return (-1);
	if (!map->ea_input)
		return (-1);
	if (!map->f_input)
		return (-1);
	if (!map->c_input)
		return (-1);
	return (1);
}

int	check_first_char(t_map *map, char *string)
{
	int	i;

	i = 0;
	if (string && string[i])
	{
		while (string[i])
		{
			if (string[i] == '\n' && map->map_parsing_started == 1)
				return (1);
			if (string[i] == '1')
				return (map->map_parsing_started = 1, 1);
			if (string[i] != ' ')
				return (0);
			i++;
		}
	}
	return (1);
}

int	check_arg(char **argv, int argc)
{
	char	*check_cub;
	int		i;
	int		len;

	len = ft_strlen(argv[1]);
	i = 3;
	check_cub = ".cub";
	if (argc != 2)
		return (-1);
	if (len < 5)
		return (-1);
	while (i >= 0)
	{
		if (check_cub[i] != argv[1][len - 1])
			break ;
		len--;
		i--;
	}
	if (i >= 0)
		return (-1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	cub.map = NULL;
	cub.map = (t_map *)malloc(sizeof(t_map));
	if (cub.map == NULL)
		return (1);
	if (argc != 2)
		return (free(cub.map), 1);
	cub.map->number_of_line = 0;
	cub.speed = 0.05;
	cub.rot_speed = 0.01;
	if (check_arg(argv, argc) == -1)
		return (free(cub.map), write(2, "Error\nWrong input\n", 18), -1);
	if (check_map(argv[1], cub.map) == -1)
		return (free(cub.map), write(2, "Error\nIssue within the .cub file\n"
				, 33), -1);
	if (windowinit(&cub) == -1)
		return (free_map(cub.map), free(cub.map), -1);
	free_map(cub.map);
	free(cub.map);
	return (1);
}
