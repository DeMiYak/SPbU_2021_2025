#include<iostream>
#include<cmath>
#include"Queue.h"
#include"Stack.h"

using namespace std;

int main()
{
    size_t p;
    cout << "Press 1 to pick the queue or 2 to pick the stack: ";
    cin >> p;
    double key;
    size_t id;

    if(p == 1)
    {
//        size_t k;
//        cout << "Press 1 for double-type queue, 2 for int-type queue";
//        cin >> k;
//        switch(k)
//        {
//        case 1:
//            queue<double> q;
//            break;
//
//        }
        queue<double> q;


        size_t p;
        cout << "Choose the method:\n1. Push\n2. PopFront\n3. GetFront\n4. SetFront\n5. IsEmpty\n6. QuantifyQueue\n7. Print queue's element\n8. PrintQueue\n\n";
        cin >> p;
        while(1 <= p && p <= 8)
        {
            switch(p)
            {
            case 1:
                cout << "Enter the number (0 to return): ";
                cin >> key;
                while(key)
                {
                    q.Push(key);
                    q.PrintQueue();
                    cin >> key;
                }
                break;
            case 2:
                cout << "Pop: " << q.PopFront();
                break;
            case 3:
                key = q.GetFront();
                cout << "Get: " << key;
                break;
            case 4:
                break;
            case 5:
                cout << "Is Empty: " << q.IsEmpty();
                break;
            case 6:
                cout << "Current amount: " << q.QuantifyQueue();
                q.PrintQueue();
                break;
            case 7:
                cout << "Enter the number: ";
                cin >> id;
                cout << q[id];
                break;
            case 8:
                q.PrintQueue();
                break;
            default:
                break;
            }
            cout << "\nChoose the method:\n1. Push\n2. PopFront\n3. GetFront\n4. SetFront\n5. IsEmpty\n6. QuantifyQueue\n7. Print queue's element\n8. PrintQueue\n\n";
            cin >> p;
        }
        queue<double> q2 = q;
        q2.PrintQueue();
    }
    else if(p == 2)
    {
//        size_t k;
//        cout << "Press 1 for double-type queue, 2 for int-type queue";
//        cin >> k;
//        switch(k)
//        {
//        case 1:
//            queue<double> q;
//            break;
//
//        }
        stack<double> s;


        size_t p;
        cout << "Choose the method:\n1. Push\n2. PopFront\n3. GetFront\n4. SetFront\n5. IsEmpty\n6. QuantifyStack\n7. Print stack's element\n8. PrintStack\n\n";
        cin >> p;
        while(1 <= p && p <= 9)
        {
            switch(p)
            {
            case 1:
                cout << "Enter the number (0 to return): ";
                cin >> key;
                while(key)
                {
                    s.Push(key);
                    s.PrintStack();
                    cin >> key;
                }
                break;
            case 2:
                cout << "Pop: " << s.Pop();
                break;
            case 3:
                key = s.GetFront();
                cout << "Get: " << key;
                break;
            case 4:
                break;
            case 5:
                cout << "Is Empty: " << s.IsEmpty();
                break;
            case 6:
                cout << "Current amount: " << s.QuantifyStack();
                s.PrintStack();
                break;
            case 7:
                cout << "Enter the number: ";
                cin >> id;
                cout << s[id];
                break;
            case 8:
                s.PrintStack();
                break;
            case 9:
                s.Test();
                break;
            default:
                break;
            }
            cout << "\nChoose the method:\n1. Push\n2. PopFront\n3. GetFront\n4. SetFront\n5. IsEmpty\n6. QuantifyStack\n7. Print stack's element\n8. PrintStack\n\n";
            cin >> p;
        }
        stack<double> s2 = s;
        s2.PrintStack();
    } else {cout << "Wrong number. Finishing programme...";}
    cout << "\n... Memory cleared";
    return 0;
}
