/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:43:37 by dabey             #+#    #+#             */
/*   Updated: 2023/05/25 16:17:15 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

void	raycast_draw(int tempo_x, t_cub *cub)
{
	unsigned int	color;

	color = 0;
	cub->rcast->tex_y = (int)cub->rcast->tex_pos & (128 - 1);
	cub->rcast->tex_pos += cub->rcast->step;
	if (cub->rcast->ray_dir_y < 0 && cub->rcast->side == 1)
		color = get_color_of_image(cub->img[1], cub->rcast->tex_x,
				cub->rcast->tex_y);
	if (cub->rcast->ray_dir_y >= 0 && cub->rcast->side == 1)
		color = get_color_of_image(cub->img[4], cub->rcast->tex_x,
				cub->rcast->tex_y);
	if (cub->rcast->ray_dir_x < 0 && cub->rcast->side == 0)
		color = get_color_of_image(cub->img[3], cub->rcast->tex_x,
				cub->rcast->tex_y);
	if (cub->rcast->ray_dir_x >= 0 && cub->rcast->side == 0)
		color = get_color_of_image(cub->img[2], cub->rcast->tex_x,
				cub->rcast->tex_y);
	if (cub->rcast->side == 1)
		color = (color >> 1) & 8355711;
	my_pixel_put (cub->img[0], tempo_x, cub->rcast->drawstart, color);
	cub->rcast->drawstart++;
}

void	raycast_end(t_cub *cub)
{
	cub->rcast->lineheight = (int)(HEIGHT / cub->rcast->perp_wall_dist);
	cub->rcast->drawstart = (-1 * cub->rcast->lineheight) / 2 + HEIGHT / 2;
	cub->rcast->drawend = cub->rcast->lineheight / 2 + HEIGHT / 2;
	if (cub->rcast->drawstart < 0)
		cub->rcast->drawstart = 0;
	if (cub->rcast->drawend >= HEIGHT)
		cub->rcast->drawend = HEIGHT - 1;
	if (cub->rcast->side == 0)
		cub->rcast->wall_x = cub->rcast->pos_y + cub->rcast->perp_wall_dist
			* cub->rcast->ray_dir_y;
	else
		cub->rcast->wall_x = cub->rcast->pos_x + cub->rcast->perp_wall_dist
			* cub->rcast->ray_dir_x;
	cub->rcast->wall_x -= floor((cub->rcast->wall_x));
	cub->rcast->tex_x = (int)(cub->rcast->wall_x * (double)(128));
	if (cub->rcast->side == 0 && cub->rcast->ray_dir_x > 0)
		cub->rcast->tex_x = 128 - cub->rcast->tex_x - 1;
	if (cub->rcast->side == 1 && cub->rcast->ray_dir_y < 0)
		cub->rcast->tex_x = 128 - cub->rcast->tex_x - 1;
	cub->rcast->step = 1.0 * 128 / cub->rcast->lineheight;
	cub->rcast->tex_pos = (cub->rcast->drawstart - HEIGHT / 2
			+ cub->rcast->lineheight / 2) * cub->rcast->step;
}

void	raycast_ray_hit(t_cub *cub)
{
	cub->rcast->hit = 0;
	while (cub->rcast->hit == 0)
	{
		if (cub->rcast->side_dist_x < cub->rcast->side_dist_y)
		{	
			cub->rcast->side_dist_x += cub->rcast->delta_dist_x;
			cub->rcast->map_x += cub->rcast->step_x;
			cub->rcast->side = 0;
		}
		else
		{
			cub->rcast->side_dist_y += cub->rcast->delta_dist_y;
			cub->rcast->map_y += cub->rcast->step_y;
			cub->rcast->side = 1;
		}
		if (cub->map->map[cub->rcast->map_x][cub->rcast->map_y] == '1')
			cub->rcast->hit = 1;
	}
	if (cub->rcast->side == 0)
		cub->rcast->perp_wall_dist = (cub->rcast->side_dist_x
				- cub->rcast->delta_dist_x);
	else
		cub->rcast->perp_wall_dist = (cub->rcast->side_dist_y
				- cub->rcast->delta_dist_y);
}

void	raycast_launch_ray(t_cub *cub)
{
	if (cub->rcast->ray_dir_x < 0)
	{
		cub->rcast->step_x = -1;
		cub->rcast->side_dist_x = (cub->rcast->pos_x - cub->rcast->map_x)
			* cub->rcast->delta_dist_x;
	}
	else
	{
		cub->rcast->step_x = 1;
		cub->rcast->side_dist_x = (cub->rcast->map_x + 1.0
				- cub->rcast->pos_x) * cub->rcast->delta_dist_x;
	}
	if (cub->rcast->ray_dir_y < 0)
	{
		cub->rcast->step_y = -1;
		cub->rcast->side_dist_y = (cub->rcast->pos_y - cub->rcast->map_y)
			* cub->rcast->delta_dist_y;
	}
	else
	{
		cub->rcast->step_y = 1;
		cub->rcast->side_dist_y = (cub->rcast->map_y + 1.0
				- cub->rcast->pos_y) * cub->rcast->delta_dist_y;
	}
}

void	raycast_start(t_cub *cub)
{
	cub->rcast->camera_x = 2 * cub->rcast->x / (double)WIDTH - 1;
	cub->rcast->ray_dir_x = cub->rcast->dir_x + cub->rcast->plane_x
		* cub->rcast->camera_x;
	cub->rcast->ray_dir_y = cub->rcast->dir_y + cub->rcast->plane_y
		* cub->rcast->camera_x;
	cub->rcast->map_x = (int)cub->rcast->pos_x;
	cub->rcast->map_y = (int)cub->rcast->pos_y;
	if (cub->rcast->ray_dir_x == 0)
		cub->rcast->delta_dist_x = 2147483647;
	else
		cub->rcast->delta_dist_x = fabs(1 / cub->rcast->ray_dir_x);
	if (cub->rcast->ray_dir_y == 0)
		cub->rcast->delta_dist_y = 2147483647;
	else
		cub->rcast->delta_dist_y = fabs(1 / cub->rcast->ray_dir_y);
}
