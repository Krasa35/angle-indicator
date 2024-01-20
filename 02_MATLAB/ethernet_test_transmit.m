% Create a UDP socket object
u = udpport;

% Change the message to "123" and send it to the specified destination IP and port
write(u, "123", "char", "192.168.113.5", 25565);

% For future writes to the same destination address and port for the udpport object u,
% you can omit the destinationAddress and destinationPort arguments.

% Write a vector of single values to the last used destinationAddress and destinationPort
write(u, 1:10, "single");

% Close the UDP socket when done
delete(u);
