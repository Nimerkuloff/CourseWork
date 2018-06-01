//Menu for testing class
#include "menu.h"
#include "Matrix.h"
#include "list.h"

void menuFunc() {


    int choice;
    bool flag = true;

    Matrix a(1);
    Matrix b(1);
    Matrix c(1);
    list<Matrix> q;
    while (flag != false) {

        cout << "************* First part ***********\n";
        cout << " -4 - Print A\n";
        cout << " -3 - Print B\n";
        cout << " -2 - Print C\n";
        cout << " -1 - Input A\n";
        cout << " 0  - Input B\n";
        cout << " 1  - ++A\n";
        cout << " 2  - --B\n";
        cout << " 3  - A+=B\n";
        cout << " 4  - A-=B\n";
        cout << " 5  - A*=B\n";
        cout << " 6  - C=A+B\n";
        cout << " 7  - C=A-B\n";
        cout << " 8  - C=A*B\n";
        cout << " 9  - A==B\n";
        cout << " 10 - A!=B\n";
        cout << "************* Second part ***********\n";
        cout << " 11 - Add Matrices A and B to List container\n";
        cout << " 12 - Remove item B-?\n";
        cout << " 13 - [] overload. Uses to print out list\n";
        cout << " 14 - Search element\n";
        cout << " 15 - Exit.\n";
        cout << " Enter number and press return: ";
        cin >> choice;

        switch (choice) {
            case -4:
                a.Print();
                break;
            case -3:
                b.Print();

                break;
            case -2:
                c.Print();

                break;
            case -1:
                a.Input();

                break;
            case 0:
                b.Input();

                break;
            case 1:
                ++a;

                break;

            case 2:
                --b;
                break;

            case 3:
                a += b;

                break;
            case 4:
                a -= b;

                break;
            case 5:
                a *= b;

                break;

            case 6:
                c = a + b;

                break;
            case 7:
                c = a - b;

                break;
            case 8:
                c = a * b;

                break;
            case 9:
                a == b;

                break;
            case 10:
                a != b;

                break;
            case 11: {
                q.add(a);
                q.add(b);

                break;
            }
            case 12:
                q.remove_item(0);

                break;
            case 13: {
                int amount = q.get_amount();
                for (int i = 0; i < amount; i++)
                    cout << q[i];

                break;
            }
                // case 14:


                //  break;
            case 15: {

                cout << "*******************************\n";
                cout << "End of Program.\n";
                flag = false;

                break;
            }
            default:

                cout << "Not a Valid Choice. \n";
                cout << "Choose again.\n";
                cin >> choice;

                break;

        }

    }

}
