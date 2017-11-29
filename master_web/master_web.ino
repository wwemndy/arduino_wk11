/*
 * This program runs on Linkit7697 as a I2C master
 */

#include <Wire.h>
#include <LWiFi.h>

const int SLAVE_ADDRESS = 1;
char ssid[] = "aa";  
char pass[] = "fish_egg_roll";
int keyIndex = 0;

int status = WL_IDLE_STATUS;
WiFiServer server(80);
String webSite = "";

void setup() {
  Wire.begin();
  Serial.begin(9600);
  buildWeb();
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print(webSite);

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.startsWith("GET /F")) {
          Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("F");
          Wire.endTransmission();
        }
        if (currentLine.startsWith("GET /R")) {
          Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("R");
          Wire.endTransmission();
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}
/*
void buildWeb(){
  webSite += "<html>";
  webSite +="<head>\n";
  webSite +="<meta charset='UTF-8'/>\n";
  webSite +="<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  webSite +="<title>Remote Motor Control</title>\n";
  webSite +="<style>";
  webSite +="html{background-color:#e5e9dc;font-family:sans-serif;}";
  webSite +=".title{text-align:center;color:darkblue;}";
  webSite +="a{display:block;text-decoration:none;background-color:lightgray;";
  webSite +="width:150px;text-align:center;margin:0 auto;margin-bottom:30px;font-size:2em;}";
  webSite +=".btn1{background-color:black;color:white;}";
  webSite +=".btn2{background-color:white;color:black;}";
  webSite +="</style>";
  webSite +="</head>\n";
  webSite += "<body>";
  webSite += "<h1 class=\"title\">Remote Motor Control</h1>";
  webSite += "<a class=\"btn1\" href=\"/F\">180</a>";
  webSite += "<a class=\"btn2\" href=\"/R\">-0-</a>";
  webSite += "</body></html>";
}*/

void buildWeb(){
  webSite +="<!DOCTYPE html>" ;
  webSite += "<html>";
   webSite += "<head>";
   webSite += "<meta charset=\"utf-8\">";
   webSite +="<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
   webSite += "<title>IOT Controler</title>";
   webSite += "<link href=\"https://fonts.googleapis.com/css?family=Caveat\" rel=\"stylesheet\">";
   webSite += "<style media=\"screen\">";
   webSite += "*{font-family: Caveat;font-size: 45px;box-sizing: border-box;}";
   webSite += ":link, :visited{color: #fe7701;text-decoration: none;}";
   webSite += "body{background-image: url(\"http://www.kanahei.com/upload/2013/06/01_g_1024_768.jpg\");background-repeat: no-repeat;background-size: cover;}";
   webSite += "main{width: 700px;height: 250px;padding: 10px;margin: 40px auto;}";
   webSite += ".btn_div{width: 300px;margin: 20px auto;}";
   webSite += ".botton{display: inline;width: 110px;padding: 0px 30px;margin: 10px auto;background-color: rgba(255, 255, 255, 0.8);";
   webSite += "  border-radius: 3px;box-shadow: 5px 5px rgba(80, 80, 80, 0.3);}";
   webSite += "#text{width: 600px;height: 100px;margin: 10px auto;padding: 0px 40px;color: rgb(75, 75, 75);}";
   webSite += "#on{float: left;color: rgb(22, 174, 153);}";
   webSite += "#off{float: right;color: rgb(236, 80, 80);}";
   webSite += "</style>";
   webSite += "</head>";
   webSite += "<body>";
   webSite += "<main>";
   webSite += "<div id=\"text\">Click Here to control your Motor :)</div>";
   webSite += "<div class=\"btn_div\">";
   webSite += "<a href=\"/F\" class=\"botton\" id=\"on\">Left</a>";
   webSite += "<a href=\"/R\" class=\"botton\" id=\"off\">Right</a>";
   webSite += "</div>";
   webSite += "</main>";
   webSite += "</body>";
   webSite += "</html>";
 }

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
