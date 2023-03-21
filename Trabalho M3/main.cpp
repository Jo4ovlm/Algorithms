#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

typedef struct
{
    string nome, cpf, telefone;
} Pessoa;

typedef struct
{
    int dia, mes, ano;
} DMA;

typedef struct
{
    string marca, modelo, placa, situ, categoria;
    int cod, qtd;
} Carro;

typedef struct
{
    string cpf, categoria;
    DMA data, dataE;
    int cod;
    float valor, pago;
} Locacao;

char simnao()
{
    char sn;
    do
    {
        sn = toupper(cin.get());
    }
    while(sn != 'S' and sn!='N');
    return sn;
}

void incluiV(Carro y)
{
    string linha="", lido="", placa="";
    Carro x;
    int n, i;
    rename("FROTA.TXT", "ANTIGOC.TXT");
    ifstream arq("ANTIGOC.TXT");
    ofstream arq2("FROTA.TXT", ios::app);
    if(!arq or !arq2)
    {
        cout<<"Arquivo nao foi aberto"<<endl;
        arq.close();
        arq2.close();
        system("pause");
        return;
    }
    cout<<"Informe a placa do veiculo: ";
    getline(cin,y.placa);
    while(getline(arq, linha))
    {
        lido = linha.substr(0,7);
        for(i=0; i<7; i++)
        {
            if(lido[i]!=' ') placa = placa + lido[i];
        }
        if(placa == y.placa)
        {
            cout<<"Carro ja cadastrado!"<<endl;
            arq.close();
            arq2.close();
            remove("FROTA.TXT");
            rename("ANTIGOC.TXT", "FROTA.TXT");
            system("pause");
            return;
        }
        arq2<<linha<<endl;
        placa = "";
    }
    cout<<"Informe a marca: ";
    getline(cin,y.marca);
    cout<<"Informe o modelo: ";
    getline(cin,y.modelo);
    do
    {
        cout<<"Informe a categoria (1 - Basico / 2 - Intermediario / 3 - Super): ";
        cin>>y.categoria;
    }
    while(y.categoria != "1" and y.categoria != "2" and y.categoria != "3");
    cin.ignore();
    do
    {
        cout<<"Informe a situacao ((L) Locado / (D) Disponivel): ";
        y.situ = toupper(cin.get());
    }
    while(y.situ != "D" and y.situ != "L");
    y.cod = rand()%100+1;
    y.qtd = 0;
    arq2<<setw(7)<<y.placa<<" "<<setw(10)<<y.marca<<" "<<setw(10)<<y.modelo<<" "<<setw(1)<<y.categoria<<" "<<setw(1)<<y.situ<<" "<<setw(3)<<y.cod<<" "<<setw(4)<<y.qtd<<endl;
    cout<<"Veiculo Cadastrado com sucesso!"<<endl;
    cin.get();
    arq.close();
    arq2.close();
    remove("ANTIGOC.TXT");
}

void incluiC(Pessoa x)
{
    int i;
    string palavra="", linha="", lido = "", nome = "";
    rename("CLIENTES.TXT", "ANTIGO.TXT");
    ifstream arq2("ANTIGO.TXT");
    ofstream arq("CLIENTES.TXT", ios::app);
    if(!arq)
    {
        cout<<"Arquivo nao foi aberto"<<endl;
        system("pause");
        return;
    }
    cout<<"Informe o nome do cliente: ";
    getline(cin, x.nome);
    while(getline(arq2, linha))
    {
        lido = linha.substr(0,10);
        for(i=0; i<10; i++)
        {
            if(lido[i]!=' ') nome = nome + lido[i];
        }
        if(nome == x.nome)
        {
            cout<<"Cliente ja cadastrado!"<<endl;
            arq.close();
            arq2.close();
            remove("CLIENTES.TXT");
            rename("ANTIGO.TXT", "CLIENTES.TXT");
            system("pause");
            return;
        }
        arq<<linha<<endl;
        nome = "";
    }
    cout<<"Informe o cpf do cliente: ";
    getline(cin, x.cpf);
    cout<<"Informe o telefone do cliente: ";
    getline(cin, x.telefone);
    arq<<setw(10)<<x.nome<<" "<<setw(11)<<x.cpf<<" "<<setw(11)<<x.telefone<<endl;
    cout<<"Cliente cadastrado!"<<endl;
    system("pause");
    arq.close();
    arq2.close();
    remove("ANTIGO.TXT");

}

void tiralista(Carro y)
{
    string linha= "", placa="", lido="";
    int i;
    rename("FROTA.TXT", "ANTIGOE.TXT");
    ifstream arq("ANTIGOE.TXT");
    ofstream arq2("FROTA.TXT");
    if(!arq or !arq2)
    {
        cout<<"Arquivo nao foi aberto"<<endl;
        system("pause");
        arq.close();
        arq2.close();
        return;
    }
    while(getline(arq,linha))
    {
        lido = linha.substr(0,7);
        y.marca = linha.substr(8,10);
        y.modelo = linha.substr(19,10);
        y.categoria = linha.substr(30,1);
        y.situ = linha.substr(32,1);
        y.cod = stoi(linha.substr(34,3));
        y.qtd = stoi(linha.substr(38,4));
        for(i=0; i<7; i++)
        {
            if(lido[i]!=' ') placa = placa + lido[i];
        }
        if(placa != "-1")
        {
            arq2<<setw(7)<<placa<<" "<<setw(10)<<y.marca<<" "<<setw(10)<<y.modelo<<" "<<setw(1)<<y.categoria<<" "<<setw(1)<<y.situ<<" "<<setw(3)<<y.cod<<" "<<setw(4)<<y.qtd<<endl;
        }
        placa = "";
    }
    cout<<"Excluido com sucesso!"<<endl;
    arq.close();
    arq2.close();
    remove("ANTIGOE.TXT");
}

void excluiV(Carro y)
{
    string placa="", linha="", lido="";
    int n, i;
    char sn;
    bool achou = false;
    rename("FROTA.TXT", "ANTIGOC.TXT");
    ifstream arq("ANTIGOC.TXT");
    ofstream arq2("FROTA.TXT", ios::app);
    if(!arq or !arq2)
    {
        cout<<"Arquivo nao foi aberto"<<endl;
        system("pause");
        return;
    }
    cout<<"Informe a placa do veiculo que deseja excluir: ";
    getline(cin,y.placa);
    while(getline(arq, linha))
    {
        sn = ' ';
        lido = linha.substr(0,7);
        y.marca = linha.substr(8,10);
        y.modelo = linha.substr(19,10);
        y.categoria = linha.substr(30,1);
        y.situ = linha.substr(32,1);
        y.cod = stoi(linha.substr(34,3));
        y.qtd = stoi(linha.substr(38,4));
        for(i=0; i<7; i++)
        {
            if(lido[i]!=' ') placa = placa + lido[i];
        }
        if(y.placa == placa)
        {
            achou = true;
            cout<<"Carro: "<<y.marca<<" "<<y.modelo<<" Placa: "<<y.placa<<endl;
            cout<<"Confirmar exclusao?"<<endl;
            sn = simnao();
            if(sn == 'S')
            {
                arq2<<setw(7)<<"-1"<<" "<<setw(10)<<y.marca<<" "<<setw(10)<<y.modelo<<" "<<setw(1)<<y.categoria<<" "<<setw(1)<<y.situ<<" "<<setw(3)<<y.cod<<" "<<setw(4)<<y.qtd<<" "<<endl;
            }
            else
            {
                cout<<"Exclusao cancelada!"<<endl;
                arq.close();
                arq2.close();
                remove("FROTA.TXT");
                rename("ANTIGOC.TXT", "FROTA.TXT");
                system("pause");
                return;
            }
        }
        else
        {
            arq2<<setw(7)<<placa<<" "<<setw(10)<<y.marca<<" "<<setw(10)<<y.modelo<<" "<<setw(1)<<y.categoria<<" "<<setw(1)<<y.situ<<" "<<setw(3)<<y.cod<<" "<<setw(4)<<y.qtd<<" "<<endl;
        }
        placa = "";
    }
    if(achou == true)
    {
        arq.close();
        arq2.close();
        remove("ANTIGOC.TXT");
        tiralista(y);
        system("pause");
    }
    else
    {
        cout<<"Veiculo não encontrado!"<<endl;
        arq.close();
        arq2.close();
        remove("FROTA.TXT");
        rename("ANTIGOC.TXT", "FROTA.TXT");
        system("pause");
    }
}


DMA dataentrega(int dias, DMA data)
{
    int dia, mes = data.mes, ano = data.ano;
    DMA datanova;
    dia = dias + data.dia;
    if(dia > 30)
    {
        dia -= 30;
        mes++;
        if(mes > 12)
        {
            mes -= 12;
            ano++;
        }
    }
    datanova.dia = dia;
    datanova.mes = mes;
    datanova.ano = ano;
    return datanova;
}

void alugaV(Pessoa x, Carro y, Locacao z, DMA data)
{
    string cpf="", placa="", linha="",linhaC="", cat="", lido="";
    int dias,i;
    bool mostrou = false, achou = false, achouC = false;
    rename("FROTA.TXT", "ANTIGOC.TXT");
    ifstream arqC("CLIENTES.TXT");
    ifstream arqV("ANTIGOC.TXT");
    ifstream arqVE("ANTIGOC.TXT");
    ofstream arqVEI("FROTA.TXT");
    ofstream arqL("LOCACAO.TXT", ios::app);
    if(!arqC or !arqV or !arqL or !arqVE or !arqVEI)
    {
        cout<<"Arquivo nao foi aberto"<<endl;
        arqC.close();
        arqV.close();
        arqVE.close();
        arqVEI.close();
        arqL.close();
        remove("FROTA.TXT");
        rename("ANTIGOC.TXT", "FROTA.TXT");
        system("pause");
        return;
    }
    cout<<"Informe o CPF do cliente: ";
    getline(cin,cpf);
    while(getline(arqC,linha))
    {
        x.nome = linha.substr(0,10);
        x.cpf = linha.substr(11,11);
        x.telefone = linha.substr(23,11);
        if(cpf == x.cpf)
        {
            achouC = true;
            do
            {
                cout<<"Informe a categoria desejada (1 - Basico / 2 - Intermediario / 3 - Super): ";
                getline(cin, cat);
            }
            while(cat != "1" and cat != "2" and cat != "3");
            while(getline(arqV,linhaC))
            {
                if(linhaC.substr(32,1) == "D" and linhaC.substr(30,1) == cat)
                {
                    cout<<linhaC<<endl;
                    mostrou = true;
                }
            }
            if(mostrou == false)
            {
                cout<<"Nenhum Carro da categoria disponivel!"<<endl;
                arqC.close();
                arqV.close();
                arqVE.close();
                arqVEI.close();
                arqL.close();
                remove("FROTA.TXT");
                rename("ANTIGOC.TXT", "FROTA.TXT");
                system("pause");
                return;
            }
            cout<<"Informe a placa do carro que voce quer alugar: ";
            getline(cin,y.placa);
            while(getline(arqVE,linhaC))
            {
                lido = linhaC.substr(0,7);
                y.marca = linhaC.substr(8,10);
                y.modelo = linhaC.substr(19,10);
                y.categoria = linhaC.substr(30,1);
                y.situ = linhaC.substr(32,1);
                y.cod = stoi(linhaC.substr(34,3));
                y.qtd = stoi(linhaC.substr(38,4));
                for(i=0; i<7; i++)
                {
                    if(lido[i]!=' ') placa = placa + lido[i];
                }
                if(y.placa == placa)
                {
                    achou = true;
                    z.cod = y.cod;
                    z.categoria = y.categoria;
                    z.cpf = x.cpf;
                    z.data = data;
                    do
                    {
                        cout<<"Quantos dias voce vai alugar? ";
                        cin>>dias;
                    }
                    while(dias <= 0);
                    if(z.categoria == "1") z.valor = 20.00 * dias;
                    if(z.categoria == "2") z.valor = 50.00 * dias;
                    if(z.categoria == "3") z.valor = 100.00 * dias;
                    z.dataE = dataentrega(dias, data);
                    arqL<<setw(3)<<z.cod<<" "<<setw(11)<<z.cpf<<" "<<setw(1)<<z.categoria<<" "<<setw(2)<<z.data.dia<<setw(2)<<z.data.mes<<setw(4)<<z.data.ano;
                    arqL<<" "<<setw(2)<<z.dataE.dia<<setw(2)<<z.dataE.mes<<setw(4)<<z.dataE.ano<<" "<<setw(6)<<z.valor<<endl;
                    y.qtd++;
                    y.situ = "L";
                }
                arqVEI<<setw(7)<<placa<<" "<<setw(10)<<y.marca<<" "<<setw(10)<<y.modelo<<" "<<setw(1)<<y.categoria<<" "<<setw(1)<<y.situ<<" "<<setw(3)<<y.cod<<" "<<setw(4)<<y.qtd<<" "<<endl;
                placa = "";
            }
            if(achou != true)
            {
                cout<<"Placa nao encontrada"<<endl;
                arqC.close();
                arqV.close();
                arqVE.close();
                arqL.close();
                system("pause");
                remove("FROTA.TXT");
                rename("ANTIGOC.TXT", "FROTA.TXT");
                return;
            }
        }
    }
    if(achouC != true){
        cout<<"CPF nao encontrado!"<<endl;
        system("pause");
        arqC.close();
        arqV.close();
        arqVE.close();
        arqVEI.close();
        arqL.close();
        remove("FROTA.TXT");
        rename("ANTIGOC.TXT", "FROTA.TXT");
        return;
    }
    arqC.close();
    arqV.close();
    arqVE.close();
    arqVEI.close();
    arqL.close();
    remove("ANTIGOC.TXT");
}

float calculaMulta(float valor, DMA dataE, DMA data)
{
    int dia;
    float multa, multaAux;
    if(dataE.ano == data.ano and dataE.mes == data.mes and dataE.dia == data.dia) return 0.0;
    if(data.dia < dataE.dia and data.mes <= dataE.dia) return 0.0;
    if(dataE.mes < data.mes)
    {
        if(dataE.dia < data.dia){
            dia = data.dia - dataE.dia;
        }else{
            dia = (data.dia + 30) - dataE.dia;
        }
        multa = valor * 0.2;
        for(int i=0; i<dia;i++){
            multaAux = valor*0.01;
        }
        return multa + multaAux;
    }
    if(dataE.mes == data.mes){
        if(data.dia > dataE.dia){
            dia = data.dia - dataE.dia;
            multa = valor * 0.2;
            for(int i=0; i<dia;i++){
                multaAux = valor*0.01;
            }
                return multa + multaAux;
            }else return 0.0;
    }
    return 0.0;
}

void devolveV(Carro y, Locacao z, DMA data)
{
    string cpf="", linha, linhaC, lido;
    int op, i;
    float multa;
    bool achou = false, achouC = false;
    rename("LOCACAO.TXT", "ANTIGOL.TXT");
    rename("FROTA.TXT", "ANTIGOC.TXT");
    ifstream arq("ANTIGOL.TXT");
    ifstream arqV("ANTIGOC.TXT");
    ofstream arqL("LOCACAO.TXT");
    ofstream arqVE("FROTA.TXT");
    cout<<"Informe o cpf de quem alugou: ";
    getline(cin,z.cpf);
    while(getline(arq,linha))
    {
        z.cod = stoi(linha.substr(0,3));
        lido = linha.substr(4,11);
        z.categoria = linha.substr(16,1);
        z.data.dia = stoi(linha.substr(18,2));
        z.data.mes = stoi(linha.substr(20,2)) ;
        z.data.ano = stoi(linha.substr(22,4));
        z.dataE.dia = stoi(linha.substr(27,2));
        z.dataE.mes = stoi(linha.substr(29,2)) ;
        z.dataE.ano = stoi(linha.substr(31,4));
        z.valor = stof(linha.substr(36,6));
        for(i=0; i<11; i++)
        {
            if(lido[i]!=' ') cpf = cpf + lido[i];
        }
        if(z.cpf == cpf and z.cod != -1)
        {
            achou = true;
            multa = calculaMulta(z.valor,z.dataE,data);
            cout<<"Codigo: "<<z.cod<<" CPF: "<<z.cpf<<" Valor: R$"<<z.valor<<" Multa: R$"<<multa<<endl;
            do
            {
                cout<<"Quanto o cliente pagou? (-1 para cancelar):";
                cin>>z.pago;
                if(z.pago == -1)
                {
                    cout<<"Devolucao cancelada!"<<endl;
                    system("pause");
                    arq.close();
                    arqV.close();
                    arqL.close();
                    arqVE.close();
                    remove("FROTA.TXT");
                    remove("LOCACAO.TXT");
                    rename("ANTIGOC.TXT", "FROTA.TXT");
                    rename("ANTIGOL.TXT", "LOCACAO.TXT");
                    return;
                }
            }
            while(z.pago < (z.valor + multa));
            if(z.pago > (z.valor + multa))
            {
                cout<<"Troco: "<<z.pago - (z.valor + multa)<<endl;
            }
            while(getline(arqV,linhaC))
            {
                y.placa = linhaC.substr(0,7);
                y.marca = linhaC.substr(8,10);
                y.modelo = linhaC.substr(19,10);
                y.categoria = linhaC.substr(30,1);
                y.situ = linhaC.substr(32,1);
                y.cod = stoi(linhaC.substr(34,3));
                y.qtd = stoi(linhaC.substr(38,4));
                if(y.cod == z.cod)
                {
                    achouC = true;
                    y.situ = "D";
                    z.cod = -1;
                }
                arqVE<<setw(7)<<y.placa<<" "<<setw(10)<<y.marca<<" "<<setw(10)<<y.modelo<<" "<<setw(1)<<y.categoria<<" "<<setw(1)<<y.situ<<" "<<setw(3)<<y.cod<<" "<<setw(4)<<y.qtd<<" "<<endl;
            }
            if(achouC != true)
            {
                cout<<"Carro nao esta mais no sistema (1 - cancelar devolucao / 2 - continuar): ";
                cin>>op;
                if(op == 1)
                {
                    cout<<"Devolucao cancelada"<<endl;
                    system("pause");
                    arq.close();
                    arqL.close();
                    arqV.close();
                    arqVE.close();
                    remove("FROTA.TXT");
                    remove("LOCACAO.TXT");
                    rename("ANTIGOC.TXT", "FROTA.TXT");
                    rename("ANTIGOL.TXT", "LOCACAO.TXT");
                }
            }
        }
        arqL<<setw(3)<<z.cod<<" "<<setw(11)<<z.cpf<<" "<<setw(1)<<z.categoria<<" "<<setw(2)<<z.data.dia<<setw(2)<<z.data.mes<<setw(4)<<z.data.ano;
        arqL<<" "<<setw(2)<<z.dataE.dia<<setw(2)<<z.dataE.mes<<setw(4)<<z.dataE.ano<<" "<<setw(6)<<z.valor<<" "<<setw(6)<<z.pago<<endl;
        cpf="";
    }
    if(achou != true)
    {
        cout<<"CPF não encontrado!"<<endl;
        system("pause");
        arq.close();
        arqL.close();
        arqV.close();
        arqVE.close();
        remove("FROTA.TXT");
        remove("LOCACAO.TXT");
        rename("ANTIGOC.TXT", "FROTA.TXT");
        rename("ANTIGOL.TXT", "LOCACAO.TXT");
    }
    cout<<"Devolucao concluida!"<<endl;
    system("pause");
    arq.close();
    arqL.close();
    arqV.close();
    arqVE.close();
    remove("ANTIGOC.TXT");
    remove("ANTIGOL.TXT");
}

void relatorioA(Carro y)
{
    string linha;
    ifstream arq("FROTA.TXT");
    cout<<"Codigo |    Marca   |   Modelo   |  Placa  | Categoria | Situacao | Locacoes"<<endl;
    while(getline(arq,linha))
    {
        y.placa = linha.substr(0,7);
        y.marca = linha.substr(8,10);
        y.modelo = linha.substr(19,10);
        y.categoria = linha.substr(30,1);
        y.situ = linha.substr(32,1);
        y.cod = stoi(linha.substr(34,3));
        y.qtd = stoi(linha.substr(38,4));
        cout<<setw(6)<<y.cod<<" | "<<setw(9)<<y.marca<<" | "<<setw(8)<<y.modelo<<" | "<<setw(7)<<y.placa;
        cout<<" | "<<setw(9)<<y.categoria<<" | "<<setw(8)<<y.situ<<" | "<<setw(8)<<y.qtd<<endl;
    }
    arq.close();
    system("pause");
}

void relatorioB(Pessoa x)
{
    string linha;
    ifstream arq("CLIENTES.TXT");
    cout<<"    Nome   |     CPF     |   Telefone"<<endl;
    while(getline(arq,linha))
    {
        x.nome = linha.substr(0,10);
        x.cpf = linha.substr(11,11);
        x.telefone = linha.substr(22,11);
        cout<<setw(10)<<x.nome<<" | "<<setw(11)<<x.cpf<<" | "<<setw(11)<<x.telefone<<endl;
    }
    arq.close();
    system("pause");
}

void relatorioC(Locacao z)
{
    string linha;
    ifstream arq("LOCACAO.TXT");
    cout<<"Codigo |     CPF     |  Data de Locacao | Data de Entrega | Valor a ser pago"<<endl;
    while(getline(arq,linha))
    {
        z.cod = stoi(linha.substr(0,3));
        z.cpf = linha.substr(4,11);
        z.categoria = linha.substr(16,1);
        z.data.dia = stoi(linha.substr(18,2));
        z.data.mes = stoi(linha.substr(20,2)) ;
        z.data.ano = stoi(linha.substr(22,4));
        z.dataE.dia = stoi(linha.substr(27,2));
        z.dataE.mes = stoi(linha.substr(29,2)) ;
        z.dataE.ano = stoi(linha.substr(31,4));
        z.valor = stof(linha.substr(36,6));
        if(z.cod != -1)
        {
            cout<<setw(6)<<z.cod<<" | "<<setw(11)<<z.cpf<<" | "<<setw(9)<<z.data.dia<<"/"<<z.data.mes<<"/"<<z.data.ano<<" | "<<setw(9)<<z.dataE.dia<<"/"<<z.dataE.mes<<"/"<<z.dataE.ano<<"  | ";
            cout<<setw(16)<<z.valor<<endl;
        }
    }
    arq.close();
    system("pause");
}

void relatorioD (Locacao z, DMA data)
{
    string linha;
    int n, i;
    ifstream arq("LOCACAO.TXT");
    cout<<"Codigo |     CPF     | Data de Locacao | Data de Entrega | Valor a ser pago"<<endl;
    while(getline(arq,linha))
    {
        z.cod = stoi(linha.substr(0,3));
        z.cpf = linha.substr(4,11);
        z.categoria = linha.substr(16,1);
        z.data.dia = stoi(linha.substr(18,2));
        z.data.mes = stoi(linha.substr(20,2)) ;
        z.data.ano = stoi(linha.substr(22,4));
        z.dataE.dia = stoi(linha.substr(27,2));
        z.dataE.mes = stoi(linha.substr(29,2)) ;
        z.dataE.ano = stoi(linha.substr(31,4));
        z.valor = stof(linha.substr(36,6));
        if(z.dataE.ano == data.ano and z.dataE.mes == data.mes and z.dataE.dia == data.dia)
        {
            cout<<setw(6)<<z.cod<<" | "<<setw(11)<<z.cpf<<" | "<<setw(9)<<z.data.dia<<"/"<<z.data.mes<<"/"<<z.data.ano<<" | "<<setw(9)<<z.dataE.dia<<"/"<<z.dataE.mes<<"/"<<z.dataE.ano<<" | ";
            cout<<setw(16)<<z.valor<<endl;
        }
    }
    arq.close();
    system("pause");
}

int main()
{
    srand(time(NULL));
    DMA data;
    data.dia = 03;
    data.mes = 07;
    data.ano = 2022;
    ofstream arq("CLIENTES.TXT", ios::app);
    ofstream arq2("FROTA.TXT",ios::app);
    ofstream arq3("LOCACAO.TXT", ios::app);
    arq.close();
    arq2.close();
    arq3.close();
    int op;
    Pessoa x;
    Carro y;
    Locacao z;
    do
    {
        system("cls");
        cout<<"Data: "<<data.dia<<"/"<<data.mes<<"/"<<data.ano<<endl;
        cout<<"Oque voce deseja fazer?"<<endl;
        cout<<"1 - Incluir Veiculo"<<endl;
        cout<<"2 - Incluir Cliente"<<endl;
        cout<<"3 - Excluir Veiculo"<<endl;
        cout<<"4 - Alugar Veiculo"<<endl;
        cout<<"5 - Devolver Veiculo"<<endl;
        cout<<"6 - Veiculos da Frota"<<endl;
        cout<<"7 - Lista de Clientes"<<endl;
        cout<<"8 - Locacoes Ativas"<<endl;
        cout<<"9 - Veiculos a serem devolvidos hoje"<<endl;
        cout<<"0 - Sair"<<endl;
        cin>>op;
        cin.ignore();
        switch(op)
        {
        case 1:
            system("cls");
            incluiV(y);
            break;
        case 2:
            system("cls");
            incluiC(x);
            break;
        case 3:
            system("cls");
            excluiV(y);
            break;
        case 4:
            system("cls");
            alugaV(x,y,z,data);
            break;
        case 5:
            system("cls");
            devolveV(y,z,data);
            break;
        case 6:
            system("cls");
            relatorioA(y);
            break;
        case 7:
            system("cls");
            relatorioB(x);
            break;
        case 8:
            system("cls");
            relatorioC(z);
            break;
        case 9:
            system("cls");
            relatorioD(z,data);
            break;
        }
    }
    while(op != 0);
    return 0;
}
