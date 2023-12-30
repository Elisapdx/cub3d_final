#include "../inc_bonus/cub3d_bonus.h"
#include "../inc_bonus/parse_err_bonus.h"
#include "../inc_bonus/mlx_win_bonus.h"
#include "../inc_bonus/mlx_err_bonus.h"

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int	get_pixel_color(t_vars *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	return (*(unsigned int*)dst);
}

int	initialize_mlx_win(t_config **conf)
{
	(*conf)->mlx = malloc(sizeof(t_vars));
	if (!(*conf)->mlx)
		return (ft_putendl_fd(MALLOC_ERR, STDERR_FILENO));
	(*conf)->mlx->mlx = mlx_init();
	if ((*conf)->mlx->mlx == NULL)
		return (ft_putendl_fd(INIT_ERR, STDERR_FILENO));
	printf("oui11\n");
	(*conf)->mlx->win = mlx_new_window((*conf)->mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	if ((*conf)->mlx->win == NULL)
		return (FAILS);
	(*conf)->mlx->img = mlx_new_image((*conf)->mlx->mlx, WIDTH, HEIGHT);
	if ((*conf)->mlx->img == NULL)
		return (FAILS);
	printf("oui22\n");
	(*conf)->mlx->addr = mlx_get_data_addr((*conf)->mlx->img, \
		&(*conf)->mlx->bpp, &(*conf)->mlx->line_len, &(*conf)->mlx->endian);
	if ((*conf)->mlx->addr == NULL)
		return (FAILS);
	printf("oui33\n");
	return (0);
}
