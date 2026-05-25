
// In order to enter as an admin, Login is "admin" and password is also "admin"

#include <iostream>
#include <fstream> // in order to file handling
#include <string>
#include <vector>
#include "header.h" // we dont write iostream and others beacuse we call the header file and it has all of tehm that is why it is enough
int main()
{
    string userFile = "users.txt";
    string gradeFile = "grades.txt";
    while (true)
    {
        vector<USERS> userList = openUSERS(userFile); // load all users from file each time login screen opens
        if (userList.empty())                         // if file is empty, create default admin account
        {
            USERS adminUser("admin", "admin", "admin", "NONE");
            userList.push_back(adminUser);
            saveUSERS(userFile, userList);
        }

        string login, parol;
        cout << endl
             << "=== ENTER PROGRAM  ===" << endl;
        cout << "Login (write 0 to close program) ";
        cin >> login;
        if (login == "0") // if login is equal to 0 it is ended
        {
            cout << "Program is ended!" << endl;
            break;
        }
        cout << "Password: ";
        cin >> parol;
        bool found = false;

        for (int i = 0; i < userList.size(); i++) // loop through all users
        {
            if (userList[i].getLogin() == login && userList[i].getParol() == parol) // check login and password
            {
                found = true;
                string pos = userList[i].getPosition();
                if (pos == "admin")
                {
                    ADMIN adminPanel(userList, userFile);
                    adminPanel.menu();
                }
                else if (pos == "professor")
                {
                    PROF profPanel(userList[i], userList, userFile, gradeFile);
                    profPanel.runMenu();
                }
                else if (pos == "student")
                {
                    STUDENT studentPanel(userList[i], gradeFile);
                    int choice;
                    while (true)
                    {
                        cout << endl
                             << "STUDENT PANEL: " << login << endl;
                        cout << "1. View Grades" << endl;
                        cout << "0. Back to login" << endl;
                        cout << "Choice: ";
                        cin >> choice;

                        if (choice == 1)
                        {
                            studentPanel.showGrades();
                        }
                        else if (choice == 0)
                        {
                            cout << "Back to login" << endl;
                            break;
                        }
                        else
                        {
                            cout << "Wrong choice" << endl;
                        }
                    }
                }
                break;
            }
        }

        if (!found)
        {
            cout << "Not founded! Check login or password" << endl;
        }
    }

    return 0;
}