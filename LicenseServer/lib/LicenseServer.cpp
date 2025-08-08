//
// Created by julian on 8/8/25.
//

#include "LicenseServer.h"

#include "License.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

void LicenseServer::run() const {
    const int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cerr << "[Server] Socket creation failed." << endl;
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Bind to all interfaces
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) < 0) {
        cerr << "[Server] Bind failed." << endl;
        cerr << "[Server] Error: " << strerror(errno) << endl;
        cerr << "[Server] Make sure the port " << port << " is not already in use." << endl;
        close(serverSocket);
        return;
    }

    if (listen(serverSocket, 5) < 0) {
        cerr << "[Server] Listen failed." << endl;
        cerr << "[Server] Error: " << strerror(errno) << endl;
        close(serverSocket);
        return;
    }

    cout << "[Server] Listening on port " << port << "..." << endl;


    while (true) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(serverSocket, &readfds);
        FD_SET(STDIN_FILENO, &readfds);
        const int maxfd = max(serverSocket, STDIN_FILENO) + 1;

        const int activity = select(maxfd, &readfds, nullptr, nullptr, nullptr);
        if (activity < 0) {
            cerr << "[Server] Select error." << endl;
            break;
        }

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            string input;
            getline(cin, input);
            if (input == "exit") {
                cout << "[Server] Shutting down..." << endl;
                break;
            }
        }

        if (FD_ISSET(serverSocket, &readfds)) {
            const int clientSocket = accept(serverSocket, nullptr, nullptr);
            if (clientSocket < 0) {
                cerr << "[Server] Accept failed." << endl;
                continue;
            }
            handleClient(clientSocket);
        }
    }

    close(serverSocket);
}

void LicenseServer::handleClient(const int clientSocket) const {
    char buffer[256];
    const ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        cerr << "[Server] Read error." << endl;
        close(clientSocket);
        return;
    }

    buffer[bytesRead] = '\0'; // Null-terminate the string
    string received(buffer);

    if (received.empty()) {
        cout << "[Server] Empty message received." << endl;
        close(clientSocket);
        return;
    }

    if (received == "getversion") {
        cout << "[Server] Client requested version." << endl;
        write(clientSocket, version.c_str(), version.size());
        close(clientSocket);
        return;
    }

    // Split message: "LICENSEKEY-MACADRESSE"
    const size_t delimiterPos = received.find('-');
    if (delimiterPos == string::npos) {
        cout << "[Server] Invalid message format. Expected: LICENSEKEY-MACADRESSE" << endl;
        close(clientSocket);
        return;
    }

    const string licenseKey = received.substr(0, delimiterPos);
    const string macAddress = received.substr(delimiterPos + 1);

    cout << "[Server] Received licenseKey: " << licenseKey << ", MAC: " << macAddress << endl;

    const bool isValid = validateLicense(licenseKey, macAddress);

    const string response = isValid ? "true" : "false";
    write(clientSocket, response.c_str(), response.size());

    close(clientSocket);
}

bool LicenseServer::validateLicense(const string &key, const string &mac) const {
    vector<License> licenses = License::fromFile(licenseFile);

    for (auto &license: licenses) {
        if (license.LicenseKey == key) {
            if (find(license.AllowedMacs.begin(), license.AllowedMacs.end(), mac) != license.
                AllowedMacs.end()) {
                cout << "[Server] MAC " << mac << " already registered, limit reached but still valid." <<
                        endl;
                return true;
            }

            if (license.RedeemedUsers < license.AllowedUsers) {
                license.AllowedMacs.push_back(mac);
                license.RedeemedUsers++;
                cout << "[Server] New MAC added: " << mac << ". Redeemed: " << license.RedeemedUsers << "/" <<
                        license.AllowedUsers << endl;

                // Save updated licenses back to file
                ofstream outFile(licenseFile);
                if (!outFile.is_open()) {
                    cerr << "[Server] Could not open license file for writing: " << licenseFile << endl;
                    return false;
                }
                outFile << LICENSE_CSV_HEADER << "\n";
                for (const auto &l: licenses) {
                    outFile << l.toString() << "\n";
                }
                outFile.close();

                return true;
            }

            cout << "[Server] Limit reached, new MAC not allowed: " << mac << endl;
            return false;
        }
    }

    cout << "[Server] License not found." << endl;
    return false;
}