/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:35:15 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/17 11:47:41 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief 2D screen coordinates(x, y) into normalized 3D coordinates(x, y, z),
 * to centers the viewport at (0, 0).
 * And maps the screen dimensions to a range of [-1, 1] range for both x and y.
 * The range from -1 to 1 is 2, calculate the (x, y) relative position on screen,
 * and multipe coordinate with 2.0f to mapping coordinate to a range [0, 2],
 * then:
 * 		x = 0 ---> x = -1, the left edge of screen
 * 		x = WIDTH ---> x = 1, the right edge of screen
 * 		x = WIDTH / 2 ---> x = 0, the center of screen
 */
static t_vector	convert_viewport(double x, double y)
{
	t_vector	converted;

	converted.x = ((x * s()->view_invw) * 2.0f) - 1;
	converted.y = ((y * s()->view_invh) * 2.0f) - 1;
	converted.z = 0;
	return (converted);
}

static void	put_pixel(t_color c, int x, int y)
{
	char	*dst;

	dst = s()->win.addr + (y * (int)WIDTH + x) * (int)(s()->win.bpp * 0.125);
	*(unsigned int *)dst = (c.alpha << 24 | c.red << 16
			| c.green << 8 | c.blue);
}

/**
 * @brief Function to render the shapes and lights
 * Main steps:
 * 		1-convert 2D screen coodinates to 3D, 
 * 		2-make a ray from carema to viewpoint,
 * 		3-find the intersected point,
 * 		TODO 4-update the color and shadow of the closest intersected point
 * 		5-print the color on sreen.
 * 
 * @param cur The current 2D coordinates on screen
 * @param converted_cur The 3D coordinates converted from 2D cur
 * @param closest The closest intersect point
 * @param ray The ray from camera direct to current viewpoint
 */
void	render(void)
{
	t_vector	cur;
	t_vector	converted_cur;
	t_hit		closest;
	t_ray		ray;

	cur.y = -1;
	while (++cur.y < HEIGHT)
	{
		cur.x = -1;
		while (++cur.x < WIDTH)
		{
			closest = init_hit();
			converted_cur = convert_viewport(cur.x, cur.y);
			ray = make_ray(converted_cur);
			if (check_intersection(s()->shapes, &ray, &closest))
				check_illumination(&closest);
			put_pixel(closest.color, cur.x, cur.y);
		}
	}
	mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.img, 0, 0);
	display_menu();
}

void	fake_render(void)
{
	t_vector	cur;
	t_vector	converted_cur;
	t_hit		closest;
	t_ray		ray;

	cur.y = 0;
	while (cur.y < HEIGHT)
	{
		cur.x = 0;
		while (cur.x < WIDTH)
		{
			closest = init_hit();
			converted_cur = convert_viewport(cur.x, cur.y);
			ray = make_ray(converted_cur);
			if (check_intersection(s()->shapes, &ray, &closest))
				check_illumination(&closest);
			put_pixel(closest.color, cur.x, cur.y);
			cur.x += 3;
		}
		cur.y += 3;
	}
	mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.img, 0, 0);
	display_menu();
}
