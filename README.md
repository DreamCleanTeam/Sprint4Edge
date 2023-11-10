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
[Link para Código Arduino](/CleanDrain.ino)
## Instalação

1. Clone este repositório.
2. Abra o arquivo [CleanDrain.ino](/CleanDrain.ino) na Arduino IDE.
3. Instale as bibliotecas necessárias usando o Gerenciador de Bibliotecas da Arduino IDE.
4. Configure o SSID e senha da rede, e o ID do seu dispostivo
5. Carregue o código para o Esp32.
## Configurações

No arquivo [CleanDrain.ino](/CleanDrain.ino), você pode configurar o seguinte:

- SSID e senha da rede WiFi.
- ID do dispositivo

## Melhorias Futuras

1. Estamos trabalhando para integrar a aba de monitoramento em nosso website
2. Futuramente pretendemos desenvolver um app mobile para notificar os valores no dispositivo
3. Após as outras funcionalidades estarem completas iremos começar o plano de monetizar vendendo dispositivos CleanDrain
4. Em caso de lucro, começaremos com o plano de um sistema de assinatura para que o lixo seja recolhido por nossos Colaboradores



