# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ariard <ariard@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/03 00:35:24 by ariard            #+#    #+#              #
#    Updated: 2018/02/09 19:21:55 by ariard           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_nm ft_otool

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
D_FLAGS		=	

DELTA		=	$$(echo "$$(tput cols)-47"|bc)

LIBFT_DIR	=	libft/
LIBFT_LIB	=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	$(LIBFT_DIR)includes/

LIBS		=	
SRC_DIR		=	src/
INC_DIR		=	includes/
OBJ_DIR		=	objs/

NM_OBJ		=	$(OBJ_DIR)nm.o
OTOOL_OBJ	=	$(OBJ_DIR)otool.o

SRC_BASE	=	\
ft_hexdump.c\
handle_32.c\
handle_64.c\
handle_fat.c\
nm.c\
otool.c\
otool_fatheader.c\
parse_archi.c\
parse_segment32.c\
parse_segment64.c\
parse_symtab.c\
parse_symtab32.c\
print_sym.c\
symtab_sort.c

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
OBJS		:=	$(filter-out $(NM_OBJ), $(OBJS))
OBJS		:=	$(filter-out $(OTOOL_OBJ), $(OBJS))
NB			=	$(words $(SRC_BASE))
INDEX		=	0

all :
	@make -C $(LIBFT_DIR)
	@make -j $(NAME)

ft_nm : $(LIBFT_LIB) $(OBJ_DIR) $(OBJS) $(NM_OBJ)
	@$(CC) $(OBJS) -o $@ \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) \
		$(LIBS) $(LIBFT_LIB) $(NM_OBJ) $(FLAGS)
	@printf "\r\033[48;5;15;38;5;25m✅ MAKE $@ \033[0m\033[K\n"

ft_otool : $(LIBFT_LIB) $(OBJ_DIR) $(OBJS) $(OTOOL_OBJ)
	@$(CC) $(OBJS) -o $@ \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) \
		$(LIBS) $(LIBFT_LIB) $(OTOOL_OBJ) $(FLAGS)
	@printf "\r\033[48;5;15;38;5;25m✅ MAKE $@ \033[0m\033[K\n"


$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(CC) $(FLAGS) $(D_FLAGS) -MMD -c $< -o $@\
		-I $(INC_DIR)\
		-I $(LIBFT_INC)

clean:			cleanlib
	@rm -rf $(OBJ_DIR)
	@printf "\r\033[38;5;202m✖ clean $(NAME).\033[0m\033[K\n"

cleanlib:
	@make -C $(LIBFT_DIR) clean

fclean:			clean fcleanlib
	@rm -f $(NAME)
	@printf "\r\033[38;5;196m❌ fclean $(NAME).\033[0m\033[K\n"

fcleanlib:		cleanlib
	@make -C $(LIBFT_DIR) fclean

re:				fclean all

relib:			fcleanlib $(LIBFT_LIB)

.PHONY :		fclean clean re relib cleanlib fcleanlib

-include $(OBJS:.o=.d)
