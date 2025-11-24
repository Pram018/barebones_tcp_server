# Barebones TCP Server

A minimal TCP server implemented in C++ using low-level socket programming.
This project was created during my networking and socket-programming learning phase, focusing on understanding how TCP communication works at a fundamental level.

##Environment

* **Operating System:** Pop!_OS (Ubuntu-based)
* **Language:** C++
* **Build System:** CMake
* **Dependencies:** Standard POSIX socket libraries (available by default on Linux)

---

##Project Structure

barebones_tcp_server/
├── build/             
├── CMakeLists.txt       
├── README.md            
└── src/
    └── main.cpp         


#Build & Run Instructions

###Requirements
* g++ or gcc (minimum 12.3.0)  
* Cmake (4.2.0)


### 1.Clone the repository

```bash
git clone https://github.com/Pram018/barebones_tcp_server.git
cd barebones_tcp_server
```

### 2.Build the project

```bash
mkdir build && cd build
cmake ..
make
```

### 3.Run the server

```bash
./bin/tcp_server
```

### 4.Test the server

You can use `netcat` or a custom client:

```bash
telnet localhost 54000
```



