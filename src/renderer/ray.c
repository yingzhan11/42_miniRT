/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:38:22 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/15 15:38:24 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Generate a ray starts from camera position to viewport point
 * Main steps:
 * 		1-calculate the viewport point offset to viewport original point,
 * 		2-map the viewport point to camera direction, relative coordinates,
 * 		3-add the viewport point to camera normalized coordinates
 * 		  to get the absolute position in 3D world,
 * 		4-set a normalized ray, start from camera
 * 		5-subtrat tmp by ray start point to get the vector from camera to
 * 		  viewport point, then normalized it to get its direction.
 * 
 * @param cur The normalized 3D coordinates of viewport point
 * @param horizontal The horizontal offset of current view point
 * @param vertical The vertival offset of current view point
 * @param tmp The tmp vector used in the operation
 * @param ray The ray from camera to view point
 */
t_ray make_ray(t_vector cur)
{
	t_vector horizontal;
	t_vector vertical;
	t_vector tmp;
	t_ray ray;

	horizontal = vector_multiple(s()->normal_w, cur.x * s()->view_w);
	vertical = vector_multiple(s()->normal_h, cur.y * s()->view_h);
	tmp = vector_add(vertical, horizontal);
	tmp = vector_add(tmp, s()->camera.normal);
	tmp = vector_add(tmp, s()->camera.coordinate);
	ray.start = s()->camera.coordinate;
	ray.normal = vector_normalize(vector_subtract(tmp, ray.start));
	return (ray);
}

/**
 * @brief Calculate a point along ray based on a given distance
 */
inline t_vector	point_on_ray(t_ray *ray, double distance)
{
	return (vector_add(ray->start, vector_multiple(ray->normal, distance)));
}