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

/*
 /*
 public class LicenseServer
{
    private const int Port = 4053;
    private const string LicenseFile = "licenses.json";
    private const string Version = "1.0.0";

    public static void Main()
    {
        var ipAddress = IPAddress.Parse("urip");
        TcpListener server = new TcpListener(ipAddress, Port);
        server.Start();
        Console.WriteLine($"[Server] Listening on port {Port}...");

        while (true)
        {
            TcpClient client = server.AcceptTcpClient();
            using NetworkStream stream = client.GetStream();

            byte[] buffer = new byte[256];
            int bytesRead = stream.Read(buffer, 0, buffer.Length);
            string received = Encoding.UTF8.GetString(buffer, 0, bytesRead).Trim();

            if (string.IsNullOrEmpty(received))
            {
                Console.WriteLine("[Server] Leere Nachricht empfangen.");
                client.Close();
                continue;
            }

            if (received.Equals("getversion", StringComparison.OrdinalIgnoreCase))
            {
                Console.WriteLine($"[Server] Client requested version.");
                byte[] versionResponse = Encoding.UTF8.GetBytes(Version);
                stream.Write(versionResponse, 0, versionResponse.Length);
                client.Close();
                continue;
            }

            // Nachricht aufsplitten: "LICENSEKEY-MACADRESSE"
            var parts = received.Split('-', 2);
            if (parts.Length != 2)
            {
                Console.WriteLine("[Server] Ungültiges Nachrichtenformat. Erwartet: LICENSEKEY-MACADRESSE");
                client.Close();
                continue;
            }

            string licenseKey = parts[0];
            string macAddress = parts[1];

            Console.WriteLine($"[Server] Received licenseKey: {licenseKey}, MAC: {macAddress}");

            bool isValid = ValidateLicense(licenseKey, macAddress);

            byte[] response = Encoding.UTF8.GetBytes(isValid.ToString().ToLower());
            stream.Write(response, 0, response.Length);
            client.Close();
        }
    }

    private static bool ValidateLicense(string key, string mac);
}
 */

#endif //C_KCY_ACCOUNTING_LICENSESERVER_H
