//
// Created by julian on 8/8/25.
//

#include "License.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <filesystem>
using namespace std;

/*
Name;LicenseKey;AllowedUsers;RedeemedUsers;AllowedMacs
x;example;2;0;example_mac_1,example_mac_2
*/
License License::fromString(const string &licenseString) {
    License license;
    istringstream stream(licenseString);
    string line;
    if (getline(stream, line)) {
        istringstream lineStream(line);

        getline(lineStream, license.Name, ';');
        getline(lineStream, license.LicenseKey, ';');

        string token;
        getline(lineStream, token, ';');
        license.AllowedUsers = stoi(token);

        getline(lineStream, token, ';');
        license.RedeemedUsers = stoi(token);

        getline(lineStream, token);
        istringstream macStream(token);
        string mac;
        while (getline(macStream, mac, ',')) {
            if (!mac.empty()) {
                license.AllowedMacs.push_back(mac);
            }
        }
    } else {
        throw runtime_error("Error: License string is empty or malformed.");
    }

    return license;
}

string License::toString() const {
    string result = Name + ";" + LicenseKey + ";" +
                    to_string(AllowedUsers) + ";" +
                    to_string(RedeemedUsers) + ";";
    for (size_t i = 0; i < AllowedMacs.size(); ++i) {
        result += AllowedMacs[i];
        if (i < AllowedMacs.size() - 1) {
            result += ",";
        }
    }
    return result;
}

vector<License> License::fromFile(const string &filePath) {
    vector<License> licenses;
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Could not open license file: " + filePath);
    }

    bool firstLine = true;
    string line;
    while (getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue;
        }
        if (!line.empty())
            licenses.push_back(fromString(line));
    }
    file.close();
    return licenses;
}
