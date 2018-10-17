# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgaitsgo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/26 14:32:25 by dgaitsgo          #+#    #+#              #
#    Updated: 2018/10/17 19:53:25 by trecomps         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRC_DIR = ./src
OBJ_DIR = ./obs
INC_DIR = ./include

SRC_FILES = \
./src/main.c\
./src/md5.c\
./src/padding.c\
./src/bitswap.c\
./src/md5_fg_values.c\
./src/h_values_hexstr.c\

OBJ_FILES = $(SRC_FILES:.c=.o)

INC_FILES = \
./include/externals_headers.h\
./include/ft_ssl_md5.h\
./include/libft.h

LIB_DIR = ./lib/libft

FLAGS = -Wall -Wextra -Werror

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ_FILES)
	make -C ./lib/libft
	gcc $(FLAGS) -o $(NAME) $(OBJ_FILES) -L$(LIB_DIR) -lft

all: $(NAME)

%.o:%.c $(INC_FILES)
	gcc -g -c -I$(INC_DIR) $< -o $@

clean:
	make -C ./lib/libft/ clean
	rm -rf $(OBJ_FILES)

fclean: clean
	make -C ./lib/libft/ fclean
	rm -rf $(NAME)

re: fclean all
