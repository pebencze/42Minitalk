CLIENT = client
SERVER = server
HEADER = minitalk.h
HEADER_BONUS = minitalk_bonus.h
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJS = server.o client.o
OBJS_BONUS = server_bonus.o client_bonus.o

all: $(SERVER) $(CLIENT) ft_printf

$(SERVER): server.o
	$(CC) $(CFLAGS) $^ -o $@ -L Ft_printf -lftprintf

$(CLIENT): client.o
	$(CC) $(CFLAGS) $^ -o $@ -L Ft_printf -lftprintf

bonus: $(SERVER_BONUS) $(CLIENT_BONUS) ft_printf

$(SERVER_BONUS): server_bonus.o
	$(CC) $(CFLAGS) $< -o $@ -L Ft_printf -lftprintf

$(CLIENT_BONUS): client_bonus.o
	$(CC) $(CFLAGS) $< -o $@ -L Ft_printf -lftprintf

%_bonus.o: %_bonus.c
	$(CC) $(CFLAGS) -I $(HEADER_BONUS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

ft_printf:
	make -C Ft_printf

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	make -C Ft_printf clean

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	make -C Ft_printf fclean

re:
	make fclean all

.PHONY: ft_printf all clean fclean re bonus


