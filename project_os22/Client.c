#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 4444
#define BUF_SIZE 3500

int main(int argc, char**argv) {
    struct sockaddr_in addr;
    int sockfd, ret;
    char buffer[BUF_SIZE];

    // 1. Stack arrays instead of malloc. Safer, faster, and prevents memory corruption.
    char search_args[4][100];
    char exit_flag[10];
    char name_reservation[50];
    char reservation_info[100];
    char room_reserved_st[20];
    
    int number_of_beds = 0;
    int min_price = 0;
    int max_price = 0;
    int room_to_reserve;
    int c;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("Error creating socket!\n");
        exit(1);
    }
    printf("Socket created...\n");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = PORT; 

    ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
    if (ret < 0) {
        printf("Error connecting to the server!\n");
        exit(1);
    }
    
    printf("Please hold on\n");
    while(1) {
        memset(buffer, 0, BUF_SIZE);
        if(recv(sockfd, buffer, BUF_SIZE - 1, 0) <= 0) break;
        if(!strncmp(buffer,"READY",5)) {
            break;
        }
    }

    printf("Connected to the server...\n");
    printf("Welcome to the Fantasy Hotels\n");
    memset(buffer, 0, BUF_SIZE);

    printf("Please enter the location of the hotel you are searching\n");
    fgets(search_args[0], 50, stdin);

    printf("Enter the number of beds\n");
    while(1) {
        if(fscanf(stdin,"%d",&number_of_beds) < 1) {
            printf("Please enter a valid number\n");
            while ((c = getchar()) != EOF && c != '\n'); 
            continue;
        }
        break;
    }

    printf("Enter the minimum price (Integers Only)\n");
    while(1) {
        if(fscanf(stdin,"%d",&min_price) < 1) {
            printf("Please enter a valid number\n");
            while ((c = getchar()) != EOF && c != '\n');
            continue;
        }
        break;
    }

    printf("Enter max price(Integers Only)\n");
    while(1) {
        if(fscanf(stdin,"%d",&max_price) < 1) {
            printf("Please enter a valid number\n");
            while ((c = getchar()) != EOF && c != '\n');
            continue;
        }
        if(max_price < min_price) {
            printf("Max price cannot be lower than min price. Try again.\n");
            continue;
        }
        break;
    }

    sprintf(search_args[1],"%d",number_of_beds);
    sprintf(search_args[2],"%d",min_price);
    sprintf(search_args[3],"%d",max_price);

    strcpy(buffer, search_args[0]);
    strcat(buffer, "\\");
    strcat(buffer, search_args[1]);
    strcat(buffer, "\\");
    strcat(buffer, search_args[2]);
    strcat(buffer, "\\");
    strcat(buffer, search_args[3]);

    // 2. Switched from sendto to send, and only sending the actual string length
    send(sockfd, buffer, strlen(buffer), 0);

    bzero(buffer, BUF_SIZE);
    recv(sockfd, buffer, BUF_SIZE - 1, 0);
    printf("%s\n", buffer);

    if(!strcmp(buffer,"There are no avalaible rooms according to your criterea\n")) {
        close(sockfd);
        exit(1);
    }

    // Flush the leftover newline from the max_price fscanf
    while ((c = getchar()) != EOF && c != '\n');

    bzero(buffer, BUF_SIZE);
    printf("In which hotel would you like to reserve a room? ");
    fgets(name_reservation, 50, stdin);
    
    printf("Type the number of the room you would like to reserve\n");
    fscanf(stdin,"%d",&room_to_reserve);

    strcpy(reservation_info, name_reservation);
    strcat(reservation_info, "\\");
    sprintf(room_reserved_st, "%d", room_to_reserve);
    strcat(reservation_info, room_reserved_st);
    
    strcpy(buffer, reservation_info);
    send(sockfd, buffer, strlen(buffer), 0);

    bzero(buffer, BUF_SIZE);
    recv(sockfd, buffer, BUF_SIZE - 1, 0);

    if(!strcmp(buffer,"The information you entered is not valid\n")) {
        printf("%s", buffer);
        close(sockfd);
        exit(1);
    }
    printf("%s", buffer);

    char checkin_date[30];
    char checkout_date[30];
    char reservation_date[100];

    // Flush the leftover newline from the room_to_reserve fscanf
    while ((c = getchar()) != EOF && c != '\n');

    printf("Enter the checkin date in the following format MM\\DD\\YY\n");
    fgets(checkin_date, 30, stdin);
    printf("Enter the checkout date\n");
    fgets(checkout_date, 30, stdin);

    strcpy(reservation_date, checkin_date);
    strcat(reservation_date, "\\");
    strcat(reservation_date, checkout_date);
    
    strcpy(buffer, reservation_date);
    send(sockfd, buffer, strlen(buffer), 0);

    bzero(buffer, BUF_SIZE);
    recv(sockfd, buffer, BUF_SIZE - 1, 0);
    printf("%s", buffer);

    if(!strcmp(buffer,"You were not able to make the reservation\n")) {
        close(sockfd);
        exit(1);
    }

    // 3. Removed the broken while(getchar()) loop that caused the program to freeze
    printf("Type exit to quit or else type anything else\n");
    fgets(exit_flag, 10, stdin);

    if(!strncmp(exit_flag, "exit", 4)) {
        send(sockfd, exit_flag, strlen(exit_flag), 0);
    }

    close(sockfd);
    return 0;
}