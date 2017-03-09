#include <stdlib.h>
#include <stdio.h>

int random_my(int min, int max)
{
  int tmp; // nie potrzebne
  if (max >= min) // min i max zawsze 0 i 100 wiêc warunek zbedny
  {
    max -= min; // od 100 odejmujemy 0?
  }
  else // nigdy sie  nie wykonuje
  {
    tmp = min - max;
    min = max;
    max = tmp;
  }
  return max ? (rand() % max + min) : min; // brak inicjalizacji generatora liczb pseudolosowych
}

int f()
{
  const int N = 17; // zmiana na dlugosc imienia i nazwiska
  int* x = (int *)malloc(N * sizeof(int)); // malloc dla N liczb oraz brak free()
  int i;
  int mean = 0;
  for (i = 0; i <= N; ++i) // N+1 liczb, ostatnia wychodzi poza zarezerowana pamiec
  {
    int val = random_my(0, 100);
    printf("%02d: %d\n", i, val);
    x[i] = val;
  }
  for (i = 0; i <= N; ++i)//N+1 liczb
  {
    mean += x[i];
  }
  mean /= N;
  return mean;
}

int main(int argc, char * argv[])
{
  int val = f();
  printf("Mean: %d\n", val);
  return 0;
}
