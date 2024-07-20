# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fli <fli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/14 16:42:15 by fli               #+#    #+#              #
#    Updated: 2024/07/12 17:58:04 by fli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -g3

CFLAGS = -Wall -Werror -Wextra

INCLUDE = ./includes/

MANDATORY = ./mandatory/

CFILES = cmd1_manager.c \
		 fd_manager.c \
		 ft_dprintf.c \
		 ft_strjoin_pipex.c \
		 last_cmd_manager.c \
		 pid_manager.c \
		 pipex_utils.c \
		 pipex.c \
		 protector.c \

BFILES = cmd1_manager_bonus.c \
		 fd_manager_bonus.c \
		 ft_dprintf_bonus.c \
		 ft_strjoin_pipex_bonus.c \
		 get_next_line_bonus.c \
		 get_next_line_utils_bonus.c \
		 here_doc_manager_bonus.c \
		 last_cmd_manager_bonus.c \
		 main_bonus.c \
		 middle_cmd_manager_bonus.c \
		 pid_manager_bonus.c \
		 pipex_utils_bonus.c \
		 protector_bonus.c \

SRC_MANDATORY = $(addprefix $(MANDATORY), $(CFILES))

SRC_BONUS = $(addprefix $(BONUS), $(BFILES))

LIBFT = ./libft/

NAME = pipex

BONUS = ./bonus/

LIB = libft.a

OBJ = $(SRC_MANDATORY:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

$(NAME): $(LIB) $(OBJ)
	@echo "Compiling pipex..."
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJ) $(LIB) -o $(NAME)

$(LIB):
	@echo "Making libft..."
	@make -C $(LIBFT)
	@cp ./libft/libft.a $(LIB)

.c.o:
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

all: $(NAME)

clean:
	@echo "Removing .o object files..."
	@rm -f $(OBJ)
	@rm -f $(OBJ_BONUS)
	@make -C $(LIBFT) fclean

fclean: clean
	@echo "Removing pipex..."
	@rm -f $(NAME)
	@rm -f $(LIB)
	@rm -f $(LIBFT)$(LIB)

re: fclean all

bonus: $(OBJ_BONUS) $(LIB)
	@echo "Making pipex bonus..."
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(OBJ_BONUS) $(LIB) -o $(NAME)

.PHONY: all clean fclean re bonus
