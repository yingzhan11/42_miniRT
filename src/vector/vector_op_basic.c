/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op_basic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:34:35 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/13 16:34:38 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//add, subtract, negat, multiple, divide

inline t_vector		vector_add(t_vector v1, t_vector v2)
{
	return (new_vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

inline t_vector		vector_subtract(t_vector v1, t_vector v2)
{
	return (new_vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

inline t_vector	vector_multiple(t_vector v1, double scalar)
{
	return (new_vector(v1.x * scalar, v1.y * scalar, v1.z * scalar));
}