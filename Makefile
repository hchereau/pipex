NAME := pipex

### LIBFT ######################################################################

PATH_LIBFT := libft/

LIBFT := $(PATH_LIBFT)libft.a

### SRCS ######################################################################

PATH_SRCS := srcs/

# SRCS += main.c
SRCS += test.c

vpath %.c $(PATH_SRCS)

### OBJS ######################################################################

PATH_OBJS := objs/

OBJS := $(patsubst %.c, $(PATH_OBJS)%.o, $(SRCS))

### HEADERS ######################################################################

PATH_INCLUDES := includes/
PATH_INCLUDES_LIBFT := $(PATH_LIBFT)includes/
INCLUDES += -I $(PATH_INCLUDES)
INCLUDES += -I $(PATH_INCLUDES_LIBFT)

HEADERS += $(PATH_INCLUDES)pipex.h

### COMPILATION #####################################################################

CC := cc

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror

### COLORS ######################################################################

GREEN := \033[0;32m
BLUE := \033[0;34m
WHITE := \033[0;37m

### RULES ######################################################################

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(BLUE)Compiling $(NAME)...$(WHITE)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(INCLUDES)
	@echo "$(GREEN)$(NAME) Compiled !$(WHITE)"

$(OBJS): $(PATH_OBJS)%.o: %.c $(HEADERS)
	@mkdir -p $(PATH_OBJS)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

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
