#include <iostream>
using namespace std;

class Country {
    private:
        float mGDP; // in billions
        float mPopulation; // in millions
        
    public:
        string mName;
        string mCapital;

    Country(string name, string capital, float gdp, float population) {
        mName = name;
        mCapital = capital;
        mGDP = gdp;
        mPopulation = population;
    }

    Country(string name) : mName{name} {
        cout << "Defaul constructor";
    }

    ~Country() {
        cout << "Destructor called for " << mName << endl;
    }

    void holdElections() {
        cout << "Elections are being held in " << mName << endl;
    }
};

int main() {
    Country myCountry = Country("Utopia", "Eden", 500.0, 10.0);
    myCountry.holdElections();
    return 0;
}