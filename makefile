NAME = webserv

FLAGS = c++ -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3

SRC =  config.cpp  main.cpp multuplixing.cpp

all : $(NAME) $(SRC) 

$(NAME) : $(SRC)	
	$(FLAGS) $(SRC) -o $(NAME)
clean : 
		rm -fr  $(NAME)

fclean : clean
		rm -fr $(NAME) 

re : clean all
