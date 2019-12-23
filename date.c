/*********************************************************************************
 *      Copyright:  (C) 2019 tianjincheng<473892093@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  date.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(2019年12月23日)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "2019年12月23日 21时29分32秒"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>          /*  See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

#define   MAXLINE    1024

int
main (int argc, char **argv)
{
    int                    sockfd, n;
    char                   recvline[MAXLINE];
    struct sockaddr_in     serveraddr;
    int                    port = 22;
    memset( recvline, 0, sizeof(recvline));
    if (argc != 2)
    {
        printf("usage: a.out <Ipaddress>\n");
        exit(0);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket[%d] error :%s\a\n", sockfd, strerror(errno));
    }

    bzero(&serveraddr, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port   = htons(port);
    if (inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) <= 0) 
    {
        printf("inet_pton error: %s\a\n", strerror(errno));
        exit(0);
    }

    if (connect(sockfd, (struct  sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        printf("connect error :%s\a\n", strerror(errno));
        exit(0);
    }
    printf("connect[%s:%d] successfully!\n", argv[1],port);

    if ((n = read(sockfd, recvline, MAXLINE)) < 0)
    {
        printf("read error :%s\a\n", strerror(errno));
        exit(0);
        
    }
    
    printf("Read data is :%s\n", recvline);

    close(sockfd);
    return 0;
} 


