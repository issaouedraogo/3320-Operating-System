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
int discSchedAlgSSTF(int * disk)
{
   //befor start SSTF algorithm, first sort the disk
   disk = sortDisk();
   //Decalre the variables
   int s = initialHead - 1, l = initialHead + 1;
   int smallDiff = 0, largeDiff = 0;
   int headMovement = 0, n = REQUESTS - 2;
   int new_head = initialHead, head_value = disk[initialHead];
   //loop until the total number of request n to reach 0
   while (n >= 0)
   {
       //absolute difference disk[new_head]
       //and disk[s] into smallDiff
       smallDiff = abs(disk[new_head] - disk[s]);
       //absolute difference disk[new_head]
       //and disk[l] into largeDiff
       largeDiff = abs(disk[l] - disk[new_head]);
       //check if smallDiff is lessthan largeDiff
       if (smallDiff < largeDiff)
       {//then add smallDiff to headMovement
           headMovement += smallDiff;
           new_head = s;
           s--;//Decrement s
       }
       else
       {//else add largeDiff to headMovement
           headMovement += largeDiff;
           new_head = l;
           l++;//increament l
       }
       n--;
   }
   //return head movments of SSTF
   return headMovement;
}
int discSchedAlgSCAN(int * ranArray) {
   int i = 0, currentValue = 0;
   int savedValue = disk[initialHead], difference = 0;
   int headMovement = 0, curr_i = 0;
   for (i = initialHead - 1; i >= 0; --i)
   {
       currentValue = disk[i];
       //absolute difference value saved and current values
       difference = abs(savedValue - currentValue);
       //add difference to the head movment
       headMovement += difference;
       //save the current value as saved value
       savedValue = currentValue;
   }
   /* used to subtract value from zero, or just add same value */
   headMovement += savedValue;
   savedValue = 0;
   for (i = initialHead + 1; i < REQUESTS; i++)
   {
       currentValue = disk[i];
       //absolute difference value saved and current values
       difference = abs(currentValue - savedValue);
       //add difference to the head movment
       headMovement += difference;
       //save the current value as saved value
       savedValue = currentValue;
   }
   //return head movments of SCAN
   return headMovement;
}
int discSchedAlgCSCAN(int *disk) {
   int i = 0, currentValue = 0;
   int savedValue = disk[initialHead], diff = 0;
   int headMovement = 0, lastIndex = 4999;
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
   //add last val - upper bound, go to and
   //add zero bounday (4999)
   headMovement += lastIndex - savedValue;
   savedValue = 0;
   headMovement += 4999;
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
   //return head movments of CSCAN
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
    printf("SSTF disk-scheduling algorithm head movements: %d\n",
       discSchedAlgSSTF(disk));
    printf("SCAN disk-scheduling algorithm head movements: %d\n",
       discSchedAlgSCAN(disk));
    printf("CSCAN disk-scheduling algorithm head movements: %d\n",
       discSchedAlgCSCAN(disk));
    system("pause");
    printf("Press enter to continue...\n");
    getchar();
    return 0;
}