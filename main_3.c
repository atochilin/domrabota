#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y) \
  unsigned z = x;  \
  x = y;           \
  y = z;

bool check(const unsigned *mass, unsigned pos, unsigned mean) { //передаем в функцию массив, позицию элемента в массиве и его значение
  for (unsigned i = pos-1; i > 0; --i) {  //проходимся назад по массиву от этого элемента 
    if (mass[i] == mean && i % 2 != 0) {  //если существует такое число и позиция нечетная(правая) то возвращаем что все окей
      return true;
    }
  }
  return false;
}

bool connectedness(const unsigned *mass, unsigned count) { 
  unsigned connect = 0;                    //будет хранить в себе количество правильных связей
  for (unsigned i = 1; i < count; i += 2) { //проходим по массиву
    if (mass[i - 1] == 1) {                 //если левая вершина 1
      if (mass[i] > mass[i - 1]) {          // и элемент справа больше
        ++connect;                          //то правильная связь
      }
    } else {                               //если левый элемент не 1
      if (mass[i] > mass[i - 1] && check(mass, i - 1, mass[i - 1]) == true) {    //проверяем на то что элемент справа больше и проверяем функцие что он с чем то уже связан
        ++connect;
      }
    }
  }
  if (connect == count / 2) {  //если колличество правильных связей равно колличеству ребер то граф связанный 
    return true;
  }
  return false;
}

int countoftops(unsigned *input, unsigned count) {      //сортируем массив по возрастанию и потом считаем количество уникальных вершин 
  unsigned size = 1; //колличество уникальных вершин 
  unsigned left = 0;  //левая граница
  unsigned right = count - 1;  //правая граница
  bool flag = true;            //показывает была ли перестановка или нет
  while ((left < right) && flag == true) {  //сортрируем по возорсатнию с помощью шейкерной сортировки
    flag = false;
    for (unsigned i = left; i < right; ++i) { //проходимся по массиву слева направо
      if (input[i] > input[i + 1]) {          //если следующий элемент больше то меняем их местами и присваиваем влагу тру
        SWAP(input[i], input[i + 1]);
        flag = true;
      }
    }
    --right;   //уменьшаем правую границу на 1 тк как справа уже стоит самый большой элемент
    for (unsigned i = right; i > left; --i) { //все тоже самое только в обратную сторону
      if (input[i - 1] > input[i]) { //
        SWAP(input[i - 1], input[i]);//
        flag = true;//
      }
    }
    ++left;//
  }

  for (unsigned i = 1; i < count; ++i) {  //считаем уникальные вершины
    if (input[i] != input[i - 1]) {       //если предыдущий элемент и текущий не равны 
      ++size;                             //увеличиваем счетчик уникальных вершин
    }
  }

  return size;
}
int main(void) {
  FILE *input = fopen("input.txt", "r");  //открываем фаил для чтения
  FILE *graph; 
  unsigned *mass; //объявляем массив  
  unsigned top1 = 0; //левая вершина
  unsigned top2 = 0;  //правая вершина
  unsigned count = 0;  //счетчик вершин для добавления памяти
  unsigned edge = 0;   //количество ребер
  bool cycle = false; //проверка на уикл
  mass = malloc(count * sizeof(unsigned));  //создаем массив
  while (!feof(input)) {  //цикл для сичтывания данных из файла в массив
    fscanf(input, "%d-%d\n", &top1, &top2); //сканируем числа в наши переменные
    if (top1 == top2) {  //если правая и левая вершины одинаковы то это цикл
      cycle = true;
    }
    count += 2;  //так как выше приняли два числа увеличиваем счетчик
    mass = (unsigned *)realloc(mass, count * (sizeof(unsigned)));  //увеличиваем размер массива  
    mass[count - 2] = top1;  //пихаем в массив наши числа
    mass[count - 1] = top2;  //
  }
  fclose(input);     //закрывем фаил так как он нам больше не нужен
  edge = count / 2;  //колличество ребер

  graph = fopen("graph.dot", "w");  //открываем фаил для визуализации графа
  fprintf(graph, "graph G{\n");      //первая страка для правильного синтаксиса
  for (unsigned i = 0; i < count; i += 2) {     //проходимся циклом по нашему массиву 
    fprintf(graph, "%d -- %d\n", mass[i], mass[i + 1]);  //и записываем в фаил наши вершины 
  }
  fprintf(graph, "}"); //для синтаксиса 
  fclose(graph);       //закрываем фаил

  if (connectedness(mass, count) == true && countoftops(mass, count) - 1 == edge && cycle == false) {  //проверям на связанность и на вершины
    printf("Граф является деревом\n");
  } else {
    printf("Граф не является деревом\n");
  }
  return 0;
}