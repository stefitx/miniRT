# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atudor <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 09:36:16 by atudor            #+#    #+#              #
#    Updated: 2024/09/18 09:36:19 by atudor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -Ofast
RM			= rm -f

# Directories
SRCS_DIR	= srcs/
OBJS_DIR	= objs/
GNL_DIR		= inc/gnl/
MLX_DIR		= inc/MLX42/
LIBFT_DIR	= inc/libft/

# Source files
FILES		= main camera
# GNL_FILES	= $(addprefix $(GNL_DIR), get_next_line.c get_next_line_utils.c)

# Headers and includes
HEADER		= inc/
INCLUDE		= -I$(HEADER) -I$(MLX_DIR)/include -I$(LIBFT_DIR)

# Source files and object files
SRCS		= $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS		= $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

# Libraries
MINILIB		= $(MLX_DIR)
LIBFT		= $(LIBFT_DIR)

all: $(NAME)

# Create the object directory if it doesn't exist
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

# Compile object files and place them in the objects directory
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)minirt.h $(MLX_DIR)/include/MLX42/MLX42.h $(LIBFT_DIR)libft.h Makefile | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJS_DIR)%.o: $(GNL_DIR)%.c $(HEADER)minirt.h | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Link everything together
$(NAME): libft.a libmlx.a $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_DIR)libft.a $(MLX_DIR)build/libmlx42.a $(INCLUDE) -L $(MLX_DIR) -L $(LIBFT_DIR) -lft -lm -ldl -lglfw -pthread -lXext -lX11 -lbsd

# Compile MiniLibX
libmlx.a:
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build
	$(MAKE) -C $(MLX_DIR)/build

# Compile libft
libft.a:
	$(MAKE) -C $(LIBFT_DIR)

# Build everything
all: $(NAME)

# Clean object files
clean:
	$(RM) -r $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MINILIB)/build clean

# Full clean: remove object files and executable
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MINILIB)/build clean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re libmlx.a libft.a
