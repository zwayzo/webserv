NAME = webserv

FLAGS = c++ -Wall -Wextra -Werror #-std=c++11 #-fsanitize=address -g3

SRC =   configFile/config.cpp \
		main.cpp multuplixing/multuplixing.cpp \
		methodes/post.cpp methodes/post_utils.cpp \
		multuplixing/sockets.cpp multuplixing/mulTools.cpp \
		configFile/tools.cpp configFile/tools2.cpp \
		configFile/tools3.cpp \
		request/HttpRequest.cpp \
		request/requestBody.cpp \
		request/request.cpp \

all : $(NAME) $(SRC) 

$(NAME) : $(SRC)	
	$(FLAGS) $(SRC) -o $(NAME)
clean : 
		rm -fr  $(NAME)

fclean : clean
		rm -fr $(NAME) 

re : clean all
