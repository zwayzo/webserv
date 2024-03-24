NAME = webserv

FLAGS = c++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3

SRC =   configFile/config.cpp  main.cpp multuplixing/multuplixing.cpp methodes/post.cpp request/request.cpp multuplixing/sockets.cpp multuplixing/mulTools.cpp \
		configFile/tools.cpp configFile/tools2.cpp configFile/tools3.cpp request/parseRequest.cpp methodes/post_utils.cpp

all : $(NAME) $(SRC) 

$(NAME) : $(SRC)	
	$(FLAGS) $(SRC) -o $(NAME)
clean : 
		rm -fr  $(NAME)

fclean : clean
		rm -fr $(NAME) 

re : clean all
