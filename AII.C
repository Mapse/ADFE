

#include <TGClient.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>
#include <RQ_OBJECT.h>
#include "Moeda.h"
#include <TSystem.h>
#include <fstream>
#include "Dadosfisg.h"

// Classe para a formação da janela.
class MyMainFrame {
   RQ_OBJECT("MyMainFrame")
private:
   TGMainFrame         *fMain;
   TString save_name;
public:
   MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
   virtual ~MyMainFrame();
   
   // Botões para cada conjunto de diagrama.
   void Histogramas();
   void Dispersao_pa();
   void Dispersao_moeda();
   
};

MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h) {
   // Create a main frame
   fMain = new TGMainFrame(p,w,h);

   // Definição dos botões. 
   TGHorizontalFrame *hframe = new TGHorizontalFrame(fMain,300,40);
   TGTextButton *draw = new TGTextButton(hframe,"Histogramas");
   TGTextButton *draw2 = new TGTextButton(hframe,"Diag. dispers.");
   TGTextButton *draw3= new TGTextButton(hframe,"Diag. dispers. moeda");

   // Desenho dos botões
   draw->Connect("Clicked()","MyMainFrame",this,"Histogramas()");
   draw2->Connect("Clicked()","MyMainFrame",this,"Dispersao_pa()");
   draw3->Connect("Clicked()","MyMainFrame",this,"Dispersao_moeda()");

   hframe->AddFrame(draw, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   hframe->AddFrame(draw2, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   hframe->AddFrame(draw3, new TGLayoutHints(kLHintsCenterX,5,5,3,4));

   // Botão para fechar a janela principal.
   TGTextButton *exit = new TGTextButton(hframe,"Sair","gApplication->Terminate(0)");
    
   hframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

   // Nome da janela principal.
   fMain->SetWindowName("ADFAE- Atividade-II");

   // Mapeia todos os botões a janela principal.
   fMain->MapSubwindows();

   // Criação do layout.
   fMain->Resize(fMain->GetDefaultSize());

   // Traça a janela principal.
   fMain->MapWindow();
}

//Desenha os histogramas de idade, massa e altura chamando a função Primtre do cabeçalho Dadosfisg.h
void MyMainFrame::Histogramas() {
    Primtre();
}

//Desenha os diagramas de dispersão chamando a função dispersao do cabeçalho Dadosfig.h
void MyMainFrame::Dispersao_pa() {
   dispersao();
}

//Desenha o diagrama de dispersão da moeda chamando a função grafdisp do cabeçalho Moeda.h.
void MyMainFrame::Dispersao_moeda() {
   grafdisp();
}

MyMainFrame::~MyMainFrame() {
   // Limpa tudo
   fMain->Cleanup();
   delete fMain;
}
void AII() {
   // Popup the GUI...
   new MyMainFrame(gClient->GetRoot(),800,600);
}