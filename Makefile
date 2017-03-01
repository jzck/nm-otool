# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhalford <jack@crans.org>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/19 03:29:38 by jhalford          #+#    #+#              #
#    Updated: 2017/03/01 16:00:29 by jhalford         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_nm ft_otool

CC			=	gcc
MKDIR		=	mkdir -p
RM			=	/bin/rm -rf

W_FLAGS		=	-Wall -Wextra -Werror
D_FLAGS		=
V_FLAGS		=	-fvisibility=hidden
FLAGS		=	$(W_FLAGS) $(D_FLAGS) $(V_FLAGS)

DELTA		=	$$(echo "$$(tput cols)-47"|bc)

LIBFT_DIR	=	libft/
LIBFT_LIB	=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	$(LIBFT_DIR)includes/

SRC_DIR		=	src/
INC_DIR		=	includes/
OBJ_DIR		=	objs/

FT_NM_OBJ	=	$(OBJ_DIR)ft_nm.o
FT_OTOOL_OBJ=	$(OBJ_DIR)ft_otool.o

SRC_BASE	=	\
dump_symtab.c\
ft_nm.c\
ft_otool.c\
hexdump.c

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
NB			=	$(words $(SRC_BASE) $(NAME))
INDEX		=	0

OBJS		:=	$(filter-out $(FT_NM_OBJ), $(OBJS))
OBJS		:=	$(filter-out $(FT_OTOOL_OBJ), $(OBJS))

all: $(NAME)

ft_nm: $(LIBFT_LIB) $(OBJ_DIR) $(OBJS) $(FT_NM_OBJ)
	@$(CC) $(FLAGS) $(D_FLAGS) \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) \
		$(LIBS) \
		$(LIBFT_LIB) $(OBJS) $(FT_NM_OBJ) \
		-o $@
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))
	@strip -x $@
	@printf "\r\e[48;5;15;38;5;25m✅ MAKE $@\e[0m\e[K\n"

ft_otool: $(LIBFT_LIB) $(OBJ_DIR) $(OBJS) $(FT_OTOOL_OBJ)
	@$(CC) $(FLAGS) $(D_FLAGS) \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) \
		$(LIBS) \
		$(LIBFT_LIB) $(OBJS) $(FT_OTOOL_OBJ) \
		-o $@
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))
	@strip -x $@
	@printf "\r\e[48;5;15;38;5;25m✅ MAKE $@\e[0m\e[K\n"


$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval COLOR=$(shell echo $$(($(PERCENT)%35+196))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB)))))
	@printf "\r\e[38;5;11m⌛ MAKE %10.10s : %2d%% \e[48;5;%dm%*s\e[0m%*s\e[48;5;255m \e[0m \e[38;5;11m %*s\e[0m\e[K" $@ $(PERCENT) $(COLOR) $(DONE) "" $(TO_DO) "" $(DELTA) "$@"
	@$(CC) $(FLAGS) -MMD -c $< -o $@\
		-I $(INC_DIR) \
		-I $(LIBFT_INC)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)
	@$(MKDIR) $(dir $(OBJS))

clean:
	@$(RM) $(OBJ_DIR)
	@printf "\r\e[38;5;202m✖ clean $(NAME).\e[0m\e[K\n"

cleanlib:
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@printf "\r\e[38;5;196m❌ fclean $(NAME).\e[0m\e[K\n"

fcleanlib:		cleanlib
	@make -C $(LIBFT_DIR) fclean

re: fclean all

relib:			fcleanlib $(LIBFT_LIB)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

.PHONY: fclean clean re relib cleanlib fcleanlib

-include $(OBJS:.o=.d)

