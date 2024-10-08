NAME := pipex

### LIBFT ######################################################################

PATH_LIBFT := libft/

LIBFT := $(PATH_LIBFT)libft.a

### SRCS ######################################################################

PATH_SRCS += srcs/

SRCS += main.c
# SRCS += test.c

# srcs/parsing/

PATH_SRCS += srcs/parsing/

SRCS += get_files_and_cmds_from_strs.c
SRCS += get_cmds.c
SRCS += get_files.c

# srcs/exec/

PATH_SRCS += srcs/exec/

# srcs/utils/

PATH_SRCS += srcs/utils/

SRCS += free_data.c
SRCS += free_cmds.c

vpath %.c $(PATH_SRCS)

### OBJS ######################################################################

PATH_OBJS := objs/

OBJS := $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

### HEADERS ######################################################################

PATH_INCLUDES := includes/
PATH_INCLUDES_LIBFT := $(PATH_LIBFT)includes/

HEADERS += $(PATH_INCLUDES)/pipex.h
HEADERS += $(PATH_INCLUDES)/parsing.h
HEADERS += $(PATH_INCLUDES)/exec.h

### COMPILATION #####################################################################

CC := cc

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += -g3

ifeq ($(debug), true)
	CFLAGS += -g3
endif

ifeq ($(sanitize), true)
	CFLAGS += -fsanitize=address,undefined -g3
endif

### COLORS #####################################################################

GREEN := \033[0;32m
BLUE := \033[0;34m
WHITE := \033[0;37m

### RULES ######################################################################

### LINT #######################################################################
CLANG_ANALYZE_OPTIONS = --analyze \
                        -Weverything \
                        -Wno-unknown-warning-option \
                        -Werror \
                        -ferror-limit=0 \
                        -Xanalyzer -analyzer-output=text \
                        -Xanalyzer -analyzer-config \
                        -Xanalyzer aggressive-binary-operation-simplification=true \
                        -Xanalyzer -analyzer-config \
                        -Xanalyzer unroll-loops=true

CPPCHECK_OPTIONS =  --enable=all \
					--inconclusive \
					--error-exitcode=1 \
					--suppress=missingIncludeSystem


all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(BLUE)Compiling $(NAME)...$(WHITE)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -I $(PATH_INCLUDES) -I $(PATH_INCLUDES_LIBFT)
	@echo "$(GREEN)$(NAME) Compiled !$(WHITE)"

$(OBJS): $(PATH_OBJS)%.o: %.c $(HEADERS)
	@mkdir -p $(PATH_OBJS)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(PATH_INCLUDES) -I $(PATH_INCLUDES_LIBFT)

$(LIBFT):
	@echo "$(BLUE)Compiling $(LIBFT) ...$(WHITE)"
	@$(MAKE) -sC $(PATH_LIBFT)
	@echo "$(GREEN)$(LIBFT) Compiled ! $(WHITE)"

clean:
	@echo "$(BLUE)Cleaning $(NAME) ...$(WHITE)"
	@$(RM) -r $(PATH_OBJS)
	@$(MAKE) -sC $(PATH_LIBFT) clean
	@echo "$(GREEN)$(NAME) Cleaned ! $(WHITE)"

fclean: clean
	@echo "$(BLUE)Full Cleaning $(NAME) ...$(WHITE)"
	@$(RM) $(NAME)
	@$(MAKE) -sC $(PATH_LIBFT) fclean
	@echo "$(GREEN)$(NAME) Fully Cleaned ! $(WHITE)"

re: fclean all

install_hooks:
	.scripts/install_hooks.sh

cppcheck: $(SRCS)
	cppcheck $(CPPCHECK_OPTIONS) $^ -I $(PATH_INCLUDES_LIBFT) -I $(PATH_INCLUDES)

clang_analyzer: $(SRCS)
	clang $(CLANG_ANALYZE_OPTIONS) $^ -I $(PATH_INCLUDES_LIBFT) -I $(PATH_INCLUDES)

norminette: $(SRCS) $(HEADERS)
	norminette $^

.PHONY: all clean fclean re cppcheck clang_analyzer norminette
