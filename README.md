# IrrigaFácil: Sistema de irrigação automatizado
Este é um projeto de irrigação automatizada que envia status em tempo real da planta.

##Para reproduzir ele você vai precisar:
 - 1 Nodemcu V3 Esp8266 ESP-12E Iot com WiFi;
 - 1 Sensor de Umidade de Solo para Arduino;
 - 1 Mini Bomba de Água Peristáltica para Projetos - AB11;
 - 1 Módulo Relé 5V 10A 2 Canais com Optoacoplador;
 – ½ Metro de Fio Paralelo 0,5mm;
 – 1,5 Metros de Mangueira para Aquário;
 - Alguns jumpers;
 - Fonte 12V.
 
 Tendo conseguido os itens, siga o diagrama da imagem "Esquema-projeto.png" dentro da pasta "imagens e diagramas". Com o projeto montado instale a opção de placa NodeMCU em sua IDE do Arduino e a biblioteca [pubsubclient](https://github.com/knolleary/pubsubclient). Baixe código substitua as constates SSID pelo nome do seu WiFi e a password pela senha dele para conectar a sua placa NodeMCU ao WiFi. Altere em seguida os defines TOPICO_SUBSCRIBE, TOPICO_PUBLISH e ID_MQTT para que não haja duplicatas no brooker. E rode o programa.
