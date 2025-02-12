

#include "miniRT_bonus.h"

static bool	new_plane(char **arg, t_plane *plane)
{
	char	**tmp;

	tmp = ft_split(arg[1], ',');
	if (!tmp)
		return (ERROR("plane: fail to split coordinate"), false);
	plane->center = parse_vector(tmp);
	free_matrix(tmp);
	tmp = ft_split(arg[2], ',');
	if (!tmp)
		return (ERROR("plane: fail to split normal"), false);
	plane->normal = parse_vector(tmp);
	if (vector_magnitude(plane->normal) < 1.0 - 1e-8)
		return (ERROR("plane: normal vector is too small"), false);
	plane->normal = vector_add(plane->normal, VEC_MIN);
	plane->normal = vector_normalize(plane->normal);
	free_matrix(tmp);
	tmp = ft_split(arg[3], ',');
	if (!tmp)
		return (ERROR("plane: fail to split color"), false);
	plane->color = parse_color(tmp);
	free_matrix(tmp);
	return (true);
}

bool	parse_plane(char **arg, t_fclass *fclass)
{
	t_shape	*shape;
	t_plane	plane;

	// if (ft_matrix_size(arg) < 7 || !check_syntax(arg, "011100"))
	// 	return (ERROR("plane: wrong args format"), false);
	// if (!check_rgb(arg[3]))
	// 	return (ERROR("plane: wrong color value"), false);
	if (!new_plane(arg, &plane))
		return (ERROR("plane: fail to create new plane"), false);
	shape = new_shape(&plane, PLANE, fclass->size, s()->shape_nbr[PLANE]);
	check_texture(arg, shape);
	shape->ks = ft_atod(arg[4]);
	shape->shininess = ft_atod(arg[5]);
	shape->refra_idx = ft_atod(arg[9]);
	shape->transparency = ft_atod(arg[10]);
	// if (shape->ks < 0 || shape->ks > 1)
	// 	return (ERROR("plane: wrong ks value"), false);
	// if (shape->shininess < 1 || shape->shininess > 128)
	// 	return (ERROR("plane: wrong shininess value"), false);
	// printf("ks %f, shininess %f\n", shape->ks, shape->shininess);
	s()->shape_nbr[PLANE]++;
	add_uv_axis(shape, shape->data.plane.normal);
	push_to_fclass(fclass, shape);
	return (true);
}


void	move_plane(t_key *keys, t_plane *plane)
{
	if (keys->key[D])
		plane->center.x += 0.3;
	else if (keys->key[A])
		plane->center.x -= 0.3;
	else if (keys->key[W])
		plane->center.y += 0.3;
	else if (keys->key[S])
		plane->center.y -= 0.3;
	else if (keys->key[E])
		plane->center.z += 0.3;
	else if (keys->key[Q])
		plane->center.z -= 0.3;
	printf("move plane\n");
}

void	rotate_plane(t_key *keys, t_plane *plane)
{
	if (keys->key[I])
		plane->normal = vector_rotate(plane->normal, X, ROTATE);
	else if (keys->key[K])
		plane->normal = vector_rotate(plane->normal, X, (-ROTATE));
	else if (keys->key[J])
		plane->normal = vector_rotate(plane->normal, Y, ROTATE);
	else if (keys->key[L])
		plane->normal = vector_rotate(plane->normal, Y, (-ROTATE));
	else if (keys->key[U])
		plane->normal = vector_rotate(plane->normal, Z, ROTATE);
	else if (keys->key[O])
		plane->normal = vector_rotate(plane->normal, Z, (-ROTATE));
	printf("rotate plane\n");
}

// bool	inter_real_plane(t_plane *plane, t_ray *ray, double *valid_t)
// {
// 	double		numerator;
// 	double		denominator;
// 	t_vector	vec;

// 	denominator = vector_dot(ray->normal, plane->normal);
// 	if (fabs(denominator) < 1e-6)
// 		return (false);
// 	vec = vector_sub(plane->center, ray->start);
// 	numerator = vector_dot(vec, plane->normal);
// 	*valid_t = numerator / denominator;
// 	return (*valid_t > 0.0);
// }
