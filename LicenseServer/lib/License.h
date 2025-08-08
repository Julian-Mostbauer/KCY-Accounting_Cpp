//
// Created by julian on 8/8/25.
//

#ifndef C_KCY_ACCOUNTING_LICENSE_H
#define C_KCY_ACCOUNTING_LICENSE_H
#include <string>
#include <vector>

#define LICENSE_CSV_HEADER "Name;LicenseKey;AllowedUsers;RedeemedUsers;AllowedMacs"

struct License {
  std::string Name;
  std::string LicenseKey;
  int AllowedUsers;
  int RedeemedUsers;
  std::vector<std::string> AllowedMacs;

  static License fromString(const std::string &licenseString);
  std::string toString() const;

  static std::vector<License> fromFile(const std::string &filePath);
};


#endif //C_KCY_ACCOUNTING_LICENSE_H