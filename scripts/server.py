import socket
import json
import argparse


def handle_json_rpc_request(request):
    try:
        request_data = json.loads(request)
        params = request_data.get('params', None)

        if params is None:
            return json.dumps({
                "jsonrpc": "2.0",
                "error": {
                    "code": -32602,
                    "message": "Invalid rpc: missing params."
                },
                "id": request_data.get('id', None)
            })
        response = {
            "jsonrpc": "2.0",
            "result": params,
            "id": request_data.get('id', None)
        }
        return json.dumps(response)

    except json.JSONDecodeError:
        return json.dumps({
            "jsonrpc": "2.0",
            "error": {
                "code": -32700,
                "message": "Parse error"
            },
            "id": None
        })


def start_server(host='localhost', port=5000):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)
    print(f"Server listening on {host}:{port}")

    while True:
        client_socket, client_address = server_socket.accept()
        print(f"Connection established with {client_address}")

        try:
            data = client_socket.recv(1024)
            if data:
                print(f"Received JSON-RPC message: {data.decode('utf-8')}")

                response = handle_json_rpc_request(data.decode('utf-8'))
                print(f"Sending response: {response}")

                client_socket.sendall(response.encode('utf-8'))
            else:
                print("No data received from client.")

        except Exception as e:
            print(f"Error: {e}")

        finally:
            client_socket.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Start a JSON-RPC server.')
    parser.add_argument('--host', type=str, default='localhost',
                        help='The host address to bind the server to (default: localhost)')
    parser.add_argument('--port', type=int, default=5000,
                        help='The port number to bind the server to (default: 5000)')

    args = parser.parse_args()

    start_server(host=args.host, port=args.port)
