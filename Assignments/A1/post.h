#ifndef POST_H
#define POST_H
#define MAX 200
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"comment.h"

//dealing with circular dependencies
typedef struct Comment Comment;
typedef struct Post Post;
//Nodes for a DOUBLY-LINKED list
typedef struct Post{
    char username[MAX];
    char caption[MAX];

    //comments are stored in a 2-linkedlist
    Comment* comments;
    Comment* endcom;

    //"comments" and "endcom" mark start and end of 2-LL
    Post* next;
    Post* prev;
}Post;

Post* createPost(char* username, char* caption);


#endif