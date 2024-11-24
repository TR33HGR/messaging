import argparse
import socket
import time


def run_client(server_address, server_port):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        client_socket.connect((server_address, server_port))
        print(f"Connected to server at {server_address}:{server_port}")

        while True:
            try:
                message = "ping"
                print(f"Sending: {message}")
                client_socket.sendall(message.encode('utf-8'))

                response = client_socket.recv(1024)
                if response:
                    print(f"Received: {response.decode('utf-8')}")
                else:
                    print("No response from server. Server may have disconnected.")
                    break

                time.sleep(5)

            except KeyboardInterrupt:
                print("\nClient is shutting down...")
                break

    except ConnectionRefusedError:
        print(f"Failed to connect to server at {server_address}:{server_port}.")
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        # Close the socket connection
        client_socket.close()
        print("Disconnected from the server.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Start a JSON-RPC server.')
    parser.add_argument('--host', type=str, default='localhost',
                        help='The host address of the server to (default: localhost)')
    parser.add_argument('--port', type=int, default=5000,
                        help='The port number of the server to (default: 5000)')

    args = parser.parse_args()

    run_client(args.host, args.port)
