# Building
# Requirements
- This project uses [CMake 3.29.2](https://cmake.org/download/).
- This project is currently **Windows only** (sorry)
## Setup
To setup, make a `build` directory & from it run:
```
cmake ..
```
To include unit tests, instead run:
```
cmake .. -DBUILD_TESTS=ON
```
## Actually building
From the `build` directory, run:
```
cmake --build .
```
## Actually running tests
To run tests, after building, while still in the `build` directory, run:
```
ctest --output-on-failure
```
**You will need to rebuild if you want to test new changes.**

# Running
This project produces 2 executables: `client.exe` & `server.exe`. After building, these will be found in the `build/src/Debug` directory.
## client.exe
To run the client, run:
```
./client.exe <username> <server ip>:<server port>
```
If it can't find a server, you will get an error & the client will exit:
```
Client: connect() - Failed to connect: 10061
```
Once running, you will be prompted to input your messages in the command line:
```
Input a message to send...
```
You will then see your message printed with your `<username>`, along with messages from other clients connected to the server:
```
i just need to document things now
tr33hgr: i just need to document things now
nathan: good 4 u
```
## server.exe
To run the server, run:
```
./server.exe <server ip>:<server port>
```
where `<server ip>` will likely be either `127.0.0.1` or the current ip of you device.

You will see an error printed every time a client disconnection. Don't worry, this just means the connection has gone down:
```
Server recv error: 10054
```
## Known problems
Neither `server.exe` or `client.exe` like `localhost` as an address.

# Notes
I used this as a opportunity to play around with `std::futures` & their associated components, as it isn't something I've used a lot. I think I've used them well for the most part, but the occasions where I use `std::async(...)` to send messages, but don't capture the future, doesn't seem correct. I couldn't find another way to express an asynchronous call that I didn't want to wait on.

You will see there are some python script for  a server & client. These were used for testing in the beginning, but are not very good. **They do not respond to SIGINT!** You will have to kill python to stop them running, so I would just ignore them.
## Assumptions / Missing Requirements
- I don't have access to a Linux machine & my WSL has decided to not work, hence I have used Windows sockets instead of BSD ones. Hopefully I have abstracted them enough to see how they could be easily replaced.

- I have also used CMake instead of Makefiles. This should be more platform agnostic and work as long as you have CMake & any C++ Compiler installed. (I also thought I saw CMake as either a task or job requirement, but it's my bad for not checking)

- I didn't see any need for any kind of concurrency outside of C++ methods, so ignored the POSIX concurrency primitives requirement.

## Things I wanted to add
- I wanted the server to be able to Multicast the messages it receives, but I ran out of time to play with that.

- I wanted to unit test the client & server classes, but I ended up fighting the threading and ran out of time.
