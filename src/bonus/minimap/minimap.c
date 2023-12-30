#include "cub3d.h"
#include "parse_err.h"

t_vars	ft_new_sprite(void *mlx, char *path)
{
	t_vars	img;
	int width;
	int height;

	width = 12;
	height = 12;
	img.img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp,
			&img.line_len, &img.endian);
	return (img);
}

void	put_img_to_window(t_vars *vars, t_vars image, int x, int y)
{
	mlx_put_image_to_window(vars->mlx, vars->win,
		image.img, x, y);
}

void	load_img(t_config **conf)
{
	t_vars *mlx;

	mlx = (*conf)->mlx;
	(*conf)->floor = ft_new_sprite(mlx->mlx, "./src/minimap/floor.xpm");
	(*conf)->door_c = ft_new_sprite(mlx->mlx, "./src/minimap/door_close.xpm");
	(*conf)->door_o = ft_new_sprite(mlx->mlx, "./src/minimap/door_open.xpm");
	(*conf)->wall = ft_new_sprite(mlx->mlx, "./src/minimap/wall.xpm");
	(*conf)->tex_player = ft_new_sprite(mlx->mlx, "./src/minimap/player.xpm");
	(*conf)->empty = ft_new_sprite(mlx->mlx, "./src/minimap/void.xpm");
}

void	put_image_minmap(t_config **conf, t_vars *vars, int i, int j)
{
	if (((*conf)->pos_mmap_y >= 0 && (*conf)->pos_mmap_x < (*conf)->map_len)
		&& ((*conf)->pos_mmap_x >= 0
			&& (*conf)->pos_mmap_y < (int) ft_strlen((*conf)->map[(int)(*conf)->pos_mmap_x])))
	{
		if ((*conf)->map[(int)(*conf)->pos_mmap_x][(int)(*conf)->pos_mmap_y] == '1')
			put_img_to_window(vars, (*conf)->wall, i * 12, j * 12);
		else if ((*conf)->map[(int)(*conf)->pos_mmap_x][(int)(*conf)->pos_mmap_y] == '0')
			put_img_to_window(vars, (*conf)->floor, i * 12, j * 12);
		else if ((*conf)->map[(int)(*conf)->pos_mmap_x][(int)(*conf)->pos_mmap_y] == '2')
			put_img_to_window(vars, (*conf)->door_c, i * 12, j * 12);
		else if ((*conf)->map[(int)(*conf)->pos_mmap_x][(int)(*conf)->pos_mmap_y] == '3')
			put_img_to_window(vars, (*conf)->door_o, i * 12, j * 12);
		else if (ft_strchr("NSWE", (*conf)->map[(int)(*conf)->pos_mmap_x][(int)(*conf)->pos_mmap_y]))
			put_img_to_window(vars, (*conf)->floor, i * 12, j * 12);
		else if ((*conf)->map[(int)(*conf)->pos_mmap_x][(int)(*conf)->pos_mmap_y] == ' ')
			put_img_to_window(vars, (*conf)->empty, i * 12, j * 12);
	}
	else
		put_img_to_window(vars, (*conf)->empty, i * 12, j * 12);
}

int	load_map(t_config **conf, t_vars *vars)
{
	int	i;
	int	j;
	t_player *p;

	p = (*conf)->character;
	(*conf)->pos_mmap_y = p->pos_y - (MID_MIMMAP - 1);
	i = -1;
	while (++i < SIZE_MINMAP)
	{
		j = -1;
		(*conf)->pos_mmap_x =p->pos_x - (MID_MIMMAP - 1);
		while (++j < SIZE_MINMAP)
		{
			put_image_minmap(conf, vars, i, j);
			(*conf)->pos_mmap_x++;
		}
		(*conf)->pos_mmap_y++;
	}
	put_img_to_window(vars, (*conf)->tex_player, (MID_MIMMAP - 1) * 12, (MID_MIMMAP - 1) * 12);
	return (SUCCES);
}
