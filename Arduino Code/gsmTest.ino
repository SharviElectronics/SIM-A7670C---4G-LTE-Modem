#include <SoftwareSerial.h>

SoftwareSerial SIMCOM(2, 3); // RX, TX

void setup() {
  // Start the serial communication with the computer (for debugging)
  Serial.begin(9600); // Communication with PC

  // Start communication with the SIMCom A7670C-LNNV module (using Serial1 or the appropriate port)
  SIMCOM.begin(9600); // Communication with module (make sure the baud rate is set correctly)

  // Wait for a second to let the serial ports initialize
  delay(1000);

  // Test the module by sending the AT command
  sendATCommand("AT");  // Basic command to test if module responds
  delay(2000);

  // Check signal strength with the +CSQ command
  sendATCommand("AT+CSQ");  // Command to check signal strength
  delay(2000);

  // Check registration status with the +CREG? command
  sendATCommand("AT+CREG?");  // Command to check network registration status
  delay(2000);

  // Check operator with the +COPS? command
  sendATCommand("AT+COPS?");  // Command to query the current network operator
  delay(2000);
  
  // Test if the module is connected to the network and ready for data transmission
  sendATCommand("AT+CGATT?");  // Command to check network attachment status
}

void loop() {
  // Continuously read data from the SIMCom module and output it to the serial monitor
  if (SIMCOM.available()) {
    String response = SIMCOM.readString();
    Serial.println("Module Response:");
    Serial.println(response);
  }

  // You can add more commands to test other features as needed
}

// Function to send an AT command and print the result
void sendATCommand(String command) {
  SIMCOM.println(command);   // Send command to module
  Serial.print("Sent: ");
  Serial.println(command);    // Print the command sent
  Serial.println("Waiting for response...");
  delay(1000);
}
