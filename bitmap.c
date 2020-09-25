/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pani_zino <pani_zino@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 10:20:45 by pani_zino     #+#    #+#                 */
/*   Updated: 2020/09/25 14:34:30 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_bitmap		*initialize_bitmap(int width, int heigth)
{
	t_bitmap	*bmp;

	bmp = ft_calloc(sizeof(t_bitmap), 1);
	ft_memcpy(&bmp->file.bitmap_type, "BM", 2);
	bmp->file.file_size = 54 + (width * heigth * 4);
	bmp->file.offset_bits = 54;
	bmp->info.size_header = 40;
	bmp->info.width = width;
	bmp->info.height = heigth;
	bmp->info.planes = 1;
	bmp->info.bit_count = 32;
	bmp->info.image_size = width * heigth;
	return (bmp);
}

static int			write_headers(int fd, t_bmp_file *file, t_bmp_info *info)
{
	int ret;

	ret = write(fd, &file->bitmap_type, 2);
	ret += write(fd, &file->file_size, 4);
	ret += write(fd, &file->reserved1, 2);
	ret += write(fd, &file->reserved2, 2);
	ret += write(fd, &file->offset_bits, 4);
	ret += write(fd, &info->size_header, 4);
	ret += write(fd, &info->width, 4);
	ret += write(fd, &info->height, 4);
	ret += write(fd, &info->planes, 2);
	ret += write(fd, &info->bit_count, 2);
	ret += write(fd, &info->compression, 4);
	ret += write(fd, &info->image_size, 4);
	ret += write(fd, &info->ppm_x, 4);
	ret += write(fd, &info->ppm_y, 4);
	ret += write(fd, &info->clr_used, 4);
	ret += write(fd, &info->clr_important, 4);
	return (ret);
}

void				fill_bmp_buff(t_bitmap *bmp,
						t_minirt *minirt, char *img_addr)
{
	void	*buff;
	int		y;
	int		x;
	int		i;

	y = bmp->info.height - 1;
	x = bmp->info.width;
	i = 0;
	buff = ft_calloc(sizeof(int), bmp->info.width * bmp->info.height);
	if (!buff)
		ft_error (MALLOC);
	while (y >= 0)
	{
		ft_memcpy(buff + (i * x * 4),
				img_addr + (y * minirt->mlx.line_length),
				(size_t)bmp->info.width * 4);
		i++;
		y--;
	}
	bmp->buff = buff;
}

void				write_bitmap(t_minirt *minirt, char *img_addr)
{
	int			fd;
	t_bitmap	*bmp;

	bmp = initialize_bitmap(minirt->scene.res_x, minirt->scene.res_y);
	fill_bmp_buff(bmp, minirt, img_addr);
	fd = open("UwU.bmp", O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		ft_error(OPEN);
	if (write_headers(fd, &bmp->file, &bmp->info) != 54)
		ft_error(WRITE);
	if (write(fd, bmp->buff, (size_t)bmp->info.width * bmp->info.height * 4) < 0)
		ft_error(WRITE);
	close(fd);
	free(bmp->buff);
	free(bmp);
}
