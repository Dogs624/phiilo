# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvander- <jvander-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/13 13:50:10 by jvander-          #+#    #+#              #
#    Updated: 2022/02/10 13:26:56 by jvander-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

#-------------------PATH----------------------

INCLUDES	=	./includes/
UTILS		=	./utils/
SOURCES		=	./srcs/
ERRORS		=	./errors/

#-------------------COMPILATION----------------------

CC			=	gcc -g
FLAGS		=	-Wall -Werror -Wextra

#-------------------SOURCES FILES----------------------

SRCS	=	$(SOURCES)philo.c \
			$(SOURCES)actions.c \
			$(SOURCES)init.c \

SRCS_UTILS	=	$(UTILS)ft_utils.c \
				$(UTILS)ft_atoi.c \
				
SRCS_ERRORS	=	$(ERRORS)ft_check_args.c \
				$(ERRORS)ft_errors.c \

#-------------------OBJECTS----------------------

OBJS_SRCS	=	$(SRCS:.c=.o)

OBJS_UTILS	=	$(SRCS_UTILS:.c=.o)

OBJS_ERRORS	=	$(SRCS_ERRORS:.c=.o)

#-------------------COLORS----------------------

RED			=	\x1b[31m

YELLOW		=	\x1b[33m

GREEN		=	\x1b[32m

NO_COLOR	=	\x1b[0m


#-------------------RULES-----------------------
%.o: %.c
		@printf "$(YELLOW)Generating philo objects... %-33.33s\r$(NO_COLOR)" $@
		@$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(OBJS_SRCS) $(OBJS_UTILS) $(OBJS_ERRORS)
			@echo "\n"
			@echo "$(GREEN)\nCompiling philo...$(NO_COLOR)"
			@$(CC) $(FLAGS) $(OBJS_SRCS) $(OBJS_ERRORS) $(OBJS_UTILS) -o $(NAME)
			@echo "Philo ready to be used!"

all:	$(NAME)

bonus:	$(NAME)

clean:
		@echo "$(RED)Deleting objects...\n$(NO_COLOR)"
	@rm -f $(OBJS_SRCS) $(OBJS_UTILS) $(OBJS_ERRORS)

fclean:	clean
		@echo "$(RED)Deleting executables...\n$(NO_COLOR)"
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re
