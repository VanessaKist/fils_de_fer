/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_drawing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkist-si <vkist-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:08:29 by vkist-si          #+#    #+#             */
/*   Updated: 2022/09/17 21:36:12 by vkist-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf_header.h"

static void	low_slope(t_img *img, t_line *line)
{
	int	decisive;
	int	ppl;

	decisive = 0;
	ppl = 0;
	put_a_pixel(img, *line);
	decisive = (2 * line->dy) - line->dx;
	while (ppl < line->dx)
	{
		ppl++;
		line->x0 += line->sx;
		if (decisive < 0)
			decisive += (2 * line->dy);
		else
		{
			line->y0 += line->sy;
			decisive += ((2 * line->dy) - (2 * line->dx));
		}
		put_a_pixel(img, *line);
	}
}

static void	high_slope(t_img *img, t_line *line)
{
	int	decisive;
	int	ppl;

	decisive = 0;
	ppl = 0;
	put_a_pixel(img, *line);
	decisive = (2 * line->dx) - line->dy;
	while (ppl < line->dy)
	{
		ppl++;
		line->y0 += line->sy;
		if (decisive < 0)
			decisive += (2 * line->dx);
		else
		{
			line->x0 += line->sx;
			decisive += ((2 * line->dx) - (2 * line->dy));
		}
		put_a_pixel(img, *line);
	}
}

static void	set_line_angle(t_img *img, t_line *line)
{
	line->dx = (line->x1 - line->x0);
	if (line->dx > 0)
		line->sx = 1;
	else
		line->sx = -1;
	line->dx = abs(line->dx);
	line->dy = (line->y1 - line->y0);
	if (line->dy > 0)
		line->sy = 1;
	else
		line->sy = -1;
	line->dy = abs(line->dy);
	if (line->dx > line->dy)
		low_slope(img, line);
	else
		high_slope(img, line);
}

static void	set_points(t_line *line, t_data *data, int i, int j)
{
	if (j != data->map.cols - 1)
	{
		line->x0 = data->dot[i][j].x + data->key.travelx;
		line->y0 = data->dot[i][j].y + data->key.travely;
		line->color = data->dot[i][j].color;
		line->x1 = data->dot[i][j + 1].x + data->key.travelx;
		line->y1 = data->dot[i][j + 1].y + data->key.travely;
		set_line_angle(&data->img, line);
	}
	if (i != data->map.rows -1)
	{
		line->x0 = data->dot[i][j].x + data->key.travelx;
		line->y0 = data->dot[i][j].y + data->key.travely;
		line->color = data->dot[i][j].color;
		line->x1 = data->dot[i + 1][j].x + data->key.travelx;
		line->y1 = data->dot[i + 1][j].y + data->key.travely;
		set_line_angle(&data->img, line);
	}
}

void	bresenham_line_drawing(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.rows)
	{
		j = 0;
		while (j < data->map.cols)
		{
			set_points(&data->img.line, data, i, j);
			j++;
		}
		i++;
	}
}
