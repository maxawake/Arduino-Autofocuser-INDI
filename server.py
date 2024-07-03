import socket
from stepper_driver import AutoFocuser

class AutoFocuserServer:
    def __init__(self, host, port):
        # Create a socket object
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Get local machine name
        self.host = host
        self.port = port

        # Bind to the port
        self.server_socket.bind((host, port))

        # Start listening for connections
        self.server_socket.listen(5)

        print(f"Server started at {host}:{port}")

        self.arduino = AutoFocuser()

    def listen(self):
        try:
            while True:
                # Establish a connection
                client_socket, addr = self.server_socket.accept()
                print(f"Got a connection from {addr}")

                # Receive data from the client
                data = client_socket.recv(1024).decode("utf-8")
                print(f"Received: {data}")

                self.arduino.write_read(data)

                # Send a response back to the client
                response = "69420"
                client_socket.send(response.encode("utf-8"))

                # Close the connection
                client_socket.close()
        except KeyboardInterrupt:
            print("\nServer stopped")
            # close the server
            self.server_socket.close()
            exit(0)

    def close(self):
        self.server_socket.close()
        print("Server closed")


if __name__ == "__main__":
    server = AutoFocuserServer("localhost", 12346)
    server.listen()
