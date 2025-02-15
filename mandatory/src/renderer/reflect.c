/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:13:46 by likong            #+#    #+#             */
/*   Updated: 2025/01/30 14:08:54 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	diffuse(t_light *light, t_hit *inter, double brightness)
{
	t_vector	light_dir;
	t_color		color;
	double		cos_angle;
	double		diffuse_ratio;
	double		attenuation;

	light_dir = vector_sub(light->point, inter->hit_point);
	attenuation = fmin(1.0, 60.0 / vector_magnitude(light_dir));
	cos_angle = vector_cos(inter->hit_normal, light_dir);
	// if (cos_angle < 0.0 && inter->shape->type == PLANE)
	// 	cos_angle = -cos_angle;
	diffuse_ratio = fmax(0.0, brightness * cos_angle * attenuation);
	color = add_bright_to_color(inter->color, diffuse_ratio);
	color = mix_color(color, light->color);
	return (color);
}
