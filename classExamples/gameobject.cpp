#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class GameObject {
private:
    float x;
    float y;


public:
    GameObject(float x=0, float y=0) : x{x}, y{y}
    {

    }

    void act()
    {
        x += (rand()%4)/3.0;
        y += (rand()%4)/3.0;
    }
    
    friend ostream& operator<<(ostream& os, const GameObject& g)
    {
        os << "GameObject at (" << g.x << ", " << g.y << ")";
        return os;
    }
 };

int main() {
    //for using objects in a game
    vector<unique_ptr<GameObject>> objects;

    for(int i=0; i<1000000; i++)objects.push_back(make_unique<GameObject>());
    
    for(auto& g:objects){
        g->act();
    }

    for(auto& g:objects){
        cout << *g << endl;
    }


    return 0;
}