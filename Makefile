CC = gcc
CFLAGS = -Wall -Wextra -Werror -I -g
NAME = ft_ssl

_DEPS_MD5 = ft_md5.h
_DEPS_SHA256 = ft_sha256.h
DEPS = $(MD5_DIR)/$(_DEPS_MD5) $(SHA256_DIR)/$(_DEPS_SHA256)

SRC = ft_getopt.c \
	ft_add_mem.c \
	ft_lstfuncs.c \
	input.c \


MD5_DIR = ./md5
MD5_SRC = creating_arrays.c ft_md5.c main.c md5.c output.c parse_help.c process_msg.c
MD5 = $(patsubst %, $(MD5_DIR)/%, $(MD5_SRC))

SHA256_DIR = ./sha256
SHA256_SRC = creating_arrays.c ft_sha256.c sha256_main_algo.c work_with_msg.c output.c sha256_parse_help.c
SHA256 = $(patsubst %, $(SHA256_DIR)/%, $(SHA256_SRC))

SRC_OBJ =$(SRC:.c=.o)
MD5_OBJ = $(MD5:.c=.o)
SHA256_OBJ = $(SHA256:.c=.o)

OBJ = $(SRC_OBJ) $(MD5_OBJ) $(SHA256_OBJ)
LIBS = ./ft_printf/libftprintf.a

all: $(NAME)

$(LIBS):
	@+$(MAKE) -C ./libft


%.o: %.c $(DEPS)
	@echo "\033[0;32m\c"
	$(CC) -g -c -o $@ $< $(CFLAGS)
	@echo "\033[0m\c"

$(NAME): $(OBJ) $(LIBS)
	@echo "\033[0;35m\c"
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	@echo "\033[0m\c"

md5: $(MD5_OBJ) $(LIBS)
	@echo "\033[0;34m\c"
	$(CC) -g -o ft_ssl_$@ $^ $(CFLAGS) $(LIBS)
	@echo "\033[0m\c"

sha256: $(SHA256_OBJ) $(LIBS)
	@echo "\033[0;34m\c"
	$(CC) -g -o ft_ssl_$@ $^ $(CFLAGS) $(LIBS)
	@echo "\033[0m\c"

clean:
	@/bin/rm -f $(OBJ)
	@+$(MAKE) clean -C ./libft

fclean: clean
	@/bin/rm -f $(NAME)
	@+$(MAKE) fclean -C ./libft


re: fclean all

.PHONY: clean fclean re
