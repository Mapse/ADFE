

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


class MyMainFrame {
   RQ_OBJECT("MyMainFrame")
private:
   TGMainFrame         *fMain;
   TRootEmbeddedCanvas *fEcanvas;
   TString save_name;
public:
   MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
   virtual ~MyMainFrame();
   void DoDraw();
   void DoDraw2();
   void DoDraw3();
   //void Save();
};

MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h) {
   // Create a main frame
   fMain = new TGMainFrame(p,w,h);

   // Create canvas widget
   fEcanvas = new TRootEmbeddedCanvas("Ecanvas",fMain,4,4);
   fMain->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX |
                   kLHintsExpandY, 10,10,10,1));
   // Create a horizontal frame widget with buttons
   TGHorizontalFrame *hframe = new TGHorizontalFrame(fMain,300,40);
   TGTextButton *draw = new TGTextButton(hframe,"Histogramas");
   TGTextButton *draw2 = new TGTextButton(hframe,"Diag. dispers.");
   TGTextButton *draw3= new TGTextButton(hframe,"Diag. dispers. moeda");

   draw->Connect("Clicked()","MyMainFrame",this,"DoDraw()");
   draw2->Connect("Clicked()","MyMainFrame",this,"DoDraw2()");
   draw3->Connect("Clicked()","MyMainFrame",this,"DoDraw3()");

   hframe->AddFrame(draw, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   hframe->AddFrame(draw2, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   hframe->AddFrame(draw3, new TGLayoutHints(kLHintsCenterX,5,5,3,4));

   TGTextButton *exit = new TGTextButton(hframe,"Sair","gApplication->Terminate(0)");
   //TGTextButton *save = new TGTextButton(hframe, "Salvar");
  //save->Connect("Clicked()","MyMainFrame",this,"Save()");
   
   //hframe->AddFrame(save, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   hframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

   // Set a name to the main frame
   fMain->SetWindowName("ADFAE- Atividade-II");

   // Map all subwindows of main frame
   fMain->MapSubwindows();

   // Initialize the layout algorithm
   fMain->Resize(fMain->GetDefaultSize());

   // Map main frame
   fMain->MapWindow();
}

//Desenha os histogramas de idade, massa e altura.
void MyMainFrame::DoDraw() {
   // Draws function graphics in randomly chosen interval
   TCanvas *fCanvas = fEcanvas->GetCanvas();
   fCanvas->Clear();
   fCanvas->Divide(2,2);
   save_name = "Histogramas.jpeg";
   Primtre();
   fCanvas->cd();
   fCanvas->Update();
}

//Desenha os diagramas de dispersão.
void MyMainFrame::DoDraw2() {
   // Draws function graphics in randomly chosen interval
   TCanvas *fCanvas = fEcanvas->GetCanvas();
   fCanvas->Clear();
   save_name = "Diagrama de dispersão.jpeg";
   //Descomentar linha abaixo para gerar uma distribuição nova de moedas.
   //retorna();
   dispersao();
   fCanvas->cd();
   fCanvas->Update();
}

//Desenha o diagrama de dispersão da moeda
void MyMainFrame::DoDraw3() {
   // Draws function graphics in randomly chosen interval
   TCanvas *fCanvas = fEcanvas->GetCanvas();
   fCanvas->Clear();
   save_name = "Diagrama de dispersão - moeda.jpeg";
   //Descomentar linha abaixo para gerar uma distribuição nova de moedas.
   //retorna();
   grafdisp();
   fCanvas->cd();
   fCanvas->Update();
}

/* void MyMainFrame::Save() {
   TCanvas *fCanvas = fEcanvas->GetCanvas();
   fCanvas->Print(save_name);
} */

MyMainFrame::~MyMainFrame() {
   // Clean up used widgets: frames, buttons, layout hints
   fMain->Cleanup();
   delete fMain;
}
void GUI() {
   // Popup the GUI...
   new MyMainFrame(gClient->GetRoot(),800,600);
}