#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

class Course;
class PLO;
class CLO;
class Question;
class OBE;
class Evaluation;

class CLO
{
private:
    int Cid;
    int id;
    char name[50];
public:
    //default constructor
    CLO(int Cid = -1, int id = -1, string name = "") {
        this->Cid = Cid;
        this->id = id;
        strcpy(this->name, name.c_str());
    }

    //getters
    int getCid() {
        return Cid;
    }
    int getId() {
        return id;
    }
    char* getName() {
        return name;
    }

    //setters
    void setCid(int Cid) {
        this->Cid = Cid;
    }
    void setId(int id) {
        this->id = id;
    }
    void setName(string name) {
        strcpy(this->name, name.c_str());
    }

    //print CLO
    void print() {

        std::cout << std::setw(6) << "CLO-" << std::setw(4) << id << " | "
            << std::setw(30) << name << std::endl;
    }

    //operator == overloaded
    bool operator==(const CLO& c) {
        if (Cid == c.Cid && id == c.id && (strcmp(name, c.name) == 0)) {
            return 1;
        }
        else
            return 0;
    }
};

class PLO {
private:
    int Pid;
    int id;
    std::string name;
public:
    // Default constructor
    PLO(int Pid = -1, int id = -1, std::string name = "") {
        this->Pid = Pid;
        this->id = id;
        this->name = name;
    }

    // Getters
    int getPid() {
        return Pid;
    }
    int getId() {
        return id;
    }
    std::string getName() {
        return name;
    }

    // Setters
    void setPid(int Pid) {
        this->Pid = Pid;
    }
    void setId(int id) {
        this->id = id;
    }
    void setName(std::string name) {
        this->name = name;
    }

    // Print PLO
    void print() {
        std::cout << std::setw(6) << "PLO-" << std::setw(4) << id << " | "
            << std::setw(30) << name << std::endl;
    }

    // Operator == overloaded
    bool operator==(const PLO& p) {
        return (Pid == p.Pid && id == p.id && name == p.name);
    }
};

class Question
{
private:
    int CourseID;
    int QId;
    int CLO_Id;
    char description[100];
    vector<Question> questions;

public:
    //default constructor
    Question(int CourseID = -1, int QId = -1, int CLO_Id = -1, string description = "")
    {
        this->CourseID = CourseID;
        this->QId = QId;
        this->CLO_Id = CLO_Id;
        strcpy(this->description, description.c_str());
    }

    //getters
    int getQId() {
        return QId;
    }
    int getCLO_Id() {
        return CLO_Id;
    }
    int getCourseID() {
        return CourseID;
    }

    //setters
    void setQId(int id) {
        QId = id;
    }
    void setCLO_Id(int id) {
        CLO_Id = id;
    }
    void setCourseID(int id) {
        CourseID = id;
    }
    void setDes(string des) {
        strcpy(this->description, des.c_str());
    }

    //print Question
    void print() {
        cout << "Question id: " << QId << "\n";
        cout << "CLO id: " << CLO_Id << "\n";
        cout << "Description: " << description << "\n";
    }

    int addQuestion(int CourseID, int Q_No, int CLO_Id, string des)
    {
        Question obj(CourseID, Q_No, CLO_Id, des);

        // Adding question to the vector
        questions.push_back(obj);

        // Open the text file in append mode
        ofstream f("questions.txt", ios::app);
        if (!f) {
            cerr << "Error opening file." << endl;
            return 1;
        }
        else {
            // Write the data in a formatted way
            f << CourseID << " " << Q_No << " " << CLO_Id << " " << des << endl;
            f.close();
            return 0;
        }
    }


};

class Evaluation
{
private:
    int Cid;
    int id;
    string type;
    vector<int> testedCLOs;
    vector<Question> questions;

public:
    Evaluation(int Cid = -1, int id = -1, string type = "")
        : Cid(Cid), id(id), type(type) {}

    void setId(int id) {
        this->id = id;
    }
    void setCid(int Cid) {
        this->Cid = Cid;
    }

    int getCid() const {
        return Cid;
    }

    int getId() const {
        return id;
    }


    string getType() const {
        return type;
    }


    void addTestedCLO(int CLO_id) {
        testedCLOs.push_back(CLO_id);
    }


    bool isCLOtested(int CLO_id) const {
        for (int tested_CLO : testedCLOs) {
            if (tested_CLO == CLO_id) {
                return true;
            }
        }
        return false;
    }


    bool hasMinimumTwoTestsPerCLO() const {
        std::vector<int> uniqueTestedCLOs;
        for (int tested_CLO : testedCLOs) {
            bool alreadyTested = false;
            for (int unique_CLO : uniqueTestedCLOs) {
                if (unique_CLO == tested_CLO) {
                    alreadyTested = true;
                    break;
                }
            }
            if (!alreadyTested) {
                uniqueTestedCLOs.push_back(tested_CLO);
            }
        }
        for (int unique_CLO : uniqueTestedCLOs) {
            int count = 0;
            for (int tested_CLO : testedCLOs) {
                if (tested_CLO == unique_CLO) {
                    count++;
                }
            }
            if (count < 2) {
                return false;
            }
        }
        return true;
    }

    int countQuestions(int CLO_Id) {
        int count = 0;
        int size = questions.size();
        for (int i = 0; i < size; i++)
        {
            if (questions[i].getCLO_Id() == CLO_Id) {
                count++;
            }
        }
        return count;
    }
    bool checkCLOHasTested(int CLO_Id) {
        if (countQuestions(CLO_Id) >= 2) {
            return true;
        }
        else
            return false;
    }

    void print() {
        cout << "Evaluation id: " << id << "\n";
    }
    void outputAllQuestions() {
        for (int i = 0; i < questions.size(); i++) {
            questions[i].print();
        }
    }

    int addQuestion(int CourseID, int Q_No, int CLO_Id, string des)
    {
        Question obj(CourseID, Q_No, CLO_Id, des);

        // Adding question to the vector
        questions.push_back(obj);

        // Open the text file in append mode
        ofstream f("questions.txt", ios::app);
        if (!f) {
            cerr << "Error opening file." << endl;
            return 1;
        }
        else {
            // Write the data in a formatted way
            f << CourseID << " " << Q_No << " " << CLO_Id << " " << des << endl;
            f.close();
            return 0;
        }
    }


    void printAllQuestions() {
        // Open the text file
        ifstream file("questions.txt");
        if (!file) {
            cerr << "Error opening file." << endl;
            return;
        }
        cout << "\n";
        // Read each line from the file and print it in a spreadsheet-like format
        string line;
        cout << setw(10) << "CourseID" << setw(10) << "Q_No" << setw(10) << "CLO_Id" << setw(30) << "Description" << endl;
        while (getline(file, line)) {
            int CourseID, Q_No, CLO_Id;
            string des;
            stringstream ss(line);
            if (ss >> CourseID >> Q_No >> CLO_Id) {
                getline(ss, des);
                cout << "|" << setw(10) << CourseID << "|" << setw(10) << Q_No << "|" << setw(10) << CLO_Id << "|" << setw(30) << des << "|" << endl;
            }
        }

        // Close the file
        file.close();
    }



    int RemoveQuestion(int CourseID, int Q_No, int CLO_Id)
    {
        bool found = false;
        int index = 0;

        //finding the index of the question to be deleted
        int size = questions.size();
        while (index < size) {
            if (questions[index].getCourseID() == CourseID && questions[index].getQId() == Q_No && questions[index].getCLO_Id() == CLO_Id) {
                found = true;
                break;
            }
            else
                index++;
        }

        //if question present
        if (found) {
            //deleting question from the vector

            vector<Question>::iterator it;
            it = index + questions.begin();
            questions.erase(it);

            //deleting the question from the binary file

            ifstream fquestion("questions.bin", ios::binary);
            ofstream dummy("dummy.bin", ios::binary);

            Question obj;

            while (fquestion.read((char*)&obj, sizeof(obj)))
            {
                if (obj.getCLO_Id() != CLO_Id || obj.getQId() == Q_No || obj.getCourseID() == CourseID)
                {
                    dummy.write((char*)&obj, sizeof(obj));
                }
            }
            fquestion.close();
            dummy.close();

            remove("questions.bin");
            if (rename("dummy.bin", "questions.bin"))
                return 1;
            else
                return 0;
        }
    }
    int UpdateQuestion(int CourseID, int Q_No, int CLO_Id, int newQ_No, int newCLO_Id, string newdes)
    {
        int index = 0;
        bool found = false;

        //finding the index of the question to be updated
        int size = questions.size();
        while (index < size) {
            if (questions[index].getCourseID() == CourseID && questions[index].getQId() == Q_No && questions[index].getCLO_Id() == CLO_Id) {
                found = true;
                break;
            }
            else
                index++;
        }

        //if question present
        if (found)
        {
            //updating question in vector
            questions[index].setQId(newQ_No);
            questions[index].setCLO_Id(newCLO_Id);
            questions[index].setDes(newdes);

            //updating question in Binary file

            fstream questionf2("questions.bin", ios::in | ios::out | ios::binary);
            Question obj;

            while (questionf2.read((char*)&obj, sizeof(obj)))
            {
                if (obj.getCourseID() == CourseID && obj.getQId() == Q_No && obj.getCLO_Id() == CLO_Id)
                {
                    obj.setQId(newQ_No);
                    obj.setCLO_Id(newCLO_Id);
                    obj.setDes(newdes);

                    std::streamoff fileptr = questionf2.tellg();
                    std::streamoff objsize = sizeof(obj);
                    questionf2.seekp(fileptr - objsize, ios::beg);

                    questionf2.write((char*)&obj, sizeof(obj));
                    questionf2.close();
                    return 1;
                }
            }
            questionf2.close();
            return 0;
        }
    }

    void deleteAllQuestions() {
        questions.clear();
    }

    bool operator==(const Evaluation& c) {
        if (Cid == c.Cid && id == c.id) {
            return 1;
        }
        else
            return 0;
    }
};


class Course
{
private:

    vector<CLO> CLOs;
    vector<Evaluation> evals;
public:
    int id;
    string name;
    Course(int id = -1, string name = "") {
        this->id = id;
        this->name = name;
    }

    int getId() const { return id; }
    const string& getName() const { return name; }

    void setId(int id) {
        this->id = id;
    }
    void setName(string name) {
        this->name = name;
    }

    int addCLO(int Cid, int id, string name) {
        CLO obj(Cid, id, name);

        // Adding CLO to the vector
        CLOs.push_back(obj);

        // Adding CLO to the text file
        ofstream f("CLOs.txt", ios::app); // Open file in append mode
        if (!f) {
            // Failed to open file
            return 1;
        }
        else {
            // Write CLO data in a specific format
            f << Cid << " " << id << " " << name << "\n";
            f.close();
            return 0;
        }
    }

    int removeCLO(int Cid, int id) {
        bool found = false;
        int index = 0;

        //finding the index of the CLO to be deleted
        int size = CLOs.size();
        while (index < size) {
            if (CLOs[index].getId() == id && CLOs[index].getCid() == Cid) {
                found = true;
                break;
            }
            else
                index++;
        }

        //if CLO present

        if (found) {
            //deleting CLO from the vector

            vector<CLO>::iterator it;
            it = index + CLOs.begin();
            CLOs.erase(it);

            //deleting the CLO from the binary file

            ifstream f("CLOs.bin", ios::binary);
            ofstream temp("temp.bin", ios::binary);

            CLO obj;

            while (f.read((char*)&obj, sizeof(obj)))
            {
                if (obj.getId() != id || obj.getCid() != Cid)
                {
                    temp.write((char*)&obj, sizeof(obj));
                }
            }
            f.close();
            temp.close();

            remove("CLOs.bin");
            if (rename("temp.bin", "CLOs.bin"))
                return 1;
            else
                return 0;
        }
    }
    int updateCLO(int Cid, int id, string name, int newId, string newName)
    {
        int index = 0;
        bool found = false;

        //finding the index of the CLO to be updated
        int size = CLOs.size();
        while (index < size) {
            if (CLOs[index].getId() == id && CLOs[index].getCid() == Cid) {
                found = true;
                break;
            }
            else
                index++;
        }

        //if CLO present

        if (found)
        {
            //updating CLO in vector

            CLOs[index].setId(newId);
            CLOs[index].setName(newName);

            //updating CLO in Binary file

            fstream f("CLOs.bin", ios::in | ios::out | ios::binary);
            CLO obj;

            while (f.read((char*)&obj, sizeof(obj)))
            {
                if (id == obj.getId() && Cid == obj.getCid())
                {
                    obj.setId(newId);
                    obj.setName(newName);

                    std::streamoff fileptr = f.tellg();
                    std::streamoff objsize = sizeof(obj);
                    f.seekp(fileptr - objsize, ios::beg);

                    f.write((char*)&obj, sizeof(obj));
                    f.close();
                    return 1;
                }
            }
            f.close();
            return 0;
        }
    }

    int addEval(int Cid, int id, string type) {
        Evaluation obj(Cid, id);

        // Adding Evaluation to the vector
        evals.push_back(obj);

        // Adding Evaluation to the text file
        ofstream f("evaluations.txt", ios::app);
        if (!f)
            return 1;
        else {
            f << Cid << " " << id << " " << type << endl;
            f.close();
            return 0;
        }
    }

    int removeEval(int Cid, int id) {
        bool found = false;
        int index = 0;

        //finding the index of the evaluation to be deleted
        int size = evals.size();
        while (index < size) {
            if (evals[index].getId() == id && evals[index].getCid() == Cid) {
                found = true;
                break;
            }
            else
                index++;
        }

        //if evaluation present
        if (found)
        {
            evals[index].deleteAllQuestions();

            //deleting evaluation from the vector
            vector<Evaluation>::iterator it;
            it = index + evals.begin();
            evals.erase(it);

            //deleting the evalutaion from the binary file
            ifstream f("evaluations.bin", ios::binary);
            ofstream temp("temp2.bin", ios::binary);

            Evaluation obj;

            while (f.read((char*)&obj, sizeof(obj)))
            {
                if (obj.getId() != id || obj.getCid() != Cid)
                {
                    temp.write((char*)&obj, sizeof(obj));
                }
            }
            f.close();
            temp.close();

            remove("evaluations.bin");
            if (rename("temp2.bin", "evaluations.bin"))
                return 1;
            else
                return 0;
        }
    }
    int updateEval(int Cid, int id, int newId)
    {
        int index = 0;
        bool found = false;

        //finding the index of the evaluation to be updated
        int size = evals.size();
        while (index < size) {
            if (evals[index].getId() == id && evals[index].getCid() == Cid) {
                found = true;
                break;
            }
            else
                index++;
        }

        //if evaluation present
        if (found)
        {
            //updating evaluation in vector
            evals[index].setId(newId);

            //updating evaluation in Binary file
            fstream f("evaluations.bin", ios::in | ios::out | ios::binary);
            Evaluation obj;

            while (f.read((char*)&obj, sizeof(obj)))
            {
                if (id == obj.getId() && Cid == obj.getCid())
                {
                    obj.setId(newId);

                    std::streamoff fileptr = f.tellg();
                    std::streamoff objsize = sizeof(obj);
                    f.seekp(fileptr - objsize, ios::beg);

                    f.write((char*)&obj, sizeof(obj));
                    f.close();
                    return 1;
                }
            }
            f.close();
            return 0;
        }
    }


    void printAllCourses() {
        // Open the file
        ifstream file("courses.txt");
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            return;
        }

        cout << "\n";
        // Read and print each line in a spreadsheet-like format
        string line;
        cout << setw(10) << "CourseID" << setw(20) << "Name" << endl;
        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string name;
            if (ss >> id >> name) {
                cout << "|" << setw(10) << id << "|" << setw(20) << name << "|" << endl;
            }
        }

        // Close the file
        file.close();


    }


    void printallCLOs() {
        // Open the file
        ifstream file("CLOs.txt");
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            return;
        }

        cout << "\n";
        // Read and print each line in a spreadsheet-like format
        string line;
        cout << setw(10) << "CourseID" << setw(10) << "CLO_Id" << setw(30) << "Name" << endl;
        while (getline(file, line)) {
            stringstream ss(line);
            int Cid, id;
            string name;
            if (ss >> Cid >> id >> name) {
                cout << "| " << setw(10) << Cid << " |" << setw(10) << id << " |" << setw(20) << name << " |" << endl;
            }
        }

        // Close the file
        file.close();
    }

    void printallEvals() {
        // Open the file
        ifstream file("evaluations.txt");
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            return;
        }

        cout << endl;
        // Read and print each line in a spreadsheet-like format
        string line;
        cout << "| " << setw(10) << "CourseID" << " | " << setw(10) << "EvalID" << " | " << setw(20) << "Type" << " |" << endl;
        while (getline(file, line)) {
            stringstream ss(line);
            int Cid, id;
            string type;
            if (ss >> Cid >> id >> type) {
                cout << "| " << setw(10) << Cid << " | " << setw(10) << id << " | " << setw(20) << type << " |" << endl;
            }
        }

        // Close the file
        file.close();
    }



    bool doesEvaExist(int evaluationIdToCheck) {
        // Open the file
        ifstream file("evaluations.txt");
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            return false; // Return false if file cannot be opened
        }

        // Read each line from the file
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int courseId, evaluationId;
            if (ss >> courseId >> evaluationId) {
                // If the evaluation ID matches, return true
                if (evaluationId == evaluationIdToCheck) {
                    file.close();
                    return true;
                }
            }
        }

        // Close the file
        file.close();

        // If evaluation ID is not found, return false
        return false;
    }


    bool CourseIDExists(int CourseIDToCheck) {
        // Open the file
        ifstream file("courses.txt");
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            return false; // Return false if file cannot be opened
        }

        // Read each line from the file
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int CourseID;
            if (ss >> CourseID) {
                // If the course ID matches, return true
                if (CourseID == CourseIDToCheck) {
                    file.close();
                    return true;
                }
            }
        }

        // Close the file
        file.close();

        // If course ID is not found, return false
        return false;
    }


    void addQuestionToEvaluation(int index, int Qid, int CLO_id, string des)
    {
        evals[index].addQuestion(evals[index].getId(), Qid, CLO_id, des);
    }
    void removeQuestionFromEvaluation(int index, int Qid, int CLO_id) {
        evals[index].RemoveQuestion(evals[index].getId(), Qid, CLO_id);
    }
    void updateQuestionFromEvaluation(int index, int Qid, int CLO_id, int newQid, int newCLO_id, string newdes) {
        evals[index].UpdateQuestion(evals[index].getId(), Qid, CLO_id, newQid, newCLO_id, newdes);
    }

    void printQuestionsInEval() {
        for (int i = 0; i < evals.size(); i++)
        {
            cout << "Evaluation id: " << evals[i].getId();
            cout << "\n";
            evals[i].printAllQuestions();
        }
    }
    void removeAllCLOs() {
        CLOs.clear();
    }
    void removeAllEvals() {
        for (int i = 0; i < evals.size(); i++) {
            evals[i].deleteAllQuestions();
        }
        evals.clear();
    }

    int checkAllCLOsHasTested()
    {
        bool tested = false;

        for (int i = 0; i < CLOs.size(); i++)
        {
            for (int j = 0; j < evals.size(); i++) {
                if (evals[j].checkCLOHasTested(CLOs[i].getId()) == true) {
                    tested = true;
                    break;
                }
            }
            if (!tested)
                return 0;
        }
        return 1;
    }

    /*/bool operator==(const Course& c) {
        if (id == c.id && (strcmp(name , c.name)==0)) {
            return 1;
        }
        else
            return 0;
    }*/
};

class Interface {
public:
    vector<Course> courses;
    vector<Course>::iterator itr2;

    void populateCourseVector() {
        ifstream file("courses.txt");
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Course course;
            if (ss >> course.id >> course.name) {
                courses.push_back(course);
            }
            else {
                cerr << "Error parsing line: " << line << endl;
            }
        }

        file.close();
    }

    int addCourse(int id, string name) {
        // Open the file in append mode
        ofstream file("courses.txt", ios::app);
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            return 1; // Return 1 to indicate failure
        }

        // Write the course data to the file
        file << id << " " << name << endl;

        // Close the file
        file.close();

        return 0; // Return 0 to indicate success
    }

    void updateCourse(int id, string name, int newId, string newName)
    {
        int index = 0;
        bool found = false;

        //finding the index of the course to be updated
        int size = courses.size();
        while (index < size) {
            if (courses[index].getId() == id && courses[index].getName() == name) {
                found = true;
                break;
            }
            else
                index++;
        }

        //if CLO present
        if (found)
        {
            //updating course in vector
            courses[index].setId(newId);
            courses[index].setName(newName);
        }
    }
    void removeCourse(int id, string name)
    {
        bool found = false;
        int index = 0;

        //finding the index of the course to be deleted
        int size = courses.size();
        while (index < size)
        {
            if (courses[index].getId() == id && courses[index].getName() == name) {
                found = true;
                break;
            }
            else
                index++;
        }

        //go to CLOs remove all CLOs with this Cid
        //go to evals remove all evals with this Cid
        //go to questions remove all questions in the respective evals
        courses[index].removeAllCLOs();
        courses[index].removeAllEvals();
        //if CLO present
        if (found)
        {
            //deleting CLO from the vector
            vector<Course>::iterator it;
            it = index + courses.begin();
            courses.erase(it);
        }
    }
};

int menu() {
    int option = 0, optionToAdd = -1, optionToRemove = -1, optionToUpdate = -1, optionToPrint = -1;

    Interface I;
    Course C;
    Evaluation E;
    Question Q;
    //I.populateCourseVector();

    cout << "Welcome to the OBE System\n";
    cout << "-------------------------\n";

    while (option != -1) {

        cout << "\nDo you want to:\n";
        cout << "Option 1: Add\n";
        cout << "Option 2: Remove\n";
        cout << "Option 3: Update\n";
        cout << "Option 4: Print\n";
        cout << "Option 5: Check\n";
        cout << "Option -1: Exit\n";
        cout << "Option: ";
        cin >> option;

        while (!(option == -1 || option == 1 || option == 2 || option == 3 || option == 4 || option == 5)) {
            cout << "Invalid option selected. Enter again : ";
            cin >> option;
        }


        if (option == 1) {
            cout << "\nDo you want to:\n";
            cout << "Option 1: Add a Course\n";
            cout << "Option 2: Add a CLO\n";
            cout << "Option 3: Add an Evaluation\n";
            cout << "Option 4: Add a Question\n";
            cout << "Option: ";
            cin >> optionToAdd;

            if (optionToAdd == 1)
            {
                //add a course
                int id;
                string name;

                cout << "Enter Course id: ";
                cin >> id;
                cout << "Enter Course name: ";
                cin >> name;
                cin.ignore();

                I.addCourse(id, name);
                cout << "Added successfully!\n";
            }
            else if (optionToAdd == 2)
            {
                //add a CLO respective to a course
                int id, Cid;
                string name;

                int index = 0;
                bool found = false;

                cout << "\nEnter corresponding Course ID: ";
                cin >> Cid;

                //finding the index of the Course to be searched

                found = C.CourseIDExists(Cid);

                if (found) {
                    cout << "Enter CLO id: ";
                    cin >> id;
                    cout << "Enter CLO name: ";
                    cin >> name;

                    C.addCLO(Cid, id, name);
                    cout << "Added successfully!\n";
                }
                else
                    cout << "Incorrect Course id!\n";

            }
            else if (optionToAdd == 3) {
                //add an evaluation respective to a course
                int id, Cid;
                string type;

                int index = 0;
                bool found = false;

                cout << "\nEnter corresponding Course ID: ";
                cin >> Cid;

                //finding the index of the Course to be searched

                found = C.CourseIDExists(Cid);

                if (found) {
                    cout << "Enter Evaluation id: ";
                    cin >> id;
                    cout << "Enter type of evaluation: ";
                    cin >> id;
                    C.addEval(Cid, id, type);
                    cout << "Added successfully!\n";
                }
                else
                    cout << "Incorrect Course Id.\n";
            }
            else if (optionToAdd == 4)
            {
                //add a question respective to a course
                int Qid, CLO_id, EvaID, Cid;
                string des;

                int i = 0;
                bool found = false;

                cout << "\nEnter corresponding Course ID: ";
                cin >> Cid;

                //finding the index of the Course to be searched
                found = C.CourseIDExists(Cid);

                if (found)
                {
                    cout << "Enter corresponding Evaluation ID: ";
                    cin >> EvaID;

                    //finding the index of the Evaluation to be searched
                    int index = C.doesEvaExist(EvaID);

                    if (index == 1)
                    {
                        cout << "Enter Question id: ";
                        cin >> Qid;
                        cout << "Enter CLO id: ";
                        cin >> CLO_id;
                        cout << "Enter Question description: ";
                        cin >> des;
                        Q.addQuestion(index, Qid, CLO_id, des);
                        cout << "Added successfully!\n";
                    }
                    else
                        cout << "Incorrect Evaluation id!\n";
                }
                else
                    cout << "Incorrect Course id!\n";

            }
            else {
                return -1;
            }
        }
        else if (option == 2) {
            cout << "\nDo you want to:\n";
            cout << "Option 1: Remove a Course\n";
            cout << "Option 2: Remove a CLO\n";
            cout << "Option 3: Remove an Evaluation\n";
            cout << "Option 4: Remove a Question\n";
            cout << "Option: ";
            cin >> optionToRemove;

            if (optionToRemove == 1) {
                //remove a course
                int id;
                string name;

                cout << "Enter Course id: ";
                cin >> id;
                cout << "Enter Course name: ";
                cin >> name;
                I.removeCourse(id, name);
                cout << "Removed successfully\n";
            }
            else if (optionToRemove == 2) {
                //remove a CLO respective to a course
                int id, Cid;
                int index = 0;
                bool found = false;

                cout << "\nEnter corresponding Course ID: ";
                cin >> Cid;

                //finding the index of the Course to be searched
                int size = I.courses.size();
                while (index < size) {
                    if (I.courses[index].getId() == Cid) {
                        found = true;
                        break;
                    }
                    else
                        index++;
                }
                if (found) {
                    cout << "Enter CLO id: ";
                    cin >> id;
                    I.courses[index].removeCLO(Cid, id);
                    cout << "Removed successfully!\n";
                }
                else
                    cout << "Incorrect Course Id.\n";

            }
            else if (optionToRemove == 3) {
                //remove a evaluation respective to a course
                int id, Cid;
                int index = 0;
                bool found = false;

                cout << "\nEnter corresponding Course ID: ";
                cin >> Cid;

                //finding the index of the Course to be searched
                int size = I.courses.size();
                while (index < size) {
                    if (I.courses[index].getId() == Cid) {
                        found = true;
                        break;
                    }
                    else
                        index++;
                }
                if (found) {
                    cout << "Enter Evaluation id: ";
                    cin >> id;
                    I.courses[index].removeEval(Cid, id);
                    cout << "Removed successfully!\n";
                }
                else
                    cout << "Incorrect Course Id.\n";
            }
            else if (optionToRemove == 4)
            {
                //remove a question respective to a course
                int Qid, CLO_id, EvaID, Cid;
                string des;

                int i = 0;
                bool found = false;

                cout << "\nEnter corresponding Course ID: ";
                cin >> Cid;

                //finding the index of the Course to be searched
                int size = I.courses.size();
                while (i < size) {
                    if (I.courses[i].getId() == Cid) {
                        found = true;
                        break;
                    }
                    else
                        i++;
                }
                if (found)
                {
                    cout << "Enter corresponding Evaluation ID: ";
                    cin >> EvaID;

                    //finding the index of the Evaluation to be searched
                    int index = C.doesEvaExist(EvaID);

                    if (index != -1)
                    {
                        cout << "Enter Question id: ";
                        cin >> Qid;
                        cout << "Enter CLO id: ";
                        cin >> CLO_id;

                        I.courses[i].removeQuestionFromEvaluation(index, Qid, CLO_id);
                        cout << "Removed successfully!\n";
                    }
                    else
                        cout << "Incorrect Evaluation id!\n";
                }
                else
                    cout << "Incorrect Course id!\n";
            }
            else {
                return -1;
            }
        }
        else if (option == 3) {
            cout << "\nDo you want to:\n";
            cout << "Option 1: Update a Course\n";
            cout << "Option 2: Update a CLO\n";
            cout << "Option 3: Update an Evaluation\n";
            cout << "Option 4: Update a Question\n";
            cout << "Option: ";
            cin >> optionToUpdate;

            if (optionToUpdate == 1) {
                //update a course
                int id, newId;
                string name, newName;

                cout << "Enter Course id: ";
                cin >> id;
                cout << "Enter Course name: ";
                cin >> name;
                cout << "Enter new Course id: ";
                cin >> newId;
                cout << "Enter new Course name: ";
                cin >> newName;

                I.updateCourse(id, name, newId, newName);
                cout << "Updated successfully!\n";
            }
            else if (optionToUpdate == 2)
            {
                //update a CLO respective to a course
                int id, Cid, newId;
                string name, newName;
                int index = 0;
                bool found = false;

                cout << "\nEnter corresponding Course ID: ";
                cin >> Cid;

                //finding the index of the Course to be searched
                int size = I.courses.size();
                while (index < size) {
                    if (I.courses[index].getId() == Cid) {
                        found = true;
                        break;
                    }
                    else
                        index++;
                }
                if (found) {
                    cout << "Enter CLO id: ";
                    cin >> id;
                    cout << "Enter new CLO id: ";
                    cin >> newId;
                    cout << "Enter CLO name: ";
                    cin >> name;
                    cout << "Enter new CLO name: ";
                    cin >> newName;
                    I.courses[index].updateCLO(Cid, id, name, newId, newName);
                    cout << "Updated successfully!\n";
                }
                else
                    cout << "Incorrect Course Id.\n";
            }
            else if (optionToUpdate == 3) {
                //update an evaluation respective to a course
                int id, Cid, newId;
                int index = 0;
                bool found = false;

                cout << "\nEnter corresponding Course ID: ";
                cin >> Cid;

                //finding the index of the Course to be searched
                int size = I.courses.size();
                while (index < size) {
                    if (I.courses[index].getId() == Cid) {
                        found = true;
                        break;
                    }
                    else
                        index++;
                }
                if (found) {
                    cout << "Enter Evaluation id: ";
                    cin >> id;
                    cout << "Enter new Evaluation id: ";
                    cin >> newId;
                    I.courses[index].updateEval(Cid, id, newId);
                    cout << "Updated successfully!\n";
                }
                else
                    cout << "Incorrect Course Id.\n";
            }
            else if (optionToUpdate == 4)
            {
                //update a question respective to an evaluation
                int Qid, CLO_id, EvaID, Cid, newQid, newCLO_id;
                string des;

                int i = 0;
                bool found = false;

                cout << "\nEnter corresponding Course ID: ";
                cin >> Cid;

                //finding the index of the Course to be searched
                int size = I.courses.size();
                while (i < size) {
                    if (I.courses[i].getId() == Cid) {
                        found = true;
                        break;
                    }
                    else
                        i++;
                }
                if (found)
                {
                    cout << "Enter corresponding Evaluation ID: ";
                    cin >> EvaID;

                    //finding the index of the Evaluation to be searched
                    int index = C.doesEvaExist(EvaID);

                    if (index != -1)
                    {
                        cout << "Enter Question id: ";
                        cin >> Qid;
                        cout << "Enter CLO id: ";
                        cin >> CLO_id;
                        cout << "Enter new Question id: ";
                        cin >> newQid;
                        cout << "Enter new CLO id: ";
                        cin >> newCLO_id;
                        cout << "Enter new Question description: ";
                        cin >> des;

                        I.courses[i].updateQuestionFromEvaluation(index, Qid, CLO_id, newQid, newCLO_id, des);
                        cout << "Updated successfully!\n";
                    }
                    else
                        cout << "Incorrect Evaluation id!\n";
                }
                else
                    cout << "Incorrect Course id!\n";
            }
            else {
                return -1;
            }
        }
        else if (option == 4) {
            cout << "\nDo you want to:\n";
            cout << "Option 1: Print all Courses\n";
            cout << "Option 2: Print all CLOs wrt Courses\n";
            cout << "Option 3: Print all Evaluations wrt Courses\n";
            cout << "Option 4: Print all Questions\n";
            cout << "Option: ";
            cin >> optionToPrint;

            if (optionToPrint == 1) {
                //print all Courses();
                C.printAllCourses();


            }
            else if (optionToPrint == 2) {
                C.printallCLOs();

            }
            else if (optionToPrint == 3) {
                //Print all Evaluations wrt Courses
                C.printallEvals();

            }
            else if (optionToPrint == 4) {
                //Print all Questions wrt Courses
                E.printAllQuestions();

            }

        }
        else if (option == 5)
        {
            cout << "Option 1: Check All CLOs Tested\n";
            int option = 1;
            if (option == 1)
            {
                int Qid, CLO_id, CourseID, Cid;
                string des;

                int i = 0;
                bool found = false;

                cout << "\nEnter Course ID: ";
                cin >> Cid;

                //finding the index of the Course
                int size = I.courses.size();
                while (i < size) {
                    if (I.courses[i].getId() == Cid) {
                        found = true;
                        break;
                    }
                    else
                        i++;
                }
                if (found)
                {
                    if (I.courses[i].checkAllCLOsHasTested() == 1) {
                        cout << "All CLOs have been tested\n";
                    }
                    else
                        cout << "All CLOs have not been tested\n";
                }
            }
        }
        else if (option == -1) {
            return 0;
        }
    }

    return -1;
}

int main() {
    SetConsoleTitle(TEXT(" Outcome Based Education Support System"));
    system("color CE");

    if (menu() == 0)
    {
        cout << "Task successful\n";
    }
    else
        cout << "Invalid option selected\n";
    return 0;
}