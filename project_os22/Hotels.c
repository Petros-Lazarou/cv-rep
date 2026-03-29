#include "Room.c"

void printHotels(hotel_t Hotels[])
{
    int i=0;
    while(i<number_of_hotels){
        printf("The name of the %d hotel is: \n", i);
        for (int a=0;a<(sizeof(Hotels[i].name))-2;a++) 
        {
         printf("%c", Hotels[i].name[a]);
        } 
        printf("\n");
        printf("The number of rooms are:%d\n", Hotels[i].number_of_rooms);
        printf("The number of floors is %d\n",Hotels[i].number_of_floors);
        i++;
    }

}


void hotelSetter(hotel_t* l_hotel,hotel_t Hotels[],char hotel_name[50],char hotel_location[50],int number_of_floors,int number_of_rooms,int stars)
{   
    
    for (int i=0;i<=50;i++)
    {
            if(hotel_name[i]=='\0')
            {
                strcpy(l_hotel->name,hotel_name);
                break;
            }
            else if(i!=49)
            {
                continue;
            }
            else 
            {
                exit(1);
            }
    }


    for (int i=0;i<50;i++)
    {
            if(hotel_location[i]=='\0')
            {
                strcpy(l_hotel->location,hotel_location);
                break;
            }
            else if(i!=49)
            {
                continue;
            }
            else 
            {
                exit(1);
            }
    }
    if (stars >5)
    {
        printf("Wrong number of stars\n");
        exit(1);
    }
    else
    {
        l_hotel->stars=stars;
    }
    l_hotel->number_of_floors=number_of_floors;
    l_hotel->number_of_rooms=number_of_rooms;
    l_hotel->ID=number_of_hotels;
    l_hotel->current_rooms=0;
    l_hotel->ptr =(room_t*) malloc(sizeof(room_t)*l_hotel->number_of_rooms);
    number_of_hotels++;
}
void print_hotel_info(hotel_t l_hotel)
{
    printf("The hotel with the ID %d has the name %s . It is located in %s, it has a total of %d of rooms and it\'s rating is at %d stars. And it's number of floors is %d.\n",l_hotel.ID,l_hotel.name,l_hotel.location,l_hotel.number_of_rooms,l_hotel.stars,l_hotel.number_of_floors);
}
char* hotel_info_st(hotel_t l_hotel)
{
    char* stars=malloc(5);
    char* temp = malloc(300);
    strcpy(temp,l_hotel.name);
    strcat(temp,".The hotel is located in ");
    strcat(temp,l_hotel.location);
    strcat(temp,".The rating for this hotel stands at ");
    sprintf(stars,"%d",l_hotel.stars);
    strcat(temp,stars);
    strcat(temp,"stars. \n The rooms avalaible for this hotel are: \n");
    return temp;
}
char* room_info_st(room_t l_room)
{
    char* view = malloc(50);
    char* temp=malloc(250);
    char* room_number=malloc(4);
    char* floor_number = malloc(3);
    char* number_of_beds = malloc(3);
    char* price= malloc(10);
    char* seasonal_price= malloc(10);
    if(l_room.sea_view)
    {
        strcpy(view,"Has a sea view");
    }
    else
    {
        strcpy(view,"Does not have a sew view");
    }
    strcpy(temp,"The room number is ");
    sprintf(room_number,"%d",l_room.number_of_room);
    strcat(temp,room_number);
    strcat(temp,".The number of the floor is ");
    sprintf(floor_number,"%d",l_room.floor);
    strcat(temp,floor_number);
    sprintf(number_of_beds,"%lu",l_room.number_of_beds);
    strcat(temp,number_of_beds);
    strcat(temp,"\nThe normal price is: ");
    sprintf(price,"%d",l_room.price);
    strcat(temp,price);
    strcat(temp,"$ \n And the seasonal price is: ");
    sprintf(seasonal_price,"%d",l_room.seasonal_price);
    strcat(temp,seasonal_price);
    strcat(temp,"$\n");
    return temp;
}
void roomAdder(hotel_t Hotels[],room_t* room,int numberofhotel)
{
    
    if(room->floor>Hotels[numberofhotel].number_of_floors)
    {
        printf("Please enter valid floors");
        exit(1);
    }
    /*if(Hotels[number_of_hotels].current_rooms>Hotels[number_of_hotels].number_of_rooms)
    {
        printf("There is no more capacity for rooms in the hotel\n");
        exit(1);
    }*/
   room_t *temp = malloc(sizeof(room_t));
    Hotels[numberofhotel].ptr[Hotels[numberofhotel].current_rooms] = *room;
    Hotels[numberofhotel].current_rooms++;
}

void flush_hotel(hotel_t hotel)
{
    char* Hotel_name;
    Hotel_name=malloc(20);
    char* num_of_hotel=malloc(5);
    strcpy(Hotel_name,"Hotel_No");
    sprintf(num_of_hotel,"%d",hotel.ID);
    strcat(Hotel_name,num_of_hotel);
    char* Hotel_info=malloc(40);
    strcpy(Hotel_info,"Info for Hotel number");
    strcat(Hotel_info,num_of_hotel);
    strcat(Hotel_info,".txt");
    mkdir(Hotel_name,0777);
    chdir(Hotel_name);
    FILE* l_fptr;
    l_fptr=fopen(Hotel_info,"w");
    fprintf(l_fptr,"%d\\%s\\%s\\%d\\%d\\%d\n",hotel.ID,hotel.name,hotel.location,hotel.number_of_rooms,hotel.stars,hotel.number_of_floors);
    fclose(l_fptr);
    FILE* fptr;
    char name[50];
    char* num=malloc(sizeof(hotel.ID)/4);
    char* affix = ".txt";

    strcpy(name,"Rooms_of_Hotel_");
    sprintf(num,"%d",hotel.ID);
    strcat(name,num);
    strcat(name,affix);

    fptr=fopen(name,"w");
    for (size_t i = 0; i < hotel.current_rooms; i++)
    {
        fprintf(fptr," %lu\\%d\\%d\\%d\\%d\\%d\n",hotel.ptr[i].number_of_beds,hotel.ptr[i].number_of_room,hotel.ptr[i].sea_view,hotel.ptr[i].floor,hotel.ptr[i].price,hotel.ptr[i].seasonal_price);
    }
    fclose(fptr);
    for (size_t i = 0; i < hotel.current_rooms; i++)
    {
        if(hotel.ptr[i].reservation_count)
        {
        flush_reservations(hotel.ptr[i].starting_node_l,hotel.ptr[i],0);
        }
    }
    
    chdir("..");
}
void room_reader(hotel_t Hotels[],int hotel_num)
{
    int k=0;
    room_t* l_room=malloc(sizeof(room_t));
    int counter=0;
    char name[50];
    int rooms_num[6];
    strcpy(name,"Rooms_of_Hotel_");
    char* affix = ".txt";
    char* room_number=malloc(sizeof(Hotels[hotel_num].ID)/4);
    sprintf(room_number,"%d",Hotels[hotel_num].ID);
    strcat(name,room_number);
    strcat(name,affix);
    FILE* line_counter;
    line_counter=fopen(name,"r");
    while(!feof(line_counter))
    {
        if(getc(line_counter)=='\n')
        {
            counter++;
        }
    }
    fclose(line_counter);
    FILE* loc_text;
    loc_text=fopen(name,"r");
    char rooms_info[counter][30];
    char** rooms_loc=malloc(sizeof(char*)* 6);
    for (size_t l = 0; l < 6; l++)
    {
        rooms_loc[l]=malloc(3);
    }
    
    for (size_t i = 0; i < counter; i++)
    {   k=0;
        fgets(rooms_info[i],30,loc_text);
        rooms_loc[k]=strtok(rooms_info[i],"\\ ");
        k++;
        while (rooms_loc[k]!=NULL)
        {
            rooms_loc[k]=strtok(NULL,"\\ ");
            k++;
        }
        for (size_t v = 0; v < 6; v++)
        {
            rooms_num[v]=strtol(rooms_loc[v],NULL,10);
        }
    
        init_room(l_room,rooms_num[0],rooms_num[1],rooms_num[2],rooms_num[3],rooms_num[4],rooms_num[5]);
        
       roomAdder(Hotels,l_room,hotel_num);
    }
    fclose(loc_text);
    
}
void print_hotel_rooms(hotel_t l_hotel)
{
    for (size_t i = 0; i < l_hotel.current_rooms; i++)
    {
        if(l_hotel.ptr[i].number_of_beds){
        print_room_info(l_hotel.ptr[i]);
        }
    }
    
}
char* hotel_rooms_st(hotel_t l_hotel)
{
    char* temp = malloc(l_hotel.current_rooms*250+10);
    for (size_t i = 0; i < l_hotel.current_rooms; i++)
    {
        if(l_hotel.ptr[i].number_of_beds){
            strcpy(temp," ");
            strcat(temp,room_info_st(l_hotel.ptr[i]));
        }
    }
    return temp;
}    
void BubbleSortRooms(hotel_t *l_hotel){
    room_t temp;
    for (size_t i = 0; i < l_hotel->current_rooms; i++)
    {
        for (size_t j = 0; j < l_hotel->current_rooms-1; j++)
        {
            if(l_hotel->ptr[j].number_of_room>l_hotel->ptr[j+1].number_of_room)
            {
                temp=l_hotel->ptr[j];
                l_hotel->ptr[j]=l_hotel->ptr[j+1];
                l_hotel->ptr[j+1]=temp;
            }
        }
        
    }
    
}


hotel_t* LinearSearch(hotel_t arr[],char given_loc[50],int bed_number,int min_price,int max_price)
{
    if(max_price<min_price)
    {
        printf("Enter Valid Prices\n");
        exit(1);
    }
    for (int i=0 ;i<MAX_HOTELS ;i++)
    {
    flag[i]=false;
    }
     matching_hotels=0;
    int loc_coun=0;
    hotel_t* temp;
    int ptr_size_f=1;
    temp=malloc(MAX_HOTELS*sizeof(hotel_t));
    room_t* temp_room;
    temp_room =malloc(sizeof(room_t)*5);
    for (size_t i = 0; i < number_of_hotels; i++)
    {
        if(arr[i].location[strlen(arr[i].location)]==' ')
        {
            arr[i].location[strlen(arr[i].location)]='\0';
        }
        if(given_loc[strlen(given_loc)]==' ')
        {
            given_loc[strlen(given_loc)]='\0';
        }

        if(!strcmp(given_loc,arr[i].location))
        {   
            hotelSetter(&temp[matching_hotels],temp,arr[i].name,arr[i].location,arr[i].number_of_floors,arr[i].number_of_rooms,arr[i].stars);
            

            matching_hotels++; 
            hotel_in_array_count=matching_hotels;
            

            
           temp[loc_coun].ptr=malloc(sizeof(room_t)*5);
            temp[loc_coun].current_rooms=0;
            for (size_t j = 0; j < arr[i].current_rooms; j++)
            {
                if(arr[i].ptr[j].number_of_beds==bed_number && arr[i].ptr[j].price>=min_price && arr[i].ptr[j].price<=max_price)
            {   room_t l_room;
                init_room(&l_room,arr[i].ptr[j].number_of_beds,arr[i].ptr[j].number_of_room,arr[i].ptr[j].sea_view,arr[i].ptr[j].floor,arr[i].ptr[j].price,arr[i].ptr[j].seasonal_price);
                    roomAdder(temp,&l_room,loc_coun);    
                    
                    flag[i] = true;       

               }
                if(!(temp[loc_coun].current_rooms+1%5))
                {
                    ptr_size_f++;
                    temp[loc_coun].ptr=realloc(temp[loc_coun].ptr,sizeof(room_t)*ptr_size_f);
                }
                
            }
            loc_coun++;
            

                      
        }

        
    }
    
        return temp;
}
void print_results(hotel_t arr[],char given_loc[50],int bed_number,int min_price,int max_price)
{
    
    hotel_t *l_temp;
    l_temp=LinearSearch(arr,given_loc,bed_number,min_price,max_price);
    for (size_t i = 0; i <hotel_in_array_count; i++)
    {
        if(flag[i]==true)
        {
        print_hotel_info(l_temp[i]);
        print_hotel_rooms(l_temp[i]);
        }
      
    }
}
char* results_st(hotel_t arr[],hotel_t *return_arr,char given_loc[50],int bed_number,int min_price,int max_price)
{
    char* temp = malloc(3000);
    hotel_t* temp_ret=malloc(MAX_HOTELS*sizeof(hotel_t));
    temp_ret=LinearSearch(arr,given_loc,bed_number,min_price,max_price);
    memcpy(return_arr,temp_ret,MAX_HOTELS*sizeof(hotel_t));
     for (size_t i = 0; i < MAX_HOTELS; i++)
        {
            if(flag[i]==true)
            {
                strcpy(temp," ");
                break;
            }
            if(i==MAX_HOTELS-1)
            {
                strcpy(temp,"There are no avalaible rooms according to your criterea\n");
            }
        }
      
   for (size_t i = 0; i <hotel_in_array_count; i++)
    {  
        
        if(flag[i]==true)
        {
            strcat(temp," ");
            strcat(temp,hotel_info_st(return_arr[i]));
            strcat(temp,hotel_rooms_st(return_arr[i]));
        }
      
    }
    printf("here\n");
    printHotels(temp_ret);
    printf("there\n");
    printf("%s\n",temp);
    if(hotel_in_array_count)
    {return temp;}
    strcpy(temp,"There are no avalaible rooms according to your criterea\n");
    return temp;
    
}
void read_hotels(hotel_t arr[])
{
    number_of_hotels=0;

    char* num;
    char** names=malloc(MAX_HOTELS*sizeof(char*));
    char* info_file;
    char* hotel_info;
    char** info;
    int room_counter=-1;
    for (size_t i = 0; i < MAX_HOTELS; i++)
    {
        names[i]=malloc(20);
        num=malloc(5);
        sprintf(num,"%lu",i);
        strcpy(names[i],"Hotel_No");
        strcat(names[i],num);
        if(chdir(names[i])==-1)
        {
            continue;
        }
        info_file=malloc(50);
        strcpy(info_file,"Info for Hotel number");
        strcat(info_file,num);
        strcat(info_file,".txt");
        hotel_info=malloc(200);
        FILE* fd;
        fd = fopen(info_file,"r");
        if(fgets(hotel_info,200,fd)==NULL)
        {
            perror("Error in reading the file");
        }
        fclose(fd);
        info=malloc(sizeof(char*)*6);
        for (size_t j = 0; j < 6; j++)
        {
            info[i]=malloc(50);
        }
        info[i]=strtok(hotel_info,"\\");
        for (size_t j = 1; j < 6; j++)
        {
            info[j]=strtok(NULL,"\\");
        }
        hotelSetter(&arr[i],arr,info[1],info[2],(int)strtol(info[5],NULL,10),(int)strtol(info[3],NULL,10),(int)strtol(info[4],NULL,10));
        room_reader(arr,i);
        char* reservation_file;
        char* l_num;
        room_counter=0;
        for (size_t j = 0; j < MAX_ROOM_NUMBER; j++)
        {
            l_num=malloc(5);
            reservation_file=malloc(40);
            strcpy(reservation_file,"Reservations_Lists_For_Room");
            sprintf(l_num,"%ld",j);
            strcat(reservation_file,l_num);
            strcat(reservation_file,".txt");
            if(access(reservation_file,F_OK)==-1)
            {  free(l_num);
                continue;
            }
            for (size_t v = 0; v < arr[i].current_rooms; v++)
            {
                if(arr[i].ptr[v].number_of_room==j)
                {
                    read_reservations_from_file(&arr[i].ptr[v],arr[i].ptr[v].starting_node_l);
                }
            }
            free(l_num);
           
            room_counter++;

        }
        
        
        free(hotel_info);
        free(num);
        chdir("..");
    }
}
short int room_hotel_validity(hotel_t* arr,hotel_t* hotel_l,room_t* room_l ,char* hotel_name, int room_number)
{   
    size_t i;
    for (i = 0; i < matching_hotels; i++)
    {      if(arr[i].name[strlen(arr[i].name)-1]==' ')
         {
            arr[i].name[strlen(arr[i].name)-1]='\0';
         }
         if(hotel_name[strlen(hotel_name)-1]==' ')
         {
            hotel_name[strlen(hotel_name)-1]='\0';
         }
        if(!strcmp(arr[i].name,hotel_name))
        {
            hotel_l->ID=arr[i].ID;
            hotel_l->number_of_floors=arr[i].number_of_floors;
            hotel_l->number_of_floors=arr[i].number_of_rooms;
            hotel_l->number_of_floors=arr[i].stars;
            strcpy(hotel_l->location,arr[i].location);
            strcpy(hotel_l->name,arr[i].name);

            break;
        }
        if(i==matching_hotels-1)
        {
            return 0;
        }
    }
  
    for (size_t j = 0; j < arr[i].current_rooms; j++)
    {
      
        if(arr[i].ptr[j].number_of_room==room_number)
        {   
            room_l->floor=arr[i].ptr[j].floor;
            room_l->number_of_beds=arr[i].ptr[j].number_of_beds;
            room_l->number_of_room=arr[i].ptr[j].number_of_room;
            room_l->price=arr[i].ptr[j].price;
            room_l->seasonal_price=arr[i].ptr[j].seasonal_price;
            room_l->reservation_count=arr[i].ptr[j].reservation_count;
            room_l->sea_view=arr[i].ptr[j].sea_view;
            room_l->year1=arr[i].ptr[j].year1;
            room_l->year2=arr[i].ptr[j].year2;
            room_l->starting_node_l=arr[i].ptr[j].starting_node_l;
            return 1;
    }
        }
        return 0;

}
 int reservation_server(hotel_t *hotels_arr,hotel_t l_hotel,room_t l_room,long dates[])
{   size_t hotel_index=0;
    size_t room_index=0;
    int l_price=0;
    for (size_t i = 0; i < number_of_hotels; i++)
    {   
        if(hotels_arr[i].ID==l_hotel.ID)
        {
            hotel_index=i;
            hotel_to_reserve=hotel_index;
            break;
        }
    }
    for (size_t i = 0; i < hotels_arr[hotel_index].current_rooms; i++)
    {
        if(hotels_arr[hotel_index].ptr[i].number_of_room==l_room.number_of_room)
        {
            room_index=i;
            room_to_reserve=room_index;
            break;
        }
    }
     char* Hotel_name;
    Hotel_name=malloc(20);
    char* num_of_hotel=malloc(5);
    strcpy(Hotel_name,"Hotel_No");
    sprintf(num_of_hotel,"%d",hotels_arr[hotel_index].ID);
    strcat(Hotel_name,num_of_hotel);
    chdir(Hotel_name);
    read_reservations_from_file(&hotels_arr[hotel_index].ptr[room_index],hotels_arr[hotel_index].ptr[room_index].starting_node_l);
    l_price=adding_reservations(&hotels_arr[hotel_index].ptr[room_index],dates[0],dates[1],dates[2],dates[3],dates[4],dates[5]);
    if(l_price)
    {
        return l_price;
    }
    chdir("..");
    return 0;
    
}

/*int main ()
{
    
    hotel_t* Hotels= malloc(sizeof(hotel_t)*MAX_HOTELS);
    current_year=get_currentyear();
    /*hotelSetter(&Hotels[number_of_hotels],Hotels,"Hotel Samaras","Lamia",6,15,5);
    hotelSetter(&Hotels[number_of_hotels],Hotels,"Hotel 47","Lamia",4,12,3);
    hotelSetter(&Hotels[number_of_hotels],Hotels,"La Casa De Hotel","Thesalloniki",4,12,3);
    hotelSetter(&Hotels[number_of_hotels],Hotels,"Lavender Hotel","Paris",8,20,4);
    hotelSetter(&Hotels[number_of_hotels],Hotels,"Lamian","Lamia",4,11,3);


  room_t l_room1;
   room_t l_room2;
   room_t l_room3;
    room_t l_room4;
    room_t l_room5;
    room_t l_room6;

   init_room(&l_room1,3,11,1,1,12,34);
  init_room(&l_room2,2,12,1,1,34,43);
   init_room(&l_room3,2,13,1,2,69,456);
    init_room(&l_room4,1,14,1,2,12,34);
  init_room(&l_room5,4,15,1,3,50,69);
   init_room(&l_room6,2,16,1,3,25,40);
   // Hotel Samaras
    roomAdder(Hotels,&l_room1,0);
    roomAdder(Hotels,&l_room2,0);
    roomAdder(Hotels,&l_room3,0);
    roomAdder(Hotels,&l_room4,0);

    //Hotel 47
    roomAdder(Hotels,&l_room1,1);
    roomAdder(Hotels,&l_room2,1);
    roomAdder(Hotels,&l_room3,1);
    roomAdder(Hotels,&l_room4,1);
    roomAdder(Hotels,&l_room5,1);
    roomAdder(Hotels,&l_room6,1);

    // La casa de Hotel
    roomAdder(Hotels,&l_room1,2);
    roomAdder(Hotels,&l_room2,2);
    roomAdder(Hotels,&l_room3,2);
    roomAdder(Hotels,&l_room4,2);
    roomAdder(Hotels,&l_room5,2);

    // Lavender Hotel
    roomAdder(Hotels,&l_room1,3);
    roomAdder(Hotels,&l_room2,3);
    roomAdder(Hotels,&l_room3,3);
    roomAdder(Hotels,&l_room4,3);

    // Lamian
    roomAdder(Hotels,&l_room1,4);
    roomAdder(Hotels,&l_room2,4);
    roomAdder(Hotels,&l_room3,4);
    roomAdder(Hotels,&l_room4,4);
    roomAdder(Hotels,&l_room5,4);
    roomAdder(Hotels,&l_room6,4);
    
    
    adding_reservations(&Hotels[0].ptr[0],3,14,2022,3,19,2022);
    adding_reservations(&Hotels[0].ptr[0],4,14,2022,4,19,2022);
    adding_reservations(&Hotels[0].ptr[1],4,14,2022,4,19,2022);

   

 
   
    flush_hotel(Hotels[0]);
    flush_hotel(Hotels[1]);
    flush_hotel(Hotels[2]);
    flush_hotel(Hotels[3]);
    flush_hotel(Hotels[4]);
    
  
 read_hotels(Hotels);
 for (size_t i = 0; i < 5; i++)
 {
    print_hotel_info(Hotels[i]);
    print_hotel_rooms(Hotels[i]);
 }
 

    return 0;
}*/
