#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

struct Color {
    int r;
    int g;
    int b;
};

ostream& operator<<(ostream& os, Color c) {
    os << "RGB(" << c.r << "," << c.g << "," << c.b << ")";
    return os;
}

unordered_map<string, Color> loadColorsFromCSV(const string& filename) {
    unordered_map<string, Color> colorLookup;
    ifstream file(filename);
    string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string name, r, g, b;
        getline(ss, name, ',');
        getline(ss, r, ',');
        getline(ss, g, ',');
        getline(ss, b, ',');
        if (!name.empty() && !r.empty() && !g.empty() && !b.empty()) {
            colorLookup[name] = Color{stoi(r), stoi(g), stoi(b)};
        }
    }
    return colorLookup;
}

int main() {
    auto colorLookup = loadColorsFromCSV("colors.csv");
    cout << colorLookup.size() << endl;
    for (const auto& pair : colorLookup) {
        cout << pair.first << ": " << pair.second << endl;
    }
    while(true) {
        string searchColor;
        cout << "Enter a color name: ";
        cin >> searchColor;
        // Convert to lowercase
        std::transform(searchColor.begin(), searchColor.end(), searchColor.begin(), [](unsigned char c){ return std::tolower(c); });
        if (colorLookup.find(searchColor) != colorLookup.end()) {
            cout << searchColor << ": " << colorLookup[searchColor] << endl;
        } else {
            cout << "Color not found!" << endl;
        }
    }
}