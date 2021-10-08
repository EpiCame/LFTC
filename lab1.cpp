#include <iostream>
#include <cmath>

using namespace std;

int main(){
    int R = 3;
    double area, perimeter;
    area = M_PI * R * R;
    perimeter = 2 * M_PI * R;
    cout << "Area: " << area << endl;
    cout << "Perimeter: " << perimeter << endl;
}

int main()
{
    int a, b;
    cout << "a="; cin>>a;
    cout << "b="; cin>>b;

    while(a != b)
    {
        if(a > b)
            a = a - b;
        else
            b = b - a;
    }
    cout << "GCD:" << a << endl;
}

int main()
{
    double nums[100], sum = 0;
    int n, i = 0;
    cout << "n="; cin>>n;
    while (i < n)
    {
        cout << "nums[" << i << "]=";
        cin >> nums[i];
        sum = sum + nums[i];
        i = i + 1;
    }
    cout << "sum: " << sum << endl;
}


//
//int main() {
//    cirleAreaAndPerimeter();
//
//}
