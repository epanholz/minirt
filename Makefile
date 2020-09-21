# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: epanholz <epanholz@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 17:08:43 by epanholz      #+#    #+#                  #
#    Updated: 2020/09/21 15:44:43 by pani_zino     ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := minirt

SRC := main.c read_file.c get_scene.c check_scene.c check_scene_utils.c object_list.c \
	cam_list.c vector_library.c utils.c make_scene.c matrix.c atod.c \
	image_list.c hooks.c light.c bitmap.c check_scene_objects.c get_objects.c libmlx.dylib \
	get_scene_loop.c light_list.c \

INC := minirt.h

FLAGS := -Wall -Wextra -Werror -I mlx -Lmlx/ -Lmlx -framework OpenGL -framework AppKit

MLX_PATH := ./mlx/

MLX := libmlx.dylib

all: $(NAME)

$(NAME): 
	@printf "\n\e[1;36m (っ◔ ◡ ◔)っ ♥ ᴄᴏᴍᴘɪʟɪɴɢ ᴍɪɴɪʀᴛ ♥\n\e[0m\n"
	@gcc $(FLAGS) -g -o $(NAME) $(SRC) $(MLX)

$(MLX):
	@printf "\n\e[1;36m (っ◔ ◡ ◔)っ ♥ ᴄᴏᴍᴘɪʟɪɴɢ ᴍʟx ♥\n\e[0m\n"
	@$(MAKE) -C $(MLX_PATH)
	@printf "\e[1;36m (っ◔ ◡ ◔)っ ♥ ᴍᴏᴠɪɴɢ ᴅʏʟɪʙ ♥\n\e[0m"
	@mv mlx/$(MLX) .

clean:
	@printf "\n\e[1;36m (っ◔ ◡ ◔)っ ♥ ʀᴇᴍᴏᴠɪɴɢ ᴇxᴇᴄᴜᴛᴀʙʟᴇ ♥\n\e[0m\n"
	@rm $(NAME) 
	
	#@rm $(MLX)
	#@$(MAKE) -C $(MLX_PATH) clean

re: clean all
