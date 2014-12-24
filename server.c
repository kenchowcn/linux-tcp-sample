#include <stdio.h>
#include <string.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  

#define PORT 8800

int main(int argc, char *argv[])  
{  
    int sfd, new_fd;
    int len;  
    struct sockaddr_in local_addr, remote_addr;
    char buf[BUFSIZ];

    if(0 > (sfd=socket(PF_INET, SOCK_STREAM, 0)))
    {    
        perror("socket");  
        return -1;  
    }
	
    memset(&local_addr, 0,sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_port=htons(PORT);
   
    if (0 > bind(sfd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr)))  
    {  
        perror("bind");  
        return -1;  
    }  
    
    listen(sfd, 10);  
      
    len = sizeof(struct sockaddr_in);  
    if (0 > (new_fd = accept(sfd, (struct sockaddr *)&remote_addr, &len)))  
    {  
        perror("accept");  
        return -1;  
    }
	
    printf("Start server ... \n");
    while(1)
    {  
	len = recv(new_fd, buf, BUFSIZ, 0);
        buf[len] = '\0';
        printf("recv: %s\n", buf);  
        
        if(0 > send(new_fd, buf, len, 0))  
        {  
            perror("write");
            return -1;  
        }  
    }

    close(new_fd);  
    close(sfd);  
    
    return 0;  
}  
