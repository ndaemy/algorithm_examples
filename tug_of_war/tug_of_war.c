#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// acquire partition problem solution
bool findPartition(int* weight, int participants, int sum) {
  int i, j;

  if (sum % 2 != 0) return false;

  bool part[sum / 2 + 1][participants + 1];

  // initialize top row as true
  for (i = 0; i <= participants; i++) part[0][i] = true;

  // initialize first column, except first row, as false
  for (i = 1; i <= sum / 2; i++) part[i][0] = false;

  // Fill the partition table in bottom up
  for (i = 1; i <= sum / 2; i++) {
    for (j = 1; j <= participants; j++) {
      part[i][j] = part[i][j - 1];
      if (i >= weight[j - 1])
        part[i][j] = part[i][j] || part[i - weight[j - 1]][j - 1];
    }
  }

  // uncomment this part to print table
  // for (i = 0; i <= sum / 2; i++) {
  //   for (j = 0; j <= participants; j++) printf("%4d", part[i][j]);
  //   printf("\n");
  // }

  return part[sum / 2][participants];
}

void tugOfWar(int* weight, int participants, int sum) {
  int gap;
  int first, second;

  // assume that there is a participant whose weight is gap
  participants++;  // assuming
  for (gap = 0; gap < sum; gap++) {
    weight[participants - 1] = gap;  // assuming
    if (findPartition(weight, participants, sum) == true) break;
    sum++;
  }

  first = sum / 2 - gap;
  second = sum / 2;
  printf("%d %d\n", first, second);
}

int main() {
  int rope, participants;  // number of rope, participants
  int weight[100];         // list of participants people's weight
  int sum;

  // input values
  scanf("%d", &rope);
  scanf("%d", &participants);
  sum = 0;
  for (int i = 0; i < participants; i++) {
    scanf("%d", &weight[i]);
    sum += weight[i];
  }

  tugOfWar(weight, participants, sum);

  return 0;
}