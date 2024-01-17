% Define the IP address and port to listen on
destIP = '192.168.1.2';  % Replace with the actual IP address of your STM32
destPort = 1234;         % Replace with the actual port used by your STM32

% Create a UDP object
udpObj = udp(destIP, destPort, 'LocalPort', 1235);  % LocalPort is the port MATLAB listens on

% Set properties for the UDP object
set(udpObj, 'Timeout', 10);  % Set timeout in seconds

% Open the UDP connection
fopen(udpObj);

try
    % Receive and display messages continuously
    while true
        % Check if there are bytes available to read
        if udpObj.BytesAvailable > 0
            receivedData = fread(udpObj, udpObj.BytesAvailable, 'char');
            disp(['Received message: ', char(receivedData')]);
        end
    end
catch ME
    % Close the UDP connection on error or when done
    fclose(udpObj);
    rethrow(ME);
end
