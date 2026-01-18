

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
char toLower(char c) {
    if (c >= 'A' && c <= 'Z') return c + ('a' - 'A');
    return c;
}

bool areStringsEqualIgnoreCase(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (toLower(s1[i]) != toLower(s2[i])) return false;
        i++;
    }
    return (s1[i] == '\0' && s2[i] == '\0');
}


int getMonthIndexByName(const char* inputName) {
    const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    for (int i = 0; i < 12; i++) {
        if (areStringsEqualIgnoreCase(inputName, months[i])) return i;
    }
    return -1; 
}

MonthRecord* setupProfile(int& count) {
    cout << "Enter number of months: ";
    cin >> count;

    MonthRecord* records = new MonthRecord[count];

    for (int i = 0; i < count; i++) {
        records[i].id = i + 1;
        getMonthName(i % 12, records[i].name);
        records[i].income = 0.0;
        records[i].expense = 0.0;
        records[i].balance = 0.0;
    }

    cout << "Profile created successfully.\n";
    return records;
}

void addData(MonthRecord* records, int count) {
    char inputName[20];
    cout << "Enter month (e.g. Jan, Feb): ";
    cin >> inputName;
    int arrIdx = getMonthIndexByName(inputName);
    if (arrIdx == -1) {
        cout << "Invalid month name! Use 3 letters (Jan, Feb...)\n";
        return;
    }
    if (arrIdx >= count) {
        cout << "Error: This month is outside your profile range.\n";
        return;
    }
    cout << "Enter income: ";
    cin >> records[arrIdx].income;
    cout << "Enter expense: ";
    cin >> records[arrIdx].expense;
    records[arrIdx].balance = records[arrIdx].income - records[arrIdx].expense;
    cout << "Result: Balance for " << records[arrIdx].name << " = ";
    if (records[arrIdx].balance > 0) cout << "+";
    cout << records[arrIdx].balance << endl;
}

int main()
{
   
}

