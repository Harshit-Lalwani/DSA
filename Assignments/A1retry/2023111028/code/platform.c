#include "platform.h"
#include "comment.h"
#include "reply.h"
#include "post.h"

#include <stdbool.h>

// TODO
// 1. addPost should return true only if post is actually created
Platform *plat;

Platform *createPlatform()
{
    Platform *platform = (Platform *)malloc(sizeof(Platform));
    platform->posts = createPost("leftpost", "leftpost");
    platform->end = createPost("rightpost", "rightpost");
    // Make "posts" and "end" as borders of the 2-linkedlist
    platform->posts->prev = NULL;
    platform->posts->next = platform->end;
    platform->end->prev = platform->posts;
    platform->end->next = NULL;
    // Set end as the lvp when list is empty
    platform->lastViewedPost = platform->end;
    return platform;
}

bool addPost(char *username, char *content)
{
    bool posted = 0;
    Post *post = createPost(username, content);
    if (post != NULL)
    {
        post->next = plat->end;
        post->prev = plat->end->prev;
        plat->end->prev->next = post;
        plat->end->prev = post;
        posted = 1;
    }
    return posted;
}

Post *viewPost(int n)
{

    Post *post = plat->end;
    for (int i = 0; i < n; i++)
    {
        if (post->prev == plat->posts)
        {
            return NULL;
        }
        post = post->prev;
    }
    plat->lastViewedPost=post;
    return post;
}

bool deletePost(int n)
{
    bool deleted = 0;
    Post *post = viewPost(n);
    if(post == plat->lastViewedPost)
    {
        plat->lastViewedPost = plat->end;
    }
    if (post != NULL)
    {

        post->prev->next = post->next;
        post->next->prev = post->prev;

        // free replies, comments, and post
        Comment *comment = post->comments;
        while (comment != NULL)
        {
            Comment *nextComment = comment->next;
            Reply *reply = comment->replies;
            while (reply != NULL)
            {
                Reply *nextReply = reply->next;
                free(reply);
                reply = nextReply;
            }
            free(comment);
            comment = nextComment;
        }
        free(post);

        deleted = 1;
    }
    return deleted;
}

Post *currPost()
{
    Post *post;
    // no post has been made, return NULL
    if (plat->posts->next == plat->end)
    {
        return NULL;
    }
    // no post was viewed, assign most recent post to lvp and return it
    else if (plat->lastViewedPost == plat->end)
    {
        plat->lastViewedPost = plat->end->prev;
        post = plat->lastViewedPost;
    }
    // general case
    else
    {
        post = plat->lastViewedPost;
    }

    return post;
}

Post *nextPost()
{
    // NOTE: here next refers to post before current
    Post *post = currPost();

    // Case of no posts / any errors in prev functions
    if (post == NULL)
    {
        return NULL;
    }

    // Case of currPost not being the first post, general case
    else if (post->prev != plat->posts)
    {
        plat->lastViewedPost = plat->lastViewedPost->prev;
        post = plat->lastViewedPost;
    }

    // Note: if currPost is the first post, it will stay the same
    return post;
}

Post *previousPost()
{
    // NOTE: here previous refers to post after current
    Post *post = currPost();

    // Case of no posts / any errors in prev functions
    if (post == NULL)
    {
        return NULL;
    }

    // Case of currPost not being the latest post
    else if (post->next != plat->end)
    {
        plat->lastViewedPost = plat->lastViewedPost->next;
        post = plat->lastViewedPost;
    }

    // Note: if currPost is the latest post, it will stay the same

    return post;
}

bool addComment(char *username, char *content)
{
    bool commented = 0;
    Post *post = currPost();
    if (post != NULL)
    {
        Comment *comment = createComment(username, content);
        post->endcom->prev->next = comment;
        comment->prev = post->endcom->prev;
        post->endcom->prev = comment;
        comment->next = post->endcom;
        commented = 1;
    }

    return commented;
}

bool deleteComment(int n)
{
    bool deleted = 0;
    Post *post = currPost();
    if (post != NULL)
    {
        Comment *comment = post->endcom;

        for (int i = 0; i < n; i++)
        {
            // Check if comment doesn't exist
            if (comment->next == post->comments)
            {
                return deleted;
            }
            comment = comment->prev;
        }
        comment->prev->next = comment->next;
        comment->next->prev = comment->prev;

        // free replies and comment
        Reply *reply = comment->replies;
        while (reply != NULL)
        {
            Reply *nextReply = reply->next;
            free(reply);
            reply = nextReply;
        }
        free(comment);

        deleted = 1;
    }
    return deleted;
}

Comment *viewComments()
{
    Comment *comments = NULL;
    Post *post = currPost();
    if (post != NULL)
    {
        comments = post->comments;
    }
    // if post/list of comments is NULL, comments will be NULL
    return comments;
}

bool addReply(char *username, char *content, int n)
{
    bool replied = 0;
    Comment *comment = currPost()->endcom;

    //go to the nth recent comment


    for (int i = 0; i < n; i++)
    {
        // Check if comment doesn't exist; if so return 0
        if (comment->next == viewComments())
        {
            printf("comment doesn't exist\n");
            return replied;
        }
        comment = comment->prev;
    }
    printf("reached comment from %s\n", comment->username);

    if (comment != NULL && comment!= viewComments())
    {
        Reply *reply = createReply(username, content);
        comment->endrep->prev->next = reply;
        reply->prev = comment->endrep->prev;
        comment->endrep->prev = reply;
        reply->next = comment->endrep;
        replied = 1;
    }
    return replied;
}

bool deleteReply(int n, int m)
{
    /*Deletes the mth recent reply to the nth
    recent comment of the lastViewedPost,
    returning whether the deletion is successful or not*/

    bool deleted = 0;
    // Comment* comment = viewComments();

    // Reach end of comments using endcom
    Comment *comment = currPost()->endcom;

    // Reach desired comment
    for (int i = 0; i < n; i++)
    {
        // Check if comment doesn't exist
        if (comment->next == viewComments())
        {
            return deleted;
        }
        comment = comment->prev;
    }

    // Reach end of replies using endrep
    Reply *reply = comment->endrep;
    // Reach desired reply
    for (int i = 0; i < m; i++)
    {
        // Check if reply doesn't exist
        if (reply->next == comment->replies)
        {
            return deleted;
        }
        reply = reply->prev;
    }

    // Pop the node of reply
    reply->prev->next = reply->next;
    reply->next->prev = reply->prev;
    free(reply);
    deleted = 1;

    return deleted;
}

void printPost(Post *post)
{
    if (post == NULL)
    {
        printf("Encountered error in printing post!\n");
        return;
    }
    printf("Username: %s\n", post->username);
    printf("Caption: %s\n", post->caption);
}

void printReply(Reply *replies)
{
    if (replies->next->next == NULL)
    {
        printf("\t\tNo replies!\n");
        return;
    }
    Reply *reply = replies;
    reply = reply->next;
    while (reply->next != NULL)
    {
        printf("\t\tUsername: %s\n", reply->username);
        printf("\t\tContent: %s\n", reply->content);
        reply = reply->next;
    }
}

void printComments(Post* post)
{
    if (post->comments->next== post->endcom)
    {
        printf("\tNo comments on this post!\n");
        return;
    }
    Comment *comment1 = post->comments->next;
        while (comment1->next != NULL)
        {
            if(comment1==NULL)
            {
                printf("\tEncountered Null comment\n");
            }
            printf("\tUsername: %s\n", comment1->username);
            printf("\tContent: %s\n", comment1->content);
            comment1 = comment1->next;
            printReply(comment1->replies);
        }
}

void printPlatform()
    {
        Post* post = plat->posts;
        while(post->next->next!=NULL)
        {
            post = post->next;
            printPost(post);
        }
    }