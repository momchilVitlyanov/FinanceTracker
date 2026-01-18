

#include <iostream>
using namespace std;


struct MonthRecord {
    int id;
    char name[10];
    double income;
    double expense;
    double balance;
};

void myStrCopy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}


bool areStringsEqual(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return false;
        i++;
    }

    return (s1[i] == '\0' && s2[i] == '\0');
}
double myAbs(double x) {
    if (x < 0) return -x;
    return x;
}
void printSpaces(int n) {
    for (int i = 0; i < n; i++) cout << " ";
}
void getMonthName(int index, char* buffer) {
    const char* names[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    if (index >= 0 && index < 12) {
        myStrCopy(buffer, names[index]);
    }
    else {
        myStrCopy(buffer, "Unknown");
    }
}


int main()
{
   
}

