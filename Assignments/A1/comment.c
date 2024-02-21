#include "comment.h"

Comment* createComment( char* username, char* content)
{
    Comment* comment = (Comment*)malloc(sizeof(Comment));
    strcpy(comment->username, username);
    strcpy(comment->content, content);
    comment->replies = createReply("leftrep","leftrep");
    comment->endrep = createReply("righrep","rightrep");
    comment->replies->next = comment->endrep;
    comment->endrep->prev = comment->replies;
    comment->replies->prev = NULL;
    comment->endrep->next = NULL;
    return comment;
}