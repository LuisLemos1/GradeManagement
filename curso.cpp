#include "curso.hpp"
/*
    Construtor e Deconstrutor.
    Ira se iniciar o menu especifico para o curso. 
    Neste caso, como e para LEI apenas, o codigo remete apenas para este especifico Curso.
*/
Curso::Curso() { // Menu do curso LEI
    int opcao;
    
    // Carregar Listas de ficheiros
    carregarListaUc();
    carregarListaAluno();
    carregarListaInscricoes();

    // Menu Principal
    do {
        do {
            if(system("cls")) system("clear");
            cout 
                << "\t************************************************************\n"
                << "\t***                 Efolio B - Inscricoes LEI            ***\n"
                << "\t************************************************************\n"
                << "\t************************ Menu Principal ********************\n"
                << "\n\tSelecione uma das opcoes seguintes:"
                << "\n\t\t1. Inscrever Aluno no Curso"
                << "\n\t\t2. Inscrever Aluno numa Unidade Curricular"
                << "\n\t\t3. Consultar Aluno"
                << "\n\t\t4. Consultar Unidade Curricular"
                << "\n\t\t5. Avaliacoes"
                << "\n\t\t0. Sair\n"
                << "\n\n\tOpcao: ";
            cin.clear();
            cin.sync();
            cin >> opcao;
            if(cin.fail())
                opcao = -1;
        } while(opcao < 0 || opcao > 5);

        switch (opcao) {
            case 1:
                menuNovoAluno();
                break;

            case 2: 
                menuInscricaoUc();
                break;

            case 3:
                menuConsultaAluno();
                break;

            case 4:
                menuConsultaUc();
                break;

            case 5:
                menuAvaliacoes();
                break;

            case 0:
                despedida();
                break;

            default:
                break;
        }
    } while(opcao !=0);
}

Curso::~Curso() {}

/*
    Funcoes remetentes a Lista de Alunos
*/
int Curso::existeUc(int codigo) {
    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if(codigo == iteratorUc->getCodigo())
            return 1;
    }
    return 0;
}

int Curso::existeAluno(int numeroAluno) {
    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        if(iteratorAluno->getNumero() == numeroAluno){
            return 1;
        }
    }
    return 0;
}

int Curso::existeAluno(int numeroAluno, int codigoUc) {
    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        if(iteratorAluno->getNumero() == numeroAluno){
            if(iteratorAluno->contemUc(codigoUc))
                return 1;
            return 0;
        }
    }
    return 0;
}

void Curso::listarUcsCurso() {
    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        cout << "\t" << iteratorUc->getCodigo() << " " << iteratorUc->getECTS() << "\t" << iteratorUc->getNome() << "\n";
    }
}

void Curso::listarAlunos() {
    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        cout << "\t" << iteratorAluno->getNumero() << "\t" << iteratorAluno->getNome() << "\n";
    }
}

void Curso::listarAlunos(int codigoUc) {
    cout << "\tAlunos por Aprovar: \n";
    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        if(iteratorAluno->contemUcPorAprovar(codigoUc))
            cout << "\t" << iteratorAluno->getNumero() << "\t" << iteratorAluno->getNome() << "\n";
    }
    cout << "\n\tTodos os alunos Inscritos: \n";
    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        if(iteratorAluno->contemUc(codigoUc))
            cout << "\t" << iteratorAluno->getNumero() << "\t" << iteratorAluno->getNome() << "\n";
    }
}

void Curso::adicionarAluno(int numero) {
    listaAluno.push_back(Aluno(numero));

    listaAluno.sort([] (const Aluno &aluno1, const Aluno &aluno2)
        {
            return aluno1.getNumero() < aluno2.getNumero();
        });
}

void Curso::inscricaoUc(int numeroAluno, int codigoUc, int notaFinal, tipoAluno_EN tipoAluno, modoAvaliacao_EN modoAvaliacao, double somaEfolio, double efolio[3], double pfolio, double exame){
    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        if(iteratorAluno->getNumero() == numeroAluno) {
            iteratorAluno->updateLista(getUc(codigoUc), notaFinal, tipoAluno, modoAvaliacao, somaEfolio, efolio, pfolio, exame);
            break;   
        }
    }   
}

void Curso::inscricaoUc(int numeroAluno, int codigoUc){
    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        if(iteratorAluno->getNumero() == numeroAluno) {
            iteratorAluno->updateLista(getUc(codigoUc));
            break;   
        }
    }    
}

void Curso::listarUcAprovadaAluno(int numeroAluno) {
    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        if(iteratorAluno->getNumero() == numeroAluno) iteratorAluno->listarUcAprovada();
    }
}

void Curso::estatisticaAluno(int numeroAluno) {
    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        if(iteratorAluno->getNumero() == numeroAluno) {
            break;
        }
    }

    cout << "\n\tTotal de UC: " << iteratorAluno->contarUc() << "\n"
    << "\tTotal de ECTS: " << iteratorAluno->somaECTS() << "\n"
    << "\tMedia: " << iteratorAluno->calcularMedia() << "\n\n";
    
    // Mensagem de Parabens - completa curso!
    if(iteratorAluno->somaECTS() == 180)
        cout << "\n\tIt's what you do in the dark that puts you in the light!\n\n\t\tPARABENS!! Concluis-te o curso!\n\n";
}

void Curso::estatisticaUc(int codigoUc) {
    int totalAlunosAprovados = 0;
    double totalNotaAprovados = 0;
    double media;

    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        if(iteratorAluno->existeUcAprovadaLista(codigoUc)) {
            totalAlunosAprovados++;
            totalNotaAprovados += iteratorAluno->getNotaUc(codigoUc);
        }
    }

    media = totalNotaAprovados / totalAlunosAprovados;

    cout << "\tTotal de alunos aprovados: " << totalAlunosAprovados << "\n\n"
    << "\tMedia: " << media << "\n\n\n";
}

/*
    Getters
*/
string Curso::getNomeAluno(int numeroAluno) {
    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        if(iteratorAluno->getNumero() == numeroAluno){
            return iteratorAluno->getNome();
        }
    }

    return "not found";
}

Uc* Curso::getUc(int codigo) {
    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if(codigo == iteratorUc->getCodigo())
            return new Uc(iteratorUc->getCodigo(), iteratorUc->getECTS(), iteratorUc->getNome(), iteratorUc->getNrEfolios(), iteratorUc->getEfolioA(), iteratorUc->getEfolioB());
    }
    return new Uc();
}

string Curso::getNomeUc(int codigoUc) {
    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if(codigoUc == iteratorUc->getCodigo())
            return iteratorUc->getNome();
    }
    return "not found";
}

/*
    Funcoes iniciais na abertura e fecho do programa.
    Le varios ficheiros da pasta ".db" na abertura.
    Guarda varios ficheiros na mesma pasta na saida.
*/
void Curso::carregarListaUc() {
    int codigo, ects, nrEfolios, efolioA, efolioB, efolioC;
    string nome;

    ifstream in;
    in.open("db\\unidadescurriculares.txt");

    while(!in.fail()) {
        in >> codigo >> ects >> nrEfolios >> efolioA >> efolioB >> efolioC;
        // std::ws ignora espacos em branco nos primeiros caracteres do string
        getline(in >> ws, nome);

        listaUc.push_back(Uc(codigo, ects, nome, nrEfolios, efolioA, efolioB));
    }
    
    // atribui uma copia do ultimo objeto, por isso removo-o
    listaUc.pop_back();

    in.close();
}

void Curso::carregarListaAluno() {
    int numero;
    string nome;

    ifstream in;
    in.open("db\\alunos.txt");

    while(!in.fail()) {
        in >> numero;
        // std::ws ignora espacos em branco nos primeiros caracteres do string
        getline(in >> ws, nome);
        listaAluno.push_back(Aluno(numero, nome));
    }
    
    // atribui uma copia do ultimo objeto, por isso removo-o
    listaAluno.pop_back();

    in.close();
}

void Curso::carregarListaInscricoes() { // Updated
    int numeroAluno, codigoUc, notaFinal;
    int tipo, modo;
    tipoAluno_EN tipoAluno;
    modoAvaliacao_EN modoAvaliacao;
    double efolio[3], somaEfolios, pfolio, exame; 

    ifstream in;
    in.open("db\\inscricoes.txt");

    while(!in.fail()) {
        in >> numeroAluno >> codigoUc >> notaFinal >> tipo
        >> modo >> somaEfolios >> efolio[0] >> efolio[1] 
        >> efolio[2] >> pfolio >> exame;
        
        // Converter para Enum
        tipoAluno = (tipo == 1 ? Novo : (tipo == 2 ? Repetente : (tipo == 3 ? Aprovado : Melhoria)));
        modoAvaliacao = (modo == 1 ? Indeciso : (modo == 2 ? Continua : Exame));  
        
        //adicionar inscricao
        inscricaoUc(numeroAluno, codigoUc, notaFinal, tipoAluno, modoAvaliacao, somaEfolios, efolio, pfolio, exame);
    }

    // atribui uma copia do ultimo objeto, por isso removo-o
    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++){
        if(iteratorAluno->getNumero() == numeroAluno){
            iteratorAluno->removerUltimaUc();
        }
    }

    in.close();
}

void Curso::guardarListaUc() {
    ofstream fout;    
    
    fout.open("db\\unidadescurriculares.txt");

    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        fout << iteratorUc->getCodigo() << " " << iteratorUc->getECTS() << " "
            << iteratorUc->getNrEfolios() << " " << iteratorUc->getEfolioA() << " "
            << iteratorUc->getEfolioB() << " " << iteratorUc->getEfolioC() << " "
            << iteratorUc->getNome() << endl;
    }

    fout.close();
}

void Curso::guardarListaAluno() {
    ofstream fout;

    fout.open("db\\alunos.txt");

    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        fout << iteratorAluno->getNumero() << " " << iteratorAluno->getNome() << endl;
    }

    fout.close();
}

void Curso::guardarListaInscricoes() {
    list<Uc> listaUc;
    ofstream fout;

    fout.open("db\\inscricoes.txt");

    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        listaUc = iteratorAluno->getLista();
        for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
            fout << iteratorAluno->getNumero() << " " << iteratorUc->getCodigo() << " " 
            << (iteratorUc->getAvaliacao()).getNotaFinal() << " " << (iteratorUc->getAvaliacao()).getTipoAluno() << " "
            << (iteratorUc->getAvaliacao()).getModoAvaliacao() << " " << (iteratorUc->getAvaliacao()).getSomaEfolio() << " "
            << (iteratorUc->getAvaliacao()).getEfolioA() << " " << (iteratorUc->getAvaliacao()).getEfolioB() << " " 
            << (iteratorUc->getAvaliacao()).getEfolioC() << " " << (iteratorUc->getAvaliacao()).getPfolio() << " "  
            << (iteratorUc->getAvaliacao()).getExame() << endl;
        }
    }

    fout.close();
}

/*
    Mensagem de Despedida e Gravar ficheiros na pasta db  
    
*/
void Curso::despedida() {
    guardarListaAluno();
    guardarListaInscricoes();
    guardarListaUc();

    cout << "\n\tAte breve!\n\n\tPressione qualquer tecla para sair...\n";
    cin.clear();
    cin.sync();
    getchar();
}


/*
    Varios menus
*/
void Curso::menuNovoAluno() {
    int numeroMatricula;

    if(system("cls")) system("clear");    
    cout 
        << "\t************************************************************\n"
        << "\t***                 Efolio B - Inscricoes LEI            ***\n"
        << "\t************************************************************\n"
        << "\t*********************** Novo Aluno ********************\n\n";

    do {
        cout << "\n\tNumero de estudante (0 para voltar ao Menu Principal): ";
        cin.clear();
        cin.sync();
        cin >> numeroMatricula;
        if(cin.fail()) numeroMatricula = -1;

        if(numeroMatricula == 0)
            return;
        
        if(numeroMatricula < 1000 || numeroMatricula > 99999){
            cout << "\n\t\t Por favor insira um numero valido entre 3 e 5 digitos";
            numeroMatricula = 1;
        } else if (existeAluno(numeroMatricula)){
            cout << "\n\t\t Aluno ja existente!";
            numeroMatricula = 1;
        }
        
    } while(numeroMatricula < 1000 || numeroMatricula > 99999);

    adicionarAluno(numeroMatricula);

    cout << "\n\n\tAluno adicionado com sucesso!\n\n"
    << "\tPressione qualquer tecla para voltar ao menu...\n";
    cin.clear();
    cin.sync();
    getchar();
}

void Curso::menuInscricaoUc() {
    int numeroMatricula;
    int codigoUc;

    do {
        cout << "\n\tNumero de estudante (0 - sair, 1 - Listar Alunos): ";
        cin.clear();
        cin.sync();
        cin >> numeroMatricula;
        if(cin.fail()) numeroMatricula = -1;

        if(numeroMatricula == 1) {
            listarAlunos();
        } else {
            if(numeroMatricula == 0)
                return;
            
            if(numeroMatricula < 1000 || numeroMatricula > 99999){
                cout << "\n\t\t Por favor insira um numero valido entre 3 e 5 digitos";
                numeroMatricula = 1;
            }

            if(!existeAluno(numeroMatricula)){
                cout << "\n\t\t Aluno nao existe!";
                numeroMatricula = 1;
            }
        }
        
    } while(numeroMatricula < 1000 || numeroMatricula > 99999);
    
    if(system("cls")) system("clear");
    cout  << "\t************************************************************\n"
        << "\t***                 Efolio B - Inscricoes LEI            ***\n"
        << "\t************************************************************\n"
        << "\t**************** Incricao na Unidade Curricular ************\n\n"
        << "\t************************************************************\n"
        << "\tNome do Aluno: " << getNomeAluno(numeroMatricula) << "\n\n" 
        << "\t---------------------------------------------------------\n\n";

    do {
        cout << "\n\tCodigo da Unidade Curricular (0 - sair, 1 - Listar UC's): ";
        cin.clear();
        cin.sync();
        cin >> codigoUc;
        if(cin.fail()) codigoUc = -1;

        if(codigoUc == 0)
            return;

        if(codigoUc == 1)
            listarUcsCurso();

        if(!existeUc(codigoUc) && codigoUc != 1)
            cout << "\n\t\t Unidade Curricular nao existe!";
    } while(!existeUc(codigoUc));

    inscricaoUc(numeroMatricula, codigoUc);

    cout << "\n\n\tPressione qualquer tecla para voltar ao menu...\n";
    cin.clear();
    cin.sync();
    getchar();
}

void Curso::menuConsultaAluno() {
    int numeroMatricula;

    do {
        cout << "\n\tNumero de estudante (0 - sair, 1 - Listar Alunos): ";
        cin.clear();
        cin.sync();
        cin >> numeroMatricula;
        if(cin.fail()) numeroMatricula = -1;

        if(numeroMatricula == 1) {
            listarAlunos();
        } else {
            if(numeroMatricula == 0)
                return;
            
            if(numeroMatricula < 1000 || numeroMatricula > 99999){
                cout << "\n\t\t Por favor insira um numero valido entre 3 e 5 digitos";
                numeroMatricula = 1;
            }

            if(!existeAluno(numeroMatricula)){
                cout << "\n\t\t Aluno nao existe!";
                numeroMatricula = 1;
            }
        }
        
    } while(numeroMatricula < 1000 || numeroMatricula > 99999);
    
    if(system("cls")) system("clear");
    cout  << "\t************************************************************\n"
        << "\t***                 Efolio B - Inscricoes LEI            ***\n"
        << "\t************************************************************\n"
        << "\t********************     Consulta Aluno     ****************\n\n"    
        << "\t************************************************************\n"
        << "\tNome do Aluno: " << getNomeAluno(numeroMatricula) << "\n\n";
    cout << left << setw(46) << "\tUC"  << "ECTS\t" << "Nota\n"
        << "\t------------------------------------------------------------\n";
    
    listarUcAprovadaAluno(numeroMatricula);
    estatisticaAluno(numeroMatricula);
    cout << "\tPressione qualquer tecla para voltar ao menu...\n";
    cin.clear();
    cin.sync();
    getchar();
}

void Curso::menuConsultaUc() {
    int codigoUc;

    do {
        cout << "\n\tCodigo da Unidade Curricular (0 - sair, 1 - Listar UC's): ";
        cin.clear();
        cin.sync();
        cin >> codigoUc;
        if(cin.fail()) codigoUc = -1;

        if(codigoUc == 0)
            return;

        if(codigoUc == 1)
            listarUcsCurso();

        if(!existeUc(codigoUc))
            cout << "\n\t\t Unidade Curricular nao existe! Selecione uma da lista disponivel.";
    } while(!existeUc(codigoUc));    
    
    if(system("cls")) system("clear");
    cout  << "\t************************************************************\n"
        << "\t***                 Efolio B - Inscricoes LEI            ***\n"
        << "\t************************************************************\n"
        << "\t********************     Consulta UC     ****************\n\n" 
        << "\tUnidade Curricular: " << getNomeUc(codigoUc) << "\n\n";
                            
    estatisticaUc(codigoUc);
    
    cout << "\tPressione qualquer tecla para voltar ao menu...\n";
    cin.clear();
    cin.sync();
    getchar();
}


/*
    Efolio B - Funcoes Avaliacao
*/
void Curso::avaliacaoAluno(int codigoUc, int numeroMatricula) {
    if(system("cls")) system("clear");
    cout  << "\t************************************************************\n"
        << "\t***                 Efolio B - Inscricoes LEI            ***\n"
        << "\t************************************************************\n"
        << "\t********************     Adicionar Nota     ****************\n\n" 
        << "\tUnidade Curricular: " << getNomeUc(codigoUc) << "\n"
        << "\tNome do Aluno: " << getNomeAluno(numeroMatricula) 
        << " (" << numeroMatricula << ")\n";
    
    // pegar no aluno
    for (iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno ++) {
        if(iteratorAluno->getNumero() == numeroMatricula) {
            iteratorAluno->avaliacaoUc(codigoUc);
        }
    }
}


void Curso::alterarCriteriosAvaliacao(int codigoUc, int nrEfolios, int efolioA, int efolioB) {
    int efolioC = 0;
    
    if(nrEfolios == 3)
        efolioC = 8 - efolioA - efolioB;

    for(iteratorUc = listaUc.begin(); iteratorUc != listaUc.end(); iteratorUc++) {
        if(codigoUc == iteratorUc->getCodigo()){
            iteratorUc->setNrEfolios(nrEfolios);
            iteratorUc->setEfolioA(efolioA);
            iteratorUc->setEfolioB(efolioB);
            iteratorUc->setEfolioC(efolioC);
            return;
        }
    }
}

int Curso::existeAlunoPorAprovar(int codigoUc) {
    for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
        if(iteratorAluno->contemUcPorAprovar(codigoUc))
            return 1;        
    }
    return 0;
}

/*
    Efolio B - Menus Avaliacao
*/
void Curso::finalizarAvaliacoes() {
    char escolha;

    do{
        cout << "\tTodas as Avaliacoes serao avaliadas. Confirmar(S ou N)?: ";
        cin.clear();
        cin.sync();
        cin >> escolha;
        if(escolha == 'S' || escolha == 's') {
            // avaliar

            for(iteratorAluno = listaAluno.begin(); iteratorAluno != listaAluno.end(); iteratorAluno++) {
                iteratorAluno->finalizarAvaliacoes();
            }
            
            cout << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }

        if(escolha == 'N' || escolha == 'n') {
            cout << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }
    } while(escolha != 'n' && escolha != 'N' && escolha != 'S' && escolha != 's');
}

void Curso::alterarCriteriosAvaliacao() {
    int codigoUc, nrEfolios, efolioA, efolioB;
    Uc *ucTemp;
    char escolha;

    do {
        cout << "\n\tCodigo da Unidade Curricular (0 - sair, 1 - Listar UC's): ";
        cin.clear();
        cin.sync();
        cin >> codigoUc;
        if(cin.fail()) codigoUc = -1;

        if(codigoUc == 0)
            return;

        if(codigoUc == 1)
            listarUcsCurso();

        if(!existeUc(codigoUc))
            cout << "\n\t\t Unidade Curricular nao existe! Selecione uma da lista disponivel.";

    } while(!existeUc(codigoUc));   
    // verificar se UC tem alunos por aprovar!
    if(existeAlunoPorAprovar(codigoUc)) {
        cout << "\n\t\tExiste Alunos Por Aprovar! Avalie estes mesmos ou termine as avaliacoes no menu." << endl
                << "\n\tPressione qualquer tecla para voltar ao menu...\n";
        cin.clear();
        cin.sync();
        getchar();
        return;
    }

    ucTemp = getUc(codigoUc);

    if(system("cls")) system("clear");
    cout  << "\t************************************************************\n"
        << "\t***                 Efolio B - Inscricoes LEI            ***\n"
        << "\t************************************************************\n"
        << "\t******************     Alterar Criterios     ***************\n\n" 
        << "\tUnidade Curricular: " << ucTemp->getNome() << endl
        << "\tNumero de Efolios: " << ucTemp->getNrEfolios() << endl
        << "\tEfolio A (Maxima cotacao): " << ucTemp->getEfolioA() << endl
        << "\tEfolio B (Maxima cotacao): " << ucTemp->getEfolioB() << endl;

    if(ucTemp->getNrEfolios() == 3)
        cout << "\tEfolio C (Maxima cotacao): " << ucTemp->getEfolioC() << endl;

    do{
        cout << "\n\tAlterar os criterios dos Efolios para avaliacao continua (S ou N)?: ";
        cin.clear();
        cin.sync();
        cin >> escolha;
        if(escolha == 'S' || escolha == 's') {
            do {
                cout << "\n\tAvaliacao continua com 2 ou 3 Efolios?\n\t";            
                cin.clear();
                cin.sync();
                cin >> nrEfolios;

                if(nrEfolios != 2 && nrEfolios != 3)
                    cout << "\n\t\tPor favor 2 ou 3 Efolios.\n";
            } while(nrEfolios != 2 && nrEfolios != 3);
            cout << "\n\tAvaliacao continua com " << nrEfolios <<  " Efolios confirmada!\n";            

            if(nrEfolios == 2) {
                do {
                    cout << "\n\tQual a nota maxima do Efolio A?\n\t";            
                    cin.clear();
                    cin.sync();
                    cin >> efolioA;

                    if(efolioA < 1 || efolioA > 7)
                        cout << "\n\t\tPor favor insira uma nota entre 1 e 7.\n";
                } while(efolioA < 1 || efolioA > 7);
                cout << "\n\tEfolio A com um maximo de " << efolioA <<  " valores confirmado!";

                efolioB = 8 - efolioA;
                cout << "\n\tEfolio B com um maximo de " << efolioB <<  " valores confirmado!\n\n";
                  
            } else if(nrEfolios == 3) {
                do {
                    cout << "\n\tQual a nota maxima do Efolio A?\n\t";            
                    cin.clear();
                    cin.sync();
                    cin >> efolioA;

                    if(efolioA < 1 || efolioA > 6)
                        cout << "\n\t\tPor favor insira uma nota entre 1 e 6.\n";
                } while(efolioA < 1 || efolioA > 6);
                cout << "\n\tEfolio A com um maximo de " << efolioA <<  " valores confirmado!";

                do {
                    cout << "\n\tQual a nota maxima do Efolio B?\n\t";            
                    cin.clear();
                    cin.sync();
                    cin >> efolioB;

                    if(efolioB < 1 || efolioB > 6)
                        cout << "\n\t\tPor favor insira uma nota entre 1 e 6.\n";
                } while(efolioB < 1 || efolioB > 6);
                cout << "\n\tEfolio B com um maximo de " << efolioB <<  " valores confirmado!"
                    << "\n\tEfolio C com um maximo de " << 8 - efolioA - efolioB <<  " valores confirmado!\n\n";
            }

            alterarCriteriosAvaliacao(codigoUc, nrEfolios, efolioA, efolioB);

            delete ucTemp;
            
            cout << "\t\tCriterios dos Efolios Alterados!\n" << endl
                << "\tPressione qualquer tecla para voltar ao menu...\n";
            cin.clear();
            cin.sync();
            getchar();
            return;
        }

        delete ucTemp;
        cout << "\t\tCriterios dos Efolios nao alterados!\n" << endl
                << "\tPressione qualquer tecla para voltar ao menu...\n";
        cin.clear();
        cin.sync();
        getchar();
        return;
    } while(escolha != 'n' && escolha != 'N' && escolha != 'S' && escolha != 's');
}

void Curso::menuAdicionarNota() {
    int numeroMatricula, codigoUc;

    do {
        cout << "\n\tCodigo da Unidade Curricular (0 - sair, 1 - Listar UC's): ";
        cin.clear();
        cin.sync();
        cin >> codigoUc;
        if(cin.fail()) codigoUc = -1;

        if(codigoUc == 0)
            return;

        if(codigoUc == 1)
            listarUcsCurso();

        if(!existeUc(codigoUc))
            cout << "\n\t\t Unidade Curricular nao existe! Selecione uma da lista disponivel.";

    } while(!existeUc(codigoUc));   
    
    do {
        if(system("cls")) system("clear");
        cout  << "\t************************************************************\n"
            << "\t***                 Efolio B - Inscricoes LEI            ***\n"
            << "\t************************************************************\n"
            << "\t********************     Adicionar Nota     ****************\n\n" 
            << "\tUnidade Curricular: " << getNomeUc(codigoUc) << "\n\n";

        do {
            cout << "\n\tNumero de estudante (0 - sair, 1 - Listar Alunos): ";
            cin.clear();
            cin.sync();
            cin >> numeroMatricula;
            if(cin.fail()) numeroMatricula = -1;

            if(numeroMatricula == 1) {
                listarAlunos(codigoUc);
            } else {
                if(numeroMatricula == 0)
                    return;
                
                if(numeroMatricula < 1000 || numeroMatricula > 99999){
                    cout << "\n\t\t Por favor insira um numero valido entre 3 e 5 digitos";
                    numeroMatricula = 1;
                }

                if(!existeAluno(numeroMatricula, codigoUc)){
                    cout << "\n\t\t Aluno nao existe!";
                    numeroMatricula = 1;
                }
            }
        } while(numeroMatricula < 1000 || numeroMatricula > 99999);

        avaliacaoAluno(codigoUc, numeroMatricula);
    } while(numeroMatricula != 0);
}

void Curso::menuAvaliacoes() {
    int opcao;

    do {
        if(system("cls")) system("clear");
        cout 
            << "\t************************************************************\n"
            << "\t***                 Efolio B - Inscricoes LEI            ***\n"
            << "\t************************************************************\n"
            << "\t************************   Avaliacoes   ********************\n"
            << "\n\tSelecione uma das opcoes seguintes:"
            << "\n\t\t1. Adicionar Nota"
            << "\n\t\t2. Alterar Criterios dos Efolios"
            << "\n\t\t3. Terminar Avaliacoes"
            << "\n\t\t0. Sair\n"
            << "\n\n\tOpcao: ";
        cin.clear();
        cin.sync();
        cin >> opcao;
        if(cin.fail())
            opcao = -1;
    } while(opcao < 0 || opcao > 3);

    switch (opcao) {
        case 1:
            menuAdicionarNota();
            break;

        case 2: 
            alterarCriteriosAvaliacao();
            break;

        case 3:
            finalizarAvaliacoes();
            break;

        default:
            break;
    }
}
