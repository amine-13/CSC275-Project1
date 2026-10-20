/*
 * Group Members:
 * Amine Gbadamassi
 * Naydon Jeffrey
 * Aneury Gonzalez
 */

#include <iostream>
#include <string>
using namespace std;


// ==================================================
// PART A: APP CLASS
// ==================================================

/*
Represents an application installed on a smartphone.
*/
class App
{
public:
    string appName;  // Name of the application
    int appSize;     // Size of the application in GB
};


// ==================================================
// PART B: SMARTPHONE CLASS DECLARATION
// ==================================================

class Smartphone
{
private:
    int capacity;       // Total storage capacity in GB
    string name;        // Name of the smartphone
    App* apps_array;    // Dynamic array of installed applications
    int nbAppsInst;     // Number of installed applications

public:
    // Method 1: Constructor
    Smartphone(int cap, string phoneName);

    // Method 2: get_available_space()
    int get_available_space();

    // Method 3: has_app()
    bool has_app(string appname);

    // Method 4: add_app()
    void add_app(string appname, int appsize);

    // Method 5: remove_app()
    void remove_app(string appname);

    // Method 6: report()
    void report();
};


// ==================================================
// PART C: METHOD DEFINITIONS
// ==================================================


// --------------------------------------------------
// Method 1: Constructor
// Purpose: Initializes the smartphone.
// --------------------------------------------------

Smartphone::Smartphone(int cap, string phoneName)
{
    capacity = cap;
    name = phoneName;

    // The smartphone starts with no installed apps
    apps_array = NULL;
    nbAppsInst = 0;
}


// --------------------------------------------------
// Method 2: get_available_space()
// Purpose: Calculates the remaining storage space.
// --------------------------------------------------

int Smartphone::get_available_space()
{
    int usedSpace = 0;

    // Calculate the total size of installed apps
    for (int i = 0; i < nbAppsInst; i++)
    {
        usedSpace += apps_array[i].appSize;
    }

    // Return the remaining storage space
    return capacity - usedSpace;
}


// --------------------------------------------------
// Method 3: has_app()
// Purpose: Checks whether an app is installed.
// --------------------------------------------------

bool Smartphone::has_app(string appname)
{
    // Search for the application
    for (int i = 0; i < nbAppsInst; i++)
    {
        if (apps_array[i].appName == appname)
        {
            return true;
        }
    }

    // The application was not found
    return false;
}


// --------------------------------------------------
// Method 4: add_app()
// Purpose: Installs an app if space is available.
// --------------------------------------------------

void Smartphone::add_app(string appname, int appsize)
{
    // Check whether the app is already installed
    if (has_app(appname))
    {
        cout << "App is already installed" << endl;
        return;
    }

    // Check whether the app size is valid
    if (appsize <= 0)
    {
        cout << "Invalid app size" << endl;
        return;
    }

    // Check whether enough storage space is available
    if (appsize > get_available_space())
    {
        cout << "Cannot install app, no available space" << endl;
        return;
    }

    // Allocate a new array with space for one more app
    App* new_array = new App[nbAppsInst + 1];

    // Copy the currently installed apps
    for (int i = 0; i < nbAppsInst; i++)
    {
        new_array[i] = apps_array[i];
    }

    // Add the new application to the array
    new_array[nbAppsInst].appName = appname;
    new_array[nbAppsInst].appSize = appsize;

    // Replace the old array with the new array
    delete[] apps_array;
    apps_array = new_array;

    // Update the number of installed apps
    nbAppsInst++;
}


// --------------------------------------------------
// Method 5: remove_app()
// Purpose: Removes an installed application.
// --------------------------------------------------

void Smartphone::remove_app(string appname)
{
    // Check whether the app is installed
    if (!has_app(appname))
    {
        cout << "App is not installed" << endl;
        return;
    }

    // Find the position of the app to remove
    int index = 0;

    while (apps_array[index].appName != appname)
    {
        index++;
    }

    // Create a smaller array if other apps remain
    App* new_array = NULL;

    if (nbAppsInst > 1)
    {
        new_array = new App[nbAppsInst - 1];

        // Copy every app except the one being removed
        int j = 0;

        for (int i = 0; i < nbAppsInst; i++)
        {
            if (i != index)
            {
                new_array[j] = apps_array[i];
                j++;
            }
        }
    }

    // Release the old array
    delete[] apps_array;

    // Update the array and app count
    apps_array = new_array;
    nbAppsInst--;

    // Confirm that the app was removed
    cout << "App removed: " << appname << endl;
}


// --------------------------------------------------
// Method 6: report()
// Purpose: Displays smartphone information and apps.
// --------------------------------------------------

void Smartphone::report()
{
    // Calculate the amount of storage currently used
    int usedSpace = capacity - get_available_space();

    cout << "Name: " << name << endl;

    cout << "Capacity: " << usedSpace
         << " out of " << capacity << " GB" << endl;

    cout << "Available space: "
         << get_available_space() << endl;

    cout << "Apps installed: " << nbAppsInst << endl;

    // Display each installed app and its size
    for (int i = 0; i < nbAppsInst; i++)
    {
        cout << "* " << apps_array[i].appName
             << " is using " << apps_array[i].appSize
             << " GB" << endl;
    }
}


// ==================================================
// PART D: MAIN FUNCTION
// ==================================================

int main()
{
    int phoneCapacity;
    string phoneName;

    // Ask for a valid smartphone capacity
    while (true)
    {
        cout << "Size of your new smartphone (32, 64 or 128 GB): ";

        if (cin >> phoneCapacity &&
            (phoneCapacity == 32 ||
             phoneCapacity == 64 ||
             phoneCapacity == 128))
        {
            break;
        }

        cout << "Invalid input. Please enter 32, 64 or 128."
             << endl;

        // Reset input if the user enters invalid data
        cin.clear();
        cin.ignore(10000, '\n');
    }

    // Ask for the smartphone name
    cout << "Smartphone name: ";
    cin >> ws;
    getline(cin, phoneName);

    // Create the smartphone
    Smartphone phone(phoneCapacity, phoneName);

    cout << "Smartphone created!" << endl;

    // Display the initial report
    phone.report();

    char choice;

    // Display the menu until the user chooses to quit
    do
    {
        cout << endl;
        cout << "(r)eport, (a)dd app, r(e)move app or (q)uit: ";

        if (!(cin >> choice))
        {
            break;
        }

        switch (choice)
        {
        case 'r':
        case 'R':
            // Display the smartphone report
            phone.report();
            break;

        case 'a':
        case 'A':
        {
            string appName;
            int appSize;

            // Ask for the application name
            cout << "App name: ";
            cin >> ws;
            getline(cin, appName);

            // Ask for a valid application size
            cout << "App size: ";

            if (!(cin >> appSize))
            {
                cout << "Invalid app size." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }

            // Attempt to install the app
            phone.add_app(appName, appSize);
            break;
        }

        case 'e':
        case 'E':
        {
            string appName;

            // Ask for the application to remove
            cout << "App name: ";
            cin >> ws;
            getline(cin, appName);

            // Attempt to remove the app
            phone.remove_app(appName);
            break;
        }

        case 'q':
        case 'Q':
            // End the program
            cout << "Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice." << endl;
        }

    } while (choice != 'q' && choice != 'Q');

    return 0;
}
