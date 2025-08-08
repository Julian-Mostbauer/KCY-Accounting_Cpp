//
// Created by julian on 8/8/25.
//
#include <iostream>

#include "../lib/LicenseServer.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <license_file> [port]" << std::endl;
        return 1;
    }
    const std::string licenseFile = argv[1];

    int port = argc > 2 ? std::atoi(argv[2]) : 4053;
    if (port <= 0) {
        std::cerr << "Invalid port number. Using default port 4053." << std::endl;
        port = 4053;
    }

    const LicenseServer server(licenseFile, port);
    server.run();
}
