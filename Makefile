# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wescande <wescande@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/29 21:32:58 by wescande          #+#    #+#              #
#    Updated: 2017/10/26 19:15:02 by jhalford         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_nm ft_otool

CC			=	gcc
W_FLAGS		=	-Wall -Wextra -Werror
D_FLAGS		=
FLAGS		=	$(W_FLAGS) $(D_FLAGS)

LEN_NAME	=	`printf "%s" $(NAME) |wc -c`
DELTA		=	$$(echo "$$(tput cols)-31-$(LEN_NAME)"|bc)

LIBFT_DIR	=	libft/
LIBFT_LIB	=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	$(LIBFT_DIR)includes/

LIBS		=

SRC_DIR		=	srcs/
INC_DIR		=	includes/
OBJ_DIR		=	objs/

NM_OBJ		=	$(OBJ_DIR)ft_nm.o
OTOOL_OBJ	=	$(OBJ_DIR)ft_otool.o

SRC_BASE	=	\
ft_otool.c\
mach_64/symbol_64_init.c\
mach_64/symbol_64_filter.c\
mach_64/symbol_64_sort.c\
mach_64/mach_64.c\
mach_64/symbol_64_free.c\
mach_64/symbol_64_format.c\
mach_32/symbol_32_free.c\
mach_32/symbol_32_sort.c\
mach_32/mach_32.c\
mach_32/symbol_32_format.c\
mach_32/symbol_32_filter.c\
mach_32/symbol_32_init.c\
ft_nm.c\
dump_symtab.c

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS		=	$(addprefix $(OBJ_DIR), $($(notdir SRC_BASE):.c=.o))
OBJS		:=	$(filter-out $(NM_OBJ), $(OBJS))
OBJS		:=	$(filter-out $(OTOOL_OBJ), $(OBJS))
NB			=	$(words $(SRC_BASE))
INDEX		=	0

MACH_64_SRC	:=	$(wildcard $(SRC_DIR)mach_64/*)
MACH_64_SRC	+=	$(INC_DIR)mach_64.h
MACH_SRC	:=	$(subst _64,_32, $(MACH_64_SRC))

SHELL		:=	/bin/bash

all:
	@make -C $(LIBFT_DIR)
	@make -j $(NAME)

# $(SRC_DIR)/mach/%.c: $(SRC_DIR)/mach_64/%.c
$(MACH_SRC):
	@mkdir -p $(SRC_DIR)/mach_32
	@echo "$@ ---> $(subst _32,_64, $@)"
	@sed s/_64/_32/g $(subst _32,_64, $@) > $@

ft_nm:		$(LIBFT_LIB) $(OBJ_DIR) $(OBJS) $(NM_OBJ)
	@$(CC) $(OBJS) -o $@ \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) \
		$(LIBS) $(LIBFT_LIB) $(NM_OBJ) $(FLAGS)
	@printf "\r\033[38;5;117m✓ MAKE $@ \033[0m\033[K\n"

ft_otool:	$(LIBFT_LIB) $(OBJ_DIR) $(OBJS) $(OTOOL_OBJ)
	@$(CC) $(OBJS) -o $@ \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) \
		$(LIBS) $(LIBFT_LIB) $(OTOOL_OBJ) $(FLAGS)
	@printf "\r\033[38;5;117m✓ MAKE $@ \033[0m\033[K\n"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(160 196 202 208 215 221 226 227 190 154 118 82 46); index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@printf "\r\033[38;5;%dm⌛ [%s]: %2d%% `printf '█%.0s' {0..$(DONE)}`%*s❙%*.*s\033[0m\033[K" $(COLOR) nm/otool $(PERCENT) $(TO_DO) "" $(DELTA) $(DELTA) "$(shell echo "$@" | sed 's/^.*\///')"
	@$(CC) $(FLAGS) $(OBJ_FLAG) -MMD -c $< -o $@\
		-I $(INC_DIR)\
		-I $(LIBFT_INC)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:			cleanlib
	@if [ -e $(OBJ_DIR) ]; then \
		rm -rf $(OBJ_DIR); \
		printf "\r\033[38;5;202m✗ clean $(NAME) \033[0m\033[K\n"; \
	fi;

cleanlib:
	@make -C $(LIBFT_DIR) clean

fclean:			clean fcleanlib
	@for file in $(NAME); do \
		if [ -e $$file ]; then \
			rm -f $$file ; \
			printf "\r\033[38;5;196m✗ fclean $$file\033[0m\033[K\n"; \
		fi; \
	done;

fcleanlib:		cleanlib
	@make -C $(LIBFT_DIR) fclean

re:				fclean all

relib:			fcleanlib $(LIBFT_LIB)

.PHONY :		fclean clean re relib cleanlib fcleanlib $(MACH_SRC)

-include $(OBJS:.o=.d)
