NAME		= philo

SRCDIR		= src
INCDIR		= includes
OBJDIR		= obj

SOURCES		= main.c \
			  init.c \
			  parse.c \
			  utils.c \
			  time.c \
			  thread.c \
			  routine.c \
			  routine_utils.c \
			  actions.c \
			  monitor.c

SRCS		= $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS		= $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
INCLUDES	= -I$(INCDIR)

RM			= rm -f
MKDIR		= mkdir -p

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re