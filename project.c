#include<stdio.h>

//sort algorithm
/*
void swap (int *a , int *b)
{
    int temp= *a ;
    *a = *b ;
    *b = temp ;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1) , j;

    for (j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int partition_r(int arr[], int low, int high)
{
    srand(time(NULL));
    int random = low + rand() % (high - low);
    swap(arr[random], arr[high]);

    return partition(arr, low, high);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pi = partition_r(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}*/

//structures
struct Film
{
    int movieLen;
    char name[10];
    char actors[10][20];
};
struct Saans
{
    struct Film *film;
    int capacity ;
    int start;
};
struct Salon
{
    int id;
    int numberOfSaans;
    struct Saans *saans[10];
};
struct Cinema
{
    struct Salon *salons[10];
    struct Film *allFilms[100];
    int numberOfFilms, numberOfSalons;
};
struct Film* findFilmByName(struct Cinema cinema,struct Film film) {
    int i,j;
    for(i=0;i<cinema.numberOfFilms;i++)
    {
        int match=1;
        for(j=0;j<10;j++)
        {
            if(film.name[i]!=(*(cinema.allFilms[i])).name[j])
            {
                match=0;
            }
        }
        if(match==1)
        {
            return (cinema.allFilms[i]);
        }
    }
    return &film;
}
int isOk(struct Salon salon){
    int i,j;
    for(i=0;i<salon.numberOfSaans;i++)
    {
        for(j=0;j<salon.numberOfSaans;j++)
        {
            if(i!=j && (*(salon.saans[i])).start<=(*(salon.saans[j])).start && (*(salon.saans[i])).start+(*((*(salon.saans[i])).film)).movieLen>(*(salon.saans[j])).start)
            {
                return 0;
            }
        }
    }
    return 1;
}

struct Cinema readData(char fileName[]) {
    /* format :i= int S=string
        number of film(i)

        for each film :
            film name(S) filmLen(i) numberOfActor(i)
            actorname(s)
            actorname(s)

        number of salons(i)
        for each salon:
            number of saans(i)
            for each saans:
                film name(s)
                capacity(i)
                start(i)
    */
    FILE *data;
    data = fopen(fileName, "r");
    // tedad salona bad filmesh bad
    struct Cinema cinema;
    int filmNumber;
    fscanf(data, "%d", &filmNumber);
    int i,j;
    for(i=0;i<filmNumber;i++)
    {
        struct Film film;
        fscanf(data, "%s", film.name);
        fscanf(data, "%d", &film.movieLen);
        int actorNumber;
        fscanf(data, "%d", &actorNumber);

        for(j=0; j<actorNumber ; j++)
        {
            fscanf(data, "%s", film.actors[j]);
        }
        cinema.allFilms[i]=&film;
    }
    int numberOfSalons;
    fscanf(data, "%d", &numberOfSalons);
    cinema.numberOfSalons=numberOfSalons;

    for(i=0;i<numberOfSalons;i++)
    {
        struct Salon salon;
        cinema.salons[i]=&salon;
        int numberOfSaans;
        fscanf(data, "%d", &numberOfSaans);
        salon.numberOfSaans=numberOfSaans;
        salon.numberOfSaans=numberOfSaans;
        for(j=0;j<numberOfSaans;j++)
        {
            struct Saans saans;
            salon.saans[j]=&saans;
            struct Film film;
            fscanf(data, "%s", film.name);

            saans.film=findFilmByName(cinema,film);

            fscanf(data, "%d", &saans.capacity);
            fscanf(data, "%d", &saans.start);
        }
    }
    return cinema;
}

int main()
{
    struct Cinema cinema=readData("data.TT");
    int i;
    for(i=0;i<cinema.numberOfSalons;i++)
    {
        if(isOk(*cinema.salons[i])==0){
            printf("salon number %d has problem in timing\n",i);
        }
    }
    return 0;
}
