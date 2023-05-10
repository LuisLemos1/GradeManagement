//Header Guards
#ifndef ALUNO
#define ALUNO

#include "uc.hpp"
#include <iostream>
#include <string>
#include <list>
#include <iomanip>

using namespace std;

class Aluno{
    private:
        int numero;
        string nome;
        list<Uc> listaUc;
        list<Uc>::iterator iteratorUc;

    public:
        /* Construtores de deconstrutor */
        Aluno(int );
        Aluno(int, string );
        virtual ~Aluno();

        /* Funcoes relacionadas a lista de Uc do Aluno*/
        void removerUltimaUc();
        void updateLista(Uc*, int, tipoAluno_EN, modoAvaliacao_EN, double, double[], double, double);
        void updateLista(Uc* );
        void listarUcAprovada();
        int existeUcAprovadaLista(int );

        /* Funcoes de calculo */
        double calcularMedia();
        int somaECTS();
        int contarUc();
        double getNotaUc(int );

        /* Alguns getters nessarios para o funcionamento do programa */
        int getNumero() const { return numero; };  
        string getNome() { return nome; };
        list<Uc> getLista() { return listaUc; };

        /*
            Efolio B - Avaliacoes
        */
        int contemUc(int );  
        int contemUcPorAprovar(int );   
        void avaliacaoUc(int );
        void finalizarAvaliacoes();
};

#endif