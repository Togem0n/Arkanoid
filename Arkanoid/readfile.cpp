#include<readfile.h>

vector<string> readLevel(const string& filename) {

    std::ifstream file(filename);
    string line;
    vector<string> lines;

    int cnt = 0;
    while (getline(file, line)) {
        if (cnt >= Row) {
            break;
        }
        lines.push_back(line);
        cnt++;
    }
    
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if (!isdigit(lines[i][j]) || j >= Column) {
                lines[i].erase(j, 1);
                j--;
            }
        }
    }
    
    file.close();
    return lines;
}