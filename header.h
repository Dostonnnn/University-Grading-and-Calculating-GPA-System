#ifndef header_h
#define header_h

#include <iostream>
#include <fstream> // in order to file handling
#include <string>
#include <vector>

using namespace std;

// to calculate overall sum of the balls
double sumBall(double quiz, double hw, double lab, double project, double midterm, double final)
{
    double sum = 0; // sum starts fron 0
    // every task has their own percentage from 100%
    sum += (quiz * 20 + hw * 5 + lab * 10 + project * 15 + midterm * 25 + final * 25) / 100;
    return sum;
}
double calculateGPA(double ball) // here we can find GPA with using if else
{
    if (ball >= 95)
    {
        return 4.5;
    }
    else if (ball >= 90 && ball < 95)
    {
        return 4.0;
    }
    else if (ball >= 85 && ball < 90)
    {
        return 3.5;
    }
    else if (ball >= 80 && ball < 85)
    {
        return 3.0;
    }
    else if (ball >= 75 && ball < 80)
    {
        return 2.5;
    }
    else if (ball >= 70 && ball < 75)
    {
        return 2.0;
    }
    else if (ball >= 60 && ball < 70)
    {
        return 1.0;
    }
    else
    {
        return 0.0;
    }
}

class USERS // this class is to save infos about Admin Prof and Student
{
private:
    // for saving important infos about users and also usign encupsalition we have used private
    string login, parol, position, course;

public:
    // constructor
    USERS(string log = "", string par = "", string pos = "", string cour = "")
    {
        login = log;
        parol = par;
        position = pos;
        course = cour;
    }

    // setters
    void setLogin(string l)
    {
        login = l;
    }
    void setParol(string p)
    {
        parol = p;
    }
    void setPosition(string po)
    {
        position = po;
    }
    void setCourse(string c)
    {
        course = c;
    }

    // getters
    string getLogin()
    {
        return login;
    }
    string getParol()
    {
        return parol;
    }
    string getPosition()
    {
        return position;
    }
    string getCourse()
    {
        return course;
    }
    // destructor is called when object is destroyed (if user put 0 menu fucntion is ended and this is called)
    ~USERS() {}
    virtual void menu()
    {
    }
};

class GRADE // in order to control grading
{
private:
    // initialize variables
    string studentLogin, course;
    double quiz, hw, lab, project, midterm, final, overall;

public:
    // constructore will give initial values when it starts
    GRADE(string sl = "", string c = "", double q = 0.0, double h = 0.0, double l = 0.0, double p = 0.0, double m = 0.0, double fi = 0.0, double over = 0.0)
    {
        studentLogin = sl;
        course = c;
        quiz = q;
        hw = h;
        lab = l;
        project = p;
        midterm = m;
        final = fi;
        overall = over;
    }

    // setters
    void setStudentLogin(string sl)
    {
        studentLogin = sl;
    }
    void setCourse(string c)
    {
        course = c;
    }
    void setQuiz(double q)
    {
        quiz = q;
    }
    void setHw(double h)
    {
        hw = h;
    }
    void setLab(double l)
    {
        lab = l;
    }
    void setProject(double p)
    {
        project = p;
    }
    void setMid(double m)
    {
        midterm = m;
    }
    void setFin(double fi)
    {
        final = fi;
    }
    void setOverall(double over)
    {
        overall = over;
    }

    // getters
    string getStudentLogin()
    {
        return studentLogin;
    }
    string getCourse()
    {
        return course;
    }
    double getQuiz()
    {
        return quiz;
    }
    double getHw()
    {
        return hw;
    }
    double getLab()
    {
        return lab;
    }
    double getProject()
    {
        return project;
    }
    double getMid()
    {
        return midterm;
    }
    double getFin()
    {
        return final;
    }
    double getOverall()
    {
        return overall;
    }

    void calculateOverall() // here calculating final overall mark
    {
        overall = sumBall(quiz, hw, lab, project, midterm, final);
    }
    GRADE operator+(GRADE second) // it is overloading and  combines overall scores of two grade objects
    {
        GRADE temp; // temperory merory
        temp.overall = overall + second.overall;
        return temp; // return new object
    }
};

// in order to read users and upload vectors
vector<USERS> openUSERS(string usersLIST)
{
    vector<USERS> list;       // to save new users
    ifstream file(usersLIST); // to read file we havr used if stream

    // if file cannot be opened it will return empty
    if (!file.is_open())
    {
        return list;
    }
    else
    {
        string l, p, po, c;

        // read every variables until it reaches end of the list
        while (file >> l >> p >> po >> c)
        {
            USERS user(l, p, po, c); // create new user
            list.push_back(user);    // and we push it to vector list (vector<USERS>)
        }
        file.close();
        return list;
    }
}

// this function is to save users as a file
void saveUSERS(string usersLIST, vector<USERS> list)
{
    ofstream file(usersLIST); // we use ofstream to write infos to file

    // we write every users and theur infos by using this cycle
    for (int i = 0; i < list.size(); i++)
    {
        file << list[i].getLogin() << " " << list[i].getParol() << " "
             << list[i].getPosition() << " " << list[i].getCourse() << endl;
    }
    file.close(); // at the end we close the file
}

// in order to read every grade of the student from file
vector<GRADE> openGRADE(string gradeLIST)
{
    vector<GRADE> list; // it is list of grades
    ifstream file(gradeLIST);

    if (!file.is_open()) //  validation here also
    {
        return list;
    }
    else
    {
        string sl, c;
        double q, h, l, p, m, fi, over;
        while (file >> sl >> c >> q >> h >> l >> p >> m >> fi >> over)
        {
            GRADE g(sl, c, q, h, l, p, m, fi, over); // herer we create grade object
            list.push_back(g);
        }
        file.close();
        return list;
    }
}

// to save grades to file
void saveGRADE(string gradeLIST, vector<GRADE> list)
{
    ofstream file(gradeLIST);
    if (!file.is_open())
    {
        cout << "File is not open!" << endl;
    }
    else
    {
        // here we write every grade to the list
        for (int i = 0; i < list.size(); i++)
        {
            file << list[i].getStudentLogin() << " " << list[i].getCourse() << " "
                 << list[i].getQuiz() << " " << list[i].getHw() << " "
                 << list[i].getLab() << " " << list[i].getProject() << " "
                 << list[i].getMid() << " " << list[i].getFin() << " "
                 << list[i].getOverall() << endl;
        }
        file.close();
    }
}

// bool checking for that if user is alredy exist it return true else not
bool checkLogin(vector<USERS> list, string login)
{
    /// by using this cycle it check every login with new login
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].getLogin() == login)
        {
            return true; // if login is exist , it return 0
        }
    }
    return false;
}

double putGRADE(string gradeName) // to put grade to tasks
{
    double grade;
    while (true) // it is endless cycle
    {
        cout << "Enter " << gradeName << " (0-100): ";
        try // try block to catch invalid input
        {
            cin >> grade;

            if (grade < 0 || grade > 100)
            {
                throw "Wrong"; // throw error
            }
        }
        catch (...) // catch any error
        {
            cout << "Error" << endl;
        }

        // chech again
        if (grade >= 0 && grade <= 100)
        {
            return grade; // return grade and exit from fucntion
        }
        else
        {
            cout << "Enter grade from 0 to 100" << endl;
        }
    }
}

// to show every result from every course of the student
void coutGrade(GRADE g)
{
    cout << "Quiz: " << g.getQuiz() << endl;
    cout << "HW: " << g.getHw() << endl;
    cout << "Lab: " << g.getLab() << endl;
    cout << "Project: " << g.getProject() << endl;
    cout << "Midterm: " << g.getMid() << endl;
    cout << "Final: " << g.getFin() << endl;
    cout << "Overall: " << g.getOverall() << endl;
    cout << "GPA: " << calculateGPA(g.getOverall()) << endl; // here nested fucntion beaceus gerOverall is located insasde the calGPA

    // if sdutent overall is more than 60 he pass or not
    if (g.getOverall() >= 60)
    {
        cout << "Status: PASS" << endl;
    }
    else
    {
        cout << "Status: FAIL" << endl;
    }
}
void coutGrade()
{
    cout << "Overloaded function" << endl;
}
// If student does not have grades in this subject new grade range will open
int findGrade(vector<GRADE> &list, string studentLogin, string course)
{
    // find grade if thes tudent in this course
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].getStudentLogin() == studentLogin && list[i].getCourse() == course)
        {
            return i; // if it is found it return will index
        }
    }
    // if it is first time grade it create new object
    GRADE newGrade(studentLogin, course);
    list.push_back(newGrade);
    return list.size() - 1; // return index
}

// class of the Professor
class PROF : public USERS
{
private:
    USERS info;
    vector<USERS> *users; // change user by directly using pointer
    string userFile, gradeFile;

public:
    // constructor: binds the professor data and the address of the users vector
    PROF(USERS u, vector<USERS> &uList, string uf, string gf)
    {
        info = u;
        users = &uList; // here by using & we connect real location of the vecgtor to poointer
        userFile = uf;
        gradeFile = gf;
    }

    // bool checking checks if the entered login is in the list and is actually a student
    bool checkStudent(string login)
    {
        for (int i = 0; i < users->size(); i++) //-> is used to access members of object through pointer
        {
            // beacuse of pointer we can reference like this code
            if ((*users)[i].getLogin() == login && (*users)[i].getPosition() == "student")
            {
                return true;
            }
        }
        return false; // this student is not avibale
    }

    // put grade to student
    void gradeMenu(string studentLogin)
    {
        vector<GRADE> list = openGRADE(gradeFile);               // read grade file
        int i = findGrade(list, studentLogin, info.getCourse()); // find student course index
        int choice;

        while (true) // endless loop
        {
            cout << "GRADE ENTRY: " << studentLogin << " - " << info.getCourse() << endl;
            coutGrade(list[i]); // show current grade before enter new
                                /// menu of the grading choice that prfessor can choice one or more
            cout << "1. Quiz" << endl;
            cout << "2. Homework" << endl;
            cout << "3. Lab" << endl;
            cout << "4. Project" << endl;
            cout << "5. Midterm" << endl;
            cout << "6. Final" << endl;
            cout << "0. Back" << endl;
            cout << "Choice: ";
            cin >> choice;

            if (choice == 0)
            {
                break;
            }
            else if (choice == 1)
            {
                list[i].setQuiz(putGRADE("Quiz"));
            }
            else if (choice == 2)
            {
                list[i].setHw(putGRADE("Homework"));
            }
            else if (choice == 3)
            {
                list[i].setLab(putGRADE("Lab"));
            }
            else if (choice == 4)
            {
                list[i].setProject(putGRADE("Project"));
            }
            else if (choice == 5)
            {
                list[i].setMid(putGRADE("Midterm"));
            }
            else if (choice == 6)
            {
                list[i].setFin(putGRADE("Final"));
            }
            else
            {
                cout << "Wrong choice" << endl;
                continue;
            }

            list[i].calculateOverall(); // if grade is changed it recalculate it
            saveGRADE(gradeFile, list); // after that new grades are wrote to
            cout << "Saved. Overall: " << list[i].getOverall() << endl;
        }
    }

    // professor to view the results of all students studying only in the subject assigned to him/her
    void showResults()
    {
        vector<GRADE> list = openGRADE(gradeFile); // upload grades
        cout << "Results for: " << info.getCourse() << endl;
        bool found = false; // intilize found at first as false

        for (int i = 0; i < list.size(); i++)
        {
            // check the professor course with course name
            if (list[i].getCourse() == info.getCourse())
            {
                cout << "Student: " << list[i].getStudentLogin() << endl;
                coutGrade(list[i]); // show grade list of all the students
                found = true;
            }
        }

        if (!found)
        {
            cout << "No data yet" << endl; // if there is no grades it show this
        }
    }

    // it is for professor in order to add new student to his course
    void addStudent()
    {
        string login, parol;
        cout << "New student login: ";
        cin >> login;

        // here also check login is exist or not
        if (checkLogin(*users, login))
        {
            cout << "Login already taken" << endl;
            return;
        }

        cout << "Password: ";
        cin >> parol;

        // create new student
        USERS newStudent(login, parol, "student", "no course");
        users->push_back(newStudent); // add to overall list
        saveUSERS(userFile, *users);  // sate to file
        cout << "Student added" << endl;
    }

    // menu of prof to control
    void runMenu()
    {
        int choice;
        while (true)
        {
            cout << "PROFESSOR: " << info.getLogin() << " | COURSE: " << info.getCourse() << endl;
            cout << "1. Enter grades" << endl;
            cout << "2. View results" << endl;
            cout << "3. Add student" << endl;
            cout << "0. Exit" << endl;
            cout << "Choice: ";
            cin >> choice;

            if (choice == 0)
            {
                break;
            }
            else if (choice == 1)
            {
                cout << "Students:" << endl;
                // show all the student grade only this course that professor teachs
                for (int i = 0; i < users->size(); i++)
                {
                    if ((*users)[i].getPosition() == "student") // only takes students
                    {
                        cout << "- " << (*users)[i].getLogin() << endl;
                    }
                }
                cout << "Enter login: ";
                string login;
                cin >> login;

                if (!checkStudent(login))
                {
                    cout << "Student not found" << endl;
                    continue;
                }
                gradeMenu(login);
            }
            else if (choice == 2)
            {
                showResults();
            }
            else if (choice == 3)
            {
                addStudent();
            }
            else
            {
                cout << "Wrong choice" << endl;
            }
        }
    }
    void menu() override // menu calls runMenu to start main functionality
    {
        runMenu();
    }
};

// class in order to control admin
class ADMIN : public USERS
{
private:
    vector<USERS> *users; // pointer to users vector (to modify original data directly)
    string userFile;

public:
    // constructor: accepts the address of the vector used by Admin
    ADMIN(vector<USERS> &uList, string uf)
    {
        users = &uList;
        userFile = uf;
    }

    // menu of the admin
    void runMenu()
    {
        int choice;
        while (true)
        {
            cout << "ADMIN PANEL" << endl;
            cout << "1. Add professor" << endl;
            cout << "2. Add student" << endl;
            cout << "3. List users" << endl;
            cout << "4. Remove user" << endl;
            cout << "0. Exit" << endl;
            cout << "Choice: ";
            cin >> choice;

            if (choice == 0)
            {
                break;
            }
            else if (choice == 1 || choice == 2)
            {
                string login, parol;
                cout << "Login: ";
                cin >> login;

                if (checkLogin(*users, login)) // check the user by login
                {
                    cout << "Login already taken" << endl;
                    continue;
                }

                cout << "Password: ";
                cin >> parol;

                if (choice == 1)
                {
                    string course;
                    cout << "Course: ";
                    cin >> course;                                    // the course name of the professor
                    USERS newProf(login, parol, "professor", course); // create new user and push it to object
                    users->push_back(newProf);
                }
                else
                {
                    USERS newStudent(login, parol, "student", "NONE");
                    users->push_back(newStudent);
                }
                saveUSERS(userFile, *users); // save new user to the file
                cout << "Added" << endl;
            }
            else if (choice == 3) // show all the users as a list
            {
                cout << "Login Position Course" << endl;
                for (int i = 0; i < users->size(); i++)
                {
                    cout << (*users)[i].getLogin() << " " << (*users)[i].getPosition() << " " << (*users)[i].getCourse() << endl;
                }
            }
            else if (choice == 4) // in order to remove from the user lists
            {
                string login;
                cout << "Remove login: ";
                cin >> login;
                bool found = false;

                for (int i = 0; i < users->size(); i++) // hang out all the users
                {
                    if ((*users)[i].getLogin() == login) // if login is found
                    {
                        // if amdin try remove admin it will not be accapted
                        if ((*users)[i].getPosition() == "admin")
                        {
                            cout << "Cannot remove admin" << endl;
                        }
                        else
                        {
                            users->erase(users->begin() + i); // it stars from the beginning and find the i index and remove from memory directly
                            saveUSERS(userFile, *users);      /// resave file
                            cout << "Removed" << endl;
                        }
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "User not found" << endl;
                }
            }
            else
            {
                cout << "Wrong choice" << endl;
            }
        }
    }
    void menu() override // menu overrides base class function and calls runMenu so behavior stays the same
    {
        runMenu();
    }
};

// class for the student
class STUDENT : public USERS
{
private:
    USERS info; // student infos
    string gradeFile;

public:
    STUDENT(USERS u, string gf)
    {
        info = u;
        gradeFile = gf;
    }

    // Method to display the student's grades in all subjects
    void showGrades()
    {
        vector<GRADE> list = openGRADE(gradeFile);      // read all the grades
        cout << "STUDENT: " << info.getLogin() << endl; // show login
        cout << "Course Overall GPA Status" << endl;

        double totalGPA = 0;
        int courseCount = 0;

        for (int i = 0; i < list.size(); i++)
        {
            // If the login in the grade list is same as the login of the logged in student
            if (list[i].getStudentLogin() == info.getLogin())
            {
                double gpa = calculateGPA(list[i].getOverall()); // Fanning GPA ko'rsatkichi

                string status = "FAIL";         // at first we intilize it as failed
                if (list[i].getOverall() >= 60) // if stufent grade is more than 60 change fail to pass
                {
                    status = "PASS";
                }

                cout << list[i].getCourse() << " " << list[i].getOverall() << " " << gpa << " " << status << endl;
                totalGPA += gpa;
                courseCount++;
            }
        }

        // show average gpa
        if (courseCount > 0)
        {
            cout << "Total GPA: " << totalGPA / courseCount << endl;
        }
        else
        {
            cout << "No grades yet" << endl;
        }
    }
    void menu() override // override menu to directly show student grades
    {
        showGrades();
    }
};

#endif