#include <iostream>
using namespace std;

int main() {
    int choice;

    cout << "=== Menu ===\n";
    cout << "1. Game\n";
    cout << "2. Help\n";
    cout << "3. Exit\n";
    cout << "Selec a choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "start game\n";
        break;
    case 2:
        cout << "Help.\n";
        break;
    case 3:
        cout << "Exit...\n";
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }

    return 0;
}
