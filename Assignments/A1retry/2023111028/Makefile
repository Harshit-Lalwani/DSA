CC=gcc

all:
	$(CC) code/main.c code/platform.c code/post.c code/comment.c code/reply.c -fsanitize=address
	./a.out