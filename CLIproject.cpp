#include <iostream>

using namespace std;

int main(int argc, char* argv[]){

cout << "Hello World From CLI" << endl;
cout << "ARG COUNT: " << argc << endl;
for (int i = 0; i < argc; i++){
   cout << "ARG " << i <<  ": " << argv[i] << endl;
}
if ((string)argv[2] == "multiply"){    //we can string cast argv[2] because argv[2] is actually 				         a character array and not a string.  
   cout << "We can do this!" << endl;
}
return 0;

}
