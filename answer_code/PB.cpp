#include<iostream>
#include<math.h>

using namespace std;

int main(){
    double a, b, c;
    double s;
    double area;
    cin >> a >> b >> c;
    s = (a + b + c) / 2;
    area = sqrt(s * (s - a) * (s - b) * (s - c));
    cout << area << endl;
    return 0;
}