#include "function.h"

int main()
{
    Bank b(100, 10);
    string c = "start";
    cout << "You can switch between BANK mode and ATM mode. " << endl;
    cout << "enter Z to toggle between modes" << endl;
    cout << "type <i> to get transaction information of the mode\n"
         << endl;
    bool toggle = true;
    cout << "BANK MODE" << endl;
    while (c != "E" || !toggle || b.isOpen())
    {
        cout << "\nEnter the operation to do: ";
        cin >> c;
        if (c == "Z")
        {
            toggle = !toggle;
            if (toggle)
                cout << "BANK MODE" << endl;
            else
                cout << "ATM MODE" << endl;
        }
        else if (c == "i")
        {
            INFO(toggle);
        }
        else
        {
            if (toggle)
                interaction(b, c[0]);
            else
                ATMInteraction(b, c[0]);
        }
    }
    return 0;
}
