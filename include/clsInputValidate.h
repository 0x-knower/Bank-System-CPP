#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "clsUtil.h"
#include "clsDate.h"

using namespace std;

class clsInputValidate{
public:

    template <typename T>
    static bool IsNumberBetween(T Num, T From, T To){
        return (Num >= From && Num <= To);
    }

    static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo){
       if(clsDate::IsDate1AfterDate2(DateFrom,DateTo)){
            clsDate::SwapDates(DateFrom,DateTo);
       }
       return !(clsDate::IsDate1BeforeDate2(Date,DateFrom) || clsDate::IsDate1AfterDate2(Date,DateTo));
    }

    template <typename T>
    static T ReadNumber(string ErrorMessage = "Invalid Number, Enter again\n"){
        T Number;
        while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
    }

    template <typename T>
    static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again:\n"){
        T Number = ReadNumber <T>();
        while (!IsNumberBetween(Number, From, To)) {
            cout << ErrorMessage;
            Number = ReadNumber<T>();
        }
        return Number;
    }



    static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		return ReadNumber<short> (ErrorMessage);
	}

    static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		return ReadNumberBetween <short> (From,To,ErrorMessage);
	}

    static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
    {
        return ReadNumber<int> (ErrorMessage);
    }

    static int ReadIntNumberBetween(int From, int To, string Message = "Number is not within ranage.\n"){
        return ReadNumberBetween <int> (From,To,Message);
    }

    static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		return ReadNumber<float> (ErrorMessage);
	}

	static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		return ReadNumberBetween <float> (From,To,ErrorMessage);
	}


    static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
    {
        return ReadNumber<double> (ErrorMessage);
    }

    static double ReadDblNumberBetween(double From, double To, string Message = "Number is not within ranage.\n"){
        return ReadNumberBetween <double> (From,To,Message);
    }

    static bool IsValideDate(clsDate Date){
        return clsDate::IsValidDate(Date);
    }

    static string ReadString(){
        string S1 ="";
        getline(cin >> ws,S1);
        return S1;
    }
};