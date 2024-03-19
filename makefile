NAME = webserv

FLAGS = c++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3

SRC =   configFile/config.cpp  main.cpp multuplixing/multuplixing.cpp multuplixing/post.cpp multuplixing/sockets.cpp multuplixing/parseRequest.cpp multuplixing/mulTools.cpp \
		configFile/tools.cpp configFile/tools2.cpp configFile/tools3.cpp 

all : $(NAME) $(SRC) 

$(NAME) : $(SRC)	
	$(FLAGS) $(SRC) -o $(NAME)
clean : 
		rm -fr  $(NAME)

fclean : clean
		rm -fr $(NAME) 

re : clean all
