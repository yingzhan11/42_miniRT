/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:08:25 by likong            #+#    #+#             */
/*   Updated: 2024/12/31 12:22:09 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_aabb	box_sphere(t_sphere *sphere)
{
	t_vector	radius_vec;
	t_aabb		sphere_box;

	radius_vec = (t_vector){sphere->radius, sphere->radius, sphere->radius};
	sphere_box.min = vector_sub(sphere->center, radius_vec);
	sphere_box.max = vector_add(sphere->center, radius_vec);
	return (sphere_box);
}

t_aabb	box_cylinder(t_cylinder *cy)
{
	t_vector	radius_vec;
	t_vector	start;
	t_vector	end;
	t_aabb		cylinder_box;

	start = vector_sub(cy->center, vector_scale(cy->normal, cy->height * 0.5));
	end = vector_add(cy->center, vector_scale(cy->normal, cy->height * 0.5));
	radius_vec = (t_vector){cy->radius, cy->radius, cy->radius};
	cylinder_box.min = vector_sub(vector_min(start, end), radius_vec);
	cylinder_box.max = vector_add(vector_max(start, end), radius_vec);
	return (cylinder_box);
}