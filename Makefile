# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: epanholz <epanholz@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 17:08:43 by epanholz      #+#    #+#                  #
#    Updated: 2020/10/11 14:46:08 by epanholz      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

SRC := main.c read_file.c read_file_utils.c get_scene.c			\
	check_scene.c check_scene_utils.c cam_list.c utils.c		\
	matrix.c atod.c object_list.c intersect_triangle.c			\
	intersect_sphere.c image_list.c hooks.c light.c				\
	bitmap.c check_scene_objects.c get_objects.c error.c		\
	get_scene_loop.c light_list.c render.c render_loop.c		\
	intersect_plane.c intersect_cylinder.c intersect_square.c	\
	vector_library1.c vector_library2.c							\

INC := minirt.h

FLAGS := -Wall -Wextra -Werror -I mlx

MFLAGS := -Lmlx/ -Lmlx -framework OpenGL -framework AppKit

MLX_PATH := ./mlx/

MLX := libmlx.dylib

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(MLX) $(OBJ)
	@printf "\n\e[1;36m ♥ ᴄᴏᴍᴘɪʟɪɴɢ ᴍɪɴɪʀᴛ ♥\n\e[0m\n"
	@gcc $(FLAGS) $(MFLAGS) -g -o $(NAME) $(SRC) $(MLX)

$(MLX):
	@printf "\n\e[1;36m ♥ ᴄᴏᴍᴘɪʟɪɴɢ ᴍʟx ♥\n\e[0m\n"
	@$(MAKE) -C $(MLX_PATH)
	@printf "\e[1;36m ♥ ᴍᴏᴠɪɴɢ ᴅʏʟɪʙ ♥\n\e[0m"
	@mv mlx/$(MLX) .
	
%.o: %.c
	@printf "\e[1;36m ᴄᴏᴍᴘɪʟɪɴɢ ᴏʙᴊᴇᴄᴛ ꜰɪʟᴇꜱ \e[0m\n"
	@gcc $(FLAGS) -c $< -o $@

clean:
	@printf "\n\e[1;36m ♥ ᴍᴀᴋᴇ ᴄʟᴇᴀɴ ♥\n\e[0m\n"
	@$(RM) $(OBJ)
	@$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	@printf "\n\e[1;36m ♥ ᴍᴀᴋᴇ ꜰᴄʟᴇᴀɴ ♥\n\e[0m\n"
	@$(RM) $(NAME) $(MLX)

re: fclean all
