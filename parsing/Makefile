# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/12 00:01:24 by ecortes-          #+#    #+#              #
#    Updated: 2025/02/06 13:46:27 by ecortes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
LDFLAGS = -lreadline

SRCS = main.c \
        libft/ft_substr.c \
        libft/ft_strlen.c \
        libft/ft_tokenadd_back.c \
        libft/ft_strdup.c \
        libft/ft_split.c \
        libft/ft_calloc.c \
        libft/ft_token_new.c \
        libft/ft_strchr.c \
        libft/ft_array_duplicate.c \
        libft/ft_strtrim.c \
        libft/ft_strncmp.c \
        libft/ft_strjoin.c \
        libft/ft_command_new.c \
        libft/ft_commandadd_back.c \
        libft/ft_tokenadd_after.c \
        libft/ft_tokensubstitute.c \
        libft/ft_strlcpy.c \
        utils/utils.c \
        utils/init.c \
        utils/free.c \
        utils/signals.c \
        tokenizer/tokens.c \
        tokenizer/tokens2.c \
        tokenizer/tokens3.c \
		tokenizer/expander.c \

OBJS = $(SRCS:.c=.o)

# Reglas
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(NAME) compilado con éxito ✅"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "Objetos eliminados 🧹"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) eliminado 🗑️"

re: fclean all

.PHONY: all clean fclean re