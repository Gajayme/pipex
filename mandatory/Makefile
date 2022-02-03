#NAMES
NAME		=	pipex

#COMP
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror

#LIBFT
LIB_DIR	=	../lib
LIBFT	=	libft.a

#INCLUDES
HEADER		=	pipex.h
INCLUDES	= 	-I .

#SC
SRC			=	pipex.c \
				utils.c

#OBJ
OBJ_DIR	=	obj
OBJ 		=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

#RMS
RM_DIR		=	rm -rf
RM_FILE		=	rm -f


#DEPS
${NAME}:	${OBJ}
			$(CC) -o $(NAME) $(OBJ) $(FLAGS) ${LIB_DIR}/${LIBFT}
									
$(OBJ)		:	| $(OBJ_DIR)

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)
			
$(OBJ_DIR)/%.o :	%.c $(HEADER) Makefile
					${CC} $(FLAGS) $(INCLUDES) -o $@ -c $<

#RULES			
all:	$(NAME)

clean:
		${RM_DIR} ${OBJ_DIR}
		
fclean:	clean
		${RM_FILE} $(NAME)
		
re:		fclean all

#OTHER
.PHONY: all clean fclean re
