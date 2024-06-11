
NAME 			= cub3D

SRCS_LIST		=	main.c \
					gnl_utils.c \
					gnl.c \
					free_data.c \
					parse_map.c \
					parse_data.c \
					ft_itoa.c \
					move_on_map.c \
					init_window.c \
					put_texture.c \
					draw_in_window.c \
					raycasting.c \
					main_func.c \
					draw_func.c \
					gnl_test.c \
					change_sight.c

SRCS_LIST_BONUS		=	main_bonus.c \
					gnl_utils_bonus.c \
					gnl_bonus.c \
					free_data_bonus.c \
					parse_map_bonus.c \
					parse_data_bonus.c \
					ft_itoa_bonus.c \
					move_on_map_bonus.c \
					init_window_bonus.c \
					put_texture_bonus.c \
					draw_in_window_bonus.c \
					raycasting_bonus.c \
					main_func_bonus.c \
					draw_func_bonus.c \
					gnl_test_bonus.c \
					change_sight_bonus.c

FOLDER			= srcs

FOLDER_BONUS	= srcs_bonus

SRCS			= $(addprefix ${FOLDER}/, ${SRCS_LIST})

SRCS_BONUS		= $(addprefix ${FOLDER_BONUS}/, ${SRCS_LIST_BONUS})

OBJS			= ${SRCS:.c=.o}

OBJS_BONUS		= ${SRCS_BONUS:.c=.o}

HEADER			= header

HEADER_BONUS	= header_bonus

OBJDIR			= obj

CC				= cc

CFLAGS 			= -Wall -Wextra -Werror -g

RM				= rm -rf

LINK			= ar rc 
 
MYLIB 			= mylib.a

PATH_MLX_LINUX 	= ./mlx/

MLX_LINUX		= ./mlx/libmlx_Linux.a

all:		${NAME}

%.o: %.c
			${CC} ${CFLAGS} -o $@ -c $<

$(NAME):	${OBJS} ${HEADER} 
			${LINK} ${MYLIB} ${OBJS}
			ranlib ${MYLIB}
			make -C ${PATH_MLX_LINUX}
			${CC} ${FLAGS} -o3 ${MYLIB} ${MLX_LINUX} -lm -lbsd -lX11 -lXext -o ${NAME}

bonus:		fclean ${OBJS_BONUS} ${HEADER_BONUS} 
			${LINK} ${MYLIB} ${OBJS_BONUS}
			ranlib ${MYLIB}
			make -C ${PATH_MLX_LINUX}
			${CC} ${FLAGS} -o3 ${MYLIB} ${MLX_LINUX} -lm -lbsd -lX11 -lXext -o $(NAME)

clean:
			${RM} ${OBJS} ${OBJDIR} ${OBJS_BONUS}

fclean:		clean
			${RM} ${NAME} ${MYLIB}

move:			${OBJS}
				mkdir -p ${OBJDIR} && mv ${OBJS} ${OBJDIR}

re:			fclean all

rebonus:	fclean bonus

.PHONY: 	all clean fclean re rebonus bonus move