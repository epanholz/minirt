# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: epanholz <epanholz@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 17:08:43 by epanholz      #+#    #+#                  #
#    Updated: 2020/09/10 11:43:02 by pani_zino     ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := minirt

SRC := main.c read_file.c get_scene.c check_scene.c check_scene_utils.c object_list.c \
	object_list_traverse.c vector_library.c utils.c make_scene.c \
	images.c hooks.c color.c bitmap.c libmlx.dylib \

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
