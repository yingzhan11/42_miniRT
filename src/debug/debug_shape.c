/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:11:39 by likong            #+#    #+#             */
/*   Updated: 2024/10/24 11:26:51 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	print_sphere(t_sphere sphere)
{
	printf("Sphere:\n");
	printf("  Center: %.2lf, %.2lf, %.2lf\n", \
		sphere.center.x, sphere.center.y, sphere.center.z);
	printf("  Radius: %.2lf\n", sphere.radius);
	printf("  Color:  %d, %d, %d\n", sphere.color.red,
		sphere.color.green, sphere.color.blue);
}

void	print_shape(t_shape *shape)
{
	printf("ID: %d\n", shape->id);
	if (shape->type == SPHERE)
		print_sphere(shape->data.sphere);
}

void	print_light(t_light *light)
{
	printf("Light coordinate: %1lf,%1lf,%1lf\n",
		light->coordinate.x, light->coordinate.y, light->coordinate.z);
	printf("Light brightness level: %1lf\n", light->brightness);
	printf("Light color: %d,%d,%d\n",
		light->color.red, light->color.green, light->color.blue);
}