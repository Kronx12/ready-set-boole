CC=clang++
RM=rm -rf
NAME=ex05

SRCS_DIR=srcs
INCS_DIR=includes
SRCS:=$(wildcard ./$(SRCS_DIR)/*.cpp)
INCS=$(wildcard ./$(INCS_DIR)/*.hpp)
OBJS:=$(SRCS:.cpp=.o)

DEBUG=-DDEBUG=1
FSANITIZE=-fsanitize=address
FLAGS=-Wall -Wextra -Werror -g $(FSANITIZE) -I$(INCS_DIR)

%.o:%.cpp
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(OBJS): $(INCS)

$(NAME): $(OBJS) $(INCS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

debug:
	$(eval FLAGS += $(DEBUG))

run: $(NAME)
	./$(NAME)

run_debug: debug clean $(NAME)
	./$(NAME)

re: fclean all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

.PHONY: all clean fclean re run debug run_debug