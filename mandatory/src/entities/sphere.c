/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:50:15 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 11:43:53 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	new_sphere(char **arg, t_sphere *sphere)
{
	char	**tmp;

	tmp = ft_split(arg[1], ',');
	if (!tmp)
		return (error("sphere: fail to split coordinate"), false);
	sphere->center = parse_vector(tmp);
	free_matrix(tmp);
	sphere->radius = ft_atod(arg[2]) * 0.5;
	if (sphere->radius < 1e-8)
		return (error("sphere: wrong diameter value"), false);
	tmp = ft_split(arg[3], ',');
	if (!tmp)
		return (error("sphere: fail to split color"), false);
	sphere->color = parse_color(tmp);
	free_matrix(tmp);
	return (true);
}

bool	parse_sphere(char **arg, t_fclass *fclass)
{
	t_shape		*shape;
	t_sphere	sphere;

	if (ft_matrix_size(arg) != 4 || !check_arg_format(arg, "2101"))
		return (error("sphere: wrong args format"), false);
	if (ft_atod(arg[2]) * 0.5 < 1e-8)
		return (error("sphere: wrong radius value"), false);
	if (!check_rgb(arg[3]))
		return (error("sphere: wrong color value"), false);
	if (!new_sphere(arg, &sphere))
		return (error("sphere: fail to create new shpere"), false);
	shape = new_shape(&sphere, SPHERE, fclass->size, s()->shape_nbr[SPHERE]);
	if (!shape)
		return (error("sphere: fail to create new shape"), false);
	s()->shape_nbr[SPHERE]++;
	push_to_fclass(fclass, shape);
	return (true);
}

/**
 * @brief If the distance between center point and a point is equal to radius
 * means the point is on the sphere
 * A ray in 3d space is represented as: R(t) = O + tD
 *		O is origin of the ray, D is direction
 * 		t is a scalar parameter the determins a specific point along the ray
 * A sphere is:	(x − Cx)^2 + (y − Cy)^2 + (z − Cz)^2 = r^2
 * 		C is the center of sphere, x, y, z is a point on the sphere
 * If a ray is intersects with a sphere, substitue ray equation 
 * into the sphere equation: ((O + tD) - C)^2 = r^2
 * Simplify this equation is:
 * 		((O-C) + tD) * ((O-C) + tD) = r^2
 * 		(O−C)*(O−C) + 2t*D*(O−C) + t^2*D*D = r^2
 * 		t^2(D*D) + 2t(D*(O-C)) + ((O-C)*(O-C)-r^2) = 0
 * So at^2 + bt + c = 0
 * 		a = D*D = dot(ray.normal)
 * 		b = 2*(D*(O-C)) = 2 * ray.normal * (ray.start - sphere.center)
 * 		c = dot(ray.start - sphere.center) - radius^2
 * 			and if c < 0, the ray origin is inside the sphere
 * 				if c = 0, the ray origin in on the sphere
 * 				if c > 0, the ray origin in outside the sphere
 * @param equation equation structure
 * @param vec the vector from ray origin to sphere center point
 */
bool	inter_sphere(t_sphere *sphere, t_ray *ray, t_hit *hit)
{
	t_equation	equation;
	t_vector	vec;

	vec = vector_sub(ray->start, sphere->center);
	equation.a = vector_dot(ray->normal, ray->normal);
	equation.b = 2.0f * vector_dot(vec, ray->normal);
	equation.c = vector_dot(vec, vec) - pow(sphere->radius, 2);
	equation.t1 = -1;
	equation.t2 = -1;
	if (solve(&equation) != -1 && (equation.t1 > 1e-8 || equation.t2 > 1e-8))
	{
		if (equation.t1 > 1e-8)
			hit->distance = equation.t1;
		else
			hit->distance = equation.t2;
		hit->color = sphere->color;
		find_valid_t(&equation);
		return (equation.t1 > 1e-8);
	}
	return (false);
}

void	move_sphere(t_key *keys, t_sphere *sphere)
{
	if (keys->key[D])
		sphere->center.x += 0.3;
	else if (keys->key[A])
		sphere->center.x -= 0.3;
	else if (keys->key[W])
		sphere->center.y += 0.3;
	else if (keys->key[S])
		sphere->center.y -= 0.3;
	else if (keys->key[E])
		sphere->center.z += 0.3;
	else if (keys->key[Q])
		sphere->center.z -= 0.3;
}

void	scaling_sphere(t_key *keys, t_sphere *sphere)
{
	if (keys->cur_keycode == LEFT && sphere->radius - 0.1 > 0)
		sphere->radius -= 0.1;
	else if (keys->cur_keycode == RIGHT)
		sphere->radius += 0.1;
}
