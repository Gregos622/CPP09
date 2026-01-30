NAME=PmergeMe
SRCS=main.cpp PmergeMe.cpp

CXX=g++

FLAGS=-Wall -Wextra -Werror -std=c++98 -g

OBJDIR=obj

OBJS=$(SRCS:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all