/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:12:09 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/05/30 20:07:31 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

int	shutwindow(t_cub *cub)
{
	int	i;

	i = 0;
	free_map(cub->map);
	free(cub->map);
	destroy_images(cub->img, cub->mlx_ptr);
	if (cub->img[0])
		mlx_destroy_image(cub->mlx_ptr, cub->img[0]->img);
	mlx_clear_window (cub->mlx_ptr, cub->window_ptr);
	mlx_destroy_window (cub->mlx_ptr, cub->window_ptr);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
	free(cub->rcast);
	while (i < 5)
	{
		if (cub->img[i])
			free(cub->img[i]);
		cub->img[i] = NULL;
		i++;
	}
	printf("Goodbye !\n");
	exit(1);
}

int	init_img(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		cub->img[i] = (t_data *)malloc(sizeof(t_data));
		if (cub->img[i] == NULL)
		{
			i--;
			while (i >= 0)
			{
				free(cub->img[i]);
				cub->img[i] = NULL;
				i--;
			}
			return (-1);
		}
		cub->img[i]->img = NULL;
		i++;
	}
	return (1);
}

void	init_player_w_n(t_cub *cub, t_rcast *rcast)
{
	if (cub->map->player == 'W')
	{
		rcast->dir_x = 0;
		rcast->dir_y = -1.0;
		rcast->plane_x = 0.66;
		rcast->plane_y = 0;
	}
	if (cub->map->player == 'N')
	{
		rcast->dir_x = -1.0;
		rcast->dir_y = 0;
		rcast->plane_x = 0;
		rcast->plane_y = -0.66;
	}
}

void	init_player(t_cub *cub, t_rcast *rcast, int i)
{
	cub->rcast = rcast;
	init_player_w_n(cub, rcast);
	if (cub->map->player == 'E')
	{
		rcast->dir_x = 0;
		rcast->dir_y = 1.0;
		rcast->plane_x = -0.66;
		rcast->plane_y = 0;
	}
	if (cub->map->player == 'S')
	{
		rcast->dir_x = 1;
		rcast->dir_y = 0;
		rcast->plane_x = 0;
		rcast->plane_y = 0.66;
	}
	cub->rcast->pos_x = (double)cub->map->player_x ;
	cub->rcast->pos_y = (double)cub->map->player_y ;
	cub->rcast->pos_x = cub->rcast->pos_x + 0.5;
	cub->rcast->pos_y = cub->rcast->pos_y + 0.5;
	cub->do_raycast = 1;
	while (i < 5)
		cub->img[i++] = NULL;
}

int	windowinit(t_cub *cub)
{
	t_rcast	*rcast;

	rcast = malloc(sizeof(t_rcast));
	if (!rcast)
		return (-1);
	init_player(cub, rcast, 0);
	cub->mlx_ptr = mlx_init();
	if (cub->mlx_ptr == NULL)
		return (write(2, "Error\nIssue with mlx_init\n", 26), free(rcast), -1);
	mlx_get_screen_size(cub->mlx_ptr, &cub->screen_x, &cub->screen_y);
	if (WIDTH <= 0 || HEIGHT <= 0 || cub->screen_x < WIDTH
		|| cub->screen_y < HEIGHT)
		return (mlx_destroy_display(cub->mlx_ptr), free(cub->mlx_ptr),
			write(2, "Screen size error\n", 18), free(rcast), -1);
	cub->window_ptr = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	if (!cub->window_ptr)
		return (mlx_destroy_display(cub->mlx_ptr), free(cub->mlx_ptr),
			write(2, "Error\nIssue with mlx_new_window\n", 32), free(rcast), -1);
	init_img_player(cub);
	mlx_loop_hook(cub->mlx_ptr, put_texture, cub);
	mlx_hook(cub->window_ptr, 2, 1l << 0, key_hook, cub);
	mlx_hook(cub->window_ptr, 33, 1L << 5, shutwindow, cub);
	mlx_loop(cub->mlx_ptr);
	return (1);
}
