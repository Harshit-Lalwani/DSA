#include"post.h"

Post* createPost(char* username, char* caption)
{
    Post* post = (Post*)malloc(sizeof(Post));
    strcpy(post->username, username);
    strcpy(post->caption, caption);
    post->comments = createComment("leftcomm","leftcomm");
    post->endcom = createComment("rightcomm","rightcomm");
    post->comments->next = post->endcom;
    post->endcom->prev = post->comments;
    post->comments->prev = NULL;
    post->endcom->next = NULL;
    return post;
}