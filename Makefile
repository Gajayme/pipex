# NAMES
NAME		=	pipex
NAME_B		= 	pipex_bonus

#DIRS
DIR_L	=	lib
DIR_M	=	mandatory
DIR_B		=	bonus

#LIB
LIBFT	=	libft.a

#RMS
RM_DIR		=	rm -rf
RM_FILE		=	rm -f

#RULES
all:	
		make -C ${DIR_L}/ all
		make -C ${DIR_M}/ all
		cp ${DIR_M}/${NAME} ${NAME} 

bonus:	
		make -C ${DIR_L}/ all
		make -C ${DIR_B}/ all
		cp ${DIR_B}/${NAME_B} ${NAME_B}

clean:
		make -C ${DIR_L}/ clean
		make -C ${DIR_M}/ clean
		make -C ${DIR_B}/ clean
		
fclean:	
		make -C ${DIR_L}/ fclean	
		make -C ${DIR_M}/ fclean
		make -C ${DIR_B}/ fclean
		${RM_FILE} $(NAME)
		${RM_FILE} $(NAME_B)
		
re:		fclean all

#OTHER
.PHONY: all bonus clean fclean re
