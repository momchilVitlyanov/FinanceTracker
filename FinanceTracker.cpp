

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
void printReport(MonthRecord* records, int count) {
    cout << "\n-------------------------------------------------\n";
    cout << "Month      | Income     | Expense    | Balance   \n";
    cout << "-------------------------------------------------\n";

    cout.flags(ios::fixed);
    cout.precision(2);

    for (int i = 0; i < count; i++) {
        cout << records[i].name;
        printSpaces(11 - 3);
        cout << "| ";

        cout << records[i].income;
        if (records[i].income < 1000) printSpaces(4); else printSpaces(3);
        cout << "| ";

        cout << records[i].expense;
        if (records[i].expense < 1000) printSpaces(4); else printSpaces(3);
        cout << "| ";
        if (records[i].balance > 0) cout << "+";
        cout << records[i].balance << endl;
    }
    cout << "-------------------------------------------------\n";

}

void searchMonth(MonthRecord* records, int count) {
    char searchName[20];
    cin >> searchName;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (areStringsEqualIgnoreCase(records[i].name, searchName)) {
            double ratio = 0.0;
            if (records[i].income != 0) {
                ratio = (records[i].expense / records[i].income) * 100.0;
            }

            cout << "Income: " << records[i].income << endl;
            cout << "Expense: " << records[i].expense << endl;

            cout << "Balance: ";
            if (records[i].balance > 0) cout << "+";
            cout << records[i].balance << endl;

            cout << "Expense ratio: " << ratio << "%" << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "Month not found.\n";
}

void sortData(MonthRecord* records, int count) {
    char type[20];
    cin >> type;

    MonthRecord* temp = new MonthRecord[count];
    for (int i = 0; i < count; i++) temp[i] = records[i];

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            bool swapNeeded = false;
            if (areStringsEqual(type, "income") && temp[j].income < temp[j + 1].income) swapNeeded = true;
            else if (areStringsEqual(type, "expense") && temp[j].expense < temp[j + 1].expense) swapNeeded = true;
            else if (areStringsEqual(type, "balance") && temp[j].balance < temp[j + 1].balance) swapNeeded = true;

            if (swapNeeded) {
                MonthRecord swapTemp = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swapTemp;
            }
        }
    }

    cout << "Sorted by monthly " << type << " (descending):\n";
    int limit = (count < 3) ? count : 3;

    for (int i = 0; i < limit; i++) {
        double val;
        if (areStringsEqual(type, "income")) val = temp[i].income;
        else if (areStringsEqual(type, "expense")) val = temp[i].expense;
        else val = temp[i].balance;

        cout << temp[i].name << ": ";
        if (areStringsEqual(type, "balance") && val > 0) cout << "+";
        cout << val << endl;
    }

    delete[] temp;
}

void forecast(MonthRecord* records, int count) {
    int monthsAhead;
    cin >> monthsAhead;

    double currentSavings = 0;
    double totalChange = 0;

    for (int i = 0; i < count; i++) {
        currentSavings += records[i].balance;
        totalChange += records[i].balance;
    }

    double avgChange = (count > 0) ? (totalChange / count) : 0;

    if (avgChange >= 0) {
        double futureSavings = currentSavings + (monthsAhead * avgChange);
        cout << "Current savings: " << currentSavings << endl;

        cout << "Avg monthly change: ";
        if (avgChange > 0) cout << "+";
        cout << avgChange << endl;

        cout << "Forecast in " << monthsAhead << " months: " << futureSavings << endl;
    }
    else {
        cout << "Current savings: " << currentSavings << endl;
        cout << "Avg monthly change: " << avgChange << endl;

        if (currentSavings <= 0) {
            cout << "You are already in debt or at 0.\n";
        }
        else {
            int monthsToZero = (int)(currentSavings / myAbs(avgChange));
            cout << "Warning! Funds will reach 0 in approx " << monthsToZero << " months.\n";
        }
    }
}
int main()
{
   
}

