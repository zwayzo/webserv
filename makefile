CPP = c++

FLAGS = -Wall -Wextra -Werror #-std=c++11 #-fsanitize=address -g3

SRC =   configFile/config.cpp \
		main.cpp multuplixing/multuplixing.cpp \
		methodes/post.cpp methodes/post_utils.cpp \
		multuplixing/sockets.cpp multuplixing/mulTools.cpp \
		configFile/tools.cpp configFile/tools2.cpp \
		configFile/tools3.cpp \
		request/HttpRequest.cpp \
		request/requestBody.cpp \
		request/request.cpp \
		response/HttpResponse.cpp \

OBJS = $(SRC:.cpp=.o)

NAME = webserv

$(NAME) : $(OBJS)
	@echo "\033[0;93m- Waiting ...\033[0m"
	@$(CPP) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "\033[0;32m- Webserver is ready ^^ \033[0m"

all : $(NAME) $(SRC)

clean :
	@rm -rf $(OBJS)
	@echo "\033[1;31m- Object files removed!\033[0m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[1;31m- All cleaned.\033[0;0m"

re : clean all

.SILENT : $(OBJS)

.PHONY: all clean fclean re

# $(NAME) : $(SRC)	
# 	$(FLAGS) $(SRC) -o $(NAME)
