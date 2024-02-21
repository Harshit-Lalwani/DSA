#ifndef PLATFORM_H
#define PLATFORM_H
#include"post.h"
#include "comment.h"
#include "reply.h"
#include<stdbool.h>

typedef struct Platform{
    Post* posts;
    Post* end;
    Post* lastViewedPost;
}Platform;

Platform* createPlatform();
bool addPost(char* username, char* content);
Post* viewPost(int n);
bool deletePost(int n);
Post* currPost(void);
Post* nextPost(void);
Post* previousPost(void);
bool addComment(char* username, char* content);
bool deleteComment(int n);
Comment* viewComments(void);
bool addReply(char* username, char* content, int n);
bool deleteReply(int n, int m);
void printPost(Post* post);
void printReply(Reply* replies);
void printComments(Comment* comments);

#endif