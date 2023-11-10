# Clean Drain device by dreamClean
![LogoDreamClean](/logo.png)

## O projeto
O Clean Drain é um tipo de bueiro inteligente, criado com o propósito de ser instalado onde a água de chuva e o lixo da rua escoam. Ele mede a quantidade de lixo em kg e o volume no bueiro. Com a ajuda do FIWARE, estamos implementando IoT para enviar as medidas coletadas dos sensores para o nosso site de monitoramento.

## Arquitetura do projeto
![DraftArquitetura](/draftArquiteturaProposta.png)

- Dispositivos:
  - Esp32
  - Sensor de proximidade ultrassônico HC-SR4
  - Célula de carga (50kg) com módulo HX711
