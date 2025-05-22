NAME = libftpp.a
TEST_NAME = libftpp_test

PATH_SRCS = ./sources/
PATH_TESTS = ./tests/
PATH_TESTS_OUT = ./bin/
PATH_INCLUDES = ./includes/
PATH_OBJS = ./objs/

SRCS =	client.cpp \
		data_buffer.cpp \
		memento.cpp \
		message.cpp \
		persistent_worker.cpp \
		server.cpp \
		thread_safe_iostream.cpp \
		thread.cpp \
		worker_pool.cpp \
		ivector2.cpp \
		ivector3.cpp \
		random_2D_coordinate_generator.cpp \
		perlin_noise_2D.cpp \
		chronometer.cpp \
		logger.cpp \
		test_helper.cpp

TEST_SRCS =	main_client.cpp \
			main_data_buffer.cpp \
			main_memento.cpp \
			main_observer.cpp \
			main_persistant_worker.cpp \
			main_pool.cpp \
			main_server.cpp \
			main_singleton.cpp \
			main_state_machine.cpp \
			main_thread.cpp \
			main_thread_safe_iostream.cpp \
			main_thread_safe_queue.cpp \
			main_worker_pool.cpp \
			main_ivector2.cpp \
			main_ivector3.cpp \
			main_random_2D_coordinate_generator.cpp \
			main_perlin_noise_2D.cpp \
			main_chronometer.cpp \
			main_logger.cpp

TEST_NAMES = $(patsubst %.cpp,%, $(TEST_SRCS))

CXFLAGS = -Wall -Wextra -Werror --std=c++20 -ggdb

OBJS = $(SRCS:%.cpp=$(PATH_OBJS)%.o)
TEST_OBJS = $(TEST_SRCS:%.cpp=$(PATH_OBJS)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(PATH_OBJS)%.o: $(PATH_SRCS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@clang++ $(CXFLAGS) -I $(PATH_INCLUDES) -c $< -o $@
	@echo "[\033[32mSUCCESS\033[0m] Compiled $<"

$(PATH_OBJS)%.o: $(PATH_TESTS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@clang++ $(CXFLAGS) -I $(PATH_INCLUDES) -c $< -o $@
	@echo "[\033[32mSUCCESS\033[0m] Compiled $<"

tests: $(NAME) $(addprefix $(PATH_TESTS_OUT),$(TEST_NAMES))

define COMPILE_TEST_TEMPLATE
$(PATH_TESTS_OUT)$(1): $(PATH_OBJS)$(1).o $(NAME)
	@mkdir -p $(PATH_TESTS_OUT)
	@clang++ $(CXFLAGS) $$< $(NAME) -o $$@
	@echo "[\033[32mSUCCESS\033[0m] Linked $(1)"
endef

$(foreach test,$(TEST_NAMES),$(eval $(call COMPILE_TEST_TEMPLATE,$(test))))

clean:
	@rm -f $(OBJS) $(TEST_OBJS)
	@echo "[\033[31mDELETED\033[0m] Objects"

fclean: clean
	@rm -rf $(NAME) $(PATH_TESTS_OUT) $(PATH_OBJS)
	@echo "[\033[31mDELETED\033[0m] $(NAME) $(PATH_TESTS_OUT) $(PATH_OBJS)"

re: fclean all

retests: fclean tests

.PHONY: all clean fclean re tests retests
