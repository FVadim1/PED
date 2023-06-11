#include <iostream>

using namespace std;

#include "../include/tcalendario.h"


int
main()
{

   TCalendario c1(02,01,1900, (char*) "Fecha correcta");
   cout<<c1--<<endl;
   cout<<--c1<<endl;
   
}
