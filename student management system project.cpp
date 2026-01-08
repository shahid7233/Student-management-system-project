#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class studentDetial
{
public:
    string UID;
    string StudentName;
    string StudentDept;
    string StudentAddress;
    double studentPhoneNo;

    studentDetial(string uid, string name, string dept, string address, double phoneNo)
    {
        UID = uid;
        StudentName = name;
        StudentDept = dept;
        StudentAddress = address;
        studentPhoneNo = phoneNo;
    }

    void DisplayDetails()
    {
        cout << "UID : " << UID << endl;
        cout << "Name : " << StudentName << endl;
        cout << "Dept : " << StudentDept << endl;
        cout << "Address : " << StudentAddress << endl;
        cout << "Phone no : " << studentPhoneNo << endl;
    }
};

vector<studentDetial> studentsList;

void processAddNewStudent();
void showDetial();
void mainInterFace();
void saveToFile();
void loadFromFile();
void removeStudentByUID();
void editdetils();

void saveToFile()
{
    ofstream file("students.txt");

    for (studentDetial &s : studentsList)
    {
        file << s.UID << " "
             << s.StudentName << " "
             << s.StudentDept << " "
             << s.StudentAddress << " "
             << s.studentPhoneNo << endl;
    }

    file.close();
}

void loadFromFile()
{
    ifstream file("students.txt");

    if (!file.is_open())
        return;

    string uid, name, dept, address;
    int phone;

    while (file >> uid >> name >> dept >> address >> phone)
    {
        studentsList.push_back(
            studentDetial(uid, name, dept, address, phone));
    }

    file.close();
}

void processAddNewStudent()
{
    string UID;
    string StudentName;
    string StudentDept;
    string StudentAddress;
    int studentPhoneNo;
    getline(cin, UID);
    cout << "Enter Student Unique Identification : " << endl;
    getline(cin, UID);
    cout << "Enter Student Name : " << endl;
    getline(cin, StudentName);
    cout << "Enter Student Dept : " << endl;
    getline(cin, StudentDept);
    cout << "Enter Student Address : " << endl;
    getline(cin, StudentAddress);
    cout << "Enter Student Phone no : " << endl;
    cin >> studentPhoneNo;
    studentDetial newStudent(UID, StudentName, StudentDept, StudentAddress, studentPhoneNo);
    cout << "Detail Add Successfuly" << endl;
    studentsList.push_back(newStudent);
    saveToFile();
}

void showDetial()
{
    string uid;
    cout << "Enter Student Unique Identification : " << endl;
    cin >> uid;

    bool found = false;
    for (studentDetial &superman : studentsList)
    {
        if (superman.UID == uid)
        {
            superman.DisplayDetails();
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Student not Found" << endl;
    }
}

void editdetils()
{
    string uid;
    cout << "Enter Student Unique Identification : " << endl;
    cin >> uid;

    bool found = false;
    for (studentDetial &superman : studentsList)
    {
        int num;
        cout << "1.Edit Name" << endl;
        cout << "2.Edit Department" << endl;
        cout << "3.Edit Address" << endl;
        cout << "4.Edit Phone NO" << endl;
        cout << "Enter 1,2,3,or 4 as Per Requairment" << endl;
        cin >> num;

        if (superman.UID == uid)
        {
            if (num == 1)
            {
                cout << "Enter New Student Name : " << endl;
                cin >> superman.StudentName;
                found = true;
                break;
            }
            else if (num == 2)
            {
                cout << "Enter New Student Dept : " << endl;
                cin >> superman.StudentDept;
                found = true;
                break;
            }
            else if (num == 3)
            {
                cout << "Enter New Student Addresss : " << endl;
                cin >> superman.StudentAddress;
                found = true;
                break;
            }
            else if (num == 4)
            {
                cout << "Enter New Student Phone No : " << endl;
                cin >> superman.studentPhoneNo;
                found = true;
                break;
            }
            else
            {
                cout << "Warning : Enter Valid Number" << endl;
                editdetils();
                break;
            }
        }
    }

    if (!found)
    {
        cout << "Student not Found" << endl;
    }
}

void removeStudentByUID()
{
    string uid;
    cout << "Enter Student Unique Identification: ";
    cin >> uid;

    for (auto it = studentsList.begin(); it != studentsList.end(); ++it)
    {
        if (it->UID == uid)
        {
            studentsList.erase(it);
            cout << "Student Data Removed Successfully" << endl;
            return;
        }
    }

    cout << "Student not Found" << endl;
}

void mainInterFace()
{
    int enterNUM;
    cout << "1.Add New Student Detials" << endl;
    cout << "2.Update Student Detials" << endl;
    cout << "3.Find Student Detials" << endl;
    cout << "4.Remove Student Detials" << endl;
    cout << "Enter 1,2,3,or 4 as Per Requairment" << endl;
    cin >> enterNUM;

    if (enterNUM == 1)
    {
        processAddNewStudent();
    }
    else if (enterNUM == 2)
    {
        editdetils();
    }
    else if (enterNUM == 3)
    {
        showDetial();
    }
    else if (enterNUM == 4)
    {
        removeStudentByUID();
    }
    else
    {
        cout << "Warning : Enter Valid Number" << endl;
        mainInterFace();
    }
}

int main()
{
    loadFromFile();
    mainInterFace();
    saveToFile();
    return 0;
}
