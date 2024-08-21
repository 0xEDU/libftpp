NAME = libftpp.a
TEST_NAME = libftpp_test

PATH_SRCS = ./srcs/
PATH_TESTS = ./tests/
PATH_INCLUDES = ./includes/
PATH_OBJS = ./objs/

CXFLAGS = -Wall -Wextra -Werror --std=c++20

OBJS = $(SRCS:%.cpp=$(PATH_OBJS)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(PATH_OBJS)%.o: $(PATH_SRCS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@clang++ $(CXFLAGS) -I $(PATH_INCLUDES) -c $< -o $@
	@echo "[\033[32mSUCCESS\033[0m] Compiled $<"

clean:
	@rm -f $(OBJS) $(TEST_OBJS)
	@echo "[\033[31mDELETED\033[0m] Objects"

fclean: clean
	@rm -f $(NAME) $(TEST_NAME)
	@echo "[\033[31mDELETED\033[0m] $(NAME) $(TEST_NAME)"

.PHONY: all clean fclean re test
