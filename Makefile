NAME		=	ProxyServer

INCLUDE		=	./srcs/

SRCS		=	./srcs/Server.cpp \
				./srcs/Client.cpp

OBJS		= ${SRCS:.cpp=.o}

CXX			= c++

RM			= rm -f

CPPFLAGS	= #-Wall -Wextra -Werror 

all:			${NAME}

$(NAME):		${OBJS} ${INCLUDE}
				${CXX} ./srcs/Server.o -o server
				${CXX} ./srcs/Client.o -o client

clean:
				${RM} ${OBJS}

fclean:			clean
				${RM} server client

re:				fclean all

.PHONY:			all clean fclean re