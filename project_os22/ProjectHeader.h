#ifndef LOC
#define LOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdatomic.h>
#define MONTHS 12
#define MAX_HOTELS 5
#define MAX_ROOM_NUMBER 1000

int days_per_month_first_year[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int days_per_month_second_year[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int current_year = 0;
int number_of_hotels = 0;
int hotel_in_array_count = 0;
int matching_hotels = 0;
int hotel_to_reserve = 0;
int room_to_reserve = 0;

bool flag[MAX_HOTELS];
typedef struct year
{
    int year;
    int total_days;
    int *reservation_array;
} year_t;
typedef struct room
{
    size_t number_of_beds;
    int floor;
    int sea_view;
    int number_of_room;
    int price;
    int seasonal_price;

    struct NodeRoomReservation *starting_node_l;
    year_t *year1;
    year_t *year2;
    int reservation_count;
} room_t;
typedef struct
{
    room_t *ptr;
    char location[50];
    char name[50]; // Na kaneis to onoma na pernei mono lowercase h uppercase
    int current_rooms;
    int number_of_rooms;
    int ID;
    int stars;
    int number_of_floors;
} hotel_t;

typedef struct date
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
} date_t;
typedef struct NodeRoomReservation
{
    date_t *first_day;
    date_t *last_day;
    int total_price;
    int days;
    int season_days;
    struct NodeRoomReservation *next;
} reservation_date;

void init_room(room_t *l_room, int number_of_beds, int room_number, int sea_view, int floor, int price, int seasonal_price);
int dateSetter(int startmonth, int startday, int startyear, int finalmonth, int finalday, int finalyear);
void Init_Reservation_Array(room_t *l_room);
int pricecalculator(room_t *l_room, int days, int season_days);
int monthisseason(int month);
void days_calculator(room_t *l_room, int *l_days, int *l_season_days, int startmonth, int startday, int startyear, int finalmonth, int finalday, int finalyear);
void display_reservation_list(struct NodeRoomReservation *l_node);
void BubbleSort(struct NodeRoomReservation *start);
void insert_reservation_in_list(struct NodeRoomReservation **head_ref, int starting_month, int starting_day, int starting_year, int final_month, int final_day, int final_year, int days, int seasondays, int total_price);
void swap(reservation_date *Node_A, reservation_date *Node_B);
int get_currentyear();
void reservation_array_setter(room_t *l_room, int startmonth, int startday, int startyear, int finalmonth, int finalday, int finalyear);
int time_ellapsed(room_t *l_room, int month, int day, int year);
int reservation_checker(room_t *l_room, int startmonth, int startday, int startyear, int finalmonth, int finalday, int finalyear);
reservation_date *get_from_reservation_list(reservation_date *head, int i);
void print_reservation_date(reservation_date *l_date);
void flush_reservations(reservation_date *l_node, room_t l_room, int l_flag);
void read_reservations_from_file(room_t *l_room, reservation_date *l_res);
void printHotels(hotel_t Hotels[]);
void hotelSetter(hotel_t *l_hotel, hotel_t Hotels[], char hotel_name[50], char hotel_location[50], int number_of_floors, int number_of_rooms, int stars);
void print_hotel_info(hotel_t l_hotel);
void roomAdder(hotel_t Hotels[], room_t *room, int numberofhotel);
void flush_hotel(hotel_t hotel);
void room_reader(hotel_t Hotels[], int hotel_num);
void print_hotel_rooms(hotel_t l_hotel);
void BubbleSortRooms(hotel_t *l_hotel);
int adding_reservations(room_t *l_room, int startmonth, int startday, int startyear, int finalmonth, int finalday, int finalyear);
#endif