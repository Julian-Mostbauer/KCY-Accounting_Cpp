//
// Created by julian on 8/8/25.
//

#ifndef C_KCY_ACCOUNTING_LICENSESERVER_H
#define C_KCY_ACCOUNTING_LICENSESERVER_H
#include <string>
#include <utility>


class LicenseServer {
    const int port;
    const std::string licenseFile;
    const std::string version = "1.0.0";

    void handleClient(int clientSocket) const;

    bool validateLicense(const std::string &key, const std::string &mac) const;

public:
    explicit LicenseServer(std::string licenseFile, const int port = 4053)
        : port(port), licenseFile(std::move(licenseFile)) {
    }

    void run() const;
};

#endif //C_KCY_ACCOUNTING_LICENSESERVER_H
