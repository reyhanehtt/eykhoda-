#include<stdio.h>
//structures
struct Film
{
    int movieLen;
    char name[10];
    char actors[10][20];
};
struct Saans
{
    struct Film film;
    int capacity ;
    int start;
	int salonId;
};
struct Salon
{
    int id;
    int numberOfSaans;
    struct Saans saans[10];
};
struct Cinema
{
    struct Salon salons[10];
    struct Film allFilms[100];
    int numberOfFilms, numberOfSalons;
};


//sort algorithm
void swap (struct Saans  *a , struct Saans  *b)
{
    struct Saans  temp= *a ;
    *a = *b ;
    *b = temp ;
}
int partition(struct Saans  arr[], int low, int high)
{
    struct Saans  pivot = arr[high];
    int i = (low - 1) , j;
    for (j = low; j <= high - 1; j++) {
        if (arr[j].start <= pivot.start) {
            i++;
            swap(&(arr[i]), &(arr[j]));
        }
    }
    swap(&(arr[i + 1]), &(arr[high]));
    return (i + 1);
}
int partition_r(struct Saans  arr[], int low, int high)
{
    srand(time(NULL));
    int random = low + rand() % (high - low);
    swap(&arr[random], &arr[high]);
    return partition(arr, low, high);
}
void quickSort(struct Saans arr[], int low, int high)
{
    if (low < high) {
        int pi = partition_r(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


struct Film findFilmByName(struct Cinema cinema,struct Film film) {
    int i,j;
    for(i=0;i<cinema.numberOfFilms;i++)
    {
        int match=1;
        for(j=0;j<10;j++)
        {
            if(film.name[j]!=(cinema.allFilms[i]).name[j])
            {
                match=0;
            }
        }
        if(match==1)
        {
            return cinema.allFilms[i];
        }
    }
	printf("not find!\n");
    return film;
}
int isOk(struct Salon salon){
    int i,j;
    for(i=0;i<salon.numberOfSaans;i++)
    {
        for(j=0;j<salon.numberOfSaans;j++)
        {
            if(i!=j && salon.saans[i].start<=salon.saans[j].start && salon.saans[i].start+salon.saans[i].film.movieLen>salon.saans[j].start)
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
                start 'in HH:MM format'
    */
    FILE *data;
    data = fopen(fileName, "r");
    struct Cinema cinema;
    fscanf(data, "%d", &(cinema.numberOfFilms));
    int i,j;
    for(i=0;i<cinema.numberOfFilms;i++)
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
        cinema.allFilms[i]=film;
	}
    fscanf(data, "%d", &cinema.numberOfSalons);
    for(i=0;i<cinema.numberOfSalons;i++)
    {
        struct Salon salon;
		salon.id=i+1;
        fscanf(data, "%d", &salon.numberOfSaans);
        salon.numberOfSaans=salon.numberOfSaans;
        salon.numberOfSaans=salon.numberOfSaans;
        for(j=0;j<salon.numberOfSaans;j++)
        {
            struct Saans saans;
			saans.salonId=salon.id;
            struct Film film;
            fscanf(data, "%s", film.name);

            saans.film=findFilmByName(cinema,film);

            fscanf(data, "%d", &saans.capacity);
			char e[6];
			fscanf(data, "%s",e);
			int start=((e[0]-'0')*10+(e[1]-'0'))*60+((e[3]-'0')*10)+(e[4]-'0');
			saans.start=start;

            salon.saans[j]=saans;
        }
        cinema.salons[i]=salon;
    }
    return cinema;
}

int main()
{
    struct Cinema cinema=readData("data.TT");
    int i,j,k;
    for(i=0;i<cinema.numberOfSalons;i++)
    {
        if(isOk(cinema.salons[i])==0){
            printf("salon number %d has problem in timing\n",i);
        }
    }
	int n=10000;
	for(i=0;i<n;i++){
		printf("enter time in (HH:MM) format:");
		char e[5];
		scanf("%s",e);
		int start=((e[0]-'0')*10+(e[1]-'0'))*60+((e[3]-'0')*10)+(e[4]-'0');
		struct Saans allValidSaans[100];
		int cnt=0;
		for(j=0;j<cinema.numberOfSalons;j++){
			struct Salon salon=cinema.salons[j];
			for(k=0;k<salon.numberOfSaans;k++){
				struct Saans saans=salon.saans[k];
				if(saans.start>=start){
					allValidSaans[cnt]=saans;
					cnt++;
				}
			}
		}
		quickSort(allValidSaans,0,cnt-1);
		int j;
		for( j=0;j<cnt;j++){
			struct Saans saans=allValidSaans[j];
			int start=saans.start;
			int end=(saans.start+saans.film.movieLen)%(60*24);
			printf("movie name:%s    start at: %d%d:%d%d until: %d%d:%d%d in Salon:%d\n",saans.film.name,(start/60)/10,(start/60)%10,(start%60)/10,(start)%10,   (end/60)/10,(end/60)%10,(end%60)/10,(end)%10,saans.salonId);
		}
	}
    return 0;
}
