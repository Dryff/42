/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:12:33 by colas             #+#    #+#             */
/*   Updated: 2023/01/09 15:50:13 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	assign_pos(t_pos *pos, t_data fdf, float x1, float y1)
{
	pos->z = fdf.map.line[pos->tab_y].arr[pos->tab_x] * 10;
	pos->z1 = fdf.map.line[(int)y1].arr[(int)x1] * 10;
	pos->x = pos->tab_x;
	pos->y = pos->tab_y;
	pos->x *= fdf.xy_scale;
	pos->y *= fdf.xy_scale;
}

void	bresenham(t_pos pos, float x1, float y1, t_data fdf)
{
	float	x_step;
	float	y_step;
	int		max;

	assign_pos(&pos, fdf, x1, y1);
	x1 *= fdf.xy_scale;
	y1 *= fdf.xy_scale;
	render_isometric(&pos.x, &pos.y, pos.z);
	render_isometric(&x1, &y1, pos.z1);
	x_step = x1 - pos.x;
	y_step = y1 - pos.y;
	max = fmax(fabs(x_step), fabs(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(pos.x - x1) || (int)(pos.y - y1))
	{
		my_mlx_pixel_put(&fdf, (int)pos.x + fdf.offsetx, \
		(int)pos.y + fdf.offsety, 0xFF00FF);
		pos.x += x_step;
		pos.y += y_step;
	}
}

void	draw_lines(t_data fdf)
{
	t_pos	pos;
	int		x;
	int		y;

	y = 0;
	pos.tab_y = 0;
	while (y < fdf.map.row_nbr)
	{
		x = 0;
		pos.tab_x = 0;
		while (x < fdf.map.line[y].size)
		{		
			if (x < fdf.map.line[y].size - 1)
				bresenham(pos, x + 1, y, fdf);
			if (y < fdf.map.row_nbr - 1)
				bresenham(pos, x, y + 1, fdf);
			x++;
			pos.tab_x = x;
		}
		y++;
		pos.tab_y = y;
	}
}

void	mlx_draw(t_map map)
{
	t_data	fdf;

	fdf.offsetx = 570;
	fdf.offsety = 200;
	fdf.xy_scale = 10;
	fdf.mlx = mlx_init();
	fdf.mlx_win = mlx_new_window(fdf.mlx, 1200, 675, "SynthWave");
	fdf.img = mlx_new_image(fdf.mlx, 1200, 675);
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bits_per_pixel, \
	&fdf.line_length, &fdf.endian);
	fdf.map = map;
	mlx_hook(fdf.mlx_win, 2, 1L << 0, get_keys, &fdf);
	mlx_hook(fdf.mlx_win, 17, 0, ft_close, &fdf);
	draw_lines(fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.mlx_win, fdf.img, 0, 0);
	mlx_loop(fdf.mlx);
}
