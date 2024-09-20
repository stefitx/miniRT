# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erigonza <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/29 19:36:23 by erigonza          #+#    #+#              #
#    Updated: 2024/09/20 18:04:10 by erigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
FLAGS = -Wall -Werror -Wextra #-g #-fsanitize=address 

INCLUDES = -I ./inc/\
           -I ./src/libft/\
		   -I ./mlx/

SRC = camera.c, inits.c, main.c

DIR_SRC = ./src
DIR_OBJ = $(DIR_SRC)/obj
OBJ = $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
DEP = $(addprefix $(DIR_OBJ)/, $(SRC:.c=.d))


all: dir $(NAME)

-include $(DEP)

dir:
	make -C ./mlx/ --no-print-directory
	make -C ./src/libft/ --no-print-directory
	mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c Makefile
	$(CC) -MMD $(FLAGS)  -c $< -o $@ $(INCLUDES)
$(NAME): $(OBJ) ./src/libft/libft.a
	$(CC) $(FLAGS) $(OBJ) ./mlx/libmlx.a -lXext -lX11 -lm -lz ./src/libft/libft.a -o $@ $(INCLUDES)
	echo "$(NAME) Created :D"

c clean:
	rm -rf $(DIR_OBJ)
	make clean -C ./src/libft/ --no-print-directory 
	echo "DEPENDENCIES Erased :D"

f fclean: clean
	rm -rf $(NAME)
	make fclean -C ./src/libft/ --no-print-directory 
	echo "EVERYTHING Erased D:"

r re: fclean all
.PHONY: fclean all clean re dir
