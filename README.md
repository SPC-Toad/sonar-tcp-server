# Arduino Sonar System with C Lang TCP Server

## Overview

This project implements a server that receives data from an Arduino-based sonar system, logging the distance and angle of detected objects. The system is designed to monitor the environment and record the presence of foreign entities.

## Features

- **Real-time Monitoring:** The server receives real-time data from the sonar system.
- **Data Logging:** Captures and logs distance and angle information to `distance_log.txt`.
- **Client-Server Architecture:** Uses TCP/IP to establish a connection between the server and the Arduino client.

## Installation

To set up the project locally, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/SPC-Toad/sonar-tcp-server.git
    ```
2. Navigate to the project directory:
    ```bash
    cd sonar-tcp-server
    ```

## Usage

1. **Set Your IP Address:**
    - Ensure you use your current device’s IP address, not the loopback address (localhost / 127.0.0.1).
    - To find your IP address:
        - **Windows:**
            ```sh
            ipconfig
            ```
        - **Linux:**
            ```sh
            ifconfig
            ```
    - Typically, it will be in the format `192.168.xx.xx`.

2. **Configure Network Details:**
    - In `server.c`, update line 48 with your IP address. When starting the server, provide a port number.
    - In `sonar.ino`, fill in the following:
        - Your Wi-Fi SSID
        - Your Wi-Fi password
        - The IP address and port number (must match the server configuration).

3. **Compile and Run the Server:**
    - Use the provided Makefile to compile and manage the server:
        ```sh
        // Compile the server
        make server
        // Start the server on port 7777 (or any other port)
        ./server 7777
        // Clean up compiled files
        make clean
        ```

Make sure the Arduino sonar system is correctly set up and ready to connect to the server.

## How It Works

The server runs on a specified IP address and port, listening for incoming connections from the Arduino sonar client.

1. **Server Initialization:** The server is set up to listen on the specified IP address and port.
2. **Client Connection:** The Arduino sonar acts as a client, establishing a connection with the server.
3. **Data Transmission:** Once connected, the sonar takes readings of the surrounding environment, including the distance and the degree of detection.
4. **Data Logging:** The server receives this data and records it into the `distance_log.txt` file, capturing both the distance and the angle at which the object was detected.

## Logs

The `distance_log.txt` file contains entries in the following format:

```
[YYYY-MM-DD HH:MM:SS] Distance @Degree°
```

For example:
```
[2024-08-21 18:06:51] 16.33 @42°
[2024-08-21 18:06:51] 36.53 @44°
```

These logs help you track the detected objects' distance and angle over time.

## Test Run

Here’s an example run. Please note this is my first video recorded on my phone, and I'm on a budget crunch!
https://github.com/user-attachments/assets/c34c284a-3a42-4dd9-9a7d-55c177a8eef7


