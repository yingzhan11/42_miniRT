/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arg_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:12:41 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:13:31 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

//[0]A [1]brightness [2]color
bool	validate_ambient(char **arg)
{
	if (ft_matrix_size(arg) != 3)
		return (error("ambient: wrong number of args, [3]"), false);
	if (!check_arg_format(arg, "201"))
		return (error("ambient: invalid number arg format"), false);
	if (ft_atod(arg[1]) < 0.0 || ft_atod(arg[1]) > 1.0)
		return (error("ambient: wrong brightness ratio range, [0-1]"), false);
	if (!check_rgb(arg[2]))
		return (error("ambient: wrong color arg"), false);
	return (true);
}

//[0]C [1]Center [2]normal [3]FOV
bool	validate_camera(char **arg)
{
	if (ft_matrix_size(arg) != 4)
		return (error("camera: wrong number of args, [4]"), false);
	if (!check_arg_format(arg, "2110"))
		return (error("camera: number arg contains invalid char"), false);
	if (!ft_isnum(arg[3]))
		return (error("camera: FOV is not an int"), false);
	if (ft_atoi(arg[3]) <= 0 || ft_atoi(arg[3]) >= 180)
		return (error("camera: FOV is out of range, [0-180,!=]"), false);
	return (true);
}

//[0]L [1]center [2]brightness [3]color
bool	validate_light(char **arg)
{
	if (ft_matrix_size(arg) != 4)
		return (error("light: wrong args format"), false);
	if (!check_arg_format(arg, "2101"))
		return (error("light: number arg contains invalid char"), false);
	if (ft_atod(arg[2]) < 0.0 || ft_atod(arg[2]) > 1.0)
		return (error("light: wrong brightness ratio range"), false);
	if (!check_rgb(arg[3]))
		return (error("light: wrong color value"), false);
	return (true);
}
