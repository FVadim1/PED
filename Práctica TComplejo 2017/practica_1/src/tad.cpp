#include <iostream>

using namespace std;

#include "tcomplejo.h"

int main(void){
  TComplejo a;
  TComplejo b(a);
  TComplejo c;
  c = a;

  if(a == b)
    cout << "1" << endl;
  else
    cout << "2" << endl;

  if(a == c)
    cout << "1" << endl;
  else
    cout << "2" << endl;


  return 0;
}
