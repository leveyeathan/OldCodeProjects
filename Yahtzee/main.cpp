#include <iostream>
#include <chrono>
#include <random>
#include <sstream>
#include <algorithm>

using namespace std;

class RandomGenerator
{
private:
    random_device randDevice;
    mt19937 mersenneTwister;
public:
    RandomGenerator(int seed = 0); // seed == 0 will use system clock for seed
    int getInt(int minVal, int maxVal);
    double getDouble(double minVal, double maxVal);
    string getString(int minLength = 8, int maxLength = 8, const string& symbols = "abcdefghijklmnopqrstuvwxyz");
};

RandomGenerator::RandomGenerator(int seed) : mersenneTwister(randDevice())
{
    mersenneTwister.seed(seed ? seed : (chrono::system_clock::now().time_since_epoch()).count());
}

int RandomGenerator::getInt(int minVal, int maxVal)
{
    return uniform_int_distribution<int>(minVal, maxVal)(mersenneTwister);
}

double RandomGenerator::getDouble(double minVal, double maxVal)
{
    return uniform_real_distribution<double>(minVal, maxVal)(mersenneTwister);
}

string RandomGenerator::getString(int minLength, int maxLength, const string& symbols)
{
    uniform_int_distribution<int> dist(0, symbols.size()-1);
    string txt(getInt(minLength, maxLength), 'x');
    for (size_t i=0;i<txt.size();i++)
    {
        txt[i] = symbols[dist(mersenneTwister)];
    }
    return txt;
}

RandomGenerator rnd;

int scoreTop(int calculation, vector<int> roll, int score){
    for(int i = 0; i < 5; i++){
        if(roll[i] == calculation){
            score = score + calculation;
        }
    }
    if(score == 0){
        cout << "None of your dice are " << calculation << ". A 0 will be put into this category.\n";
    }
    return score;
}
int scoreThreeOfKind(int score, vector<int> roll){
    for(int i = 0; i < 5; i++){
        if(roll[i] == roll[i+1] && roll[i+1] == roll [i+2] && roll[i+2] != roll[i+3]){
            score = roll[0]+roll[1]+roll[2]+roll[3]+roll[4];
        }
    }
    if(score == 0){
        cout << "There is no 3 of a kind here. A 0 will be put in this category.";
    }
    return score;
}
int scoreFourOfKind(int score, vector<int> roll){
    for(int i = 0; i < 5; i++){
        if(roll[i] == roll[i+1] && roll[i+1] == roll [i+2] && roll[i+2] == roll[i+3] && roll[i+3] != roll[i+4]){
            score = roll[0]+roll[1]+roll[2]+roll[3]+roll[4];
        }
    }
    if(score == 0){
        cout << "There is no 4 of a kind here. A 0 will be put in this category.";
    }
    return score;
}
int scoreSmallStraight(int score, vector<int> roll){
    for(int i = 0; i < 3; i++){
        if(roll[i] == 1 && roll[i+1] == 2 && roll[i+2] == 3 && roll[i+3] == 4){
            score = 30;
        }
        else{
            if(roll[i] == 2 && roll[i+2] == 3 && roll[i+3] == 4 && roll[i+4] == 5){
                score = 30;
            }
            else{
                if(roll[i] == 3 && roll[i+2] == 4 && roll[i+3] == 5 && roll[i+4] == 6){
                    score = 30;
                }
            }
        }
        if(score == 0){
            cout << "This is not a small straight. A 0 will be put in this section for your score.\n";

        }
    }
    return score;

}
int scoreLargeStraight(int score, vector<int> roll){
    if(roll[0] == 1 && roll[1] == 2 && roll[2] == 3 && roll[3] == 4 && roll[4] == 5){
        score = 40;
    }
    else{
        if(roll[0] == 2 && roll[1] == 3 && roll[2] == 4 && roll[3] == 5 && roll[4] == 6){
            score = 40;
        }
        else{
            cout << "This is not a large straight. A 0 will be put in this section for your score.\n";
        }
    }
    return score;

}
int scoreFullHouse(int score, vector<int> roll){
    if(roll[0] == roll[1] && roll[2] == roll[3] && roll[3] == roll[4] && roll[1] != roll[2]){
        score = 25;
    }
    else{
        if(roll[0] == roll[1] && roll[1] == roll[2] && roll[3] == roll[4] && roll[2] != roll[3])
            score = 25;
        else{
            cout << "This is not a full house. A 0 will be put in for this category.\n";
        }
    }
    return score;

}
int scoreYahtzee(int score, vector<int> roll, vector<bool> completedCalculations){
    if(roll[0] == roll[1] && roll[1] == roll[2] && roll[2] == roll[3] && roll[3] == roll[4] && roll[4] == roll[5]){
        if(completedCalculations[12] == true){
            int num = 1;
            completedCalculations.push_back(num);
            score = 100;
        }
        else{
            score = 50;
        }
    }
    if(score == 0){
        cout << "This is not a Yahtzee. A 0 will be put in this section for your score.\n";
        score = 0;
    }
    return score;

}
int scoreChance(int score, vector<int> roll){
    score = roll[0]+roll[1]+roll[2]+roll[3]+roll[4];
    return score;
}

int chooseCalculation(vector<bool> completedCalculations){
    int calculation;

    while(true){
        cout << "Which category would you like to score this in?\n";
        cout << "Top:\n";
        cout << "1 - Ones\n";
        cout << "2 - Twos\n";
        cout << "3 - Threes\n";
        cout << "4 - Fours\n";
        cout << "5 - Fives\n";
        cout << "6 - Sixes\n";
        cout << " \n";
        cout << "Bottom:\n";
        cout << "7 - 3 of a kind\n";
        cout << "8 - 4 of a kind\n";
        cout << "9 - Full House\n";
        cout << "10 - Small Straight\n";
        cout << "11 - Large Straight\n";
        cout << "12 - Yahtzee\n";
        cout << "13 - Chance\n";
        cin >> calculation;

        if(!completedCalculations[calculation - 1]){
            break;
        }
        cout << "You have already put a score in this category. Please choose another.\n";
        cout << "\n";
    }
    return calculation;
}

void recordScore(int score, int calculation, vector<bool>& completedCalculations, vector<int>& topScores, vector<int>& bottomScores){
    if(calculation < 7 && completedCalculations[calculation - 1] == false){
        topScores.push_back(score);
        completedCalculations[calculation - 1] = true;
    }
    if(!(calculation == 12) && completedCalculations[calculation - 1] == false && calculation > 6){
        bottomScores.push_back(score);
        completedCalculations[calculation - 1] = true;
    }
}

void rerollDice(vector<int>& dice, string reroll){
    stringstream ss{reroll};
    for(int i = 0; i < 5; i++){
        int value = 0;
        if(ss >> value && value == 0){
            int die = rnd.getInt(1,6);
            dice[i] = die;
        }
    }
}

void displayReroll(vector<int>& roll){
    string reroll;

    cout << " \n";
    cout << "Please indicate which dice you would like to keep by typing '1' for each die you want to keep and '0' for each die you don't.\n";
    cout << " \n";
    cout << "(For example, you could type '1 1 0 0 0' to keep the first 2 dice.)\n";

    getline(cin, reroll);

    rerollDice(roll, reroll);

    cout << "Your new roll is...\n";
    for(int i = 0; i < 5; i++){
        cout << roll[i] << endl;
    }
}

int grandTotal(vector<int> topScores, vector<int> bottomScores){
    int topScore = 0;
    int bottomScore = 0;
    for(int i = 0; i < (int)topScores.size(); i++){
        topScore = topScore + topScores[i];
    }
    for(int i = 0; i < (int)bottomScores.size(); i++){
        bottomScore = bottomScore + bottomScores[i];
    }
    if(topScore > 63){
        topScore = topScore + 35;
    }
    int finalScore;
    finalScore = topScore + bottomScore;
    return finalScore;
}

void scoreDice(vector<int> topScores, vector<int> bottomScores, vector<int> roll, int calculation, vector<bool>& completedCalculations) {

    int score = 0;
    sort(roll.begin(), roll.end());

    switch(calculation) {
    case 1:
        score = scoreTop(calculation, roll, score);
        break;
    case 2:
        score = scoreTop(calculation, roll, score);
        break;
    case 3  :
        score = scoreTop(calculation, roll, score);
        break;
    case 4  :
        score = scoreTop(calculation, roll, score);
        break;
    case 5  :
        score = scoreTop(calculation, roll, score);
        break;
    case 6  :
        score = scoreTop(calculation, roll, score);
        break;
    case 7  :
        score = scoreThreeOfKind(score, roll);
        break;
    case 8  :
        score = scoreFourOfKind(score, roll);
        break;
    case 9  :
        score = scoreFullHouse(score, roll);
        break;
    case 10  :
        score = scoreSmallStraight(score, roll);
        break;
    case 11  :
        score = scoreLargeStraight(score, roll);
        break;
    case 12  :
        score = scoreYahtzee(score, roll, completedCalculations);
        break;
    case 13  :
        score = scoreChance(score, roll);
        break;
    }
    recordScore(score, calculation, completedCalculations, topScores, bottomScores);

    cout << " \n";
    cout << "The score recorded for this round was " << score << ".\n";
    cout << "Press enter to roll again.\n";
}

int main()
{
    vector<int> topScores;
    vector<int> bottomScores;

    vector<bool> completedCalculations;
    completedCalculations.resize(13);

    cout << " \n";
    cout << "*** Welcome to Yahtzee! ***\n";
    cout << " \n";

    for(int i = 0; i < completedCalculations.size(); i++){

        int turnNumber = i + 1;

        cout << "You are on turn: " << turnNumber << endl;

        vector<int> roll;
        while(roll.size() < 5){
            int die = rnd.getInt(1,6);
            roll.push_back(die);
        }
        cout << " \n";
        cout << "Your dice are...\n";
        for(int i = 0; i < 5; i++){
            cout << roll[i] << endl;
        }

        displayReroll(roll);

        displayReroll(roll);

        int calculation = chooseCalculation(completedCalculations);

        scoreDice(topScores, bottomScores, roll, calculation, completedCalculations);

        string enter;
        cin.ignore(1000, '\n');
        getline(cin, enter);
    }
    cout << "Your final score is: " << grandTotal(topScores, bottomScores) << endl;
}
