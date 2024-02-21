#ifndef COMMENT_H
#define COMMENT_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"reply.h"

#define MAX 200

typedef struct Comment{
    char username[MAX];
    char content[MAX];

    //Reply is a 2-linkedlist
    struct Reply* replies;
    struct Reply* endrep;
    //endrep marks the end of 2-LL

    struct Comment* next;
    struct Comment* prev;
}Comment;

Comment* createComment( char* username, char* content);

#endif