#include "ihm_drone.h"
#include "ui_ihm_drone.h"

#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

IHM_Drone::IHM_Drone(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IHM_Drone)
{
    ui->setupUi(this);
}

IHM_Drone::~IHM_Drone()
{
    delete ui;
}




void IHM_Drone::on_pushButton_clicked()
{
    HANDLE portaSerial; // Ponteiro para porta
    DCB dadosSerial; // Estrutura para configuração
    string nomeporta = "COM3"; // Nome da porta (COMXX)
    // Pode ser utilizado strings padrão C
     nomeporta = "\\\\.\\" + nomeporta;
    // Abrindo a porta
    portaSerial = CreateFileA(nomeporta.c_str(), GENERIC_READ | GENERIC_WRITE,
                              0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if(portaSerial == INVALID_HANDLE_VALUE){ // Testa se conseguiu abrir
        cout << "Problemas na abertura da porta...";
    }
     // Configurando porta serial
     SecureZeroMemory(&dadosSerial, sizeof(DCB)); // Cria estrutura nula
     dadosSerial.DCBlength = sizeof(DCB);
     if(!GetCommState(portaSerial,&dadosSerial)){ // Testa sucesso na obtenção dos dados da porta
        cout << "Problemas na obtencao dos parametros da porta..." << endl;;
     }
     dadosSerial.BaudRate = CBR_9600; // Configura Baud em 9600
     dadosSerial.ByteSize = 8; // 8 Bits por dado
     dadosSerial.Parity = NOPARITY; // Paridade (sem paridade)
     dadosSerial.StopBits = ONESTOPBIT; // Um bit de parada
     if(!SetCommState(portaSerial, &dadosSerial)) // Testa sucesso na conf.
     {
     cout << "Problemas ao alterar as configuracoes da porta..." << endl;;

     }
     PurgeComm(portaSerial, PURGE_RXCLEAR | PURGE_TXCLEAR); // Limpa buffers
     Sleep(1500); // Aguarda Arduino retornar do reset

     // Serial pronta para uso!
     cout << "Serial Configurada!" << endl;


     DWORD dadosEscritos;
      unsigned char x = 0;
      while(x<250)
      {
      WriteFile(portaSerial, &x, 1, &dadosEscritos, NULL);
      x++;
      Sleep(50);
      }

     // Fecha a porta após o uso
     CloseHandle(portaSerial);

     }

