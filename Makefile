NAME := pipex

### LIBFT ######################################################################

PATH_LIBFT := libft/

LIBFT := $(PATH_LIBFT)libft.a

### SRCS ######################################################################

PATH_SRCS += srcs/

# SRCS += main.c
SRCS += test.c

# srcs/parsing/

PATH_SRCS += srcs/parsing/

SRCS += get_files_and_commands.c
SRCS += get_commands.c

# srcs/utils/

PATH_SRCS += srcs/utils/

SRCS += free_data.c

vpath %.c $(PATH_SRCS)

### OBJS ######################################################################

PATH_OBJS := objs/

OBJS := $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

### HEADERS ######################################################################

PATH_INCLUDES := includes/
PATH_INCLUDES_LIBFT := $(PATH_LIBFT)includes/

HEADERS += $(PATH_INCLUDES)/pipex.h
HEADERS += $(PATH_INCLUDES)/parsing.h

### COMPILATION #####################################################################

CC := cc

CFLAGS += -Wall
CFLAGS += -Wextra
# CFLAGS += -Werror
CFLAGS += -g3

ifeq ($(debug), true)
	CFLAGS += -g3
endif

ifeq ($(sanitize), true)
	CFLAGS += -fsanitize=address,undefined -g3
endif

### COLORS ######################################################################

GREEN := \033[0;32m
BLUE := \033[0;34m
WHITE := \033[0;37m

### RULES ######################################################################

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

.PHONY: all clean fclean re
