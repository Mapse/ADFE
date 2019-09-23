#include <iostream>
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "TFile.h"
#include "TTree.h"

using namespace RooFit;
//Factory


void ex18(){
    //definir o workspce

    unsigned n = 1000;
    RooWorkspace w("w");

    // Criar a pdf com a ajuda da factory, x, med e err é roorealvar, ga é a pdf

    w.factory("Gaussian::ga(x[-10, 10], med[1, -1000, 1000], err[2, 0 ,1000])");

    //retira a pdf
    RooAbsPdf *ga = w.pdf("ga");

    RooRealVar *x = w.var("x");

    RooDataSet *data = ga->generate(*x,n);
    data->SetName("gaus show");

    RooPlot *p = x->frame();
    p->SetTitle("a");
    data->plotOn(p);
    p->Draw();

    ga->plotOn(p);
    ga->fitTo(*data);
    
    p->Draw();

    w.import(*data);

    w.Print();

    w.writeToFile("teste.root", true);
}

void ex19(){

    TFile *file = new TFile("teste.root");

    //  O get pega um TObject e o (RooWorkspace*) converte para o que a gente quer.
    RooWorkspace *w = (RooWorkspace*) file->Get("w");

    RooAbsPdf *ga = w->pdf("ga");

    RooAbsData *da = w->data("gaus show");

    RooPlot *p = w->var("x")->frame();
    p->SetTitle("a");
    da->plotOn(p);
    
    
    RooFitResult * res = ga->fitTo(*da, Save(true), Minimizer("Minuit"), Range(0., 10.)); //RooFit::Range!!!!!!!
    ga->plotOn(p);
    ga->paramOn(p);
    p->Draw();

    res->Print();
    
    
}    

void ex20(){
    
    TFile *file = new TFile("teste.root");

    TTree *tree = new TTree("tree", "tree");

    
    int nevents = tree->ReadFile("Hgg.txt", "x/D");
    
    RooWorkspace w("w");

    // Criar as funções.

// nome da variavel, valor in, range
    w.factory("nback[10000, 0, 10000]");
    w.var("nback")->setMin(0.1*nevents); //se nao botar isso aqui dá ruim.
    w.var("nback")->setMax(10*nevents);
    w.factory("x[110, 160]");

    w.factory("a1[7.5, -500, 500]");
    w.factory("a2[-1.5, -500, 500]");
    w.factory("expr::za('-(a1*x/100 + a2*(x/100)^2)', a1, a2, x)");
    w.factory("Exponential::bg(za,1)");

    w.factory("nsig[100, 0, 1000]");

    w.factory("mass[130, 110, 150]");
    w.factory("err[1, 0.5, 5.]");
    
    w.factory("Gaussian::sig(x, mass, err)");

    w.factory("SUM::total(nsig*sig, nback*bg)");

    RooAbsPdf *sinal = w.pdf("sig");
    RooAbsPdf *modelo = w.pdf("total");

    RooRealVar *x = w.var("x");

    RooDataSet data("data", "data", *x, Import(*tree));

    RooFitResult *res = modelo->fitTo(data);

    RooPlot *p = x->frame();
    data.plotOn(p);
    modelo->plotOn(p);
    modelo->plotOn(p, Components("bg"), LineStyle(kDashed));
    modelo->plotOn(p, Components("sig"), LineColor(kRed));


    p->Draw();
    





}