# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: epanholz <epanholz@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 17:08:43 by epanholz      #+#    #+#                  #
#    Updated: 2020/06/18 12:32:07 by epanholz      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minirt

SRC = test_main.c read_file.c get_scene.c check_scene_utils.c object_list.c check_scene.c

INC = minirt.h

FLAGS = -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): 
	gcc $(FLAGS) -o $(NAME) $(SRC)

clean:
	rm $(NAME)

re: clean all