#ifndef REPLY_H
#define REPLY_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 200
#include "post.h"

typedef struct Reply{
    char username[MAX];
    char content[MAX];
    struct Reply* next;
    struct Reply* prev;
}Reply;

Reply* createReply( char* username, char* content);

#endif
