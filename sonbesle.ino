#include <SPI.h>
#include <Ethernet.h>
#include<Servo.h>

Servo ser;
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //ethernet modülün mac adresi
byte ip[] = { 192, 168, 1, 178 };                      // yerel ağ içerisinde kullanabileceğiniz ip adresi örneğin ("192.168.1.178")
byte gateway[] = { 192,168,1,1 };                   // vereceğiniz ip nin ilk değerinden sonra iki tane 0 ve sona 1 vermeniz yeterli
byte subnet[] = { 255, 255, 255, 0 };                  // bu ayarları ip4 üzerinden manuel yapmanız gerektiğine dikkat edin
EthernetServer server(80);                             //haberleşeceğimiz port adresi
String readString;                                // tarayıcı üzerinden göndereceğimiz string (dizi) tanımlaması
void setup() {
Ethernet.begin(mac, ip, gateway, subnet); // ethernet başlatıldı
server.begin(); // sunucu başlatıldı
ser.attach(7);
}
 
void loop() {
EthernetClient client = server.available(); // sunucu mevcutken ethernet kullanıcısı tanımlandı
if (client) {
while (client.connected()) { // kullanıcı bağlıyken
if (client.available()) { // ve de mevcutken
char c = client.read();  // kullanıcı isteğini okuyup karakter c ye eşitleme
 
if (readString.length() < 100) { // tarayıcıdan gelecek olan istek karakter olarak okunup
readString += c; // string (diziye) kaydediliyor
//Serial.print(c); // isterseniz serial monitörden çift // kaldırarak görüntüleyebilirsiniz
}
if (c == '\n') { // http isteği sonlanması
 
client.println("HTTP/1.1 200 OK"); //send new page
client.println("Content-Type: text/html");
client.println();
client.println("<HTML>");
client.println("<HEAD>");
client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
client.println("</HEAD>");
client.println("<BODY>");
client.println("<H1>Evcil Hayvan Besleyici</H1>");
client.println("<a href=\"/?button1on\"\">BESLE</a>");
client.println("<br />");
client.println("<hr />");
client.println("<br />"); 
client.println("</BODY>");
client.println("</HTML>");
 
delay(1);
 
client.stop(); // kullanıcı sonlandırma
 
if (readString.indexOf("?button1on") > 0) {
  ser.write(180);
  delay(2000);
  ser.write(-180);
  delay(2000);



}

 
readString = ""; // bi sonra ki okuma için temizleme işlemi
 
}
}
}
}
}
