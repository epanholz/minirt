# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: epanholz <epanholz@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 17:08:43 by epanholz      #+#    #+#                  #
#    Updated: 2020/06/20 18:07:58 by epanholz      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minirt

SRC = test_main.c read_file.c get_scene.c check_scene_utils.c object_list.c check_scene.c

INC = minirt.h

FLAGS = -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): 
	@printf "\n"
	@printf "\e[1;36m (っ◔ ◡ ◔)っ ♥ ᴄᴏᴍᴘɪʟɪɴɢ ᴍɪɴɪʀᴛ ♥\n\e[0m"
	@gcc $(FLAGS) -o $(NAME) $(SRC)
	@printf "\n"

clean:
	@printf "\n"
	@printf "\e[1;36m (っ◔ ◡ ◔)っ ♥ ʀᴇᴍᴏᴠɪɴɢ ᴇxᴇᴄᴜᴛᴀʙʟᴇ ♥\n\e[0m"
	@rm $(NAME)
	@printf "\n"

re: clean all

circle:
	@printf "\n"
	@printf "\e[1;36m█▀▀ █▀▀█ █▀▄▀█ █▀▀█ ░▀░ █░░ ░▀░ █▀▀▄ █▀▀▀ 　 █▀▀ ░▀░ █▀▀█ █▀▀ █░░ █▀▀\n\e[0m"
	@printf "\e[1;36m█░░ █░░█ █░▀░█ █░░█ ▀█▀ █░░ ▀█▀ █░░█ █░▀█ 　 █░░ ▀█▀ █▄▄▀ █░░ █░░ █▀▀\n\e[0m"
	@printf "\e[1;36m▀▀▀ ▀▀▀▀ ▀░░░▀ █▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ▀░░▀ ▀▀▀▀ 　 ▀▀▀ ▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀▀▀\n\e[0m"
	@gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit circle.c
	@./a.out
	@printf "\n"

square:
	@printf "\n"
	@printf "\e[1;36m█▀▀ █▀▀█ █▀▄▀█ █▀▀█ ░▀░ █░░ ░▀░ █▀▀▄ █▀▀▀ 　 █▀▀ █▀▀█ █░░█ █▀▀█ █▀▀█ █▀▀\n\e[0m"
	@printf "\e[1;36m█░░ █░░█ █░▀░█ █░░█ ▀█▀ █░░ ▀█▀ █░░█ █░▀█ 　 ▀▀█ █░░█ █░░█ █▄▄█ █▄▄▀ █▀▀\n\e[0m"
	@printf "\e[1;36m▀▀▀ ▀▀▀▀ ▀░░░▀ █▀▀▀ ▀▀▀ ▀▀▀ ▀▀▀ ▀░░▀ ▀▀▀▀ 　 ▀▀▀ ▀▀▀█ ░▀▀▀ ▀░░▀ ▀░▀▀ ▀▀▀\n\e[0m"
	@gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit square.c
	@./a.out
	@printf "\n"