#include "ProjectHeader.h"
void Init_Reservation_Array(room_t* l_room);


void swap(reservation_date* Node_A,reservation_date* Node_B);
void init_room(room_t* l_room,int number_of_beds,int room_number,int sea_view,int floor,int price,int seasonal_price)
{
    l_room->reservation_count=0;
    l_room->number_of_beds=number_of_beds;
    /*if(l_room->number_of_room>MAX_ROOM_NUMBER)
    {
        printf("This is greater than the maximum room number\n");
        exit(1);
    }*/
    l_room->number_of_room=room_number;
    l_room->sea_view=sea_view;
    l_room->floor=floor;
    l_room->price=price;
    l_room->seasonal_price=seasonal_price;
    
    Init_Reservation_Array(l_room);

}
int dateSetter(int startmonth,int startday,int startyear,int finalmonth,int finalday,int finalyear)
{
   
    
    
    if((startmonth>12||finalmonth>12)||((startmonth>finalmonth)&&(!(startyear<finalyear))))
    {
        printf("Please enter valid months\n");
        return 0;
    }
    if((startday==finalday)||(startday>days_per_month_first_year[startmonth-1]||finalday>days_per_month_second_year[finalmonth-1])||((startday>finalday)&&(((!(startmonth<=finalmonth)))&&(startyear==finalyear)))||(!(startyear<=finalyear)))
    {
        printf("Please enter valid days\n");
        return 0;
    }
    return 1;
}
void Init_Reservation_Array(room_t* l_room)
{
    l_room->year1=malloc(sizeof(year_t));
    l_room->year2=malloc(sizeof(year_t));
    l_room->year1->year=current_year;
    l_room->year2->year=current_year+1;
    if((l_room->year1->year%4==0&&l_room->year1->year%100!=0)||(l_room->year1->year%400==0))
    {
        days_per_month_first_year[1]=29;
        l_room->year1->total_days=366;
    }
    else
    {
    l_room->year1->total_days=365;  
    }
     if((l_room->year2->year%4==0&&l_room->year2->year%100!=0)||(l_room->year2->year%400==0))
    {
        days_per_month_second_year[1]=29;
       l_room->year2->total_days=366;

    }
    else
    {
        l_room->year2->total_days=366;
    }
    l_room->year1->reservation_array=malloc(sizeof(int)*l_room->year1->total_days);if(l_room->year1->reservation_array==NULL){perror("Error here");}
    l_room->year2->reservation_array=malloc(sizeof(int)*l_room->year1->total_days);if(l_room->year2->reservation_array==NULL){perror("Error here");}
     for (size_t i = 0; i < l_room->year1->total_days; i++)
    {
        l_room->year1->reservation_array[i]=0;
    }
    for (size_t i = 0; i < l_room->year2->total_days; i++)
    {
       l_room->year2->reservation_array[i]=0;
    }
}
int pricecalculator(room_t *l_room,int days,int season_days)
{
    int total_price=0;
    total_price+=(l_room->price)*(days);
    total_price+=(l_room->seasonal_price)*(season_days);
    return total_price;
}
int monthisseason(int month)
{
    if(month>5&&month<9)
    {
        return 1;
    }
    return 0;
}
void days_calculator(room_t* l_room,int* l_days,int* l_season_days,int startmonth,int startday,int startyear,int finalmonth,int finalday,int finalyear)
{   
    int days=0;
    int seasondays=0;
    if(startmonth==finalmonth)
    {   
        if(monthisseason(startmonth))
        {
        seasondays=finalday-startday;
          
        }
    else{
        days=finalday-startday;
    }
    
    }

    else if(finalmonth-startmonth==1&&(startyear==finalyear))
    {
        if(monthisseason(startmonth))
        {
        seasondays+=days_per_month_first_year[startmonth-1]-startday;
        }
        else
        {
            days+=days_per_month_first_year[startmonth-1]-startday;
        }
        if(monthisseason(finalmonth)){
        seasondays+=startday;
        }
        else
        {
            days+=finalday;
        }
    
    }
    else if(startyear==finalyear)
    {
        if(monthisseason(startmonth))
        {
        seasondays+=days_per_month_first_year[startmonth-1]-startday;
        }
        else
        {
            days+=days_per_month_first_year[startmonth-1]-startday;
        }
    
        for (size_t i = startmonth; i < finalmonth-1; i++)
        {
            if(monthisseason(i+1))
            {
              seasondays+=days_per_month_first_year[i];  
            }
            else{
           days+=days_per_month_first_year[i];
           }
        }
        if(monthisseason(finalmonth))
        {
        seasondays+=finalday;
        }
        else
        {
            days+=finalday;
        }
    
    }
    else
    {
         if(monthisseason(startmonth))
        {
        seasondays+=days_per_month_first_year[startmonth-1]-startday;
        }
        else
        {
            days+=days_per_month_first_year[startmonth-1]-startday;
        }
        
        if(startmonth!=12){
        for (size_t i =startmonth ; i < 13; i++)
        {if(monthisseason(i+1)){
            seasondays+=days_per_month_first_year[i];
            }
             else
        {
            days+=days_per_month_first_year[i];
        }
        }
       
        }
        if(finalmonth!=1)
        {
        for (size_t i = finalmonth-1; i ; i--)
        {if(monthisseason(i+1))
        {
            seasondays+=days_per_month_second_year[i];
            }
        else
        {
            days+=days_per_month_second_year[i];
        }
        }
            
        }
        if(monthisseason(finalmonth)){
        seasondays+=finalday;}
        else
        {
            days+=finalday;
        }
     
    }

    *l_days=days;
    *l_season_days=seasondays;
    
}
void print_room_info(room_t l_room)
{   char* view = malloc(50);
    if(l_room.sea_view)
    {
        strcpy(view,"Has a sea view");
    }
    else
    {
        strcpy(view,"Does not have a sew view");
    }

    printf("The number of the room is %d in the floor number %d.%s and there are %ld beds.\n"
    ,l_room.number_of_room,l_room.floor,view,l_room.number_of_beds);
}



void display_reservation_list(struct NodeRoomReservation* l_node)
{
   
    while(l_node!=NULL)
    {
        printf("The reservation dates are:  from %u \\ %u \\ %u  to %u \\ %u \\ %u \n",l_node->first_day->month,l_node->first_day->day,l_node->first_day->year,l_node->last_day->month,l_node->last_day->day,l_node->last_day->year);
        printf("The total days are %d and the total price is %d$ \n",l_node->days+l_node->season_days,l_node->total_price);
        l_node=l_node->next;
    }
}
void BubbleSort(struct NodeRoomReservation *start)
{
	int swapped, i;
	struct NodeRoomReservation *ptr1;
	struct NodeRoomReservation *lptr = NULL;

	if (start == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != lptr)
		{   if (ptr1->first_day->year> ptr1->next->first_day->year)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			else if (ptr1->first_day->month > ptr1->next->first_day->month&&(ptr1->first_day->year==ptr1->next->first_day->year))
			{

				swap(ptr1, ptr1->next);
				swapped = 1;
			}
            else if (ptr1->first_day->day > ptr1->next->first_day->day&&(ptr1->first_day->year==ptr1->next->first_day->year)&&(ptr1->first_day->month == ptr1->next->first_day->month))
            {
               swap(ptr1, ptr1->next);
				swapped = 1;
            }
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
	while (swapped);
}
void insert_reservation_in_list(struct NodeRoomReservation** head_ref,int starting_month,int starting_day,int starting_year,int final_month,int final_day,int final_year,int days,int seasondays,int total_price)
{   struct NodeRoomReservation* new_node = (struct NodeRoomReservation*) malloc(sizeof(struct NodeRoomReservation));
    new_node->first_day=malloc(sizeof(date_t));
    new_node->last_day=malloc(sizeof(date_t));
    struct NodeRoomReservation *last = *head_ref;  
    new_node->first_day->month=starting_month;
    new_node->first_day->day=starting_day;
    new_node->first_day->year=starting_year;
    new_node->last_day->month=final_month;
    new_node->last_day->day=final_day;
    new_node->last_day->year=final_year;
    new_node->days=days;
    new_node->season_days=seasondays;
    new_node->total_price=total_price;
    new_node->next = NULL;

    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }
 
    while (last->next != NULL)
        last = last->next;
 
    last->next = new_node;
    return;
}
void swap(reservation_date* Node_A,reservation_date* Node_B)
{
    reservation_date* temp=malloc(sizeof(reservation_date));
    if(temp==NULL)
    {
        perror("An error has occured");
        exit(1);
    }
    temp->first_day=malloc(sizeof(date_t));
    if(temp->first_day==NULL)
    {
        perror("An error has occured");
        exit(1);
    }
    temp->last_day=malloc(sizeof(date_t));
    if(temp->last_day==NULL)
    {
        perror("An error has occured");
        exit(1);
    }
    temp->first_day->day=Node_A->first_day->day;
    temp->first_day->month=Node_A->first_day->month;
    temp->first_day->year=Node_A->first_day->year;
    temp->last_day->day=Node_A->last_day->day;
    temp->last_day->month=Node_A->last_day->month;
    temp->last_day->year=Node_A->last_day->year;
    
    Node_A->first_day->day=Node_B->first_day->day;
    Node_A->first_day->month=Node_B->first_day->month;   
    Node_A->first_day->year=Node_B->first_day->year;
    Node_A->last_day->day=Node_B->last_day->day;
    Node_A->last_day->month=Node_B->last_day->month;
    Node_A->last_day->year=Node_B->first_day->year;           

    Node_B->first_day->day=temp->first_day->day;
    Node_B->first_day->month=temp->first_day->month;   
    Node_B->first_day->year=temp->first_day->year;
    Node_B->last_day->day=temp->last_day->day;
    Node_B->last_day->month=temp->last_day->month;
    Node_B->last_day->year=temp->first_day->year;           
    
}
int get_currentyear()
{
    time_t t;   
    time(&t);
    char* time_l= ctime(&t);
    char* token;
    int year;
    token = strtok(time_l," ");
   
    for (size_t i = 0; i < 4; i++)
    {
    
      token = strtok(NULL, " ");
    
    }
    year=(int)strtol(token,NULL,10); 
    return year;         
}
void reservation_array_setter(room_t* l_room,int startmonth,int startday,int startyear,int finalmonth,int finalday,int finalyear)

    {   int sum=0;
    if(startmonth==finalmonth&&startyear==finalyear)
    {

        if(startyear==l_room->year1->year)
        {

            for (size_t i = 0; i < startmonth-1; i++)
            {
                sum+=days_per_month_first_year[i];
            }
            for (size_t i = sum+startday; i < sum+finalday+1; i++)
            {
                l_room->year1->reservation_array[i]=1;
            }
            
        }
        else if (startyear==l_room->year2->year)
        {
            for (size_t i = 0; i < startmonth-1; i++)
            {
                sum+=days_per_month_first_year[i];
            }
            for (size_t i = sum+startday; i < sum+finalday+1; i++)
            {
                l_room->year2->reservation_array[i]=1;
            }
            
        }
    }
    else if(startmonth<finalmonth&&startyear==finalyear)
    {
        if(startyear==l_room->year1->year)
        {
            for (size_t i = 0; i < startmonth-1; i++)
            {
                sum+=days_per_month_first_year[i];
            }
            for (size_t i = sum+startday; i <(sum+days_per_month_first_year[startmonth-1] ); i++)
            {
                l_room->year1->reservation_array[i]=1;
            }
            sum+=days_per_month_first_year[startmonth-1];
            for (size_t i = sum; i <sum+ finalday+1; i++)
            {
                l_room->year1->reservation_array[i]=1;
                printf("The number 2 is %lu",i);

            }
            if(finalyear==l_room->year2->year)
        {
            for (size_t i = 0; i < finalmonth-1; i++)
            {
                sum+=days_per_month_second_year[i];
            }
            for (size_t i = sum+finalday; i <(sum+days_per_month_first_year[finalmonth-1] ); i++)
            {
                l_room->year2->reservation_array[i]=1;
            }
            sum+=days_per_month_first_year[startmonth-1];
            for (size_t i = sum; i <sum+ finalday+1; i++)
            {
                l_room->year2->reservation_array[i]=1;

            }
            
        }
    }
    }
    else if(startyear!=finalyear)
    {
        for (size_t i = 0; i < startmonth-1; i++)
        {
            sum+=days_per_month_first_year[i];
        }
        for (size_t i = sum+startday; i <(l_room->year1->total_days ); i++)
        {
                l_room->year1->reservation_array[i]=1;
        }
        sum=0;
        for (size_t i = 0; i < finalmonth-1; i++)
            {
                sum+=days_per_month_second_year[i];
            }
        for (size_t i = 0; i <sum+ finalday+1; i++)
        {
        l_room->year2->reservation_array[i]=1;
        }  
    
    }

}
int time_ellapsed(room_t* l_room,int month, int day, int year)
{
    int sum=0;
    int break_fl=0;
    if(year==l_room->year1->year)
    {
       
        for (size_t i = 1; i < MONTHS+1; i++)
        {
            if(month==i)
            {
                for (size_t j = 1; j < days_per_month_first_year[i+1]; j++)
                {                

                    if(day==j)
                    {
                        sum+=j;
                        break_fl=1;
                        break;
                    }
                }
                if(break_fl)
                {
                    break;
                }
            }
            sum+=days_per_month_first_year[i-1];
        }
    }
    if(year==l_room->year2->year)
        {
       
            for (size_t i = 1; i < MONTHS+1; i++)
            {
                if(month==i)
                {
                    for (size_t j = 1; j < days_per_month_second_year[i+1]; j++)
                    {               

                        if(day==j)
                        {
                            sum+=j;
                            break_fl=1;
                            break;
                        }
                    }
                    if(break_fl)
                    {
                        break;
                    }
                }
                sum+=days_per_month_second_year[i-1];
            }
    }
    return sum;
        
}
int reservation_checker(room_t* l_room,int startmonth,int startday,int startyear,int finalmonth,int finalday,int finalyear )
{
    int ellapsed_days1=time_ellapsed(l_room,startmonth,startday,startyear);
    int ellapsed_days2=time_ellapsed(l_room,finalmonth,finalday,finalyear);
    if((startyear==l_room->year1->year)&&(finalyear==l_room->year1->year))
    {
        
        for (size_t i = ellapsed_days1-1; i < ellapsed_days2; i++)
        {
            

            if(l_room->year1->reservation_array[i]==1)
            {
                return 1;
            }
        }
        
    }
     else if((startyear==l_room->year2->year)&&(finalyear==l_room->year2->year))
    {
        for (size_t i = ellapsed_days1-1; i < ellapsed_days2; i++)
        {

            if(l_room->year2->reservation_array[i]==1)
            {
                return 1;
            }
        }
      
    }
    else if((startyear==l_room->year1->year)&&(finalyear==l_room->year2->year))
    {
         

     for (size_t i = ellapsed_days1-1; i < l_room->year1->total_days; i++)
     {
        if(l_room->year1->reservation_array[i]==1)
        {            

            return 1;
        }
     }
     for (size_t j = 0; j < 22; j++)
     {

         if(l_room->year2->reservation_array[j]==1)
         {
             return 1;
         }
     }
    }
        return 0;        

}
 int adding_reservations (room_t* l_room,int startmonth,int startday,int startyear,int finalmonth,int finalday,int finalyear)
{
   if(l_room->reservation_count==0)
    {
        l_room->starting_node_l =NULL;
    }


    int days=0;
    int season_days=0;
    int l_price=0;
    if(!dateSetter(startmonth,startday,startyear,finalmonth,finalday,finalyear))
    {
        return 0;
    };
    if(!reservation_checker(l_room,startmonth,startday,startyear,finalmonth,finalday,finalyear))
    {  
        days_calculator(l_room,&days,&season_days,startmonth,startday,startyear,finalmonth,finalday,finalyear);
        l_price=pricecalculator(l_room,days,season_days);
        insert_reservation_in_list(&l_room->starting_node_l,startmonth,startday,startyear,finalmonth,finalday,finalyear,days,season_days,l_price);

        BubbleSort(l_room->starting_node_l);
        reservation_array_setter(l_room,startmonth,startday,startyear,finalmonth,finalday,finalyear);
            l_room->reservation_count++;

        return l_price;
    }
    else{
       return 0;
    }

}
reservation_date* get_from_reservation_list(reservation_date* head,int i)
{   
    int counter=0;
    reservation_date* temp;
    temp = malloc(sizeof(reservation_date));
    temp=head;
   while(temp!=NULL)
   {
       if(counter==i)
       {
           return temp;
       }
       counter++;
       temp=temp->next;
   }
}
void print_reservation_date(reservation_date* l_date)
{
    printf("The starting date is %d\\%d\\%d\n",l_date->first_day->month,l_date->first_day->day,l_date->first_day->year);
    printf("The last date is %d\\%d\\%d\n",l_date->last_day->month,l_date->last_day->day,l_date->last_day->year);
}
void flush_reservations(reservation_date* l_node,room_t l_room,int l_flag)
{
    char* Hotel_Folder=malloc(50);
    char* Hotel_Number=malloc(5);

    strcpy(Hotel_Folder,"Hotel_No");
    sprintf(Hotel_Number,"%d",hotel_to_reserve);
    strcat(Hotel_Folder,Hotel_Number);
   
    char name[50];
    strcpy(name,"Reservations_Lists_For_Room");
    char* affix = ".txt";
   
    char* room_number=malloc(sizeof(l_room.number_of_room)/4);
    sprintf(room_number,"%d",l_room.number_of_room);

    strcat(name,room_number);
    strcat(name,affix);
      if(l_flag)
    {   remove(name);
        chdir(Hotel_Folder);
    }
    FILE *fptr = fopen(name,"w");
    if(fptr == NULL)
    {
        perror("There was an error in creating ");
    }
    while(l_node!=NULL)
    {
        fprintf(fptr," %u\\%u\\%u  to %u\\%u\\%u\n",l_node->first_day->month,l_node->first_day->day,l_node->first_day->year,l_node->last_day->month,l_node->last_day->day,l_node->last_day->year);
        l_node=l_node->next;
    }
    fclose(fptr);
}


void read_reservations_from_file(room_t* l_room,reservation_date* l_res)
{
    char ch;
    size_t i=0;
    size_t j=0;
    int counter=1;
    char name[50];
    int dates_num[6];
    strcpy(name,"Reservations_Lists_For_Room");
    char* affix = ".txt";
    char* room_number=malloc(sizeof(l_room->number_of_room)/4);
    sprintf(room_number,"%d",l_room->number_of_room);
    strcat(name,room_number);
    strcat(name,affix);
    FILE* line_counter;
    if((line_counter=fopen(name,"r"))==NULL)
    {
        return;
    }
    while(getc(line_counter)!=EOF)
    {
        if(getc(line_counter)=='\n')
        {
            counter++;
        }
    }
    fclose(line_counter);
     char reservations [counter][30];
    FILE *fptr = fopen(name,"r");
    if(fptr == NULL)
    {
        perror("There was an error in openning the file ");
    }
     while (fgets(reservations[i], 30, fptr))
    {
    
        if (reservations[i][strlen(reservations[i]) - 1] == '\n')
            i++;
    }

    fclose(fptr);

    char **dates =malloc(sizeof(char*)* 6);
    for (size_t l = 0; l < 6; l++)
    {
        dates[l]=malloc(3);
    }
    int k=0;
   
    for (size_t l = 0; l < counter; l++)
    {
        k=0;
    dates[k]=strtok(reservations[l],"\\ to");
    k++;
    while(dates[k]!=NULL)
    {
        dates[k]=strtok(NULL,"\\ to");
        k++;
    }
    for (size_t v = 0; v < 6; v++)
    {
       dates_num[v]=strtol(dates[v],NULL,10);
    }


    adding_reservations(l_room,dates_num[0],dates_num[1],dates_num[2],dates_num[3],dates_num[4],dates_num[5]);

    }
    
}
  