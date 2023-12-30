#include "../inc_bonus/cub3d_bonus.h"
#include "../inc_bonus/parse_err_bonus.h"
#include "../inc_bonus/mlx_win_bonus.h"

/*
* 1. ce calcul permet de placer chaque colonne de l'ecran dans l'intervalle -1 à 1. 
* -> qui donc représente la perspective linéaire de gauche à droite.
* 2. ces calculs permette d'ajuster la direction du rayon en fonction de la postion
* -> sur l'ecran. Donc en fonction de cam_x les variables plane_x et plane_y 
* -> introduisent la perspective horizontale.
* 3. represente la case de la map dans lequel le ray se trouve.
* 4. deltaX et deltaY sont des variables que le rayon doit parcourir pour passer
* -> d'un côté x à l'autre ou d'un côté y à l'autre.
*/
void	init_ray_dir(t_ray *ray, t_player *character, int x)
{
	ray->cam_x = 2 * x / (double)WIDTH - 1;
	ray->ray_x = character->dir_x + character->plane_x * ray->cam_x;
	ray->ray_y = character->dir_y + character->plane_y * ray->cam_x;
	ray->map_x = (int)character->pos_x;
	ray->map_y = (int)character->pos_y;
	if (ray->ray_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = ft_abs(1 / ray->ray_x);
	if (ray->ray_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = ft_abs(1 / ray->ray_y);
}

void	define_ray_dir(t_ray *ray, t_player *character)
{
	if (ray->ray_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (character->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - character->pos_x) * ray->delta_x;
	}
	if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (character->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - character->pos_y) * ray->delta_y;
	}
}

void	start_dda_algo(char **map, t_ray *ray)
{
	bool	wall_hit;

	ray->door_hit = false;
	wall_hit = false;
	while (wall_hit != true)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = false;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = true;
		}
		if (map[ray->map_x][ray->map_y] == '1' \
			|| map[ray->map_x][ray->map_y] == '2')
			wall_hit = true;
		if (map[ray->map_x][ray->map_y] == '2')
			ray->door_hit = true;
	}
}

void	get_wall_height(t_ray *ray)
{
	if (ray->side == false)
		ray->wall_dist = ray->side_dist_x - ray->delta_x;
	else
		ray->wall_dist = ray->side_dist_y - ray->delta_y;
	ray->line_height = (int)(HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	fill_colors(char **color_table, int *to_fill)
{
	int	i;

	i = 0;
	while (color_table[i] && i < 3)
	{
		to_fill[i] = ft_atoi(color_table[i]);
		i++;
	}
}

/*
1. commence a dessiner le ciel a partir de 0 jusqua le debut du mur
2. ensuite dessine le sol parce que on s'en fou, on retrace le mur par dessus.
*/
void	draw_floor_sky(t_config **conf, int draw_start, int x)
{
	// int x;
	// int middle;
	// middle = WIDTH * HEIGHT / 2 - 1; // indice du pixel au milieu de la hauteur totale de la fenêtre à la dernière colonne
	// x = HEIGHT * WIDTH - 1; // indice du dernier élément dans un tableau stockes par colonnes
	int	color_c;
	int	color_f;
	int	i;
	int	ceiling[3];
	int	floor[3];

	fill_colors((*conf)->c_color, ceiling);
	fill_colors((*conf)->f_color, floor);
	i = 0;
	color_c = create_trgb(0, ceiling[0], ceiling[1], ceiling[2]);
	color_f = create_trgb(0, floor[0], floor[1], floor[2]);
	while (i < HEIGHT)
	{
		if (i <= draw_start)
			my_mlx_pixel_put((*conf)->mlx, x, i, color_c);
		else
			my_mlx_pixel_put((*conf)->mlx, x, i, color_f);
		i++;
	}
}

int	find_orientation(t_ray *ray, t_player *p)
{
	// regarder si le rayon correspond a un mur sur le cote droit
	if (ray->door_hit == true)
		return (DOOR);
	if (ray->side == true && p->pos_y < ray->map_y)
		return (EAST);
	else if (ray->side == true && p->pos_y > ray->map_y)
		return (WEST);
	else if (ray->side == false && p->pos_x > ray->map_x)
		return (NORTH);
	else if (ray->side == false && p->pos_x < ray->map_x)
		return (SOUTH);
	return (FAILS);
}

/*
* apply the correct pixel color from the texture
*/
void	apply_texture(t_config **conf, int dir, int x, int y)
{
	int		color;
	t_ray	*r;

	color = 0;
	r = (*conf)->ray;
	if (dir == DOOR)
		color = get_pixel_color(&(*conf)->text[DOOR], r->tex_x, r->tex_y);
	else if (dir == NORTH)
		color = get_pixel_color(&(*conf)->text[NORTH], r->tex_x, r->tex_y);
	else if (dir == SOUTH)
		color = get_pixel_color(&(*conf)->text[SOUTH], r->tex_x, r->tex_y);
	else if (dir == EAST)
		color = get_pixel_color(&(*conf)->text[EAST], r->tex_x, r->tex_y);
	else if (dir == WEST)
		color = get_pixel_color(&(*conf)->text[WEST], r->tex_x, r->tex_y);
	my_mlx_pixel_put((*conf)->mlx, x, y, color);
}

int	draw_walls(t_config **conf, t_ray *ray, int x)
{
	int	dir;
	// printf("draw_start avant la boucle: %d\ndraw_end: %d\n", i, ray->draw_end);
	draw_floor_sky(conf, ray->draw_start, x);
	while (ray->draw_start < ray->draw_end)
	{
		ray->tex_y = (int)ray->text_pos & (TEXTURE_H - 1);
		ray->text_pos += ray->step_text;
		dir = find_orientation(ray, (*conf)->character);
		if (dir == FAILS)
			return (ft_putendl_fd("Error\n", STDERR_FILENO));
		apply_texture(conf, dir, x, ray->draw_start);
		ray->draw_start++;
	}
	return (0);
}

void	find_texture_size(t_ray *ray, t_player *p)
{
	if (ray->side == true)
		ray->wall_hit = p->pos_x + ray->wall_dist * ray->ray_x;
	else
		ray->wall_hit = p->pos_y + ray->wall_dist * ray->ray_y;
	ray->wall_hit -= floor(ray->wall_hit);
	ray->tex_x = ray->wall_hit * TEXTURE_W;
	if ((ray->side == false && ray->ray_x > 0) \
		|| (ray->side == true && ray->ray_y < 0))
		ray->tex_x = TEXTURE_W - ray->tex_x - 1;
	ray->step_text = 1.0 * TEXTURE_H / ray->line_height;
	ray->text_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) \
		* ray->step_text;
}

int	render_game(t_config **conf, t_ray *ray, t_player *character)
{
	t_vars	*mlx;
	int	x;

	x = 0;
	mlx = (*conf)->mlx;
	//printf("pos_x: %f\npos_y: %f\n", (*conf)->character->pos_x, (*conf)->character->pos_y);
	//* itere sur l'entièreté de la fenetre.
	while (x < WIDTH)
	{
		init_ray_dir(ray, character, x);
		define_ray_dir(ray, character);
		start_dda_algo((*conf)->map, ray);
		get_wall_height(ray);
		find_texture_size(ray, character);
		if (draw_walls(conf, ray, x) == FAILS)
			return (FAILS);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}

void	init_ray_struct(t_ray *ray)
{
	ray->cam_x = 0;
	ray->ray_x = 0;
	ray->ray_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side = false;
	ray->door_hit = false;
	ray->wall_dist = 0;
	ray->line_height = 0;
	ray->draw_end = 0;
	ray->draw_start = 0;
}

void	do_move(t_config **conf, double new_x, double new_y)
{
	char		**map;
	t_player	*p;

	map = (*conf)->map;
	p = (*conf)->character;
	if (map[(int)(p->pos_x + new_x * (MOVE_SPEED + 0.1))][(int)(p->pos_y)] != '1' \
		&& map[(int)(p->pos_x + new_x * (MOVE_SPEED + 0.1))][(int)(p->pos_y)] != '2')
		p->pos_x += new_x * MOVE_SPEED;
	if (map[(int)(p->pos_x)][(int)(p->pos_y + new_y * (MOVE_SPEED + 0.1))] != '1' \
		&& map[(int)(p->pos_x)][(int)(p->pos_y + new_y * (MOVE_SPEED + 0.1))] != '2')
		p->pos_y += new_y * MOVE_SPEED;
}

/*
* DROITE
* do_move(map, p, p->plane_x * MOVE_SPEED, p->plane_y * MOVE_SPEED);
* GAUCHE
* do_move(map, p, -p->plane_x * MOVE_SPEED, -p->plane_y * MOVE_SPEED);
*/
void	move_keys(t_config **conf, int key_pressed)
{
	t_player	*p;

	p = (*conf)->character;
	if (key_pressed == W_KEY)
		do_move(conf, p->dir_x, p->dir_y);
	else if (key_pressed == S_KEY)
		do_move(conf, -p->dir_x, -p->dir_y);
	else if (key_pressed == A_KEY)
		do_move(conf, -p->dir_y, p->dir_x);
	else if (key_pressed == D_KEY)
		do_move(conf, p->dir_y, -p->dir_x);
}

void	rotate_keys(t_config **conf, int key_pressed)
{
	t_player	*p;

	p = (*conf)->character;
	if (key_pressed == RIGHT_KEY)
	{
		p->old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
		p->dir_y = p->old_dir_x * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
		p->old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y * sin(-ROT_SPEED);
		p->plane_y = p->old_plane_x * sin(-ROT_SPEED) + p->plane_y * cos(-ROT_SPEED);
	}
	else if (key_pressed == LEFT_KEY)
	{
		p->old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
		p->dir_y = p->old_dir_x * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
		p->old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
		p->plane_y = p->old_plane_x * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
	}
}

int	mouse_move(t_config **conf)
{
	int	x;
	int	y;

	if ((*conf)->mouse_show == true)
	{
		mlx_mouse_show();
		return (0);
	}
	mlx_mouse_hide();
	mlx_mouse_get_pos((*conf)->mlx->win, &x, &y);
	if (x < WIDTH / 2)
		rotate_keys(conf, LEFT_KEY);
	else if (x > WIDTH / 2)
		rotate_keys(conf, RIGHT_KEY);
	mlx_mouse_move((*conf)->mlx->win, WIDTH / 2, HEIGHT / 2);
	render_game(conf, (*conf)->ray, (*conf)->character);
	load_map(conf, (*conf)->mlx);
	return (1);
}

void	destroy_and_exit()
{
	exit(1);
}

void	handle_door(t_config **conf)
{
	int			i;
	t_player	*p;

	i = -1;
	p = (*conf)->character;
	while ((*conf)->map[++i])
	{
		int j = -1;
		while ((*conf)->map[i][++j])
		{
			if ((*conf)->map[i][j] == '2')
			{
				if ((int)p->pos_x == i && (int)p->pos_y == j)
					return ;
				(*conf)->map[i][j] = '3';
			}
			else if ((*conf)->map[i][j] == '3')
			{
				if ((int)p->pos_x == i && (int)p->pos_y == j)
					return ;
				(*conf)->map[i][j] = '2';
			}
		}
	}
}

int	key_handler(int key_pressed, t_config **conf)
{
	t_player	*p;

	p = (*conf)->character;
	if (key_pressed == ESC_KEY)
		destroy_and_exit();
	if (key_pressed == 46 && !(*conf)->mouse_show)
	{
		(*conf)->mouse_show = true;
		return (0);
	}
	else if (key_pressed == 46 && (*conf)->mouse_show)
	{
		(*conf)->mouse_show = false;
		return (0);
	}
	else if (key_pressed == 49)
		handle_door(conf);
	move_keys(conf, key_pressed);
	rotate_keys(conf, key_pressed);
	mlx_destroy_image((*conf)->mlx->mlx, (*conf)->mlx->img);
	(*conf)->mlx->img = mlx_new_image((*conf)->mlx->mlx, WIDTH, HEIGHT);
	if ((*conf)->mlx->img == NULL)
		return (FAILS);
	(*conf)->mlx->addr = mlx_get_data_addr((*conf)->mlx->img, \
		&(*conf)->mlx->bpp, &(*conf)->mlx->line_len, &(*conf)->mlx->endian);
	if ((*conf)->mlx->addr == NULL)
		return (FAILS);
	render_game(conf, (*conf)->ray, p);
	load_map(conf, (*conf)->mlx);
	return (0);
}

/*
TODO initialise window mlx ✅
TODO cast rays and understand how it works ✅
TODO once rays are casted, use DDA algorithm to find a wall ✅
TODO calculate distance to draw vertical line for the wall ✅
TODO once we found out how it works, apply textures on the walls
*/

int	ft_close()
{
	exit(0);
}

/*	if (load_map(conf, (*conf)->mlx) == SUCCES)
		return (ft_putendl_fd(MINMAP_ERR, STDERR_FILENO));
*/

int	init_game(t_config **conf)
{
	t_vars	*mlx;

	mlx = (*conf)->mlx;
	(*conf)->ray = malloc(sizeof(t_ray));
	if (!(*conf)->ray)
		return (ft_putendl_fd(MALLOC_ERR, STDERR_FILENO));
	init_ray_struct((*conf)->ray);
	load_img(conf);
	render_game(conf, (*conf)->ray, (*conf)->character);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	if (load_map(conf, (*conf)->mlx) != SUCCES)
		return (ft_putendl_fd(MINMAP_ERR, STDERR_FILENO));
	(*conf)->mouse_show = false;
	mlx_loop_hook(mlx->mlx, &mouse_move, conf);
	mlx_hook(mlx->win, 2, 1L << 0, &key_handler, conf);
	mlx_hook(mlx->win, 17, 0, ft_close, conf);
	mlx_loop(mlx->mlx);
	return (0);
}
