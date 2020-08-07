# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: epanholz <epanholz@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 17:08:43 by epanholz      #+#    #+#                  #
#    Updated: 2020/08/07 19:56:11 by epanholz      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := minirt

SRC := test_main.c read_file.c get_scene.c check_scene.c check_scene_utils.c object_list.c \
	object_list_traverse.c object_list_traverse_test.c vector_library.c utils.c make_scene.c \
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

circle:
	@printf "\n"
	@printf "\e[1;36m (っ◔ ◡ ◔)っ ♥ ᴄᴏᴍᴘɪʟɪɴɢ ᴄɪʀᴄʟᴇ ♥\n\e[0m"
	@gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit circle.c
	@./a.out
	@printf "\n"

square:
	@printf "\n"
	@printf "\e[1;36m (っ◔ ◡ ◔)っ ♥ ᴄᴏᴍᴘɪʟɪɴɢ ꜱQᴜᴀʀᴇ ♥\n\e[0m"
	@gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit square.c
	@./a.out
	@printf "\n"

test:
	@printf "\n"
	@printf "\e[1;36m (っ◔ ◡ ◔)っ ♥ ᴛʀʏɪɴɢ ᴏᴜᴛ ꜱᴏᴍᴇ ꜱᴛᴜꜰꜰ ♥\n\e[0m"
	@gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit trying_stuff.c
	@./a.out
	@printf "\n"

tracer:
	@printf "\n"
	@printf "\e[1;36m (っ◔ ◡ ◔)っ ♥ test tracer ♥\n\e[0m"
	@gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit test_tracer.c
	@./a.out
	@printf "\n"