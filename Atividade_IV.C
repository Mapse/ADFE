#include <iostream>
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooGaussian.h"
#include "RooFitResult.h"
#include "TFile.h"
#include "TTree.h"


using namespace RooFit;
//Factory


void ex18(){
    
    // Criação do workspace.
    RooWorkspace w("w");

    // Criação da pdf com a ajuda da factory.
    w.factory("Gaussian::ga(x[-10, 10], med[1], err[2])");

    // Retira a pdf do worskpace para plotagem.
    RooAbsPdf *ga = w.pdf("ga");

    // Retira a variável x do workspace para criar o frame.
    RooRealVar *x = w.var("x");

    // Criação do conjunto de 1000 dados a partir da gaussiana.
    unsigned n = 1000;
    RooDataSet *data = ga->generate(*x,n);
    data->SetName("Gaussiana ex. 18");
    
    // Crição do frame.
    RooPlot *p = x->frame();
    p->SetTitle("Fit da gaussiana");
    p->SetYTitle("N#acute{u}mero de eventos / (0.2)");
    
    // Plotagem dos dados no frame p.
    data->plotOn(p);
    
    // Fitagem e plotagem da gaussiana.
    ga->plotOn(p);
    ga->fitTo(*data);
    
    p->Draw();

    // Inserindo os dados no workspace w.
    w.import(*data);

    // Printando o conteúdo do workspace.
    w.Print();

    // Criando o arquivo.
    w.writeToFile("ex18.root", true);
}

void ex19(){

    // Pega o arquivo ex18.root
    TFile *file = new TFile("ex18.root");

    //  O get pega um TObject e o (RooWorkspace*) converte para o que a gente quer.
    RooWorkspace *w = (RooWorkspace*) file->Get("w");

    // Pega a gaussiana que está no workspace do ex 18.
    RooAbsPdf *ga = w->pdf("ga");

    // Pega os dados.
    RooAbsData *da = w->data("Gaussiana ex. 18");

    // Criação do frame.
    RooPlot *p = w->var("x")->frame();
    p->SetTitle("Fitagem");
    p->SetYTitle("N#acute{u}mero de eventos / (0.2)");

    // Insere os dados no plot.
    da->plotOn(p);
    
    // Fita usando o Fumili e guarda o resultado no res.
    RooFitResult *res = ga->fitTo(*da, Save(true),Minimizer("Minuit2"), Range(0., 10.)); //RooFit::Range!!!!!!!
    // Insere a gausiana no frame.
    ga->plotOn(p);
    // Adiciona uma caixa com os valores dos parâmetros e erros no frame.
    
    ga->paramOn(p);
    p->Draw();

    w->Print();
    
    
}    

void ex20(){
    
    // Cria o arquivo ex20.root
    TFile *file = new TFile("ex20.root");

    // Cria a tree para pegar os dados de Hgg.txt
    TTree *tree = new TTree("tree", "tree");
    
    // Lê o arquivo e insere a quantidade de dados em nevents.
    unsigned nevents = tree->ReadFile("Hgg.txt", "x/D");
    
    // Cria o workspace
    RooWorkspace w("w");
    
    // Cria o número de dados do background com limites entre 0.1 * nevents e 10 * nevents.
    w.factory("nback[10000, 3077, 307700]");
    
    // Cria x em torno da média da massa so Higgs.
    w.factory("x[110, 150]");

    // Criação da exponencial do modelo com dois parâmetros.
    w.factory("a1[7.5, -500, 500]");
    w.factory("a2[-1.5, -500, 500]");
    w.factory("expr::za('-(a1*x/100 + a2*(x/100)^2)', a1, a2, x)");
    w.factory("Exponential::bg(za,1)");

    // Número de eventos so sinal.
    w.factory("nsig[100, 0, 1000]");

    // Massa e erro do modelo.
    w.factory("mass[130, 110, 150]");
    w.factory("err[1, 0.5, 5.]");
    
    // Cria a gaussiana do modelo.
    w.factory("Gaussian::sig(x, mass, err)");

    // Soma as gaussiana com a exponencial, incluindo o número de backgrounds e de sinal.
    w.factory("SUM::total(nsig*sig, nback*bg)");

    // Pega na factory de w os Objetos da gaussiana e da exponencial.
    RooAbsPdf *sinal = w.pdf("sig");
    RooAbsPdf *modelo = w.pdf("total");

    // Pega na factory de w o objeto x.
    RooRealVar *x = w.var("x");

    // Importa da tree os dados.
    RooDataSet data("data", "data", *x, Import(*tree));

    // Fita os dados com a função somada.
    RooFitResult *res = modelo->fitTo(data);
        
    // Pega o frame.
    RooPlot *p = x->frame();
    // Insere os dados no frame.
    data.plotOn(p);
    // Insere a função somada no frame.
    modelo->plotOn(p);
    // Pega a exponencial de background e plota com linhas tracejadas.
    modelo->plotOn(p, Components("bg"), LineStyle(kDashed));
    // Pega a gaussiana e plota com linha contínua vermelha.
    modelo->plotOn(p, Components("sig"), LineColor(kRed));


    p->Draw();
    

}

void roofitlearn(){

    // Criação do worskpace para guardar tudo.
    RooWorkspace w("w");

    // Criação das variáveis x, média e desvio padrão para a gaussiana.
    RooRealVar x("x", "x", -10, 10);
    RooRealVar med("med", "med", 5);
    RooRealVar err("sigma", "sigma", 3);

    // Criação da gaussiana com os parâmetros criados acima.
    RooGaussian f("f", "f", x, med, err);

    // Importando a gaussiana para o workspace.
    w.import(f);

    // Printar os elementos que estão no workspace na tela do root.
    w.Print();
 
    // Pegar as variavéis do workspace.
    // w.var("x") pega o x do workspace, ->frame() pega o frame pro plot.
    RooPlot * frame = w.var("x")->frame();

    // Pega a pdf (gausiana) do workspace e taca o ploton dela no frame.
    w.pdf("f")->plotOn(frame);

    // Escrevendo o arquivo.
    w.writeToFile("teste.root");

    // Botar pdf na factory. EXPR cria uma pdf
    w.factory("EXPR::pdfshow('sqrt(a*x)+b')");

    // Botar função na factory. expr cria uma função.
    w.factory("expr::f('(1-d)/2', d[0,1])");

   
    
}

void roofitsum(){

    RooWorkspace w("w");

    w.factory("Gaussian::gauss1(x[0,10],mean1[2],sigma[1]");
    w.factory("Gaussian::gauss2(x,mean2[3],sigma)");
    w.factory("ArgusBG::argus(x,k[-1],9.0)");
    w.factory("SUM::sum(g1frac[0.5]*gauss1, g2frac[0.1]*gauss2, argus)");

    RooPlot *frame = w.var("x")->frame();
    
    w.pdf("sum")->plotOn(frame,Components("argus"),LineStyle(kDashed));
    frame->Draw();
} 
