/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:24:37 by likong            #+#    #+#             */
/*   Updated: 2024/10/29 08:59:13 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	delete_fclass(t_fclass *fclass)
{
	if (!fclass)
		return ;
	free_matrix((char **)fclass->array);
	free(fclass);
}



void	nc_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	delete_scene()
{
	delete_fclass(s()->light);
	delete_fclass(s()->shapes);
	free_matrix(s()->args);
	// if (s()->win.img)
	// 	mlx_delete_image(s()->win.mlx, s()->win.img);
	// if (s()->win.mlx)
	// 	mlx_terminate(s()->win.mlx);
	if (s()->win.img)
		mlx_destroy_image(s()->win.mlx, s()->win.img);
	if (s()->win.disp)
		mlx_destroy_window(s()->win.mlx, s()->win.disp);
	if (s()->win.mlx)
		mlx_destroy_display(s()->win.mlx);
	nc_free(s()->win.mlx);
}

void	error_exit(char *message)
{
	delete_scene();
	printf("Error: %s\n", message);
	exit(FAILURE);
}
