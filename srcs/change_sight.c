/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_sight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebouvi <tlebouvi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 01:35:55 by dabey             #+#    #+#             */
/*   Updated: 2023/05/26 15:19:21 by tlebouvi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3D.h"

void	change_sight_type_1(t_cub *cub, double *olddir_x, double *oldplane_x)
{
	*olddir_x = cub->rcast->dir_x;
	*oldplane_x = cub->rcast->plane_x;
	cub->rcast->dir_x = cub->rcast->dir_x * cos(1 * cub->rot_speed)
		- cub->rcast->dir_y * sin(1 * cub->rot_speed);
	cub->rcast->dir_y = *olddir_x * sin(1 * cub->rot_speed)
		+ cub->rcast->dir_y * cos(1 * cub->rot_speed);
	cub->rcast->plane_x = cub->rcast->plane_x * cos(1 * cub->rot_speed)
		- cub->rcast->plane_y * sin(1 * cub->rot_speed);
	cub->rcast->plane_y = *oldplane_x * sin(1 * cub->rot_speed)
		+ cub->rcast->plane_y * cos(1 * cub->rot_speed);
}

int	change_sight(t_cub *cub, int type)
{
	double	olddir_x;
	double	oldplane_x;

	if (type == 1)
		change_sight_type_1(cub, &olddir_x, &oldplane_x);
	else if (type == 2)
	{
		olddir_x = cub->rcast->dir_x;
		oldplane_x = cub->rcast->plane_x;
		cub->rcast->dir_x = cub->rcast->dir_x * cos(-1 * cub->rot_speed)
			- cub->rcast->dir_y * sin(-1 * cub->rot_speed);
		cub->rcast->dir_y = olddir_x * sin(-1 * cub->rot_speed)
			+ cub->rcast->dir_y * cos(-1 * cub->rot_speed);
		cub->rcast->plane_x = cub->rcast->plane_x * cos(-1 * cub->rot_speed)
			- cub->rcast->plane_y * sin(-1 * cub->rot_speed);
		cub->rcast->plane_y = oldplane_x * sin(-1 * cub->rot_speed)
			+ cub->rcast->plane_y * cos(-1 * cub->rot_speed);
	}
	cub->do_raycast = 1;
	return (1);
}
