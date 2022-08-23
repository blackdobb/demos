# How to build
```sh
mkdir build
cd build
cmake ..
cmake --build .
```
# How to use CPP to build a simple socket server and client

## What's expected
ECHO server: which means send back any received message/data intact.
Client: read and send a string entered by users to server, then print received data.

## Server

According to the requirement, we could know server should be like:

``` 
while(true) {
    buff = received data;
    send buff back;
}
```
Obviously, we omitted the connecting and the disconnecting process of the network in this pseudo-code.
In this case, we choose TCP for connecting, in a completed TCP, the server and client should finish the following things:
* Connection between server and client.
* Data transfer in server and client.
* Disconnection between server and client.

Adding these premises to the pseudo-code, we can get the following pseudo-code:
```
while(true) {
    establish connection to client;
    buff = the data received0 from client;
    send buff back;
    Disconnect with client;
}
```

### How to establish a connect
In socket programming, the server and client connected by socket, before connected, server should do the following things:
* create a socket. socket()
* Bind the socket to the specified ip + port. bind()
* Let socket listen for request at the bound port (waiting for client connect to the port). listen()

After client sent the connection request and connected successfully, accept(), server will get the client socket, so all the data sending and receiving could be done on this client's socket.

socket(): needs three arguments, socket(domain, socket type, protocol), two processes can communicate each other only if their sockets are of the same type and in the same domain.

#### domain
There are two widly used address domain, the unix domain and the Internet domain.
* unix domain: for two processes which share a common file system communicate. The symbol constant **AF_UNIX** is used for the unix domain.
* Internet domain: for any two hosts on the Internet. **AF_INET** for Internet 
* There are actually many other options which can be used here for specialized purposes.

#### socket type
The second argument is the type of socket. Recall that there are two choices here: SOCK_STREAM and SOCK_DGRAM: 
* SOCK_STREAM: a stream socket in which characters are read in a continuous stream as if from a file or pipe
* SOCK_DGRAM: a datagram socket, in which messages are read in chunks.


#### protocol
The third argument is the protocol. If this argument is zero (and it always should be except for unusual circumstances), the operating system will choose the most appropriate protocol. It will choose TCP for stream sockets and UDP for datagram sockets.

### Send and Receive data
* Send data: using socket to get the data send by client, and save it to buffer. recv()
* Receive data: send back the data in buff using socket.
* Disconnect after send and receive. Disconnect by only close the client socket.

After all this done, we could see the pseudo-code as shown below:
```
sockfd = socket();    // create a socket
bind(sockfd, ip::port and some config);    // bind the ip+port, config the connection type etc..
listen(sockfd);        // listen to the bound port
while(true)
{
    connfd = accept(sockfd);    // waiting for the connection from the client until success，it will return the client socket.
    recv(connfd, buff); // receive the data from client, and put it to buffer.
    send(connfd, buff); // send back the data to client
    close(connfd);      // Disconnect with client.
}
```


## Client

The responsible for client:
* Create socket
* Using socket and the known server ip+port to connect the server.
* Receive and send data.
* Close connection.

The pseudo-code will be:
```
sockfd = socket(); // create a socket.
connect(sockfd, ip::port and some config); // initiate a connection using specified ip+port.
scanf("%s", buff); // reading the input from users.
send(sockfd, buff); // send data to server.
recv(sockfd, buff); // receive data from server.
close(sockfd); // disconnect with server.
```



# sockect