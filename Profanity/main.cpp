#include <iostream>

using namespace std;

string profanityGenerator(int val){

    switch(val){
    case 1:
        return "shit";
    case 2:
        return "piss";
    case 3:
        return "fuck";
    case 4:
        return "cunt";
    case 5:
        return "cocksucker";
    case 6:
        return "motherfucker";
    case 7:
        return "tits";
    case 8:
        return "fart";
    case 9:
        return "turd";
    case 10:
        return "twat";
     default:
        cout << "i fucked your mommmmmmmmmm" << endl;
        return "kys";

    }
}
int main()
{
    int val;
    cout << "Type a integer between 1 and 10, inclusive, to get a swear word." << endl;
    while(true){
     cin >> val;
     cout << profanityGenerator(val) << endl;
    }

}
