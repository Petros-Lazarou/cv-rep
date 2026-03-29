#include <asm-generic/socket.h>

#include "Hotels.c"
#define PORT 4444
#define BUF_SIZE 3500
#define CLADDR_LEN 100
#define MAX_THREADS 5

void *thread_func1(void *arg);
hotel_t *l_Hotels;
pthread_mutex_t l_mutex;
atomic_short thread_fl[MAX_THREADS];
typedef struct thread_args
{
  struct sockaddr_in *addr;
  struct sockaddr_in *cl_addr;
  int sockfd;
  int newsockfd;
  int len;
  int ret;
  int stat;
  int pos;
} arg_th;
typedef struct unique_thread_arg
{
  arg_th *l_thread;
  int num;
  char *buffer;
} u_thread;
void main()
{
  int l_stat;
  void *address = 0;
  struct sockaddr_in addr, cl_addr;
  int sockfd, len, ret, newsockfd;
  char *buffer;
  int j = 0;
  int optval = 1;
  pid_t childpid;
  char clientAddr[CLADDR_LEN];
  pthread_t loc_thread[MAX_THREADS];
  int creation_stat = 0;
  
  for (size_t i = 0; i < MAX_THREADS; i++)
  {
    thread_fl[i] = 2;
  }

  // --- 1. MOVED THESE HERE (Before the socket and loops) ---
  pthread_mutex_init(&l_mutex, NULL);
  l_Hotels = malloc(sizeof(hotel_t) * MAX_HOTELS);
  read_hotels(l_Hotels); 
  // --------------------------------------------------------

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    printf("Error creating socket!\n");
    exit(1);
  }
  printf("Socket created...\n");
  
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
  
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port =PORT;

  ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  if (ret < 0)
  {
    printf("Error binding!\n");
    exit(1);
  }
  printf("Binding done...\n");
  
  //printHotels(l_Hotels); 
  
  printf("Waiting for a connection...\n");
  listen(sockfd, 10);
  
  while (1)
  {

    while (1)
    {
      if (thread_fl[j] == 2 || thread_fl[j] == 1)
      {
        break;
      }
      j++;
      if (j == MAX_THREADS)
      {
        j = 0;
      }
      sleep(1);
    }
    len = sizeof(cl_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cl_addr, &len);
    if (newsockfd < 0)
    {
      printf("Error accepting connection!\n");
    }
    printf("Connection accepted...\n");

    inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
    
    
    arg_th *l_thread;
    l_thread = malloc(sizeof(arg_th));
    l_thread->addr = &addr;
    l_thread->cl_addr = &cl_addr;
    l_thread->len = len;
    l_thread->ret = ret;
    l_thread->sockfd = sockfd;
    l_thread->newsockfd = newsockfd;
    u_thread *thread_arguements = malloc(sizeof(u_thread));
    thread_arguements->l_thread = l_thread;
    
    for (size_t i = 0; i < MAX_THREADS; i++)
    {
      if (thread_fl[i] == 1)
      {
        pthread_join(loc_thread[i], &address);
        thread_fl[i] = 2;
      }
      for (size_t i = 0; i < MAX_THREADS; i++)
      {
        if (thread_fl[i] == 2)
        {
          thread_arguements->num = i;
          thread_fl[i] = 0;
          if (!pthread_create(&loc_thread[i], NULL, thread_func1, (void *)thread_arguements))
          {
            creation_stat = 1;
            break;
          };
        }
      }
      if (creation_stat == 1)
      {
        creation_stat = 0;
        break;
      }
    }
  
  }
}
void *thread_func1(void *arg)
{
  current_year = get_currentyear();
  u_thread *thread_struct = (u_thread *)arg;
  arg_th *struct_ptr = thread_struct->l_thread;
  thread_struct->buffer = malloc(BUF_SIZE);
  int number_of_beds = 0;
  int min_price = 0;
  int max_price = 0;
  char *Hotel_location = malloc(50);
  char **args = malloc(4 * sizeof(char *));
  for (size_t i = 0; i < 4; i++)
  {
    args[i] = malloc(50);
  }
    read_hotels(l_Hotels);

  send(struct_ptr->newsockfd, "READY", 6, 0);
  memset(thread_struct->buffer, 0, BUF_SIZE);
  struct_ptr->ret = recv(struct_ptr->newsockfd, thread_struct->buffer, BUF_SIZE, 0);
  if (struct_ptr->ret < 0)
  {
    perror("Recieve");
    printf("Error receiving data!\n");
  }
  args[0] = strtok(thread_struct->buffer, "\\\n");
  for (size_t i = 1; i < 4; i++)
  {
    args[i] = strtok(NULL, "\\\n");
  }
  
  number_of_beds = (int)strtol(args[1], NULL, 10);
  min_price = (int)strtol(args[2], NULL, 10);
  max_price = (int)strtol(args[3], NULL, 10);
  strcpy(Hotel_location, args[0]);
  printf("%s\n", thread_struct->buffer);
  bzero(thread_struct->buffer, BUF_SIZE);
 
  char *info_loc;                                                 
  hotel_t *eligible_rooms = malloc(sizeof(hotel_t) * MAX_HOTELS); 
  info_loc = results_st(l_Hotels, eligible_rooms, Hotel_location, number_of_beds, min_price, max_price);
 
  bzero(thread_struct->buffer, BUF_SIZE);
  strcpy(thread_struct->buffer, info_loc);
  if ((send(struct_ptr->newsockfd, thread_struct->buffer, BUF_SIZE, 0) == -1))
  {
    perror("Error in sending the text");
  }
  char *hotel_name;
  char *room_num = malloc(10);
  int room_number;
    hotel_t *l_hotel = malloc(sizeof(hotel_t));
  room_t *l_room = malloc(sizeof(room_t));
  while(1){
  bzero(thread_struct->buffer, BUF_SIZE);
  strcpy(thread_struct->buffer," ");
  if (recv(struct_ptr->newsockfd, thread_struct->buffer, BUF_SIZE, 0)<0)
  {
    perror("There was an error in reieving");
  }
  printf("Recieved from client %s\n", thread_struct->buffer);
  
  hotel_name = strtok(thread_struct->buffer, "\\\n");
  room_num = strtok(NULL, "\\\n");
  room_number = strtol(room_num, NULL, 10);
  if (room_hotel_validity(eligible_rooms, l_hotel, l_room, hotel_name, room_number))
  {
    printf("Is valid\n");
    bzero(thread_struct->buffer, BUF_SIZE);
    strcpy(thread_struct->buffer, "The room is valid,\n Enter the days you would like to make the reservation.\n");
    send(struct_ptr->newsockfd, thread_struct->buffer, BUF_SIZE, 0);
    bzero(thread_struct->buffer, BUF_SIZE);

    break;
  }
  else
  {
    printf("Is not valid\n");
    bzero(thread_struct->buffer, BUF_SIZE);
    strcpy(thread_struct->buffer, "The information you entered is not valid\n");

    send(struct_ptr->newsockfd, thread_struct->buffer, BUF_SIZE, 0);
          printf("Here we go again\n");

  }
}
  recv(struct_ptr->newsockfd, thread_struct->buffer, BUF_SIZE, 0);
  printf("Buffer:%s", thread_struct->buffer);
  char **reservation_date_st = malloc(2000);
  long reservation_date_num[6];
  for (size_t i = 0; i < 6; i++)
  {
    reservation_date_st = malloc(1000);
  }
  reservation_date_st[0] = strtok(thread_struct->buffer,"/\\\n");
  for (size_t i = 1; i < 6; i++)
  {
    reservation_date_st[i] = strtok(NULL,"\\/ \n");
  }
  for (size_t i = 0; i < 6; i++)
  {
    reservation_date_num[i] = strtol(reservation_date_st[i], NULL, 10);
  }
  
  pthread_mutex_lock(&l_mutex);
  hotel_to_reserve=0;
  room_to_reserve=0;
  read_hotels(l_Hotels);
  int l_price=reservation_server(l_Hotels,*l_hotel,*l_room,reservation_date_num);
  char* l_price_st=malloc(10);
 if(l_price)
 {
  bzero(thread_struct->buffer,BUF_SIZE);
  strcpy(thread_struct->buffer,"You were able to make the reservation and the price is \n");
  sprintf(l_price_st,"%d",l_price);
  strcat(thread_struct->buffer,l_price_st);
  strcat(thread_struct->buffer,"$\n");
  flush_reservations(l_Hotels[hotel_to_reserve].ptr[room_to_reserve].starting_node_l,l_Hotels[hotel_to_reserve].ptr[room_to_reserve],1);
 }
 else
 {
  bzero(thread_struct->buffer,BUF_SIZE);
  strcpy(thread_struct->buffer,"You were not able to make the reservation\n");
 }
   sendto(struct_ptr->newsockfd, thread_struct->buffer, BUF_SIZE, 0, (struct sockaddr *)&struct_ptr->cl_addr, struct_ptr->len);
pthread_mutex_unlock(&l_mutex);
  if (!strncmp(thread_struct->buffer, "exit", 4))
  {
    close(struct_ptr->newsockfd);
    thread_fl[thread_struct->num] = 1;
    
  }
  

  close(struct_ptr->newsockfd);
  thread_fl[thread_struct->num] = 1;
  
}