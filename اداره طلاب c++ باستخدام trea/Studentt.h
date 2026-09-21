
#include <iostream>
#include <string>

using namespace std;
template <class T>
class StudentNode
{
public:

    T id;
    string name;
    double grade;

    StudentNode<T>* left;
    StudentNode<T>* right;

    StudentNode()
    {
        left = 0;
        right = 0;
    }

    StudentNode(T studentID, string studentName, double studentGrade)
    {
        id = studentID;
        name = studentName;
        grade = studentGrade;

        left = 0;
        right = 0;
    }
};
template <class T>
class StudentBST
{
public:

    StudentNode<T>* root;

    StudentBST()
    {
        root = 0;
    }
    void addStudent(T id, string name, double grade)
    {
        if (root == 0)
        { root = new StudentNode<T>(id, name, grade);
        }
        else
        {
            StudentNode<T>* tmp = root;
            StudentNode<T>* parent = 0;

            while (tmp != 0)
            {
                parent = tmp;

                if (id < tmp->id)
                    tmp = tmp->left;
                else
                    tmp = tmp->right;
            }

            if (id < parent->id)
                parent->left =
                    new StudentNode<T>(id, name, grade);

            else
                parent->right =
                    new StudentNode<T>(id, name, grade);
        }
    }
    StudentNode<T>* searchStudent(T id)
    {
        StudentNode<T>* tmp = root;

        while (tmp != 0)
        {
            if (id == tmp->id)
                return tmp;

            else if (id < tmp->id)
                tmp = tmp->left;

            else
                tmp = tmp->right;
        }

        return 0;
    }
    bool updateStudent(T id, string newName, double newGrade)
    {
        StudentNode<T>* student =
            searchStudent(id);

        if (student == 0)
            return false;

        student->name = newName;
        student->grade = newGrade;

        return true;
    }
	    void displayStudents(StudentNode<T>* tmp)
    {
        if (tmp != 0)
        {
            displayStudents(tmp->left);

            cout << "ID: " << tmp->id
                 << " | Name: " << tmp->name
                 << " | Grade: " << tmp->grade;

            if (tmp->grade >= 50)
                cout << " | Status: PASS";
            else
                cout << " | Status: FAIL";

            cout << endl;

            displayStudents(tmp->right);
        }
    }
    void displayStudents()
    {
        if (root == 0)
        {
            cout << "\nNo students found.\n";
            return;
        }

        cout << "\n========== All Students ==========\n";

        displayStudents(root);

        cout << "==================================\n";
    }
    bool isempty()
    {
        return root == 0;
    }
    bool deleteStudent(T id)
    {
        StudentNode<T>* tmp = root;
        StudentNode<T>* parent = 0;
        while (tmp != 0 && tmp->id != id)
        {
            parent = tmp;

            if (id < tmp->id)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        if (tmp == 0)
            return false;
        if (tmp->left == 0 &&
            tmp->right == 0)
        {
            if (tmp == root)
                root = 0;

            else if (parent->left == tmp)
                parent->left = 0;

            else
                parent->right = 0;

            delete tmp;

            return true;
        }

        if (tmp->left == 0)
        {
            if (tmp == root)
                root = tmp->right;

            else if (parent->left == tmp)
                parent->left = tmp->right;

            else
                parent->right = tmp->right;

            delete tmp;

            return true;
        }


        // Only Left Child

        if (tmp->right == 0)
        {
            if (tmp == root)
                root = tmp->left;

            else if (parent->left == tmp)
                parent->left = tmp->left;

            else
                parent->right = tmp->left;

            delete tmp;

            return true;
        }


        // Two Children

        StudentNode<T>* successorParent = tmp;

        StudentNode<T>* successor = tmp->right;


        while (successor->left != 0)
        {
            successorParent = successor;
            successor = successor->left;
        }


        tmp->id = successor->id;
        tmp->name = successor->name;
        tmp->grade = successor->grade;


        if (successorParent->left == successor)
            successorParent->left = successor->right;

        else
            successorParent->right = successor->right;


        delete successor;

        return true;
    }
    double getHighestGrade(StudentNode<T>* tmp)
    {
        if (tmp == 0)
            return 0;

        double highest = tmp->grade;

        double leftHighest =
            getHighestGrade(tmp->left);
        double rightHighest =
            getHighestGrade(tmp->right);
        if (leftHighest > highest)
            highest = leftHighest;

        if (rightHighest > highest)
            highest = rightHighest;


        return highest;
    }

    double getHighestGrade()
    {
        return getHighestGrade(root);
    }
    int countPassed(StudentNode<T>* tmp)
    {
        if (tmp == 0)
            return 0;

        int count = 0;


        if (tmp->grade >= 50)
            count++;


        count += countPassed(tmp->left);
        count += countPassed(tmp->right);


        return count;
    }
    int countPassed()
    {
        return countPassed(root);
    }
    int countFailed(StudentNode<T>* tmp)
    {
        if (tmp == 0)
            return 0;

        int count = 0;

        if (tmp->grade < 50)
            count++;


        count += countFailed(tmp->left);
        count += countFailed(tmp->right);


        return count;
    }
    int countFailed()
    {
        return countFailed(root);
    }
    StudentNode<T>* getRoot()
    {
        return root;
    }
    void clear(StudentNode<T>* tmp)
    {
        if (tmp != 0)
        {
            clear(tmp->left);

            clear(tmp->right);

            delete tmp;
        }
    }
    ~StudentBST()
    {
        clear(root);
    }
};
template <class T>
class QueueNode
{
public:

    T info;

    QueueNode<T>* next;


    QueueNode(T value)
    {
        info = value;
        next = 0;
    }
};
template <class T>
class StudentQueue
{
public:

    QueueNode<T>* front;
    QueueNode<T>* rear;


    StudentQueue()
    {
        front = 0;
        rear = 0;
    }

    bool isEmpty()
    {
        return front == 0;
    }
    void enqueue(T id)
    {
        QueueNode<T>* newNode =
            new QueueNode<T>(id);


        if (rear == 0)
        {
            front = rear = newNode;
        }

        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }
    T dequeue()
    {
        if (isEmpty())
            return T();

        T id = front->info;
        QueueNode<T>* temp = front;
        if (front == rear)
            front = rear = 0;

        else
            front = front->next;


        delete temp;


        return id;
    }

    T getFront()
    {
        if (isEmpty())
            return T();


        return front->info;
    }
    ~StudentQueue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }
};

                      



