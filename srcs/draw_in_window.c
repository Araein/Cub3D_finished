/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_in_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:47:31 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/05/26 15:18:06 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

int	draw_floor_and_ceiling(t_cub *cub)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < WIDTH)
	{
		while (j < HEIGHT / 2)
		{
			my_pixel_put(cub->img[0], i, j, get_color(0, cub->map->rgb_floor[0],
					cub->map->rgb_floor[1], cub->map->rgb_floor[2]));
			j++;
		}
		while (j >= HEIGHT / 2 && j <= HEIGHT)
		{
			my_pixel_put(cub->img[0], i, j, get_color(0, cub->map->rgb_c[0],
					cub->map->rgb_c[1], cub->map->rgb_c[2]));
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	draw_player(t_cub *cub, double i, double j)
{
	int	a;
	int	b;

	a = -1;
	b = -1;
	while (i < WIDTH)
	{
		while (j < HEIGHT)
		{
			if (i == floor(cub->rcast->pos_y * 10) && j
				== floor(cub->rcast->pos_x * 10))
			{
				a = i;
				b = j;
			}
			if (a != -1 && b != -1 && (i >= a && i < a + 2)
				&& (j >= b && j < b + 2) && a < WIDTH / 2 && b < HEIGHT / 2)
				my_pixel_put(cub->img[0], (int)i, (int)j, 902230603);
			j++;
		}
		i++;
		j = 0;
	}
}

void	if_loop_draw(t_cub *cub)
{
	cub->hundred_i = cub->i + 10;
	while (cub->i < cub->hundred_i)
	{
		cub->hundred_j = cub->j + 10;
		while (cub->j < cub->hundred_j)
		{
			if (cub->i % 10 == 0 || cub->j % 10 == 0)
				my_pixel_put (cub->img[0], cub->i, cub->j, 300);
			else
				my_pixel_put (cub->img[0], cub->i, cub->j, 255255255);
			cub->j++;
		}
		cub->j = cub->j - 10;
		cub->i++;
	}
}

void	loop_draw(t_cub *cub, int a, int b)
{
	if (cub->map->map[a][b] == '1')
		if_loop_draw(cub);
	else if (cub->map->map[a][b] == '0'
		|| isplayer(cub->map->map[a][b]))
	{
		cub->hundred_i = cub->i + 10;
		while (cub->i < cub->hundred_i)
		{
			cub->hundred_j = cub->j + 10;
			while (cub->j < cub->hundred_j)
			{
				my_pixel_put (cub->img[0], cub->i, cub->j, 300);
				cub->j++;
			}
			cub->j = cub->j - 10;
			cub->i++;
		}
	}
	else
		cub->i += 10;
}

int	draw(t_cub *cub, int a, int b)
{
	cub->j = 0;
	cub->i = 0;
	while (cub->map->map[a] && cub->i < WIDTH / 2 && cub->j < HEIGHT / 2)
	{
		while (cub->map->map[a][b] && cub->i < WIDTH / 2 && cub->j < HEIGHT / 2)
		{
			cub->hundred_i = 0;
			cub->hundred_j = 0;
			if (isplayer(cub->map->map[a][b]) && cub->map->player_x == 0
				&& cub->map->player_y == 0)
			{
				cub->map->player_x = cub->i + 5;
				cub->map->player_y = cub->j + 5;
				cub->map->pos_x = a;
				cub->map->pos_y = b;
			}
			loop_draw(cub, a, b);
			b++;
		}
		cub->i = 0;
		cub->j += 10;
		a++;
		b = 0;
	}
	return (draw_player (cub, 0, 0), 1);
}
