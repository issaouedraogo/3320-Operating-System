#include <stdio.h>
#include <stdlib.h>
#define CYLINDERS 5000
#define REQUESTS 1000
int initialHead = 0;
int disk[REQUESTS];
int* sortDisk()
{
   int temp = 0, m = 0, n = 0;
   //sort the disk using sorting algorithm
   for (m = 0; m < REQUESTS; ++m)
   {
       for (n = m + 1; n < REQUESTS; ++n)
       {
           if (disk[m] > disk[n])
           {
               temp = disk[m];
               disk[m] = disk[n];
               disk[n] = temp;
           }
       }
   }
   return disk;
}
int discSchedAlgFCFS(int *ran_array)
{
   int i = 0, headMovement = 0;
   int this_start = disk[initialHead];
   for (i = initialHead; i < REQUESTS; i++)
       //add absolute difference disk[i]
       //and this_start to head movement
       headMovement += abs(disk[i] - this_start);
   for (i = 0; i < initialHead; i++)
       headMovement += abs(this_start - ran_array[i]);
   //return head movments of fcfs
   return headMovement;
}

int discSchedAlgLOOK(int* ranArray)
{
   int i = 0, currentValue = 0;
   int savedValue = disk[initialHead], diff = 0;
   int headMovement = 0, curr_i = 0;
   for (i = initialHead + 1; i < REQUESTS; i++)
   {
       currentValue = disk[i];
       //absolute difference value saved and current values
       diff = abs(savedValue - currentValue);
       //add difference to the head movment
       headMovement += diff;
       //save the current value as saved value
       savedValue = currentValue;
   }
   for (i = initialHead - 1; i >= 0; --i)
   {
       currentValue = disk[i];
       //absolute difference value saved and current values
       diff = abs(currentValue - savedValue);
       //add difference to the head movment
       headMovement += diff;
       //save the current value as saved value
       savedValue = currentValue;
   }
   //return head movments of LOOK
   return headMovement;
}
int discSchedAlgCLOOK(int* ranArray)
{
   int i = 0, currentValue = 0;
   int savedValue = disk[initialHead];
   int diff = 0;
   int headMovement = 0;
   for (i = initialHead + 1; i < REQUESTS; i++)
   {
       currentValue = disk[i];
       //absolute difference value saved and current values
       diff = abs(savedValue - currentValue);
       //add difference to the head movment
       headMovement += diff;
       //save the current value as saved value
       savedValue = currentValue;
   }
   for (i = 0; i < initialHead; i++)
   {
       currentValue = disk[i];
       //absolute difference value saved and current values
       diff = abs(currentValue - savedValue);
       //add difference to the head movment
       headMovement += diff;
       //save the current value as saved value
       savedValue = currentValue;
   }
   //return head movments of CLOOK
   return headMovement;
}
int main(int argc, char *argv[])
{
   int i = 0;
   //get intial postion from command line argument
   initialHead = atoi(argv[1]);
   if (argc != 2)
   {
       printf("Pass command line argument for"
           " initial head postion from 0-4999.\n");
       return -1;
   }
   //Generate 1000 cylinder requests
   for (i = 0; i < REQUESTS; i++)
   {//Generate random number between 1 to 5000
       disk[i] = rand() % 5000;
   }
    printf("\nThe initial position of the disk head:%d", initialHead);
    printf(" , value at intial head: %d\n\n", disk[initialHead]);
    printf("FCFS disk-scheduling algorithm head movements: %d\n",
       discSchedAlgFCFS(disk));
    printf("LOOK disk-scheduling algorithm head movements: %d\n",
       discSchedAlgLOOK(disk));
    printf("C-LOOK disk-scheduling algorithm head movements: %d\n\n",
       discSchedAlgCLOOK(disk));
    system("pause");
    printf("Press enter to continue...\n");
    getchar();
    return 0;
}