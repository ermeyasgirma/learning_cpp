#include <iostream>
using namespace std;

class Country {
    private:
        float gdp; // in billions
        float population; // in millions
        
    public:
        string name;
        string capital;

    Country(string name, string capital, float gdp, float population) {
        this->name = name;
        this->capital = capital;
        this->gdp = gdp;
        this->population = population;
    }

    void holdElections() {
        cout << "Elections are being held in " << this->name << endl;
    }
};

int main() {
    Country myCountry = Country("Utopia", "Eden", 500.0, 10.0);
    myCountry.holdElections();
    return 0;
}