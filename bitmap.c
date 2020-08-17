/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 19:25:34 by epanholz      #+#    #+#                 */
/*   Updated: 2020/08/17 20:45:49 by pani_zino     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bitmap	*initialize_bitmap(int width, int heigth)
{
	t_bitmap	*bmp;

	bmp = ft_calloc(sizeof(t_bitmap), 1);

	ft_memcpy(&bmp->file.bitmap_type, "BM", 2);
	bmp->file.file_size = 14 + 40 + (bmp->info.width * bmp->info.height * 4);
	bmp->file.offset_bits = 14 + 40;
	bmp->info.size_header = 40;
	bmp->info.width = width;
	bmp->info.height = heigth;
	bmp->info.planes = 1;
	bmp->info.bit_count = 32;
	bmp->info.image_size = width * heigth;
	return (bmp);
}

void	write_file_header(int fd, t_bmp_file_header *file_header)
{
	write(fd, &file_header->bitmap_type, 2);
	write(fd, &file_header->file_size, 4);
	write(fd, &file_header->reserved1, 2);
	write(fd, &file_header->reserved2, 2);
	write(fd, &file_header->offset_bits, 4);
}

void	write_info_header(int fd, t_bmp_info_header *info_header)
{
	write(fd, &info_header->size_header, 4);
	write(fd, &info_header->width, 4);
	write(fd, &info_header->height, 4);
	write(fd, &info_header->planes, 2);
	write(fd, &info_header->planes, 2);
	write(fd, &info_header->compression, 4);
	write(fd, &info_header->image_size, 4);
	write(fd, &info_header->ppm_x, 4);
	write(fd, &info_header->ppm_y, 4);
	write(fd, &info_header->clr_used, 4);
	write(fd, &info_header->clr_important, 4);
}

int		fill_bmp_buff(t_bitmap *bmp, t_minirt *minirt, char *img_addr)
{
	void	*buff;
	int		y;
	int 	x;
	int		i;

	y = bmp->info.height - 1;
	x = bmp->info.width;
	i = 0;
	buff = ft_calloc(sizeof(int), bmp->info.width * bmp->info.height);
	if (!buff)
		return (0);
	while (y >= 0)
	{
		ft_memcpy(buff + (i * x * 4), img_addr + (y * minirt->var.line_length), (size_t)bmp->info.width * 4);
		//ft_memcpy(buff + (i * x * 4), img_addr + ((y * minirt->var.line_length) + (i * (minirt->var.bits_per_pixel / 8))), x * 4);
		i++;
		y--;
	}
	bmp->buff = buff;
	return (1);
}

int			write_bitmap_to_file(t_bitmap *bmp, t_minirt *minirt, char *img_addr)
{
	int fd;
	int	ret;

	ret = 1;
	fd = open("UwU.bmp", O_WRONLY | O_CREAT, 0644); //create + 0644 chmod to read write 
	write_file_header(fd, &bmp->file);
	write_info_header(fd, &bmp->info);
	
	// (void)minirt;
	// (void)img_addr;
	// write(fd, bmp->buff, (size_t)bmp->info.width * bmp->info.height * 4);

	int		y;
	int		x;
	unsigned char	pad;

	pad = 0;
	y =  minirt->scene.res_y - 1;
	char *pixel;
	x = 0;
	while (y >= 0)
	{
		//printf("y: %d\n", y);
		while (x < minirt->scene.res_x)
		{
			pixel = img_addr + ((y * minirt->var.line_length) + (x * (minirt->var.bits_per_pixel / 8)));
			write(fd, pixel + 2, 1);
			write(fd, pixel + 1, 1);
			write(fd, pixel, 1);
			write(fd, &pad, 1);
			x++;
		}
		x = 0;
		y--;
	}
	
	close(fd);
	free(bmp->buff);
	free(bmp);
	return (ret);
}

	// if (write(fd, bmp->buff, (size_t)bmp->info.width * bmp->info.height * 4) != bmp->info.width * bmp->info.height * 4)
	// 	ret = 0;

	// if (!fd || !write_bmp_header(fd, &bmp->file) || !write_dib_header(fd, &bmp->info))
	// 	ret = 0;

	// int		y;
	// int		x;
	// unsigned char	pad;

	// pad = 0;
	// y = bmp->info.height - 1;
	// x = 0;
	// while (y >= 0)
	// {
	// 	while (x < minirt->scene.res_x)
	// 	{
	// 		write(fd, img_addr + ((y * minirt->var.line_length) + (x * (minirt->var.bits_per_pixel / 8))), 3);
	// 		write(fd, &pad, 1);
	// 		x++;
	// 	}
	// 	x = 0;
	// 	y--;
	// }