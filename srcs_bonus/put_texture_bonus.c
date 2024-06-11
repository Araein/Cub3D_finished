/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabey <dabey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:00:37 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/06/01 19:20:57 by dabey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3D_bonus.h"

int	convert_images(t_cub *cub)
{
	int	pos;

	pos = 128;
	cub->img[0]->img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->img[1]->img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->map->ea_input, &pos, &pos);
	if (cub->img[1]->img == NULL)
		return (-1);
	cub->img[2]->img = mlx_xpm_file_to_image (cub->mlx_ptr,
			cub->map->no_input, &pos, &pos);
	if (cub->img[2]->img == NULL)
		return (destroy_images(cub->img, cub->mlx_ptr), -1);
	cub->img[3]->img = mlx_xpm_file_to_image (cub->mlx_ptr,
			cub->map->we_input, &pos, &pos);
	if (cub->img[3]->img == NULL)
		return (destroy_images(cub->img, cub->mlx_ptr), -1);
	cub->img[4]->img = mlx_xpm_file_to_image (cub->mlx_ptr,
			cub->map->so_input, &pos, &pos);
	if (cub->img[4]->img == NULL)
		return (destroy_images(cub->img, cub->mlx_ptr), -1);
	return (1);
}

int	create_images(t_cub *cub)
{
	int	i;

	if (cub->img[0]->img != NULL)
	{
		mlx_destroy_image(cub->mlx_ptr, cub->img[0]->img);
		cub->img[0]->img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	}
	else
	{
		if (convert_images(cub) == -1)
			return (shutwindow(cub), -1);
		i = 0;
		while (i < 5)
		{
			cub->img[i]->addr = mlx_get_data_addr(cub->img[i]->img,
					&cub->img[i]->bits_per_pixel, &cub->img[i]->line_length,
					&cub->img[i]->endian);
			i++;
		}
	}
	return (1);
}

void	raycast(t_cub *cub)
{
	int	tempo_x;

	tempo_x = WIDTH - 1;
	cub->rcast->x = 0;
	cub->rcast->hit = 0;
	while (cub->rcast->x < WIDTH)
	{
		raycast_start(cub);
		raycast_launch_ray(cub);
		raycast_ray_hit(cub);
		raycast_end(cub);
		while (cub->rcast->drawstart <= cub->rcast->drawend)
			raycast_draw(tempo_x, cub);
		cub->rcast->x++;
		tempo_x--;
	}
}

int	put_texture(t_cub *cub)
{
	if (cub->do_raycast == 1)
	{
		create_images(cub);
		draw_floor_and_ceiling(cub);
		if (cub->do_raycast == 1)
		{
			raycast(cub);
			if ((HEIGHT > 100 || WIDTH > 100) && cub && cub->map
				&& cub->map->map)
				draw(cub, 0, 0);
		}
		cub->do_raycast = 0;
		mlx_put_image_to_window (cub->mlx_ptr, cub->window_ptr,
			cub->img[0]->img, 0, 0);
	}
	return (1);
}

char	*cut_texture(char *string)
{
	char	*tempo;
	int		i;
	int		len;

	if (string)
	{
		len = ft_strlen(string);
		i = 2;
		while (string[i] == ' ')
			i++;
		while (string[len - 1] == ' ')
			len--;
		if (i <= 2)
			return (NULL);
		tempo = ft_substr(string, i, len - i);
		free(string);
		return (tempo);
	}
	else
		return (NULL);
}
