/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_preset_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:32:47 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:32:50 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static t_vector	camera_position(t_vector min, t_vector max, int preset)
{
	t_vector	vec;
	double		diagonal;
	double		camera_distance;

	ft_bzero(&vec, sizeof(t_vector));
	vec.x = (min.x + max.x) / 2;
	vec.y = (min.y + max.y) / 2;
	vec.z = (min.z + max.z) / 2;
	diagonal = sqrt(pow(max.x - min.x, 2) + pow(max.y - min.y, 2)
			+ pow(max.z - min.z, 2));
	camera_distance = (diagonal / 2) / tan(RADIAN(45) / 2.0);
	camera_distance += diagonal * 0.2;
	if (preset == 1)
		vec.z = min.z - camera_distance;
	else if (preset == 2)
		vec.z = max.z + camera_distance;
	else if (preset == 3)
		vec.y = max.y + camera_distance;
	else if (preset == 4)
		vec.y = min.y - camera_distance;
	else if (preset == 5)
		vec.x = min.x - camera_distance;
	else if (preset == 6)
		vec.x = max.x + camera_distance;
	return ((t_vector){vec.x, vec.y, vec.z});
}

void	camera_preset(int preset)
{
	t_camera	new_camera;

	new_camera = copy_camera(s()->camera);
	new_camera.coordinate = camera_position(s()->bvh->box.min,
			s()->bvh->box.max, preset);
	if (preset == 1)
		new_camera.normal = vector_normalize(vector_add(C_FRONT, VEC_MIN));
	else if (preset == 2)
		new_camera.normal = vector_normalize(vector_add(C_BACK, VEC_MIN));
	else if (preset == 3)
		new_camera.normal = vector_normalize(vector_add(C_TOP, VEC_MIN));
	else if (preset == 4)
		new_camera.normal = vector_normalize(vector_add(C_BOTTOM, VEC_MIN));
	else if (preset == 5)
		new_camera.normal = vector_normalize(vector_add(C_LEFT, VEC_MIN));
	else if (preset == 6)
		new_camera.normal = vector_normalize(vector_add(C_RIGHT, VEC_MIN));
	new_camera.fov = 45;
	s()->camera = copy_camera(new_camera);
	init_viewport();
}
