//Header Guards
#ifndef AVALIACAO
#define AVALIACAO

#include <string>
#include <list>
#include <iostream>
#include <cmath>

using namespace std;

enum tipoAluno_EN {
    Novo = 1,
    Repetente = 2,
    Aprovado = 3,
    Melhoria = 4
};

enum modoAvaliacao_EN {
    Indeciso = 1,
    Continua = 2,
    Exame = 3,
};

class Avaliacao {
    private:
        int notaFinal = 0;
        tipoAluno_EN tipoAluno = Novo;
        modoAvaliacao_EN modoAvaliacao = Indeciso;
        double somaEfolio = -1; // mantem um registo do melhor conjunto de efolios
        double efolio[3] = {-1, -1, -1}; //Utilizado durante o ano, de forma a manter o conjunto com melhor qualificacao
        double pfolio = -1;
        double exame = -1;

    public:
        /*
            Construtores e Descontrutor
        */
        Avaliacao(int, tipoAluno_EN, modoAvaliacao_EN, double , double[], double, double);
        Avaliacao();
        virtual ~Avaliacao();        

        /*
            Funcoes auxiliares de Avaliacao
        */
        void finalizarAvaliacao();
        void resetAvaliacaoTemp();
        double somarEfolios();
        void manterNotasEfolios();
        
        /*
            Getters and Setters
        */
        int getNotaFinal() { return notaFinal; };
        tipoAluno_EN getTipoAluno() { return tipoAluno; };
        modoAvaliacao_EN getModoAvaliacao() { return modoAvaliacao; };
        double getSomaEfolio() { return somaEfolio; };
        double getEfolioA() { return efolio[0]; };
        double getEfolioB() { return efolio[1]; };
        double getEfolioC() { return efolio[2]; };
        double getPfolio() { return pfolio; };
        double getExame() { return exame; };

        void setNotaFinal(int n) { notaFinal = n; };
        void setTipoAluno(tipoAluno_EN t) { tipoAluno = t; };
        void setModoAvaliacao(modoAvaliacao_EN m) { modoAvaliacao = m; };
        void setSomaEfolio() { somaEfolio = somarEfolios(); };
        void setEfolioA(double a) { efolio[0] = a; };
        void setEfolioB(double b) { efolio[1] = b; };
        void setEfolioC(double c) { efolio[2] = c; };
        void setPfolio(double p) { pfolio = p; };
        void setExame(double e) { exame = e; };
};

#endif