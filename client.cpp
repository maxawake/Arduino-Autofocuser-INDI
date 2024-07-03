#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Client {
public:
    int sock;
    // Server address
    struct sockaddr_in server_address;
    Client(const std::string& ip_address, int port) {
        // Create a socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            std::cerr << "Failed to create socket" << std::endl;
            return;
        }

        // Server address
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);
        inet_pton(AF_INET, ip_address.c_str(), &server_address.sin_addr);

        // Connect to the server
        if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
            std::cerr << "Failed to connect to server" << std::endl;
            close(sock);
            return;
        }
    }

    ~Client() {
        // Close the socket
        close(sock);
    }

    void send_data(const std::string& message) {
        send(sock, message.c_str(), message.size(), 0);
    }

    std::string receive_data() {
        char buffer[1024];
        ssize_t bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            return std::string(buffer);
        }
        return "";
    }
};

int main() {
    // Create a client
    Client client("127.0.0.1", 12346);
    // Send data to the server
    client.send_data("1");
    // Receive data from the server
    std::string received = client.receive_data();
    std::cout << "Received from server: " << received << std::endl;
}
