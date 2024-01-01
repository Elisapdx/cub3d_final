/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:13:04 by epraduro          #+#    #+#             */
/*   Updated: 2024/01/01 16:31:36 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/cub3d_bonus.h"
#include "../inc/bonus/err_type_bonus.h"

t_mlx	ft_new_sprite(void *mlx, char *path)
{
	t_mlx	img;
	int		width;
	int		height;

	width = 12;
	height = 12;
	img.img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp,
			&img.line_len, &img.endian);
	return (img);
}

void	put_img_to_window(t_mlx *mlx, t_mlx image, int x, int y)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win,
		image.img, x, y);
}

void	load_img(t_config **conf)
{
	t_mlx	*mlx;

	mlx = (*conf)->mlx;
	(*conf)->data->door_c = ft_new_sprite(mlx->mlx, \
		"./src/bonus/minimap_bonus/door_close.xpm");
	(*conf)->data->floor = ft_new_sprite(mlx->mlx, \
		"./src/bonus/minimap_bonus/floor.xpm");
	(*conf)->data->door_o = ft_new_sprite(mlx->mlx, \
		"./src/bonus/minimap_bonus/door_open.xpm");
	(*conf)->data->wall = ft_new_sprite(mlx->mlx, \
		"./src/bonus/minimap_bonus/wall.xpm");
	(*conf)->data->tex_player = ft_new_sprite(mlx->mlx, \
		"./src/bonus/minimap_bonus/player.xpm");
	(*conf)->data->empty = ft_new_sprite(mlx->mlx, \
		"./src/bonus/minimap_bonus/void.xpm");
}

void	put_image_minmap(t_data *data, t_config **conf, int i, int j)
{
	if ((data->pos_mmap_y >= 0 && data->pos_mmap_x < (*conf)->map->map_len)
		&& (data->pos_mmap_x >= 0 && data->pos_mmap_y < \
			(int)ft_strlen((*conf)->map->sketch[(int)data->pos_mmap_x])))
	{
		if ((*conf)->map->sketch[(int)data->pos_mmap_x]
			[(int)data->pos_mmap_y] == '1')
			put_img_to_window((*conf)->mlx, data->wall, i * 12, j * 12);
		else if ((*conf)->map->sketch[(int)data->pos_mmap_x]
			[(int)data->pos_mmap_y] == '0')
			put_img_to_window((*conf)->mlx, data->floor, i * 12, j * 12);
		else if ((*conf)->map->sketch[(int)data->pos_mmap_x]
			[(int)data->pos_mmap_y] == '2')
			put_img_to_window((*conf)->mlx, data->door_c, i * 12, j * 12);
		else if ((*conf)->map->sketch[(int)data->pos_mmap_x] \
			[(int)data->pos_mmap_y] == '3')
			put_img_to_window((*conf)->mlx, data->door_o, i * 12, j * 12);
		else if (ft_strchr("NSWE", (*conf)->map->sketch[(int)data->pos_mmap_x] \
			[(int)data->pos_mmap_y]))
			put_img_to_window((*conf)->mlx, data->floor, i * 12, j * 12);
		else if ((*conf)->map->sketch[(int)data->pos_mmap_x] \
			[(int)data->pos_mmap_y] == ' ')
			put_img_to_window((*conf)->mlx, data->empty, i * 12, j * 12);
	}
	else
		put_img_to_window((*conf)->mlx, data->empty, i * 12, j * 12);
}

int	load_map(t_config **conf, t_mlx *mlx)
{
	int			i;
	int			j;
	t_player	*p;

	p = (*conf)->usr;
	(*conf)->data->pos_mmap_y = p->pos_y - (MID_MIMMAP - 1);
	i = -1;
	while (++i < SIZE_MINMAP)
	{
		j = -1;
		(*conf)->data->pos_mmap_x = p->pos_x - (MID_MIMMAP - 1);
		while (++j < SIZE_MINMAP)
		{
			put_image_minmap((*conf)->data, conf, i, j);
			(*conf)->data->pos_mmap_x++;
		}
		(*conf)->data->pos_mmap_y++;
	}
	put_img_to_window(mlx, (*conf)->data->tex_player, \
		(MID_MIMMAP - 1) * 12, (MID_MIMMAP - 1) * 12);
	return (SUCCESS);
}
