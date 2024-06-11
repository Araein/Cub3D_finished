/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_on_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:13:29 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/05/30 19:47:53 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3D_bonus.h"

int	move_left(t_cub *cub, t_map *map)
{
	int		value_x;
	int		value_y;
	double	tempo_pos_x;

	tempo_pos_x = cub->rcast->pos_x;
	value_x = (int)(cub->rcast->pos_x + cub->rcast->plane_x * cub->speed);
	value_y = (int)(cub->rcast->pos_y);
	if ((value_x >= 0 && value_y >= 0) && map->map[value_x][value_y] != '1')
		cub->rcast->pos_x += cub->rcast->plane_x * cub->speed;
	else
		return (1);
	value_x = (int)cub->rcast->pos_x;
	value_y = (int)(cub->rcast->pos_y + cub->rcast->plane_y * cub->speed);
	if ((value_x >= 0 && value_y >= 0) && map->map[value_x][value_y] != '1')
		cub->rcast->pos_y += cub->rcast->plane_y * cub->speed;
	else
	{
		cub->rcast->pos_x = tempo_pos_x;
		return (1);
	}
	if (map->map[value_x][value_y - 1] == '1' && cub->rcast->pos_y
		<= (double)value_y - 1)
		cub->rcast->pos_y = (double)value_y - 1 + 0.000001;
	cub->do_raycast = 1;
	return (1);
}

int	move_right(t_cub *cub, t_map *map)
{
	int		value_x;
	int		value_y;
	double	tempo_pos_x;

	tempo_pos_x = cub->rcast->pos_x;
	value_x = (int)(cub->rcast->pos_x - cub->rcast->plane_x * cub->speed);
	value_y = (int)(cub->rcast->pos_y);
	if ((value_x >= 0 && value_y >= 0) && map->map[value_x][value_y] != '1')
		cub->rcast->pos_x -= cub->rcast->plane_x * cub->speed;
	else
		return (1);
	value_x = (int)cub->rcast->pos_x;
	value_y = (int)(cub->rcast->pos_y - cub->rcast->plane_y * cub->speed);
	if ((value_x >= 0 && value_y >= 0) && map->map[value_x][value_y] != '1')
		cub->rcast->pos_y -= cub->rcast->plane_y * cub->speed;
	else
	{
		cub->rcast->pos_x = tempo_pos_x;
		return (1);
	}
	cub->do_raycast = 1;
	return (1);
}

int	move_up(t_cub *cub, t_map *map)
{
	int		value_x;
	int		value_y;
	double	tempo_pos_x;

	tempo_pos_x = cub->rcast->pos_x;
	value_x = (int)(cub->rcast->pos_x + cub->rcast->dir_x * cub->speed);
	value_y = (int)cub->rcast->pos_y;
	if ((value_x >= 0 && value_y >= 0) && map->map[value_x][value_y] != '1')
		cub->rcast->pos_x += cub->rcast->dir_x * cub->speed;
	else
		return (1);
	value_x = (int)cub->rcast->pos_x;
	value_y = (int)(cub->rcast->pos_y + cub->rcast->dir_y * cub->speed);
	if ((value_x >= 0 && value_y >= 0) && map->map[value_x][value_y] != '1')
		cub->rcast->pos_y += cub->rcast->dir_y * cub->speed;
	else
	{
		cub->rcast->pos_x = tempo_pos_x;
		return (1);
	}
	cub->do_raycast = 1;
	return (1);
}

int	move_down(t_cub *cub, t_map *map)
{
	int		value_x;
	int		value_y;
	double	tempo_pos_x;

	tempo_pos_x = cub->rcast->pos_x;
	value_x = (int)(cub->rcast->pos_x - cub->rcast->dir_x * cub->speed);
	value_y = (int)(cub->rcast->pos_y);
	if (map->map[value_x][value_y] != '1')
		cub->rcast->pos_x -= cub->rcast->dir_x * cub->speed;
	else
		return (1);
	value_x = (int)cub->rcast->pos_x;
	value_y = (int)(cub->rcast->pos_y - cub->rcast->dir_y * cub->speed);
	if (map->map[value_x][value_y] != '1')
		cub->rcast->pos_y -= cub->rcast->dir_y * cub->speed;
	else
	{
		cub->rcast->pos_x = tempo_pos_x;
		return (1);
	}
	cub->do_raycast = 1;
	return (1);
}

void	init_img_player(t_cub *cub)
{
	cub->map->player_x = 0;
	cub->map->player_y = 0;
	if (init_img (cub) == -1)
		shutwindow(cub);
}
