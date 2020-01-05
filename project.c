#include<stdio.h>

struct Film
{
    int movieLen;
    char act[10][20] ;
};
struct Saans
{
    struct Film film ;
    int capacity ;
    int start , ending ;
};
struct Salons
{
    struct Saans saans[10];
};
struct Cinema
{
    struct Salons salons[10] ;
};
int main()
{

    return 0;
}
