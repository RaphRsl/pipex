# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 15:57:33 by rroussel          #+#    #+#              #
#    Updated: 2023/07/07 16:21:10 by rroussel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef VERBOSE
MAKEFLAGS += --no-print-directory
endif

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_CYAN=\033[0;36m
COLOUR_END=\033[0m

CC		= gcc
CFLAGS	= -Werror -Wextra -Wall
NAME	= pipex

SRC_PATH = src/
OBJ_PATH = obj/

SRC	= pipex.c \
	message.c \
	env_parsing.c \
	utils.c \
	starter.c \
	file_access.c \
	ft_split.c \
	ft_strjoin.c \
	str_utils.c \
	get_next_line.c \
	get_next_line_utils.c
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC		= -I ./includes/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH) $(OBJ_PATH)get_next_line/
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@sleep .05
	@printf "\033[1A"
	@printf "\033[K"
	
$(NAME): $(OBJS)
	@echo "$(COLOUR_CYAN)\
		██████╗ ██╗██████╗ ███████╗██╗  ██╗\n\
		██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝\n\
		██████╔╝██║██████╔╝█████╗   ╚███╔╝ \n\
		██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ \n\
		██║     ██║██║     ███████╗██╔╝ ██╗\n\
		╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝  by rroussel$(COLOUR_END)"
		
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "↪ Finished, $(COLOUR_BLUE)pipex$(COLOUR_END) $(COLOUR_GREEN)compiled$(COLOUR_END)"

bonus: all

clean:
	@echo "Cleaning files..."
	@rm -rf $(OBJ_PATH)
	@echo "↪ Finished, $(COLOUR_BLUE)files$(COLOUR_END) $(COLOUR_RED)cleaned$(COLOUR_END)"

fclean: clean
	@echo "Cleaning binaries..."
	@rm -f $(NAME)
	@echo "↪ Finished, $(COLOUR_BLUE)binaries$(COLOUR_END) $(COLOUR_RED)cleaned$(COLOUR_END)"

re: fclean all
	@echo "↪ Finished, $(COLOUR_BLUE)re-make$(COLOUR_END) $(COLOUR_GREEN)done$(COLOUR_END)"

.PHONY: all re clean fclean
