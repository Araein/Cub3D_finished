/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:40:42 by tlebouvi          #+#    #+#             */
/*   Updated: 2023/05/30 17:36:36 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/cub3D_bonus.h"

void	destroy_images(t_data *img[5], void *mlx_ptr)
{
	if (!mlx_ptr || !img || !*img)
		return ;
	if (img[1]->img != NULL)
	{
		mlx_destroy_image(mlx_ptr, img[1]->img);
		img[1]->img = NULL;
	}
	if (img[2]->img != NULL)
	{
		mlx_destroy_image(mlx_ptr, img[2]->img);
		img[2]->img = NULL;
	}
	if (img[3]->img != NULL)
	{
		mlx_destroy_image(mlx_ptr, img[3]->img);
		img[3]->img = NULL;
	}
	if (img[4]->img != NULL)
	{
		mlx_destroy_image(mlx_ptr, img[4]->img);
		img[4]->img = NULL;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
	}
	tab = NULL;
}

void	free_map(t_map *map)
{
	if (map->no_input)
		free(map->no_input);
	if (map->so_input)
		free(map->so_input);
	if (map->we_input)
		free(map->we_input);
	if (map->ea_input)
		free(map->ea_input);
	if (map->f_input)
		free(map->f_input);
	if (map->c_input)
		free(map->c_input);
	free_tab(map->map);
}
