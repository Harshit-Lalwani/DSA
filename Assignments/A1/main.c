#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"platform.h"
#include"post.h"
#include"comment.h"
#include"reply.h"

extern Platform* plat;

int main()
{
    int x;
    printf("Enter mode: ");
    scanf("%d", &x);
    if(x==1)
    {
        while(1)
    {
        printf("Please enter command\n");
        char com1[1000];
        char com2[1000];
        char com3[1000];
        char com4[1000];
        scanf("%s", com1);
        if(strcmp("create_platform",com1)==0)
        {
            plat = createPlatform();
        }
        else if(strcmp(com1,"add_post")==0)
        {
            scanf("%s", com2);
            scanf("%s", com3);
            if(addPost(com2, com3))
            {
                printf("Post added successfully!\n");
            }
        }
        else if(strcmp(com1,"delete_post")==0)
        {
            scanf("%s", com2);
            //atoi converts string to int
            if(deletePost(atoi(com2)))
            {
                printf("Post deleted successfully!\n");
            }
        }
        else if(strcmp(com1,"add_comment")==0)
        {
            scanf("%s", com2);
            scanf("%s", com3);
            if(addComment( com2, com3))
            {
                printf("Comment added successfully!\n");

            }
        }
        else if(strcmp(com1,"delete_comment")==0)
        {
            scanf("%s", com2);
            if(deleteComment(atoi(com2)))
            {
                printf("Comment deleted successfully!\n");
            }
        }
        else if(strcmp(com1,"add_reply")==0)
        {
            scanf("%s", com2);
            scanf("%s", com3);
            scanf("%s", com4);
            if(addReply(com2, com3,atoi(com4)))
            {
                printf("Reply added successfully!\n");
            }
        }
        else if(strcmp(com1,"delete_reply")==0)
        {
            scanf("%s", com2);
            scanf("%s", com3);
            if(deleteReply(atoi(com2), atoi(com3)))
            {
                printf("Reply deleted successfully!\n");
            }
        }
        else if(strcmp(com1,"view_post")==0)
        {
            scanf("%s", com2);
            printPost(viewPost(atoi(com2)));
        }
        else if(strcmp(com1,"current_post")==0)
        {
            printPost(currPost());
        }
        else if(strcmp(com1,"previous_post")==0)
        {
            printPost(previousPost());
        }
        else if(strcmp(com1,"next_post")==0)
        {
            printPost(nextPost());
        }
        else if(strcmp(com1,"view_comments")==0 || strcmp(com1,"view_all_comments")==0)
        {
            printComments(currPost());
        }
        else if(strcmp(com1,"print_platform")==0)
        {
            printPlatform();
        }
        else{
            printf("Please enter valid command\n");
        }
    }

    }

    else{
        plat = createPlatform();
        addPost("user1", "post1");
        addPost("user2", "post2");
        addPost("user3", "post3");
        addPost("user4", "post4");
        addPost("user5", "post5");
        printf("Printing platform after adding 5 posts\n");
        printPlatform();
        printf("Printing 2nd last post\n");
        printPost(viewPost(2));
        printf("adding comment\n");
        printf("\n%d\n",addComment("user1", "comment1"));
        Post* poster = currPost();
        printf("Printing comments\n");
        // poster->comments;
    }
}