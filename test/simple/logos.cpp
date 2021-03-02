#include "../../include/logos.hpp"
#include "../../include/color.hpp"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    Logo logo;
    Color color;
    int n = 30;
    for(int k=0; k<n; k++)
    {
        cout << Logo::randomLogo() << endl;   
    }
}
