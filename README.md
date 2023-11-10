# Clean Drain device by dreamClean
![LogoDreamClean](/logo.png)
## Sumário
- [O projeto](#o-projeto)
- [Arquitetura do projeto](#arquitetura-do-projeto)
- [Dispositivos](#dispositivos)
## O projeto
O Clean Drain é um tipo de bueiro inteligente, criado com o propósito de ser instalado onde a água de chuva e o lixo da rua escoam. Ele mede a quantidade de lixo em kg e o volume no bueiro. Com a ajuda do FIWARE, estamos implementando IoT para enviar as medidas coletadas dos sensores para o nosso site de monitoramento.

## Arquitetura do projeto
![DraftArquitetura](/draftArquiteturaProposta.png)

- Dispositivos:
  - Esp32
  - Sensor de proximidade ultrassônico HC-SR4
  - Célula de carga (50kg) com módulo HX711
  - fiação
  - Bateria 
## Recursos Necessários

- Esp32
- Sensor de proximidade ultrassônico HC-SR4
- Célula de carga (50kg) com módulo HX711
- Bateria recarregável
- Software Arduino IDE
- Bibliotecas necessárias (HX711.h,Wire.h,Wifi.h,PubSubClient.h,Ultrasonic.h)

### Imagem exemplificando o projeto montado 
![Imagem Arduino Montado](/Hardware.png)
### Código do arduino comentado
    Deve se alterar o SSID e a senha da rede como o projeto está no seu começo de desenvolvimento
![Codigo do arduino](/CleanDrain.ino)



