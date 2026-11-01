#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen :protected clsScreen{
private :
  static  bool _Login(){
        bool LoginFaild = false;
        short FaildLoginCount = 0;
        string Username, Password;
        do
        {
            if (LoginFaild){
                FaildLoginCount ++;
                cout << "\n\nInvlaid Username/Password!";
                cout << "\nYou have " << (3 - FaildLoginCount) << " Trials to login.\n";
                if(FaildLoginCount == 3){
                    cout << "\nYour are Locked after 3 faild trials.";
                    return false;
                }
            }

            cout << "\nEnter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenu();
        return true;
    }

public:
    static bool ShowLoginScreen(){
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();
    }
};

