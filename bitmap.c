/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: epanholz <epanholz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 19:25:34 by epanholz      #+#    #+#                 */
/*   Updated: 2020/08/07 21:46:12 by epanholz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bitmap	*initialize_bitmap(int width, int heigth)
{
	t_bitmap	*bmp;

	bmp = ft_calloc(sizeof(t_bitmap), 1);

	ft_memcpy(&bmp->file.bitmap_type, "BM", 2);
	bmp->file.file_size = 54 * (width * heigth * 4);
	bmp->file.offset_bits = 14 + 40;
	bmp->info.size_header = 40;
	bmp->info.width = width;
	bmp->info.height = heigth;
	bmp->info.planes = 1;
	bmp->info.bit_count = 32;
	bmp->info.image_size = width * heigth;
	return (bmp);
}

static int	write_bmp_header(int fd, t_bmp_file_header *file_header)
{
	int	written;

	written = write(fd, &file_header->bitmap_type, 2);
	written += write(fd, &file_header->file_size, 4);
	written += write(fd, &file_header->reserved1, 2);
	written += write(fd, &file_header->reserved2, 2);
	written += write(fd, &file_header->offset_bits, 4);
	return (written == 14);
}

static int	write_dib_header(int fd, t_bmp_info_header *info_header)
{
	int	written;

	written = write(fd, &info_header->size_header, 4);
	written += write(fd, &info_header->width, 4);
	written += write(fd, &info_header->height, 4);
	written += write(fd, &info_header->planes, 2);
	written += write(fd, &info_header->planes, 2);
	written += write(fd, &info_header->compression, 4);
	written += write(fd, &info_header->image_size, 4);
	written += write(fd, &info_header->ppm_x, 4);
	written += write(fd, &info_header->ppm_y, 4);
	written += write(fd, &info_header->clr_used, 4);
	written += write(fd, &info_header->clr_important, 4);
	return (written == 40);
}

int		frame_to_bitmap(t_bitmap *bmp, int line_length, char *img_addr)
{
	void	*buff;
	int		y;
	int		i;

	y = bmp->info.height - 1;
	i = 0;
	buff = ft_calloc(sizeof(int), bmp->info.width * bmp->info.height);
	if (!buff)
		return (0);
	while (y >= 0)
	{
		ft_memcpy(buff + (i * bmp->info.width * 4), img_addr + (y * line_length),(size_t)bmp->info.width * 4);
		y--;
		i++;
	}
	bmp->buff = buff;
	return (1);
}

int			write_bitmap_to_file(t_bitmap *bmp)
{
	int fd;
	int	ret;

	ret = 1;
	fd = open("UwU.bmp", O_WRONLY | O_CREAT, 0644); //create + 0644 chmod to read write 
	if (!fd || !write_bmp_header(fd, &bmp->file) || !write_dib_header(fd, &bmp->info))
		ret = 0;
	if (write(fd, bmp->buff,(size_t)bmp->info.width * bmp->info.height * 4) != bmp->info.width * bmp->info.height * 4)
		ret = 0;
	close(fd);
	free(bmp->buff);
	free(bmp);
	return (ret);
}