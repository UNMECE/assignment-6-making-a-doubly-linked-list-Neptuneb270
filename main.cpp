#include "coordinate.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>

/*
struct _coordinate
{
  float x;
  float y;
  int coord_id;
  struct _coordinate *next;
  struct _coordinate *previous;
};
typedef struct _coordinate Coordinate;
*/

void display(Coordinate *coord);
void get_last(Coordinate *list_start);

using namespace std;

int main(int argc, char *argv[]) {
   int num_coords = stoi(argv[1]);

   //Init header node
   Coordinate *coord_list = (Coordinate*)malloc(sizeof(Coordinate));
   coord_list->coord_id = 0;
   coord_list->next = coord_list;
   coord_list->previous = coord_list;

   //Adding coords
   for (int i = 0; i < num_coords; i++) {
      add_coordinate(coord_list->previous, rand() % 30, rand() & 30);
   }
   
   forward_display(coord_list);
   delete_coordinate(coord_list, 2);
   forward_display(coord_list);

   closest_to(coord_list, 10.2,1.3);
   backward_display(coord_list->previous);
   
   return 0;
}

void display(Coordinate *coord) {
   cout << "Node #" << coord->coord_id
        << " [x = " << coord->x
        << ", y = " << coord->y
        << ", next_id = " << coord->next->coord_id
        << ", preivous_id = " << coord->previous->coord_id
        << "]" << endl;
}

void add_coordinate(Coordinate *list_end, float x, float y) {
   cout << "ADDING COORD: ";
   Coordinate *new_coord = (Coordinate*)malloc(sizeof(Coordinate));
   //Set data
   new_coord->x = x;
   new_coord->y = y;
   new_coord->coord_id = list_end->coord_id + 1;
   
   //Tie in new coord
   new_coord->previous = list_end;
   new_coord->next = list_end->next;
  
   //Rewrite last coordi
   list_end->next->previous = new_coord;
   list_end->next = new_coord;
   display(new_coord);
}

void forward_display(Coordinate *list_beginning) {
   cout << endl << "Forward Display ----------" << endl;
   Coordinate *temp = (Coordinate*) malloc(sizeof(Coordinate));
   temp = list_beginning;

   do {
      display(temp);
      temp = temp->next;
   } while (temp->coord_id != 0);

   free(temp);
   cout << "--------------------" << endl << endl;
}
void backward_display(Coordinate *list_end) {
   cout << endl << "Backwards Display -------------" << endl;
   Coordinate *temp = (Coordinate*) malloc(sizeof(Coordinate));
   temp = list_end;
   display(temp);
   
   do {
      temp = temp->previous;
      display(temp);
   } while (temp->coord_id != 0);

   free(temp);
   cout << "---------------------" << endl << endl;
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete) {
   Coordinate *current = list_beginning;  
   while (current->coord_id != coord_id_to_delete) {
      current = current->next;
   }
  
   Coordinate *temp = current;
   current->next->previous = temp->previous;
   current->previous->next = temp->next;

   Coordinate *temp2 = list_beginning;
   for (int i = 0; i < list_beginning->previous->coord_id; ++i) {
      temp2->coord_id = i;
      temp2 = temp2->next;
   }
}

int list_length(Coordinate *list_beginning) {
   return list_beginning->previous->coord_id;
}

void closest_to(Coordinate *list_beginning, float x, float y) {
   Coordinate *temp = list_beginning->next;
   float curr_dist = (float)hypot((double)temp->x, (double)temp->y);
   float min_dist = curr_dist;
   temp = temp->next;

   while (temp->coord_id != list_length(list_beginning)) {
      curr_dist = (float)hypot((double)temp->x, (double)temp->y);
      min_dist = (curr_dist < min_dist) ? curr_dist : min_dist;
      temp = temp->next;
   }
   cout << min_dist << endl;
}
