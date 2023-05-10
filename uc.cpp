#include "uc.hpp"

/*
    Construtores e Descontrutor
*/
Uc::Uc(int cod, int e, string n, int nr, int a, int b, int c, int nota, tipoAluno_EN t, modoAvaliacao_EN m, double s, double ef[3], double p, double ex) {
    codigo = cod;
    ects = e;
    nome = n;
    nrEfolios = nr;
    efolioA = a;
    efolioB = b;
    efolioC = c;
    avaliacao = Avaliacao(nota, t, m, s, ef, p, ex);
}

Uc::Uc(int cod, int e, string n, int nr, int a, int b) {
    codigo = cod;
    ects = e;
    nome = n;
    nrEfolios = nr;
    efolioA = a;
    efolioB = b;
    efolioC = (nrEfolios == 3 ? 8 - efolioA - efolioB : 0);
}

Uc::Uc() {}

Uc::~Uc() {}

/* 
    Efolio B - Avaliacoes
*/
void Uc::avaliacaoEfolioA() {
    double nota;
    char escolha;

    do {
        cout << "\n\tQual a nota do Efolio A? (0 a " << efolioA << ")\n\t";            
        cin.clear();
        cin.sync();
        cin >> nota;

        if(nota < 0 || nota > efolioA)
            cout << "\n\t\tPor favor insira uma nota entre 0 a " << efolioA << endl;
    } while(nota < 0 || nota > efolioA);

    do{
        cout << "\tNota do Efolio A: " << nota << " valores. Confirmar(S ou N)?: ";
        cin.clear();
        cin.sync();
        cin >> escolha;
        if(escolha == 'S' || escolha == 's') {
            avaliacao.setEfolioA(nota);
            cout << "\t\tNota Efolio A submetida!\n" << endl
                << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }

        if(escolha == 'N' || escolha == 'n') {
            cout << "\t\tNota Efolio A nao submetida!\n" << endl
                << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }
    } while(escolha != 'n' && escolha != 'N' && escolha != 'S' && escolha != 's');
}

void Uc::avaliacaoEfolioB() {
    double nota;
    char escolha;

    do {
        cout << "\n\tQual a nota do Efolio B? (0 a " << efolioB << ")\n\t";            
        cin.clear();
        cin.sync();
        cin >> nota;

        if(nota < 0 || nota > efolioB)
            cout << "\n\t\tPor favor insira uma nota entre 0 a " << efolioB << endl;
    } while(nota < 0 || nota > efolioB);

    do{
        cout << "\tNota do Efolio B: " << nota << " valores. Confirmar(S ou N)?: ";
        cin.clear();
        cin.sync();
        cin >> escolha;
        if(escolha == 'S' || escolha == 's') {
            avaliacao.setEfolioB(nota);
            cout << "\t\tNota Efolio B submetida!\n" << endl;
            if(nrEfolios == 2 && avaliacao.somarEfolios() < 3.5) {
                avaliacao.setExame(-2); // remete para exame de recurso
                avaliacao.setModoAvaliacao(Exame);
                cout << "\t\tSoma dos efolios inferior a 3.5, aluno remetido para exame de recurso!\n" << endl
                    << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
                return;
            }

            if(avaliacao.getSomaEfolio() < avaliacao.somarEfolios())
                avaliacao.setSomaEfolio();
            
            cout << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }

        if(escolha == 'N' || escolha == 'n') {
            cout << "\t\tNota Efolio B nao submetida!\n" << endl
                << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }
    } while(escolha != 'n' && escolha != 'N' && escolha != 'S' && escolha != 's');
}

void Uc::avaliacaoEfolioC() {
    double nota;
    char escolha;

    do {
        cout << "\n\tQual a nota do Efolio C? (0 a " << efolioC << ")\n\t";            
        cin.clear();
        cin.sync();
        cin >> nota;

        if(nota < 0 || nota > efolioC)
            cout << "\n\t\tPor favor insira uma nota entre 0 a " << efolioC << endl;
    } while(nota < 0 || nota > efolioC);

    do{
        cout << "\tNota do Efolio C: " << nota << " valores. Confirmar(S ou N)?: ";
        cin.clear();
        cin.sync();
        cin >> escolha;
        if(escolha == 'S' || escolha == 's') {
            avaliacao.setEfolioC(nota);
            cout << "\t\tNota Efolio C submetida!\n" << endl;
            if(avaliacao.somarEfolios() < 3.5) {
                avaliacao.setExame(-2); // remete para exame de recurso
                avaliacao.setModoAvaliacao(Exame);
                cout << "\t\tSoma dos efolios inferior a 3.5, aluno remetido para exame de recurso!\n" << endl
                    << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
                return;
            }

            if(avaliacao.getSomaEfolio() < avaliacao.somarEfolios())
                avaliacao.setSomaEfolio();
            
            cout << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }

        if(escolha == 'N' || escolha == 'n') {
            cout << "\t\tNota Efolio C nao submetida!\n" << endl
                << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }
    } while(escolha != 'n' && escolha != 'N' && escolha != 'S' && escolha != 's');
}

void Uc::avaliacaoPfolio() {
    double nota, notaFinalTemp;
    char escolha;

    do {
        cout << "\n\tQual a nota do Pfolio? (0 a 12)\n\t";            
        cin.clear();
        cin.sync();
        cin >> nota;

        if(nota < 0 || nota > 12)
            cout << "\n\t\tPor favor insira uma nota entre 0 e 12.\n";
    } while(nota < 0 || nota > 12);

    do{
        cout << "\tNota do Pfolio: " << nota << " valores. Confirmar(S ou N)?: ";
        cin.clear();
        cin.sync();
        cin >> escolha;
        if(escolha == 'S' || escolha == 's') {
            avaliacao.setPfolio(nota);
            notaFinalTemp = avaliacao.somarEfolios() + nota;
            cout << "\t\tNota Pfolio submetida!\n" << endl;
            if(nota < 5.5 || notaFinalTemp < 9.5) { 
                avaliacao.setPfolio(-2); // remete para pfolio de recurso
                cout << "\t\tSoma total inferior a 9.5 ou pfolio inferior a 5.5, aluno remetido para pfolio de recurso!\n" << endl
                    << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
                return;
            }
            
            if(avaliacao.getNotaFinal() + 0.5 <= notaFinalTemp) {
                avaliacao.setNotaFinal(round(notaFinalTemp));
                if(avaliacao.getTipoAluno() == Melhoria)
                    cout << "\t\tAluno melhorou a nota com sucesso!\n" << endl;
                else 
                    cout << "\t\tAluno Aprovado!\n" << endl;
                avaliacao.setTipoAluno(Aprovado);
                avaliacao.resetAvaliacaoTemp();
                cout << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
                return;
            }

            if(avaliacao.getTipoAluno() == Melhoria) {
                avaliacao.setTipoAluno(Aprovado); // remete para pfolio de recurso
                avaliacao.resetAvaliacaoTemp();
                cout << "\t\tAluno nao conseguiu a melhoria de nota, mas aprovou!\n" << endl
                    << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
            }
        }

        if(escolha == 'N' || escolha == 'n') {
            cout << "\t\tNota Pfolio nao submetida!\n" << endl
                << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }
    } while(escolha != 'n' && escolha != 'N' && escolha != 'S' && escolha != 's');
}

void Uc::avaliacaoPfolioRecurso() {
    double nota, notaFinalTemp;
    char escolha;

    do {
        cout << "\n\tQual a nota do Pfolio de Recurso? (0 a 12)\n\t";            
        cin.clear();
        cin.sync();
        cin >> nota;

        if(nota < 0 || nota > 12)
            cout << "\n\t\tPor favor insira uma nota entre 0 e 12.\n";
    } while(nota < 0 || nota > 12);

    do{
        cout << "\tNota do Pfolio de Recurso: " << nota << " valores. Confirmar(S ou N)?: ";
        cin.clear();
        cin.sync();
        cin >> escolha;
        if(escolha == 'S' || escolha == 's') {
            avaliacao.setPfolio(nota);
            notaFinalTemp = avaliacao.somarEfolios() + nota;
            cout << "\t\tNota Pfolio de Recurso submetida!\n" << endl;
            if(nota < 5.5 || notaFinalTemp < 9.5) {
                if(avaliacao.getTipoAluno() == Melhoria) {
                    avaliacao.setTipoAluno(Aprovado);
                    avaliacao.resetAvaliacaoTemp();
                    cout << "\t\tAluno nao conseguiu a melhoria de nota!\n" << endl
                        << "\tPressione qualquer tecla para voltar ao menu...\n";
                    cin.clear();
                    cin.sync();
                    getchar();
                    return;
                }
                avaliacao.setTipoAluno(Repetente);
                avaliacao.resetAvaliacaoTemp();
                cout << "\t\tSoma total inferior a 9.5 ou pfolio inferior a 5.5, aluno reprovado!\n" << endl
                    << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
                return;
            }
            
            if(avaliacao.getNotaFinal() + 0.5 <= notaFinalTemp) {
                avaliacao.setNotaFinal(round(notaFinalTemp));
                if(avaliacao.getTipoAluno() == Melhoria)
                    cout << "\t\tAluno melhorou a nota com sucesso!\n" << endl;
                else 
                    cout << "\t\tAluno Aprovado!\n" << endl;
                avaliacao.setTipoAluno(Aprovado);
                avaliacao.resetAvaliacaoTemp();
                cout << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
                return;
            }

            if(avaliacao.getTipoAluno() == Melhoria) {
                avaliacao.setTipoAluno(Aprovado); 
                avaliacao.resetAvaliacaoTemp();
                cout << "\t\tAluno nao conseguiu a melhoria de nota!\n" << endl
                    << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
            }
        }

        if(escolha == 'N' || escolha == 'n') {
            cout << "\t\tNota Pfolio de Recurso nao submetida!\n" << endl
                << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }
    } while(escolha != 'n' && escolha != 'N' && escolha != 'S' && escolha != 's');
}

void Uc::avaliacaoExame() {
    double nota;
    char escolha;

    do {
        cout << "\n\tQual a nota do Exame? (0 a 20)\n\t";            
        cin.clear();
        cin.sync();
        cin >> nota;

        if(nota < 0 || nota > 20)
            cout << "\n\t\tPor favor insira uma nota entre 0 e 20.\n";
    } while(nota < 0 || nota > 20);

    do{
        cout << "\tNota do Exame: " << nota << " valores. Confirmar(S ou N)?: ";
        cin.clear();
        cin.sync();
        cin >> escolha;
        if(escolha == 'S' || escolha == 's') {
            if(nota < 9.5) {
                avaliacao.setExame(-2);
                cout << "\t\tNota insuficiente, aluno remetido para recurso!\n" << endl
                    << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
                return;
            }

            if(avaliacao.getNotaFinal() + 0.5 < nota) {
                avaliacao.setNotaFinal(round(nota));
                if(avaliacao.getTipoAluno() == Melhoria)
                    cout << "\t\tAluno melhorou a nota com sucesso!\n" << endl;
                else 
                    cout << "\t\tAluno Aprovado!\n" << endl;
                avaliacao.setTipoAluno(Aprovado);
                avaliacao.resetAvaliacaoTemp();
                cout << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
                return;
            }

            if(avaliacao.getTipoAluno() == Melhoria) {
                avaliacao.setTipoAluno(Aprovado);
                avaliacao.resetAvaliacaoTemp();
                cout << "\t\tAluno nao conseguiu a melhoria de nota, mas aprovou!\n" << endl
                    << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
            }
        }

        if(escolha == 'N' || escolha == 'n') {
            cout << "\t\tNota Exame nao submetida!\n" << endl
                << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }
    } while(escolha != 'n' && escolha != 'N' && escolha != 'S' && escolha != 's');
}

void Uc::avaliacaoExameRecurso() {
    double nota;
    char escolha;

    do {
        cout << "\n\tQual a nota do Exame de Recurso? (0 a 20)\n\t";            
        cin.clear();
        cin.sync();
        cin >> nota;

        if(nota < 0 || nota > 20)
            cout << "\n\t\tPor favor insira uma nota entre 0 e 20.\n";
    } while(nota < 0 || nota > 20);

    do{
        cout << "\tNota do Exame de Recurso: " << nota << " valores. Confirmar(S ou N)?: ";
        cin.clear();
        cin.sync();
        cin >> escolha;
        if(escolha == 'S' || escolha == 's') {
            if(nota < 9.5) {
                if(avaliacao.getTipoAluno() == Melhoria) {
                    avaliacao.setTipoAluno(Aprovado);
                    avaliacao.resetAvaliacaoTemp();
                    cout << "\t\tAluno nao conseguiu a melhoria de nota!\n" << endl
                        << "\tPressione qualquer tecla para voltar ao menu...\n";
                    cin.clear();
                    cin.sync();
                    getchar();
                }
                avaliacao.resetAvaliacaoTemp();
                avaliacao.setTipoAluno(Repetente);
                cout << "\t\tNota insuficiente, aluno reprovado!\n" << endl
                    << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
                return;
            }

            if(avaliacao.getNotaFinal() + 0.5 < nota) {
                avaliacao.setNotaFinal(round(nota));
                if(avaliacao.getTipoAluno() == Melhoria)
                    cout << "\t\tAluno melhorou a nota com sucesso!\n" << endl;
                else 
                    cout << "\t\tAluno Aprovado!\n" << endl;
                avaliacao.setTipoAluno(Aprovado);
                avaliacao.resetAvaliacaoTemp();
                cout << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
                return;
            }

            if(avaliacao.getTipoAluno() == Melhoria) {
                avaliacao.setTipoAluno(Aprovado);
                avaliacao.resetAvaliacaoTemp();
                cout << "\t\tAluno nao conseguiu a melhoria de nota, mas aprovou!\n" << endl
                    << "\tPressione qualquer tecla para voltar ao menu...\n";
                cin.clear();
                cin.sync();
                getchar();
            }
        }

        if(escolha == 'N' || escolha == 'n') {
            cout << "\t\tNota Exame nao submetida!\n" << endl
                << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }
    } while(escolha != 'n' && escolha != 'N' && escolha != 'S' && escolha != 's');
}

/*
    Efolio B - Menus
*/
void Uc::menuAvaliacaoIndeciso() {
    int opcao;
    char escolha;
    double melhorSomaEfolios = avaliacao.getSomaEfolio();

    // Caso esteja em melhoria ou for repetente, mostra os valores dos efolios anteriores caso este passe    
    if(melhorSomaEfolios >= 3.5) 
        cout << "\n\tMelhor nota de efolios de anos anteriores (0 a 8 valores): " << melhorSomaEfolios << " valores\n\n";
        
    if(avaliacao.getTipoAluno() == Aprovado) {
        // pedir por confirmacao de melhoria no caso do aluno estar aprovado 
        do{
            cout << "\tDeseja inscrever-se para melhoria (S ou N)?: ";
            cin.clear();
            cin.sync();
            cin >> escolha;
            if(escolha == 'S' || escolha == 's') 
                avaliacao.setTipoAluno(Melhoria);            

            if(escolha == 'N' || escolha == 'n') {
                return;
            }
        } while(escolha != 'n' && escolha != 'N' && escolha != 'S' && escolha != 's');
    }
    cout << "\n\tModo de Avaliacao: Indeciso" << endl << endl;

    do{
        cout << "\n\tEscolha um modo de avaliacao:"
            << "\n\t\t1. Avaliacao Continua"
            << "\n\t\t2. Avaliacao por Exame Final"
            << "\n\t\t0. Voltar ao menu principal"
            << "\n\n\tOpcao: ";
        cin.clear();
        cin.sync();
        cin >> opcao;
        if(cin.fail())
            opcao = -1;

        if(opcao == 0)
            return;
    } while(opcao < 1 || opcao > 2);

    switch(opcao) {
        case 1:
            if(melhorSomaEfolios >= 3.5) {
                do{
                    cout << "\tDeseja manter as notas dos efolios dos anos anteriores (S ou N)?: ";
                    cin.clear();
                    cin.sync();
                    cin >> escolha;
                    if(escolha == 'S' || escolha == 's') {
                        avaliacao.manterNotasEfolios();
                        cout << "\t\tNotas dos efolios guardadas!" << endl;
                    }
                } while(escolha != 'n' && escolha != 'N' && escolha != 'S' && escolha != 's');
            }
            avaliacao.setModoAvaliacao(Continua);
            cout << "\t\tModo de avaliacao continua guardado!\n" << endl;
            cout << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            break;

        case 2:
            avaliacao.setModoAvaliacao(Exame);
            cout << "\t\tModo de avaliacao por exame final guardado!\n" << endl;
            cout << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            break;
        
        default:
            break;
    }
}

void Uc::menuAvaliacaoContinua() {
    double pfolio = avaliacao.getPfolio();
    //Mostrar notas correntes
    cout << "\n\tSomatorio de Efolios: " << avaliacao.somarEfolios() << " valores";
    
    cout << "\n\tPfolio: ";
    if(pfolio != -1 && pfolio != -2)
        cout << pfolio << endl;
    else
        cout << "Nao avaliado" << endl;

    // Percorrer o percurso da avaliacao continua. Avalia quando uma nota nao foi atribuida
    if(avaliacao.getEfolioA() == -1)
        avaliacaoEfolioA();
    else if(avaliacao.getEfolioB() == -1)
        avaliacaoEfolioB();
    else if(avaliacao.getEfolioC() == -1 && nrEfolios == 3)
        avaliacaoEfolioC();
    else if(pfolio == -1)  
        avaliacaoPfolio();
    else if(pfolio == -2) 
        avaliacaoPfolioRecurso();
}

void Uc::menuAvaliacaoExame() {
    if(avaliacao.getExame() == -1) // Caso o Exame nao seja avaliado
        avaliacaoExame();
    else if(avaliacao.getExame() == -2)
        avaliacaoExameRecurso();
}

void Uc::avaliacaoUc() {

   // Mostrar Tipo de Aluno
    cout << "\tTipo de Aluno: ";
    if(avaliacao.getTipoAluno() == Novo)
        cout << "Novo" << endl;
    else if(avaliacao.getTipoAluno() == Repetente)
        cout << "Repetente" << endl;
    else if(avaliacao.getTipoAluno() == Aprovado)
        cout << "Aprovado" << endl;
    else
        cout << "Melhoria" << endl;

    if (avaliacao.getNotaFinal() > 0)
        cout << "\tNota final de anos anteriores: " << avaliacao.getNotaFinal() << endl;

    
    switch(avaliacao.getModoAvaliacao()) {
        case Indeciso:
            menuAvaliacaoIndeciso();
            break;

        case Continua:
            menuAvaliacaoContinua();
            break;

        case Exame:
            menuAvaliacaoExame();
            break;

        default:
            break;
    }
}