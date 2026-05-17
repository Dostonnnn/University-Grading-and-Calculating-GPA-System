#ifndef header_h
#define header_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

double sumBall(double quiz, double hw, double lab, double project, double midterm, double final) // add every grade to sum;
{
    double sum = 0;
    sum += (quiz * 20 + hw * 5 + lab * 10 + project * 15 + midterm * 25 + final * 25) / 100;
    return sum;
}

double calculateGPA(double ball)
{
    if (ball >= 95)
        return 4.5;
    else if (ball >= 90)
        return 4.0;
    else if (ball >= 85)
        return 3.5;
    else if (ball >= 80)
        return 3.0;
    else if (ball >= 75)
        return 2.5;
    else if (ball >= 70)
        return 2.0;
    else if (ball >= 60)
        return 1.0;
    else
        return 0.0;
}

class USERS
{
private: // use privete in prder to save information about user;
    string login, parol, position, course;

public:
    // create a constructure
    USERS(string log = "", string par = "", string pos = "", string cour = "")
    {
        login = log;
        parol = par;
        position = pos;
        course = cour;
    }
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
};

class GRADE
{
private:
    string studentLogin, course;
    double quiz, hw, lab, project, midterm, final, overall;

public:
    // Konstruktor (Yangi baho obyekti yaratilayotganda boshlang'ich qiymat berish uchun)
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

    // SETTERLAR (Qiymatlarni o'zgartirish uchun)
    void setStudentLogin(string sl)
    {
        studentLogin = sl;
    }
    void setFan(string c)
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

    string getStudentLogin()
    {
        return studentLogin;
    }
    string getFan()
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

    // calculate overall
    void calculateOverall()
    {
        overall = sumBall(quiz, hw, lab, project, midterm, final);
    }
};

vector<USERS> openUSERS(string usersLIST)
{
    vector<USERS> list;
    ifstream file(usersLIST);
    if (!file.is_open())
    {
        return list;
    }
    else
    {
        string l, p, po, c;
        while (file >> l >> p >> po >> c)
        {
            USERS user(l, p, po, c);
            list.push_back(user);
        }
        file.close();
        return list;
    }
}

void saveUSERS(string usersLIST, vector<USERS> list)
{
    ofstream file(usersLIST);
    for (int i = 0; i < (int)list.size(); i++)
    {
        file << list[i].getLogin() << " "
             << list[i].getParol() << " "
             << list[i].getPosition() << " "
             << list[i].getCourse() << " " << endl;
    }
    file.close();
}

vector<GRADE> openGRADE(string gradeLIST)
{
    vector<GRADE> list;
    ifstream file(gradeLIST);
    if (!file.is_open())
    {
        return list;
    }
    else
    {
        string sl, c;
        double q, h, l, p, m, fi, over;
        while (file >> sl >> c >> q >> h >> l >> p >> m >> fi >> over)
        {
            GRADE g(sl, c, q, h, l, p, m, fi, over);
            list.push_back(g);
        }
    }
    file.close();
    return list;
}

void saveGRADE(string gradeLIST, vector<GRADE> list)
{
    ofstream file(gradeLIST);
    if (!file.is_open())
    {
        cout << "File is not open!" << endl;
    }
    else
    {
        for (int i = 0; i < (int)list.size(); i++)
        {
            file << list[i].getStudentLogin() << " "
                 << list[i].getFan() << " "
                 << list[i].getQuiz() << " "
                 << list[i].getHw() << " "
                 << list[i].getLab() << " "
                 << list[i].getProject() << " "
                 << list[i].getMid() << " "
                 << list[i].getFin() << " "
                 << list[i].getOverall() << " " << endl;
        }

        file.close();
    }
}

bool checkLogin(vector<USERS> list, string login)
{
    for (int i = 0; i < (int)list.size(); i++)
    {
        if (list[i].getLogin() == login)
        {

            return true;
        }
    }
    return false;
}

double putGRADE(string gradeNAME)
{
    double grade;
    while (true)
    {
        cout << "Enter " << gradeNAME << " (0-100): ";
        cin >> grade;
        if (grade >= 0 && grade <= 100)
        {
            return grade;
        }
        else
        {
            cout << "Enter grade from 0 to 100" << endl;
        }
    }
}

void coutGrade(GRADE g)
{
    cout << "Quiz: " << g.getQuiz() << endl;
    cout << "Homework: " << g.getHw() << endl;
    cout << "Lab: " << g.getLab() << endl;
    cout << "Project: " << g.getProject() << endl;
    cout << "Midterm: " << g.getMid() << endl;
    cout << "Final: " << g.getFin() << endl;
    cout << "Overall: " << g.getOverall() << endl;
    cout << "GPA: " << calculateGPA(g.getOverall()) << endl;
    if (g.getOverall() >= 60)
    {
        cout << "Status: PASS" << endl;
    }
    else
    {
        cout << "Status: FAIL" << endl;
    }
}

class PROF
{
private:
    USERS info;
    vector<USERS> *users;
    string userFile;
    string gradeFile;
};

#endif