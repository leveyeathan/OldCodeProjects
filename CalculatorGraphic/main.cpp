#include <iostream>
#include "graphics.h"
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;
using namespace mssm;

class Calculator{
public:
    void button(char x);
    string display();
    void calculate();
    bool eq = false;

private:
    string number1;
    string answer;
    char op = 'q';
    double x;
    double y;
};

void Calculator::button(char k){
    if(op == 'q'){
        switch (k)
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            if(number1.length() < 21){
                number1.append(1, k);
            }
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            op = k;
            if(number1.length() > 0){
                x = stod(number1);
                number1.clear();
            }
            break;
        case '=':
            eq = true;
            calculate();
            break;
        case 'c':
            number1.clear();
            answer.clear();
            op = 'q';
        default:
            break;
        }
    }
    else{
        switch (k)
        {
        case ' ':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            if(number1.length() < 21){
                number1.append(1, k);
            }
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            op = k;
            if(number1.length() > 0){
                y = stod(number1);
            }
            calculate();
            break;
        case '=':
            eq = true;
            if(number1.length() > 0){
                y = stod(number1);
            }
            calculate();
            break;
        case 'c':
            number1.clear();
            answer.clear();
            op = 'q';
        default:
            break;
        }
    }
}

void Calculator:: calculate(){
    if(op == 'q'){
        answer = to_string(x);
    }
    if(op == '+'){
        x = (x+y);
        answer = to_string(x);
    }
    if(op == '-'){
        x = (x-y);
        answer = to_string(x);
    }
    if(op == '*'){
        x = (x*y);
        answer = to_string(x);
    }
    if(op == '/'){
        x = (x/y);
        answer = to_string(x);
    }
    if(eq){
        op = 'q';
        number1.clear();
        eq = false;
    }
    number1.clear();
}

string Calculator::display(){
    if(number1.length() > 0){
        return number1;
    }
    return answer;
}

class Button{
public:
    Vec2d center;
    string value;
    string text;
public:
    void draw(Graphics& g);
    bool test(Vec2d location);
};

void Button::draw(Graphics& g){
    double x = center.x;
    double y = center.y;
    g.rect(x, y, 100, 100, GREEN, BLUE);
    g.text(x + 25, y + 25, 50, value, GREEN);
}

bool Button::test(Vec2d location){
    if(location.x > center.x && location.x < center.x+100 && location.y > center.y && location.y < center.y+100){
        return true;
    }
    else{
        return false;
    }
}
void graphicsMain(Graphics& g)
{
    Calculator Fred;

    vector<Button> buttons;
    vector<string> values {"0", "1", "4", "7", "c", "2", "5", "8", "=", "3", "6", "9", "/", "*", "-", "+"};

    for(int i = 1; i < 6; i++){
        for(int k = 1; k < 5; k++){
            Button x;
            x.center = {100.*(i+1), 100.*k};
            buttons.push_back(x);
        }
    }
    for(int i = 0; i < values.size(); i++){
        buttons[i].value = values[i];
    }

    while (g.draw())
    {
        g.clear();

        g.rect(200, 500, 400, 100, GREEN, BLUE);
        g.rect(220, 520, 360, 60, GREEN, BLACK);
        for(int i = 0; i < values.size(); i++){
            buttons[i].draw(g);
        }

        g.text(230, 530, 30, Fred.display(), GREEN);

        for (const Event& e : g.events())
        {
            switch (e.evtType)
            {
            case EvtType::MousePress:
            {
                double a = e.x;
                double b = e.y;
                Vec2d location{a, b};
                for(int i = 0; i < buttons.size(); i++){
                    if(buttons[i].test(location)){
                        Fred.button(buttons[i].value[0]);
                        g.rect(buttons[i].center.x, buttons[i].center.y, 100, 100, GREEN, GREEN);
                    }
                }
            }
                break;
            case EvtType::MouseRelease:
                break;
            case EvtType::MouseWheel:
                break;
            case EvtType::MouseMove:
                break;
            case EvtType::KeyPress:
                break;
            case EvtType::KeyRelease:
                break;
            default:
                break;
            }
        }
    }
}

int main()
{
    Graphics g("Graphics", 1200, 800, graphicsMain);
}
